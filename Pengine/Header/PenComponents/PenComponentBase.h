#pragma once 

#include "PenDefine/PengineDefine.h"		//PengineDefine
#include "PenStructsAndEnum/PenComponentState.h"

#include <iostream>

namespace Pengine
{
	class PenOctopus;
	class PenPropertyManager;
}

namespace Pengine::Components
{
	class PenComponentBase
	{
		friend class PenOctopus;	

	public:
		PenComponentBase() = default;
		PenComponentBase(const PenComponentBase& other) = default;
		PenComponentBase(PenComponentBase& other) = default;
		virtual ~PenComponentBase() = default;

		PenComponentBase& operator=(const PenComponentBase& rhs) = default;
		PenComponentBase& operator=(PenComponentBase&& rhs) = default;

		bool IsState(PenComponentState state);

		void SetState(PenComponentState state, bool enable = true);

		const PenObjectId getPenObjectId() const;

		virtual void registerProperty(PenPropertyManager* manager);
	
	private:
		void setPenObjectId(const PenObjectId id);

		PenObjectId m_objId = g_PenObjectInvalidId;
		std::bitset<8>	 m_flags = std::bitset<8>((size_t)PenComponentState::ENABLE);	//Bit operation to check component's specific state
	};
}	