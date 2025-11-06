#pragma once 

#include "PengineDefine.h"

namespace Pengine
{
	class PenComponentsBase
	{
	public:
		PenComponentsBase() = delete;

		PenComponentsBase(PenComponentsId id) : m_id(id) {}	

		virtual ~PenComponentsBase() = default;

		PenComponentsId getId() const;
	private :
		PenComponentsId m_id;
	};
}