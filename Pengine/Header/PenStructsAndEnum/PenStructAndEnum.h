#pragma once

#include <string>
#include "Vector/Vector3/Vector3.h"
#include "Vector/Vector2/Vector2.h"


namespace Pengine
{
	#pragma region ENUM

		#pragma region INPUT

		enum PenInputState
		{
			E_NONE,
			E_RELEASED,
			E_PRESSED,
			E_DOWN
		};

		enum PenInput : int
		{
			key_0 = 0, key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9,
			key_A, key_B, key_C, key_D, key_E, key_F, key_G, key_H, key_I, key_J,
			key_K, key_L, key_M, key_N, key_O, key_P, key_Q, key_R, key_S, key_T,
			key_U, key_V, key_W, key_X, key_Y, key_Z, key_ENTER, key_SPACE, key_ESCAPE,
			key_MOUSE_LEFT, key_MOUSE_RIGHT, key_MOUSE_WHEEL, key_LEFT_CONTROL
		};

		enum CursorState
		{
			E_NORMAL,
			E_HIDDEN,
			E_DISABLED
		};

		#pragma endregion

	namespace Components
	{
		enum class PenComponentState 
		{ 
			ENABLE = 0x01, 
			DIRTY = 0x02 
		};

		enum PenComponentTypeEnum : int
		{
			E_TRANSFORM = 0,
			E_RENDERER = 1,
			E_CAMERA = 2,
			E_LIGHT = 3
		};
	}

	namespace Resources
	{
		//DO NOT TOUCH THE ORDER OR IT'LL BROKE THE EVERY LOADING VALUE (should define a int for every type)
		enum PenResourceType : int
		{
			E_MATERIAL = 0,
			E_MODEL = 2,
			E_SHADER,
			E_SHADER_PROGRAM,
			E_TEXTURE,
			E_SCENE,
			E_NONE
		};

		#define MAT_DROP_ID "MATERIAL"
		#define MODEL_DROP_ID "MODEL"
		#define SHADER_DROP_ID "SHADER"
		#define SHADER_PROG_DROP_ID "SHADER_PROG"
		#define TEXTURE_DROP_ID "TEXTURE"
	}

	namespace Log
	{
		enum PenLogLevel
		{
			E_NORMAl,
			E_WARNING,
			E_ERROR,
			E_DEBUG,
			E_DEBUG_WARNING,
		};
	}

	namespace ui
	{
		enum PenStyleFlag
		{
			E_ALPHA,                            // float     Alpha
			E_DISABLED_ALPHA,                   // float     DisabledAlpha
			E_WINDOW_PADDING,                   // ImVec2    WindowPadding
			E_WINDOW_ROUNDING,                  // float     WindowRounding
			E_WINDOW_BORDER_SIZE,               // float     WindowBorderSize
			E_WINDOW_MIN_SIZE,                  // ImVec2    WindowMinSize
			E_WINDOW_TITLE_ALIGN,               // ImVec2    WindowTitleAlign
			E_CHILD_ROUDING,                    // float     ChildRounding
			E_CHILD_BORDER_SIZE,                // float     ChildBorderSize
			E_POP_UP_ROUNDING,                  // float     PopupRounding
			E_POP_UP_BORDER_SIZE,               // float     PopupBorderSize
			E_FRAME_PADDING,                    // ImVec2    FramePadding
			E_FRAME_ROUNDING,                   // float     FrameRounding
			E_FRAME_BORDER_SIZE,                // float     FrameBorderSize
			E_ITEM_SPACING,                     // ImVec2    ItemSpacing
			E_ITEM_INNER_SPACING,               // ImVec2    ItemInnerSpacing
			E_INDENT_SPACING,                   // float     IndentSpacing
			E_CELL_PADDING,                     // ImVec2    CellPadding
			E_SCROLLBAR_SIZE,                   // float     ScrollbarSize
			E_SCROLLBAR_ROUNDING,               // float     ScrollbarRounding
			E_GRAB_MIN_SIZE,                    // float     GrabMinSize
			E_GRAB_ROUNDING,                    // float     GrabRounding
			E_TAB_ROUNDING,                     // float     TabRounding
			E_TAB_BORDER_SIZE,                  // float     TabBorderSize
			E_TAB_BAR_BORDER_SIZE,              // float     TabBarBorderSize
			E_TAB_OVERLINE_SIZE,                // float     TabBarOverlineSize
			E_TABLEANGLE_HEADERS_ANGLE,         // float     TableAngledHeadersAngle
			E_TABLEANGLE_HEADERS_TEXT_ALIGN,    // ImVec2  TableAngledHeadersTextAlign
			E_BUTTON_TEXT_ALIGN,                // ImVec2    ButtonTextAlign
			E_SELECTABLE_TEXT_ALIGN,            // ImVec2    SelectableTextAlign
			E_SEPARATOR_TEXT_BORDER_SIZE,       // float     SeparatorTextBorderSize
			E_SEPARATOR_TEXT_ALIGN,             // ImVec2    SeparatorTextAlign
			E_SEPARATOR_TEXT_PADING,            // ImVec2    SeparatorTextPadding
			E_DOCKING_SEPARATOR_SIZE            // float     DockingSeparatorSize
		};

