#pragma once 

#include "PengineDefine.h"

namespace Pengine::Components
{
	/// <summary>
	/// Base Class for all components, containes a defined ID
	/// </summary>
	class PenComponentsBase
	{
	public:
		PenComponentsBase() = delete;

		PenComponentsBase(PenComponentsId id) : m_id(id) {}

		virtual ~PenComponentsBase() = default;

		virtual void render() = 0;

		//TODO : const char* getTypename();

		PenComponentsId getId() const;
	private :
		PenComponentsId m_id;
	};
}