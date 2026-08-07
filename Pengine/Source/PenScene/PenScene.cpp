#include "PenScene/PenScene.h"

#include "PenStructsAndEnum/PenResourcesType.h"

#include "PenCore/PenCore.h"				//PenCore
#include "PenOctopus/PenOctopus.h"
#include "PenColor/PenColor.h"				//PenColor
#include "PenObject/PenObjectManager.h"		//PenObjectManager
#include "PenLogManager/PenLogManager.h"
#include "PenSerializer/PenSerializer.h"
#include "PenProperty/PenPropertyManager.h"

#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenLight/PenLight.h"
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenTransform/PenTransform.h"


using namespace Pengine;

PenScene::PenScene()
{
	this->m_backgroundColor = PenColor::Green;
	this->m_scenePath = "Dummy Scene";
}

PenScene::PenScene(const std::string& path)
{
	this->m_backgroundColor = PenColor::Green;
	this->m_scenePath = path;
}

bool PenScene::serializeScene()
{
	std::ofstream outfile(this->m_scenePath, std::ios::binary);
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	serializer->write(outfile, (int)Resources::PenResourceType::E_SCENE);

	uint32_t objCount = static_cast<uint32_t>(this->m_objects.size());
	serializer->write(outfile, PenMath::Vector3f{this->m_backgroundColor.r,  this->m_backgroundColor.g, this->m_backgroundColor.b});
	serializer->write(outfile, objCount);

	for (Pengine::PenObjectId objId : this->m_objects)
	{
		if(!this->serializeObject(outfile, objId))
		{
			std::string path = this->m_scenePath;
			PenCore::LogManager()->LogWarning("Failed to save scene : " + path, __FILE__, __LINE__);
			return false;
		}
	}

	PenCore::LogManager()->Log("Succesfully saved scene : " + this->m_scenePath, __FILE__, __LINE__);

	return true;
}

void PenScene::loadScene(const std::string& filePath)
{
	this->m_scenePath = filePath;

	PenCore::LogManager()->Log("Loading scene : " + filePath, __FILE__, __LINE__);

	std::ifstream infile(filePath, std::ios::binary);
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	int type = 0;
	serializer->read(infile, type);

	PenMath::Vector3f color = PenMath::Vector3f::Zero();
	serializer->read(infile, color);

	this->m_backgroundColor = PenColor(color.x, color.y, color.z, 1.f);

	uint32_t objectSize = 0;
	serializer->read(infile, objectSize);

	for(int i = 0; i < objectSize; ++i)
	{
		loadObject(infile);
	}
}

bool PenScene::serializeObject(std::ostream& out, PenObjectId id)
{
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	std::string name = Pengine::PenCore::PenOctopus()->getNameById(id);
	serializer->write(out, name);

	std::vector<Pengine::IPenProperty*> properties = Pengine::PenCore::PenOctopus()->PropertyManager()->getProperties(id);

	int nbComponent = 0;

	for(IPenProperty* prop : properties)
	{
		if (prop->getType() == Pengine::PenPropertyType::E_COMPONENT)
			nbComponent++;
	}

	serializer->write(out, nbComponent);


	for (IPenProperty* prop : properties)
	{
		if (prop->getType() == Pengine::PenPropertyType::E_COMPONENT)
		{
			Pengine::Components::PenComponentBase* comp = static_cast<Pengine::Components::PenComponentBase*>(prop->getData());
			if (!comp->serialize(out))
				return false;
		}
	}

	return true;
}

void PenScene::loadObject(std::ifstream& infile)
{
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	std::string name = "";
	serializer->read(infile, name);

	PenObjectId id = PenCore::PenOctopus()->createPenObject(name);

	this->addObject(id);

	int nbComponent = 0;
	serializer->read(infile, nbComponent);


	for(int i = 0; i < nbComponent; ++i)
	{
		loadComponent(infile, id);
	}
}

void PenScene::loadComponent(std::ifstream& infile, PenObjectId id)
{
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();
	int compType = 0;
	serializer->read(infile, compType);

	switch (compType)
	{
	case Components::PenComponentTypeEnum::E_CAMERA:
	{
		Components::PenCamera camComp;
		camComp.load(infile);
		PenCore::PenOctopus()->addComponent(id, camComp);
		break;
	}

	case Components::PenComponentTypeEnum::E_LIGHT:
	{
		Components::PenLight lightComp;
		lightComp.load(infile);
		PenCore::PenOctopus()->addComponent(id, lightComp);
		break;
	}

	case Components::PenComponentTypeEnum::E_RENDERER:
	{
		Components::PenRenderer renderComp;
		renderComp.load(infile);
		PenCore::PenOctopus()->addComponent(id, renderComp);
		break;
	}	
	case Components::PenComponentTypeEnum::E_TRANSFORM:
	{
		Components::PenTransform transComp;
		Components::PenTransform& added = PenCore::PenOctopus()->addComponent(id, transComp);
		added.load(infile);
		break;
	}
	default:
		break;
	}
}

void PenScene::changeBackgroundColor(const PenColor& col)
{
	this->m_backgroundColor = col;
}

const PenColor& Pengine::PenScene::getBackgroundColor() const
{
	return this->m_backgroundColor;
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

const std::string& PenScene::getSceneName()
{
	return this->m_scenePath;
}



#pragma endregion	