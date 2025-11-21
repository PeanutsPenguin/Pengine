#pragma once 

#include <memory>

namespace Penditor
{
	class PenFreeCam;

	class PenCore
	{
	public:
		PenCore() = delete;

		~PenCore() = delete;

		static void runEditor();

		static void destroy();

		static std::unique_ptr<PenFreeCam>& getEditorCam();

	private:
		static void update(double dt);

		static std::unique_ptr<PenFreeCam> m_editorCam;
		
		static bool m_shouldStop;
	};
}
