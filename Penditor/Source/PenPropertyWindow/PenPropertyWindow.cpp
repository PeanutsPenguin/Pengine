#include "PenPropertyWindow/PenPropertyWindow.h"
#include "PenPropertyWindow/PenPropertySettings.h"

#include "PenCore/PenCore.h"
#include "PenOctopus/PenOctopus.hpp"
#include "PenUIManager/PenUIManager.h"
#include "PenProperty/PenPropertyManager.h"
#include "PenComponents/PenComponentBase.h"

#include "PenBuffer/PenTextureBuffer.h"

#include "PenResources/PenResourceManager.hpp"
#include "PenResources/AllPenResources.h"

#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenRenderer/PenRenderer.h"

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
		this->m_renderingType = PropertiesRenderingType::E_PENOBJECT;
		const Pengine::PenObjectId selectedObject = PenditorCore::PickingHandler()->getSelectedObject();

		m_objectEuler = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(selectedObject).getGlobalTransform().rotation.getRotationEuler();
		Pengine::PenCore::UIManager()->removeInputFocus();
	}

	void PenPropertyWindow::changeRenderTypeToResource(const PenFileData& data)
	{
		this->m_renderingType = E_PENRESOURCES;
		this->m_currentData = data;
	}

	void PenPropertyWindow::changeRenderTypeToNone()
	{
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
		PenMath::Vector2 windowSize = manager->getContentSize();

		manager->setUICursorPosX((windowSize.x * 0.5f) - PROP_HALF_ICON_SIZE);
		manager->renderImage(this->m_currentData.icon->dataPtr()->getTextID(), { PROP_ICON_SIZE, PROP_ICON_SIZE });
		manager->renderCenterText(this->m_currentData.fileName.c_str());

		switch(this->m_currentData.type)
		{
			case Pengine::Resources::PenResourceType::E_MATERIAL:
				this->renderMaterialResource();
			break;
			case Pengine::Resources::PenResourceType::E_MODEL:
				this->renderModelResource();
			break;
			case Pengine::Resources::PenResourceType::E_SHADER:
				this->renderShaderResource();
			break;
			case Pengine::Resources::PenResourceType::E_SHADER_PROGRAM:
				this->renderShaderProgramResource();
			break;
			case Pengine::Resources::PenResourceType::E_TEXTURE:
				this->renderTextureResource();
			break;
			case Pengine::Resources::PenResourceType::E_NONE:
			default:
				manager->renderCenterText("Folder");
				manager->renderSeperator();
				break;
		}

		//Render preview window
	}	

	void PenPropertyWindow::renderMaterialResource()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		std::shared_ptr<Pengine::Resources::PenMaterial> mat = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenMaterial>(this->m_currentData.pathFile.c_str());

		manager->renderCenterText("PenMaterial");
		manager->renderSeperator();

		this->renderAlbedo(mat);
		this->renderRoughness(mat);
		this->renderMettallic(mat);
		this->renderAmbientOccluion(mat);
		this->renderNormal(mat);
	}

	void PenPropertyWindow::renderAlbedo(std::shared_ptr<Pengine::Resources::PenMaterial> mat)
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->setUICursorPosY(manager->getUICursorPos().y + 10.f);
		manager->renderText("Albedo");

		PenMath::Vector2 curPos = manager->getUICursorPos();

		manager->setUICursorPosY(curPos.y + HALF_TEX_SIZE);
		manager->renderText("Texture : ");
		manager->renderOnSameLine();
		manager->setUICursorPosY(curPos.y + QUARTER_TEX_SIZE);

		if (mat->getAlbedo().isPropertyValid())
			manager->renderImage(mat->getAlbedo().texture->dataPtr()->getTextID(), { TEX_SIZE, TEX_SIZE });
		else
			manager->renderImage(0, { TEX_SIZE, TEX_SIZE });

		if(manager->beginDragAndDropTarget())
		{
			const Pengine::DragAndDropData* droppedData = manager->getDroppedData(TEXTURE_ID);

			if(droppedData != nullptr)
			{
				std::shared_ptr<Pengine::Resources::PenTexture> texture = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>(droppedData->filePath);

				if(texture)
					mat->setAlbedo(texture);
			}
		}


		manager->renderOnSameLine(150);

		manager->renderText("Raw Value : ");
		manager->renderOnSameLine();
		PenMath::Vector3f albedoCpy = mat->getAlbedo().defaultValue;

		if (manager->renderColorPickerVec3("##AlbedoRawValue", albedoCpy))
			mat->setAlbedo(albedoCpy);

		manager->renderSeperator();
	}

	void PenPropertyWindow::renderRoughness(std::shared_ptr<Pengine::Resources::PenMaterial> mat)
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->setUICursorPosY(manager->getUICursorPos().y + 10.f);
		manager->renderText("Roughness");

		PenMath::Vector2 curPos = manager->getUICursorPos();

		manager->setUICursorPosY(curPos.y + HALF_TEX_SIZE);
		manager->renderText("Texture : ");
		manager->renderOnSameLine();
		manager->setUICursorPosY(curPos.y + QUARTER_TEX_SIZE);

		if (mat->getRoughness().isPropertyValid())
			manager->renderImage(mat->getRoughness().texture->dataPtr()->getTextID(), { TEX_SIZE, TEX_SIZE });
		else
			manager->renderImage(0, { TEX_SIZE, TEX_SIZE });

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::DragAndDropData* droppedData = manager->getDroppedData(TEXTURE_ID);

			if (droppedData != nullptr)
			{
				std::shared_ptr<Pengine::Resources::PenTexture> texture = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>(droppedData->filePath);

				if (texture)
					mat->setAlbedo(texture);
			}
		}

		manager->renderOnSameLine(150);

		manager->renderText("Raw Value : ");
		manager->renderOnSameLine();

		manager->setNextItemWidth(Setting::sPropertySettings::s_sliderMinWidth);

		float roughCpy = mat->getRoughness().defaultValue;

		if (manager->renderSliderFloat("##RoughnessRawValue", 0, 1, &roughCpy))
			mat->setRoughness(roughCpy);

		manager->renderSeperator();
	}

	void PenPropertyWindow::renderMettallic(std::shared_ptr<Pengine::Resources::PenMaterial> mat)
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->setUICursorPosY(manager->getUICursorPos().y + 10.f);
		manager->renderText("Metallic");

		PenMath::Vector2 curPos = manager->getUICursorPos();

		manager->setUICursorPosY(curPos.y + HALF_TEX_SIZE);
		manager->renderText("Texture : ");
		manager->renderOnSameLine();
		manager->setUICursorPosY(curPos.y + QUARTER_TEX_SIZE);

		if (mat->getMetallic().isPropertyValid())
			manager->renderImage(mat->getMetallic().texture->dataPtr()->getTextID(), { TEX_SIZE, TEX_SIZE });
		else
			manager->renderImage(0, { TEX_SIZE, TEX_SIZE });

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::DragAndDropData* droppedData = manager->getDroppedData(TEXTURE_ID);

			if (droppedData != nullptr)
			{
				std::shared_ptr<Pengine::Resources::PenTexture> texture = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>(droppedData->filePath);

				if (texture)
					mat->setAlbedo(texture);
			}
		}

		manager->renderOnSameLine(150);

		manager->renderText("Raw Value : ");
		manager->renderOnSameLine();

		manager->setNextItemWidth(Setting::sPropertySettings::s_sliderMinWidth);

		float metCpy = mat->getRoughness().defaultValue;

		if (manager->renderSliderFloat("##MettallicRawValue", 0, 1, &metCpy))
			mat->setMetallic(metCpy);

		manager->renderSeperator();
	}

	void PenPropertyWindow::renderAmbientOccluion(std::shared_ptr<Pengine::Resources::PenMaterial> mat)
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->setUICursorPosY(manager->getUICursorPos().y + 10.f);
		manager->renderText("Ambient Occlusion");

		PenMath::Vector2 curPos = manager->getUICursorPos();

		manager->setUICursorPosY(curPos.y + HALF_TEX_SIZE);
		manager->renderText("Texture : ");
		manager->renderOnSameLine();
		manager->setUICursorPosY(curPos.y + QUARTER_TEX_SIZE);

		if (mat->getAmbientOcclusion().isPropertyValid())
			manager->renderImage(mat->getAmbientOcclusion().texture->dataPtr()->getTextID(), { TEX_SIZE, TEX_SIZE });
		else
			manager->renderImage(0, { TEX_SIZE, TEX_SIZE });

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::DragAndDropData* droppedData = manager->getDroppedData(TEXTURE_ID);

			if (droppedData != nullptr)
			{
				std::shared_ptr<Pengine::Resources::PenTexture> texture = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>(droppedData->filePath);

				if (texture)
					mat->setAlbedo(texture);
			}
		}

		manager->renderOnSameLine(150);

		manager->renderText("Raw Value : ");
		manager->renderOnSameLine();

		manager->setNextItemWidth(Setting::sPropertySettings::s_sliderMinWidth);

		float aoCpy = mat->getRoughness().defaultValue;

		if (manager->renderSliderFloat("##AORawValue", 0, 1, &aoCpy))
			mat->setAmbientOcclusion(aoCpy);

		manager->renderSeperator();
	}

	void PenPropertyWindow::renderNormal(std::shared_ptr<Pengine::Resources::PenMaterial> mat)
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->setUICursorPosY(manager->getUICursorPos().y + 10.f);
		manager->renderText("Normal");

		PenMath::Vector2 curPos = manager->getUICursorPos();

		manager->setUICursorPosY(curPos.y + HALF_TEX_SIZE);
		manager->renderText("Texture : ");
		manager->renderOnSameLine();
		manager->setUICursorPosY(curPos.y + QUARTER_TEX_SIZE);

		if (mat->getAmbientOcclusion().isPropertyValid())
			manager->renderImage(mat->getNormal()->dataPtr()->getTextID(), { TEX_SIZE, TEX_SIZE });
		else
			manager->renderImage(0, { TEX_SIZE, TEX_SIZE });

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::DragAndDropData* droppedData = manager->getDroppedData(TEXTURE_ID);

			if (droppedData != nullptr)
			{
				std::shared_ptr<Pengine::Resources::PenTexture> texture = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>(droppedData->filePath);

				if (texture)
					mat->setAlbedo(texture);
			}
		}

		manager->renderSeperator();
	}

	void PenPropertyWindow::renderTextureResource()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->renderCenterText("PenTexture");
		manager->renderSeperator();
	}

	void PenPropertyWindow::renderModelResource()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->renderCenterText("PenModel");
		manager->renderSeperator();
	}

	void PenPropertyWindow::renderShaderResource()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->renderCenterText("PenShader");
		manager->renderSeperator();
	}

	void PenPropertyWindow::renderShaderProgramResource()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		manager->renderCenterText("PenShaderProgram");
		manager->renderSeperator();
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
			case Pengine::PenPropertyType::E_MODEL:
				this->renderModelProp(prop, manager);
				break;
			case Pengine::PenPropertyType::E_MATERIAL:
				this->renderMaterialProp(prop, manager);
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
		
		PenMath::Vector2 windowSize = manager->getContentSize();

		std::string id = "##";
		id += prop->getName();

		manager->renderText(name.c_str());
		manager->renderOnSameLine();

		float fluid_width = windowSize.x * Setting::sPropertySettings::s_vec3Width;

		if (fluid_width < Setting::sPropertySettings::s_vec3MinWidth)
			fluid_width = Setting::sPropertySettings::s_vec3MinWidth;
		
		float posX	= 10.f + windowSize.x - fluid_width;

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

		PenMath::Vector2 windowSize = manager->getContentSize();

		std::string name = prop->getName();
		name += " :";

		std::string id = "##";
		id += prop->getName();

		manager->renderText(name.c_str());
		manager->renderOnSameLine();

		float fluid_width = windowSize.x * Setting::sPropertySettings::s_vec3Width;

		if (fluid_width < Setting::sPropertySettings::s_vec3MinWidth)
			fluid_width = Setting::sPropertySettings::s_vec3MinWidth;

		float posX = 10.f + windowSize.x - fluid_width;

		manager->setUICursorPosX(posX);
		manager->setNextItemWidth(fluid_width);

		if (manager->renderVector3(m_objectEuler, id.c_str()))
		{
			PenMath::Quaternion* quat = static_cast<PenMath::Quaternion*>(prop->getData());
			quat->setRotationEuler(m_objectEuler);
			m_currentComponent->SetState(Pengine::Components::PenComponentState::DIRTY);
		}
	}

	void PenPropertyWindow::renderMaterialProp(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager)
	{
		if (!m_headerOpen)
			return;

		std::string name = prop->getName();
		name += " :";

		PenMath::Vector2 curPos = manager->getUICursorPos();
		manager->setUICursorPosY(curPos.y + 15);
		manager->renderText(name.c_str());
		manager->renderOnSameLine();

		Pengine::Resources::PenMaterial* mat = static_cast<Pengine::Resources::PenMaterial*>(prop->getData());

		manager->renderOnSameLine();
		manager->setUICursorPosY(curPos.y + 7.5f);

		if (manager->renderButton(mat->getResourcePath().c_str(), { 0, 30 }))
			Penditor::PenditorCore::FileExplorerWindow()->selectPath(mat->getResourcePath().c_str());

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::DragAndDropData* droppedData = manager->getDroppedData(MAT_ID);

			if (droppedData != nullptr)
			{
				std::shared_ptr<Pengine::Resources::PenMaterial> mat = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenMaterial>(droppedData->filePath);

				if (mat)
				{
					Pengine::Components::PenRenderer* comp = static_cast<Pengine::Components::PenRenderer*>(this->m_currentComponent);
					comp->setMaterial(mat);
				}
			}
		}

	}

	void PenPropertyWindow::renderModelProp(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager)
	{
		if (!m_headerOpen)
			return;

		std::string name = prop->getName();
		name += " :";

		PenMath::Vector2 curPos = manager->getUICursorPos();
		manager->setUICursorPosY(curPos.y + 15);
		manager->renderText(name.c_str());
		manager->renderOnSameLine();

		Pengine::Resources::PenModel* model = static_cast<Pengine::Resources::PenModel*>(prop->getData());

		manager->renderOnSameLine();
		manager->setUICursorPosY(curPos.y + 7.5f);

		if(manager->renderButton(model->getResourcePath().c_str(), {0, 30}))
			Penditor::PenditorCore::FileExplorerWindow()->selectPath(model->getResourcePath().c_str());

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::DragAndDropData* droppedData = manager->getDroppedData(MODEL_ID);

			if (droppedData != nullptr)
			{
				std::shared_ptr<Pengine::Resources::PenModel> model = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenModel>(droppedData->filePath);

				if (model)
				{
					Pengine::Components::PenRenderer* comp = static_cast<Pengine::Components::PenRenderer*>(this->m_currentComponent);
					comp->setModel(model);
				}
			}
		}
	}
}
