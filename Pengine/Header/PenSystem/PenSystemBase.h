#pragma once 

#include <set>

#include "PengineDefine.h"

namespace Pengine::System
{
	class PenSystemBase
	{
	public:
		PenSystemBase() = default;
		PenSystemBase(const PenSystemBase& other) = default;
		PenSystemBase(PenSystemBase&& other) = default;
		virtual ~PenSystemBase() = default;

		PenSystemBase& operator=(const PenSystemBase& rhs) = default;
		PenSystemBase& operator=(PenSystemBase&& rhs) = default;

		virtual void onEntityInserted(const PenObjectId newObj) = 0;
		virtual void onEntityDestroyed(const PenObjectId obj) = 0;

		virtual void update(double dt) = 0;

		std::set<PenObjectId> m_PenObject;
		PenComponentSignature m_signature;
	};
}