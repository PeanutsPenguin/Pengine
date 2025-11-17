#include "PenComponents/PenRenderer/PenRenderer.h"

using namespace Pengine::Components;

PenRenderer::~PenRenderer()
{
	if (!this->m_model)
	{
		this->m_model.reset();
		this->m_model = nullptr;
	}

	if(!this->m_shader)
	{
		this->m_shader.reset();
		this->m_shader = nullptr;
	}
}

//
//void PenRenderer::setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog)
//{
//	this->m_shader = prog;
//}
//
//void PenRenderer::setModel(std::shared_ptr<Pengine::Resources::PenModel> model)
//{
//	this->m_model = model;
//}
//
//void PenRenderer::render()
//{
//	m_model->render(m_shader);
//}
