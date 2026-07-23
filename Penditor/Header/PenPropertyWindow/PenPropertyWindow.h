#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "Vector/Vector3/Vector3.h"

#include "PenditorStructAndEnum/PenPropertiesObjectType.h"
#include "PenditorStructAndEnum/PenFileData.h"

#define PROP_ICON_SIZE 100
#define PROP_HALF_ICON_SIZE 50

#define TEX_SIZE 50
#define HALF_TEX_SIZE 25
#define QUARTER_TEX_SIZE 12

namespace Pengine
{
	class IPenProperty;
	
	namespace Components
	{
		class PenComponentBase;
	}

	namespace ui
	{
		class PenUIManager;
	}

	namespace Resources
	{
		class PenResourceBase;
		class PenMaterial;
	}
}


namespace Penditor::Window
{
	class PenPropertyWindow : public Pengine::ui::PenVirtualWindow
	{
	public:
		PenPropertyWindow() = default;
		PenPropertyWindow(const char* title, int flags = 0);
		PenPropertyWindow(const PenPropertyWindow& other) = default;
		PenPropertyWindow(PenPropertyWindow&& other) = default;
		~PenPropertyWindow() final = default;

		PenPropertyWindow& operator=(const PenPropertyWindow& rhs) = default;
		PenPropertyWindow& operator=(PenPropertyWindow&& rhs) = default;

		void renderCalls() final;

		void	changeRenderTypeToObject();
		void	changeRenderTypeToResource(const PenFileData& data);
		void	changeRenderTypeToNone();

	private:
		void	renderSelectedObject();
		void	renderSelectedResource();

		void	renderMaterialResource();
		void	renderAlbedo(std::shared_ptr<Pengine::Resources::PenMaterial> mat);
		void	renderRoughness(std::shared_ptr<Pengine::Resources::PenMaterial> mat);
		void	renderMettallic(std::shared_ptr<Pengine::Resources::PenMaterial> mat);
		void	renderAmbientOccluion(std::shared_ptr<Pengine::Resources::PenMaterial> mat);
		void	renderNormal(std::shared_ptr<Pengine::Resources::PenMaterial> mat);

		void	renderTextureResource();
		void	renderModelResource();
		void	renderShaderResource();
		void	renderShaderProgramResource();

		void	renderProperty			(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderComponentProp		(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderVector3Prop		(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderQuaternionProp	(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderModelProp			(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderMaterialProp		(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);

		PenMath::Vector3f										m_objectEuler		= PenMath::Vector3f::Zero();
		PropertiesRenderingType									m_renderingType		= PropertiesRenderingType::E_NONE;
		Pengine::Components::PenComponentBase*					m_currentComponent	= nullptr;
		PenFileData												m_currentData;
		bool													m_headerOpen		= true;
	};
}