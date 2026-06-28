#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "Vector/Vector3/Vector3.h"

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
		~PenPropertyWindow() final;

		PenPropertyWindow& operator=(const PenPropertyWindow& rhs) = default;
		PenPropertyWindow& operator=(PenPropertyWindow&& rhs) = default;

		void renderCalls() final;

	private:

		void	renderProperty			(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderComponentProp		(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderVector3Prop		(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);
		void	renderQuaternionProp	(Pengine::IPenProperty* prop, Pengine::ui::PenUIManager* manager);

		bool									m_headerOpen		= true;
		Pengine::Components::PenComponentBase*	m_currentComponent	= nullptr;
		PenMath::Vector3f						m_objectEuler		= PenMath::Vector3f::Zero();
		bool m_tempInit = false;
	};
}