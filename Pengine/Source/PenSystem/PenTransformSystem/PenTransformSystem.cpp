#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

#include "PenComponents/PenTransform/PenTransform.h"	//Transform Components
#include "PenCore/PenCore.h"							//Core
#include "PenOctopus/PenOctopus.h"						//Octopus

//Std
#include <iostream>



using namespace Pengine::System;

void PenTransformSystem::update(double dt)
{

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
	if (this->m_children[oldParent].find(obj) == this->m_children[oldParent].end() || oldParent == PenObjectInvalidId)
	{
		this->removeRoot(obj);
		std::cout << __FUNCTION__ "Invalid old parent, deleting objects\n";
		return;
	}
	else
		m_children[oldParent].erase(obj);

	//If new parent exist
	if (newParent != PenObjectInvalidId)
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
	if (parent == PenObjectInvalidId) 
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

	if (parent == PenObjectInvalidId)
		this->removeRoot(obj);
	else
		this->m_children[parent].erase(obj);
}
