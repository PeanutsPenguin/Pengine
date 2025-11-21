#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

#include "PenComponents/PenTransform/PenTransform.h"	//Transform Components
#include "PenComponents/PenCamera/PenCamera.h"			//Camera Components
#include "PenCore/PenCore.h"							//Core
#include "PenOctopus/PenOctopus.h"						//Octopus

//Std
#include <iostream>

using namespace Pengine::System;

void PenTransformSystem::update(double dt)
{
	std::queue<PenObjectId> process;
	for (const auto& root : this->m_PenObject) {
		process.push(root);
	}

	while (!process.empty()) {
		PenObjectId current = process.front();
		process.pop();

		Components::PenTransform& transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(current);
		PenObjectId	parent = transform.getParent();


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
				result = ptransform.getGlobalTransform().combine(transform.getLocalTransform());
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

void PenTransformSystem::addChild(const PenObjectId obj, const PenObjectId parent)
{
	this->m_children[parent].insert(obj);
}

void PenTransformSystem::reparentChild(const PenObjectId obj, const PenObjectId oldParent, const PenObjectId newParent, bool keepPosition)
{
	if(oldParent == newParent)
	{
		std::cout << __FUNCTION__ "Same parent\n";
		return;
	}

	//If old parent doesn't exist
	if (this->m_children[oldParent].find(obj) == this->m_children[oldParent].end() || oldParent == g_PenObjectInvalidId)
	{
		this->removeRoot(obj);
		std::cout << __FUNCTION__ "Invalid old parent, deleting objects\n";
		return;
	}
	else
		m_children[oldParent].erase(obj);

	//If new parent exist
	if (newParent != g_PenObjectInvalidId)
	{
		//If new Parent is in the root array
		if(this->m_PenObject.count(newParent))
		{
			m_children[newParent].insert(obj);
		}
		else
		{
			m_PenObject.insert(newParent);
			this->m_children[newParent].insert(obj);
		}
	}
	else 
		m_PenObject.insert(obj);
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
		{
			m_children[parent].insert(newObj);
		}
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
