#include "PenScene/PenScene.h"

#include "PenColor/PenColor.h"				//PenColor
#include "PenObject/PenObjectManager.h"		//PenObjectManager
#include "PenCore/PenCore.h"				//PenCore

using namespace Pengine;

PenScene::PenScene()
{
	this->m_backgroundColor = new PenColor();
	*this->m_backgroundColor = PenColor{.1f, .1f, .1f, 1.f};
}

Pengine::PenScene::~PenScene()
{
	if(this->m_backgroundColor)
	{
		delete this->m_backgroundColor;
		this->m_backgroundColor = nullptr;
	}
}

void PenScene::changeBackgroundColor(const PenColor& col)
{
	*this->m_backgroundColor = col;
}

const PenColor& Pengine::PenScene::getBackgroundColor() const
{
	return *this->m_backgroundColor;
}

void PenScene::removeObject(const PengineIds obj)
{
	this->m_objects.erase(obj);
}

void PenScene::addObject(const PengineIds obj)
{
	this->m_objects.insert(obj);
}

bool PenScene::isObjectInScene(const PengineIds obj)
{
	return this->m_objects.count(obj);
}



#pragma endregion	