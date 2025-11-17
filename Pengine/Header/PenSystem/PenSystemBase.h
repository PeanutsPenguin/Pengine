#pragma once 

#include <set>

#include "PengineDefine.h"

namespace Pengine::System
{
	class PenSystemBase
	{
	public:
		PenSystemBase() = default;
		virtual ~PenSystemBase() = default;

		virtual void onEntityDestroyed() = 0;

		std::set<PenObjectId> m_PenObject;
		PenComponentSignature m_signature;
	};
}