#include "PenComponents/PenRenderer/PenRenderer.h"

using namespace Pengine::Components;

PenRenderer::PenRenderer()
{
	this->SetState(PenComponentState::ENABLE, true);
}

void PenRenderer::setModel(std::shared_ptr<Pengine::Resources::PenModel> model)
{
	this->m_model = model;
}

void PenRenderer::setMaterial(std::shared_ptr<Pengine::Resources::PenMaterial> mat)
{
	if(mat)
		this->m_material = mat;
	//TODO else : set default mat
}

void PenRenderer::render()
{
	m_model->render();
}

std::shared_ptr<Pengine::Resources::PenMaterial> PenRenderer::getMaterial()
{
	return this->m_material;
}
