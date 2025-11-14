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


#pragma endregion	