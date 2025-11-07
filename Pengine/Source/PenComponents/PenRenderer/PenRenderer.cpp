#include "PenComponents/PenRenderer/PenRenderer.h"

using namespace Pengine::Components;


void PenRenderer::setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog)
{
	this->m_shader = prog;
}

void PenRenderer::setModel(std::shared_ptr<Pengine::Resources::PenModel> model)
{
	this->m_model = model;
}

void PenRenderer::render()
{
	m_model->render(m_shader);
}
