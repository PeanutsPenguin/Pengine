#include "PenObject/PenObject.h"

using namespace Pengine;


#pragma region Fucntions
const std::vector<PenComponentsId>& PenObject::getComponents() const
{
	return this->m_components;
}

const PenObjectId PenObject::getId() const
{
	return this->m_id;
}
#pragma endregion
