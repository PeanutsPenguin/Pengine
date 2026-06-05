#pragma once 

#include <memory>

namespace Penditor
{
	class PenFreeCam;

	class PenditorCore
	{
	public:
		PenditorCore() = delete;

		~PenditorCore() = delete;

		static void runEditor();

		static void stopEditor();

		static void destroy();

		static std::unique_ptr<PenFreeCam>& getEditorCam();

	private:
		static void update(double dt);

		static void handleInputs();

		static std::unique_ptr<PenFreeCam> m_editorCam;
		
		static bool m_shouldStop;
	};
}
