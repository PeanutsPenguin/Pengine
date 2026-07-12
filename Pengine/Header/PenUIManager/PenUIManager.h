#pragma once 

#include "Vector/Vector2/Vector2.h"
#include "Vector/Vector3/Vector3.h"

#include "PenStructsAndEnum/PenTreeNodeFlags.h"

namespace Pengine::Window
{
	class WindowWrapper;
}

namespace Pengine::ui
{
	class PenUIManager
	{
	public:
		PenUIManager() = default;
		PenUIManager(const PenUIManager& other) = default;
		PenUIManager(PenUIManager&& other) = default;
		~PenUIManager();

		PenUIManager& operator=(const PenUIManager& rhs) = default;
		PenUIManager& operator=(PenUIManager&& rhs) = default;

		bool	init(Window::WindowWrapper* window);

		void	newFrame(bool dockableWindow);

		void	endFrame();

		void	shutDown();

		PenMath::Vector2	getContentSize();
		PenMath::Vector2	getUICursorPos();
		float				getFrameHeight();

		void				setUICursorPos(const PenMath::Vector2f& pos);
		void				setUICursorPosX(float x);
		void				setUICursorPosY(float y);
		void				setNextItemWidth(float width);
		

		bool				isWindowHovered();
		bool				isItemClicked();
		void				removeInputFocus();
		void				popTree();
		
		void				renderOnSameLine(float spacing = 0);
		void				renderImage(int textureID, const PenMath::Vector2& size);
		void				renderBool(bool* value, const char* name);
		void				renderText(const char* value);
		bool				renderCollapsingHeader(const char* name);

		bool				renderVector3(PenMath::Vector3& vec, const char* name);		//Vec3 int
		bool				renderVector3(PenMath::Vector3f& vec, const char* name);	//Vec3 float
		bool				renderTreeNode(const char* name, PenTreeNodeFlags flags);
	};
}