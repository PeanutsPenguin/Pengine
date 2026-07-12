#pragma once 

namespace Pengine::ui
{
    enum PenTreeNodeFlags : int
    {
        E_NONE = 0,
        E_SELECTED = 1 << 0,                 // Draw as selected
        E_FRAMED = 1 << 1,                  // Draw frame with background (e.g. for CollapsingHeader)
        E_OVERLAP_ALLOWED = 1 << 2,         // Hit testing to allow subsequent widgets to overlap this one
        E_NO_TREE_PUSH = 1 << 3,            // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
        E_DEFAULT_OPEN = 1 << 5,            // Default node to be open
        E_DOUBLIC_CLICK_OPEN = 1 << 6,      // Open on double-click instead of simple click (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
        E_OPEN_ON_ARROW = 1 << 7,           // Open when clicking on the arrow part (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
        E_LEAF = 1 << 8,                    // No collapsing, no arrow (use as a convenience for leaf nodes).
        E_BULLET = 1 << 9,                  // Display a bullet instead of arrow. IMPORTANT: node can still be marked open/close if you don't set the _Leaf flag!
        E_FRAME_PADDING = 1 << 10,          // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding() before the node.
    };
}

