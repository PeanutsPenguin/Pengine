#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenProperty/PenPropertyManager.h"

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
	else 
		this->m_material = Resources::PenMaterial::defaultMaterial();
}

void PenRenderer::render()
{
	m_model->render();
}

void PenRenderer::registerProperty(PenPropertyManager* manager)
{
	PenObjectId id = this->getPenObjectId();
	manager->addProperty(id, "Renderer Component", E_COMPONENT, this);
	manager->addProperty(id, "Model", E_MODEL, this->m_model.get());
	manager->addProperty(id, "Material", E_MATERIAL, this->m_material.get());
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
