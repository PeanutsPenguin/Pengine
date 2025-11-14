#include "PenObject/PenObject.h"

#include "PenCore/PenCore.h"
#include "PenComponents/PenComponentsManager.h"

using namespace Pengine;

const std::vector<PenComponentsId>& PenObject::getComponents() const
{
	return this->m_components;
}

void PenObject::render()
{
	
}

const PenObjectId PenObject::getId() const
{
	return this->m_id;
}
