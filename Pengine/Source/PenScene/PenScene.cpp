#include "PenScene/PenScene.h"

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

bool PenScene::serializeScene(const char* filePath)
{
	std::ofstream outfile(filePath, std::ios::binary);
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	uint32_t objCount = static_cast<uint32_t>(this->m_objects.size());
	serializer->write(outfile, PenMath::Vector3f{this->m_backgroundColor->r,  this->m_backgroundColor->g, this->m_backgroundColor->b});
	serializer->write(outfile, objCount);

	for (Pengine::PenObjectId objId : this->m_objects)
	{
		if(!this->serializeObject(outfile, objId))
		{
			std::string path = filePath;
			PenCore::LogManager()->LogWarning("Failed to save scene : " + path, __FILE__, __LINE__);
			return false;
		}
	}

	return true;
}

void PenScene::loadScene(const char* filePath)
{
	std::ifstream infile(filePath, std::ios::binary);
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	PenMath::Vector3f color = PenMath::Vector3f::Zero();
	serializer->read(infile, color);

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