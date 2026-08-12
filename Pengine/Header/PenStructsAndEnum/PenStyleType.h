#pragma once 

namespace Pengine::ui
{
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
}