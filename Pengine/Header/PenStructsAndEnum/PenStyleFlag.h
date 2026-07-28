#pragma once 

namespace Pengine::ui
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
}