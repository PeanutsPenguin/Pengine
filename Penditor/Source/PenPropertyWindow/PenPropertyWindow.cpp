#include "PenPropertyWindow/PenPropertyWindow.h"

#include "PenCore/PenCore.h"
#include "PenOctopus/PenOctopus.hpp"
#include "PenUIManager/PenUIManager.h"
#include "PenProperty/PenPropertyManager.h"
#include "PenComponents/PenComponentBase.h"
#include "PenPropertyWindow/PenPropertySettings.h"
#include "PenComponents/PenTransform/PenTransform.h"

namespace Penditor::Window
{
	PenPropertyWindow::PenPropertyWindow(const char* title, int flags)
	{
		m_title = title;
		m_flgas = flags;

	}

	PenPropertyWindow::~PenPropertyWindow()
	{

	}

	void PenPropertyWindow::renderCalls()
	{
		const Pengine::PenObjectId selectedObject = 1;

		//TODO: this will be moved with Picking
		if(!m_tempInit)
		{
			m_objectEuler = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(selectedObject).getGlobalTransform().rotation.getRotationEuler();
			m_tempInit = true;
		}

		std::vector<Pengine::IPenProperty*> prop = Pengine::PenCore::PenOctopus()->PropertyManager()->getProperties(selectedObject);
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		for (int i = 0; i < prop.size(); ++i)
			this->renderProperty(prop[i], manager);
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
