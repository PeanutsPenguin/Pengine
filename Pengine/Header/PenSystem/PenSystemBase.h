#pragma once 

#include <set>

#include "PenDefine/PengineDefine.h"		//PengineDefine

namespace Pengine::System
{
	class PenSystemManager;

	class PenSystemBase
	{
	public:

		friend class PenSystemManager;

		PenSystemBase() = default;
		PenSystemBase(const PenSystemBase& other) = default;
		PenSystemBase(PenSystemBase&& other) = default;
		virtual ~PenSystemBase() = default;

		PenSystemBase& operator=(const PenSystemBase& rhs) = default;
		PenSystemBase& operator=(PenSystemBase&& rhs) = default;

		virtual void onEntityInserted(const PenObjectId newObj) = 0;
		virtual void onEntityDestroyed(const PenObjectId obj) = 0;

		virtual void update(double dt) = 0;

		const std::set<PenObjectId>& getRegisteredObject() { return this->m_PenObject; }

	protected:
		std::set<PenObjectId> m_PenObject;
		PenComponentSignature m_signature;
	};
}