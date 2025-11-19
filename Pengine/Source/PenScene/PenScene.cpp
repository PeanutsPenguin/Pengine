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
void PenScene::changeBackgroundColor(const PenColor& col)
{
	*this->m_backgroundColor = col;
}

const PenColor& Pengine::PenScene::getBackgroundColor() const
{
	return *this->m_backgroundColor;
}

void PenScene::removeObject(const PenObjectId obj)
{
	this->m_objects.erase(obj);
}

void PenScene::addObject(const PenObjectId obj)
{
	this->m_objects.insert(obj);
}

bool PenScene::isObjectInScene(const PenObjectId obj)
{
	return this->m_objects.count(obj);
}



#pragma endregion	