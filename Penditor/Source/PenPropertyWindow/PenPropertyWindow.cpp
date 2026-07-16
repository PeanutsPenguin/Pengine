#include "PenPropertyWindow/PenPropertyWindow.h"

#include "PenCore/PenCore.h"
#include "PenOctopus/PenOctopus.hpp"
#include "PenUIManager/PenUIManager.h"
#include "PenProperty/PenPropertyManager.h"
#include "PenResources/PenResourceManager.hpp"
#include "PenComponents/PenComponentBase.h"
#include "PenPropertyWindow/PenPropertySettings.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenResources/AllPenResources.h"

#include "PickingHandler/PickingHandler.h"
#include "Penditor/Penditor.h"
#include "PenFileExplorerWindow/PenFileExplorerWindow.h"

namespace Penditor::Window
{
	PenPropertyWindow::PenPropertyWindow(const char* title, int flags)
	{
		p_title = title;
		p_flags = flags;

	}

	PenPropertyWindow::~PenPropertyWindow()
	{

	}

	void PenPropertyWindow::renderCalls()
	{
		switch (this->m_renderingType)
		{
		case E_PENOBJECT:
			this->renderSelectedObject();
			break;
		case E_PENRESOURCES:
			this->renderSelectedResource();
			break;
		case E_NONE:
		default:
			break;
		}
	}

	void PenPropertyWindow::changeRenderTypeToObject()
	{
		this->m_currentResource = nullptr;
		this->m_renderingType = PropertiesRenderingType::E_PENOBJECT;
		const Pengine::PenObjectId selectedObject = PenditorCore::PickingHandler()->getSelectedObject();

		m_objectEuler = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(selectedObject).getGlobalTransform().rotation.getRotationEuler();
		Pengine::PenCore::UIManager()->removeInputFocus();
	}

	void PenPropertyWindow::changeRenderTypeToResource(const PenFileData& data)
	{
		switch (data.type)
		{
		case Pengine::Resources::PenResourceType::E_MATERIAL:
			this->m_currentResource = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenMaterial>(data.pathFile.c_str());
			break;
		case Pengine::Resources::PenResourceType::E_MODEL:
			this->m_currentResource = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenModel>(data.pathFile.c_str());
			break;
		case Pengine::Resources::PenResourceType::E_SHADER:
			this->m_currentResource = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenShader>(data.pathFile.c_str());
			break;
		case Pengine::Resources::PenResourceType::E_SHADER_PROGRAM:
			this->m_currentResource = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenShaderProgram>(data.pathFile.c_str());
			break;
		case Pengine::Resources::PenResourceType::E_TEXTURE:
			this->m_currentResource = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>(data.pathFile.c_str());
			break;
		default:
			this->m_currentResource = nullptr;
			break;
		}

		//if Null dispaly folder

		this->m_renderingType = E_PENRESOURCES;
		this->m_currentData = data;
	}

	void PenPropertyWindow::changeRenderTypeToNone()
	{
		this->m_currentResource = nullptr;
		this->m_renderingType = E_NONE;
	}

	void PenPropertyWindow::renderSelectedObject()
	{
		const Pengine::PenObjectId selectedObject = PenditorCore::PickingHandler()->getSelectedObject();

		if (selectedObject == Pengine::g_PenObjectInvalidId)
			return;

		Pengine::ui::PenUIManager*			manager = Pengine::PenCore::UIManager().get();
		std::vector<Pengine::IPenProperty*> prop	= Pengine::PenCore::PenOctopus()->PropertyManager()->getProperties(selectedObject);

		for (int i = 0; i < prop.size(); ++i)
			this->renderProperty(prop[i], manager);
	}

	void PenPropertyWindow::renderSelectedResource()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->renderText(this->m_currentData.pathFile.c_str());
	}

	void PenPropertyWindow::renderProperty(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager)
	{
		switch(prop->getType())
		{
			case Pengine::PenPropertyType::E_COMPONENT:
				this->renderComponentProp(prop, manager);
				break;
			case Pengine::PenPropertyType::E_VEC3:
				this->renderVector3Prop(prop, manager);
				break;
			case Pengine::PenPropertyType::E_QUATERNION:
				this->renderQuaternionProp(prop, manager);
				break;
		}
	}

	void PenPropertyWindow::renderComponentProp(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager)
	{
		m_currentComponent = static_cast<Pengine::Components::PenComponentBase*>(prop->getData());
		
		bool enabled = m_currentComponent->IsState(Pengine::Components::PenComponentState::ENABLE);
		
		manager->renderBool(&enabled, "##Enabled");
		manager->renderOnSameLine();
		m_headerOpen = manager->renderCollapsingHeader(prop->getName());


		if (enabled != m_currentComponent->IsState(Pengine::Components::PenComponentState::ENABLE))
			m_currentComponent->SetState(Pengine::Components::PenComponentState::ENABLE, enabled);
	}

	void PenPropertyWindow::renderVector3Prop(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager)
	{
		if (!m_headerOpen)
			return;

		std::string name = prop->getName();
		name += " :";
		
		std::string id = "##";
		id += prop->getName();

		manager->renderText(name.c_str());
		manager->renderOnSameLine();

		PenMath::Vector2 windowSize		= manager->getContentSize();
		float fluid_width				= windowSize.x * Setting::sPropertySettings::s_vec3Width;

		if (fluid_width < Setting::sPropertySettings::s_vec3MinWidth)
			fluid_width = Setting::sPropertySettings::s_vec3MinWidth;
		

		float posX	= manager->getUICursorPos().x + windowSize.x - fluid_width;

		manager->setUICursorPosX(posX);
		manager->setNextItemWidth(fluid_width);

		PenMath::Vector3f* vec = static_cast<PenMath::Vector3f*>(prop->getData());

		if (manager->renderVector3(*vec, id.c_str()))
			m_currentComponent->SetState(Pengine::Components::PenComponentState::DIRTY);
	}

	void PenPropertyWindow::renderQuaternionProp(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager)
	{
		if (!m_headerOpen)
			return;

		std::string name = prop->getName();
		name += " :";

		std::string id = "##";
		id += prop->getName();

		manager->renderText(name.c_str());
		manager->renderOnSameLine();

		PenMath::Vector2 windowSize = manager->getContentSize();
		float fluid_width = windowSize.x * Setting::sPropertySettings::s_vec3Width;

		if (fluid_width < Setting::sPropertySettings::s_vec3MinWidth)
			fluid_width = Setting::sPropertySettings::s_vec3MinWidth;

		float posX = manager->getUICursorPos().x + windowSize.x - fluid_width;

		manager->setUICursorPosX(posX);
		manager->setNextItemWidth(fluid_width);

		if (manager->renderVector3(m_objectEuler, id.c_str()))
		{
			PenMath::Quaternion* quat = static_cast<PenMath::Quaternion*>(prop->getData());
			quat->setRotationEuler(m_objectEuler);
			m_currentComponent->SetState(Pengine::Components::PenComponentState::DIRTY);
		}
	}
}
