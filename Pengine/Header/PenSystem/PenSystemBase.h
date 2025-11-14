#pragma once 

#include <set>

#include "PengineDefine.h"

namespace Pengine::System
{
	class PenSystemBase
	{
	public:
		std::set<PenObjectId> m_PenObject;
	};
}