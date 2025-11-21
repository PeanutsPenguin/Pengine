#pragma once 

namespace Pengine
{
	enum PenInputType
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
		key_MOUSE_LEFT, key_MOUSE_RIGHT, key_MOUSE_WHEEL
	};
}