		enum PenStyleColorType
		{
			E_TEXT,
			E_TEXT_DISABLED,
			E_WINDOW_BG,                        // Background of normal windows
			E_CHILD_BG,                         // Background of child windows
			E_POPUP_BG,                         // Background of popups, menus, tooltips windows
			E_BORDER,
			E_BORDER_SHADOW,
			E_FRAME_BG,                         // Background of checkbox, radio button, plot, slider, text input
			E_FRAME_BG_HOVERED,
			E_FRAME_BG_ACTIVE,
			E_TITLE_BG,                         // Title bar
			E_TITLE_BG_ACTIVE,                  // Title bar when focused
			E_TITLE_BG_COLLAPSED,               // Title bar when collapsed
			E_MENU_BAR_BG,
			E_SCROLLBAR_BG,
			E_SCROLLBAR_GRAB,
			E_SCROLLBAR_GRAB_HOVERED,
			E_SCROLLBAR_GRAB_ACTIVE,
			E_CHECKMARK,                        // Checkbox tick and RadioButton circle
			E_SLIDER_GRAB,
			E_SLIDER_GRAB_ACTIVE,
			E_BUTTON,
			E_BUTTON_HOVERED,
			E_BUTTON_ACTIVE,
			E_HEADER,                           // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
			E_HEADER_HOVERED,
			E_HEADER_ACTIVE,
			E_SEPARATOR,
			E_SEPARATOR_HOVERED,
			E_SEPARATOR_ACTIVE,
			E_RESIZE_GRIP,                      // Resize grip in lower-right and lower-left corners of windows.
			E_RESIZE_GRIP_HOVERED,
			E_RESIZE_GRIP_ACTIVE,
			E_TAB_HOVERED,                      // Tab background, when hovered
			E_TAB,                              // Tab background, when tab-bar is focused & tab is unselected
			E_TAB_SELECTED,                     // Tab background, when tab-bar is focused & tab is selected
			E_TAB_SELECTED_OVERLINE            // Tab horizontal overline, when tab-bar is focused & tab is selected
		};

		enum PenTreeNodeFlags : int
		{
			E_NONE = 0,
			E_SELECTED = 1 << 0,					// Draw as selected
			E_FRAMED = 1 << 1,						// Draw frame with background (e.g. for CollapsingHeader)
			E_OVERLAP_ALLOWED = 1 << 2,				// Hit testing to allow subsequent widgets to overlap this one
			E_NO_TREE_PUSH = 1 << 3,				// Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
			E_DEFAULT_OPEN = 1 << 5,				// Default node to be open
			E_DOUBLIC_CLICK_OPEN = 1 << 6,			// Open on double-click instead of simple click (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
			E_OPEN_ON_ARROW = 1 << 7,				// Open when clicking on the arrow part (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
			E_LEAF = 1 << 8,						// No collapsing, no arrow (use as a convenience for leaf nodes).
			E_BULLET = 1 << 9,						// Display a bullet instead of arrow. IMPORTANT: node can still be marked open/close if you don't set the _Leaf flag!
			E_FRAME_PADDING_ALIGN = 1 << 10,        // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding() before the node.
			E_SPAN_RIGHT_WIDTH = 1 << 11,			// Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line without using AllowOverlap mode.
			E_SPAN_FULL_WIDTH = 1 << 12,			// Extend hit box to the left-most and right-most edges (cover the indent area).
		};

		enum PenVirtualWindowFlags
		{
			NONE = 0,
			NO_TITLE_BAR = 1 << 0,
			NO_RESIZE = 1 << 1,
			NO_MOVE = 1 << 2,
			NO_SCROLL_BAR = 1 << 3,
			NO_MOUSE_SCROLL = 1 << 4,
			NO_MOUSE_INPUT = 1 << 9,
			NO_COLLAPSE = 1 << 5,
			AUTO_RESIZE = 1 << 6,
			NO_BACKGROUND = 1 << 7,
			NO_META_DATA = 1 << 8,
			MENU_BAR = 1 << 10,
			HORIZONTAL_SCROLL_BAR = 1 << 11,
			NO_FOCUS_ON_APPEARING = 1 << 12,
			NO_BRING_TO_FRONT_ON_FOCUS = 1 << 13,
			ALWAYS_VERTICAL_SCROLL_BAR = 1 << 14,
			ALWAYS_HORIZONTAL_SCROLL_BAR = 1 << 15,
			NO_NAV_INPUTS = 1 << 16,
			NO_NAV_FOCUS = 1 << 17,
			UNSAVED_DOC = 1 << 18,
			NO_DOCKING = 1 << 19,
			NO_NAV = NO_NAV_INPUTS | NO_NAV_FOCUS,
			NO_DECORATIONS = NO_TITLE_BAR | NO_RESIZE | NO_SCROLL_BAR | NO_COLLAPSE,
			NO_INPUTS = NO_MOUSE_INPUT | NO_NAV_INPUTS | NO_NAV_FOCUS
		};
	}

	enum PenLightType : int
	{
		E_INVALID = 0,
		E_DIRECTIONNAL,
		E_POINT,
		E_SPOT
	};

	enum PenLoadingStatus
	{
		E_NOT_LOADED,
		E_LOADING,
		E_LOADED
	};

	enum PenPropertyType
	{
		E_COMPONENT,
		E_STRING,
		E_INT,
		E_FLOAT,
		E_VEC3,
		E_VEC2,
		E_QUATERNION,
		E_COLOR,
		E_MODEL,
		E_MATERIAL
	};

	enum PenShaderType : int
	{
		E_INVALID_SHADER = 0,
		E_VERTEX_SHADER,
		E_FRAGMENT_SHADER
	};

	#pragma endregion

	#pragma region STRUCT

	struct DragAndDropData
	{
		Resources::PenResourceType type;
		char filePath[256];
	};

	struct PenVertex
	{
		PenMath::Vector3f position;
		PenMath::Vector3f normal;
		PenMath::Vector2f uv;
		PenMath::Vector3f tangent;
	};

	namespace Log
	{
		struct PenLog
		{
			std::string message;
			std::string file;
			PenLogLevel level;
			unsigned int line;
			unsigned int count = 1;
		};
	}

	#pragma endregion
}