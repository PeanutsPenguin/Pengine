#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenProperty/PenPropertyManager.h"

#include "PenCore/PenCore.h"
#include "PenLogManager/PenLogManager.h"
#include "PenSerializer/PenSerializer.h"

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
	manager->addProperty(id, "Model", E_MODEL, &this->m_model);
	manager->addProperty(id, "Material", E_MATERIAL, &this->m_material);
}

bool PenRenderer::serialize(std::ostream& out)
{
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	if (!this->m_model->isLoaded() || !this->m_material->isLoaded())
		return false;

	serializer->write(out, (int)PenComponentTypeEnum::E_RENDERER);
	serializer->write<bool>(out, this->IsState(PenComponentState::ENABLE));
	serializer->write(out, this->m_model->getResourcePath());
	serializer->write(out, this->m_material->getResourcePath());

	return true;
}

void PenRenderer::load(std::ifstream& infile)
{
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	bool enabled = false;

	std::string modelPAth = "";
	std::string matPath = "";

	serializer->read<bool>(infile, enabled);
	serializer->read(infile, modelPAth);
	serializer->read(infile, matPath);

	this->m_model = PenCore::ResourcesManager()->loadResourceFromFile<Resources::PenModel>(modelPAth.c_str());
	this->m_material = PenCore::ResourcesManager()->loadResourceFromFile<Resources::PenMaterial>(matPath.c_str());

	if (!enabled)
		this->SetState(PenComponentState::ENABLE, false);

	this->SetState(PenComponentState::DIRTY);
}

std::shared_ptr<Pengine::Resources::PenMaterial> PenRenderer::getMaterial()
{
	if(!this->m_material)
	{
		PenCore::LogManager()->LogWarning("Material of object : " + std::to_string(this->getPenObjectId()) + " has not been found, replace it with default material", __FILE__, __LINE__);
		this->setMaterial(Resources::PenMaterial::defaultMaterial());
	}

	return this->m_material;
}
