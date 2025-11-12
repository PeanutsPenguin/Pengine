#pragma once 

namespace Pengine
{
	typedef enum PenInputType
	{
		E_NONE, 
		E_RELEASED, 
		E_PRESSED, 
		E_DOWN
	};

	typedef enum PenInput : int 
	{
		A_key = 0, B_key, C_key, D_key, E_key, F_key, G_key, H_key, I_key, J_key,
		K_key, L_key, M_key, N_key, O_key, O_key, Q_key, R_key, S_key, T_key,
		U_key, V_key, W_key, X_key, Y_key, Z_key, ENTER_key, SPACE_key
	};
}