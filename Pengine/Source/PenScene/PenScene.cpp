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
Pengine::PenScene::~PenScene()
{
	if(this->m_backgroundColor)
	{
		delete this->m_backgroundColor;
		this->m_backgroundColor = nullptr;
	}
}
#pragma endregion

#pragma region Functions

void PenScene::render()
{
	clearBackground();

	for (int i = 0; i < m_objects.size(); ++i)
		PenCore::ObjectManager()->getObjectById(m_objects[i]).render();
}

void PenScene::clearBackground()
{
	glClearColor(m_backgroundColor->r, m_backgroundColor->g, m_backgroundColor->b, m_backgroundColor->a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PenScene::changeBackgroundColor(const PenColor& col)
{
	*this->m_backgroundColor = col;
}

bool PenScene::addObjectById(const PenObjectId id)
{
	if(PenCore::ObjectManager()->isObjectExisting(id))
	{
		this->m_objects.push_back(id);
		return true;
	}

	return false;
}

PenObjectId PenScene::createObject()
{
	PenObject& obj = PenCore::ObjectManager()->createPenObject();

	this->m_objects.push_back(obj.getId());

	return obj.getId();
}

#pragma endregion	