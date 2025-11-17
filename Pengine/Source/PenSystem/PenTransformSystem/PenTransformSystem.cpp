#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

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
	}

	this->m_PenObject.erase(obj);
}

void PenTransformSystem::addChild(const PenObjectId obj, const PenObjectId parent)
{
	this->m_children[parent].insert(obj);
}

void PenTransformSystem::reparentChild(const PenObjectId obj, const PenObjectId oldParent, const PenObjectId newParent, bool keepPosition)
{
	if (oldParent == -1)
		m_PenObject.erase(obj);
	else if (m_children[oldParent].find(child) == m_children[oldParent].end()) {
		ERROR_LOG("Reparenting impossible, parent and child link not found");
		assert(false);
	}
	else
		m_children[oldParent].erase(child);

	if (newParent.GetId() != gobjects::InvalidId)
		m_children[newParent].insert(child);
	else
		m_rootEntities.insert(child);
}
