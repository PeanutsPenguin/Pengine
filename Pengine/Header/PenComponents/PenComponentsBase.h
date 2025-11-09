#pragma once 

#include "PengineDefine.h"

namespace Pengine::Components
{
	class PenComponentsBase
	{
	public:
		PenComponentsBase() = delete;

		PenComponentsBase(PenComponentsId id) : m_id(id) {}

		virtual void render() = 0;

		virtual ~PenComponentsBase() = default;

		PenComponentsId getId() const;
	private :
		PenComponentsId m_id;
	};
}