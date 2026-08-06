#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

#include "PenComponents/PenTransform/PenTransform.h"	//Transform Components
#include "PenComponents/PenCamera/PenCamera.h"			//Camera Components
#include "PenCore/PenCore.h"							//Core
#include "PenOctopus/PenOctopus.h"						//Octopus
#include "PenLogManager/PenLogManager.h"

//Std
#include <iostream>

using namespace Pengine::System;

void PenTransformSystem::update(double dt)
{
	std::queue<PenObjectId> process;
	for (const auto& root : this->m_PenObject)
		process.push(root);

	while (!process.empty()) 
	{
		PenObjectId current = process.front();
		process.pop();

		Components::PenTransform&	transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(current);
		PenObjectId					parent = transform.getParent();

		if (parent == g_PenObjectInvalidId)
			transform.setLocalTransform(transform.getGlobalTransform());	  // roots global and local should be equal

		// check if component is dirty with some flags
		if (transform.IsState(Components::PenComponentState::DIRTY))
		{
			if (PenCore::PenOctopus()->containsComponent<Components::PenCamera>(current))
				PenCore::PenOctopus()->getComponent<Components::PenCamera>(current).SetState(Components::PenComponentState::DIRTY);

			PenMath::Transform result = transform.getLocalTransform();

			if (parent != g_PenObjectInvalidId) 
			{
				Components::PenTransform& ptransform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(parent);
				result = transform.getLocalTransform().combine(ptransform.getGlobalTransform());
			}

			transform.setGlobalTransform(result);
		}

		if (this->m_children.contains(current)) 
		{
			for (auto child : this->m_children[current]) 
			{
				if (transform.IsState(Components::PenComponentState::DIRTY)) 
					PenCore::PenOctopus()->getComponent<Components::PenTransform>(child).SetState(Components::PenComponentState::DIRTY);

				process.push(child);
			}
		}

		transform.SetState(Components::PenComponentState::DIRTY, false);
	}
}

void PenTransformSystem::addRoot(const PenObjectId obj)
{
	this->m_PenObject.insert(obj);
}

void PenTransformSystem::removeRoot(const PenObjectId obj)
{
	if(this->m_children.find(obj) != this->m_children.end())
	{
		std::set<PenObjectId> children = this->m_children[obj];

		for (PenObjectId child : children)
			this->m_PenObject.insert(child);

		this->m_children.erase(obj);
	}

	this->m_PenObject.erase(obj);
}

void PenTransformSystem::reparent(const PenObjectId obj, const PenObjectId oldParent, const PenObjectId newParent, bool keepPosition)
{
	if(oldParent == newParent)
	{
		PenCore::LogManager()->LogWarning("Object already has the same parent", __FILE__, __LINE__);
		return;
	}

	//If old parent doesn't exist
	if (this->m_children[oldParent].find(obj) == this->m_children[oldParent].end() || oldParent == g_PenObjectInvalidId)
		PenCore::LogManager()->LogWarning("No old Parent detected", __FILE__, __LINE__);
	else
	{
		m_children[oldParent].erase(obj);

		if (m_children[oldParent].size() == 0)
			m_children.erase(oldParent);
	}

	//If new parent exist
	if (newParent != g_PenObjectInvalidId)
	{
		//If new Parent is in the root array
		if(this->m_PenObject.count(newParent))
		{
			m_children[newParent].insert(obj);
			m_PenObject.erase(obj);
		}
		else
		{
			m_PenObject.insert(newParent);
			m_PenObject.erase(obj);
			this->m_children[newParent].insert(obj);
		}
	}
	else 
		m_PenObject.insert(obj);

	Components::PenTransform& transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(obj);
	transform.setParent(newParent);
}

void PenTransformSystem::onEntityInserted(const PenObjectId newObj)
{
	Components::PenTransform& transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(newObj);
	PenObjectId	parent = transform.getParent();

	//If Parent is invalid attach to root
	if (parent == g_PenObjectInvalidId) 
		this->m_PenObject.insert(newObj);
	else 
	{
		//If parent is in root array
		if (this->m_PenObject.count(parent))
			m_children[parent].insert(newObj);
		else
		{
			m_PenObject.insert(parent);
			this->m_children[parent].insert(newObj);
		}
	}
}

void PenTransformSystem::onEntityDestroyed(const PenObjectId obj)
{
	m_PenObject.erase(obj);

	Components::PenTransform& transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(obj);
	PenObjectId	parent = transform.getParent();

	if (parent == g_PenObjectInvalidId)
		this->removeRoot(obj);
	else
		this->m_children[parent].erase(obj);
}

bool PenTransformSystem::hasChild(Pengine::PenObjectId id)
{
	if (this->m_children.find(id) == this->m_children.end())
		return false;

	return true;
}

const std::set<Pengine::PenObjectId>& PenTransformSystem::getChilds(Pengine::PenObjectId id)
{
	if (this->m_children.find(id) == this->m_children.end())
		PenCore::LogManager()->LogError("Entity : " + std::to_string(id) + "has no childrens", __FILE__, __LINE__);

	return this->m_children[id];
}
