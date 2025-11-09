#include "PenObject/PenObject.h"

#include "PenCore/PenCore.h"
#include "PenComponents/PenComponentsManager.h"
using namespace Pengine;


#pragma region Fucntions
const std::vector<PenComponentsId>& PenObject::getComponents() const
{
	return this->m_components;
}

void PenObject::render()
{
	for(int i = 0; i < m_components.size(); ++i)
	{
		Components::PenComponentsBase* ptr = PenCore::getInstance()->getComponentsManager()->getComponentById(m_components[i]);
		if(ptr)
			ptr->render();
	}
}

const PenObjectId PenObject::getId() const
{
	return this->m_id;
}
#pragma endregion
