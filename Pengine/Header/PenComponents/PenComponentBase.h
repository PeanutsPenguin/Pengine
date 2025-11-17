#pragma once 

#include "PengineDefine.h"
#include "PenStructsAndEnum/PenComponentState.h"

namespace Pengine::Components
{
	class PenComponentBase
	{
	public:
		PenComponentBase(void) = default;

		PenComponentBase(const PenComponentBase& other) = default;

		PenComponentBase(PenComponentBase& other) = default;

		virtual ~PenComponentBase(void) = default;

		PenComponentBase& operator=(const PenComponentBase& rhs) = default;
		PenComponentBase& operator=(PenComponentBase&& rhs) = default;

		bool IsState(PenComponentState state);

		void SetState(PenComponentState state, bool enable = true);

	private:
		std::bitset<8>	 m_flags = std::bitset<8>((size_t)PenComponentState::ENABLE);	//Bit operation to check component's specific state
	};
}	