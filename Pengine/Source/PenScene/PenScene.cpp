#include "PenScene/PenScene.h"
#include "PenColor/PenColor.h"

#include "PenObject/PenObjectManager.h"
#include "PenCore/PenCore.h"

#include <glad/glad.h>

using namespace Pengine;

#pragma region Constructors and Destructor
PenScene::PenScene()
{
	this->m_backgroundColor = new PenColor();
	*this->m_backgroundColor = PenColor::Blue;
}
#pragma endregion

#pragma region Functions

void PenScene::render()
{
	clearBackground();
}

void PenScene::clearBackground()
{
	glClearColor(m_backgroundColor->r, m_backgroundColor->g, m_backgroundColor->b, m_backgroundColor->a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool PenScene::addObjectById(const PenObjectId id)
{
	if(PenCore::getInstance()->getObjectManager()->isObjectExisting(id))
	{
		this->m_objects.push_back(id);
		return true;
	}

	return false;
}

PenObjectId PenScene::createObject()
{
	PenObject& obj = PenCore::getInstance()->getObjectManager()->createPenObject();

	this->m_objects.push_back(obj.getId());

	return obj.getId();
}

#pragma endregion	