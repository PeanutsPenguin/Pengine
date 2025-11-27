#include "PenComponents/PenRenderer/PenRenderer.h"

#include <iostream>

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
	if(!this->m_material)
	{
		std::cout << __FUNCTION__ "\t Material of object : " << this->getPenObjectId() << " has not been found, replace it with default material\n";
		this->setMaterial(Resources::PenMaterial::defaultMaterial());
	}

	return this->m_material;
}
