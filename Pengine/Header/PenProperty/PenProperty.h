#pragma once 

#include "PenStructsAndEnum/PenPropertyType.h"

namespace Pengine
{
	class IPenProperty
	{
	public:
		IPenProperty() = default;
		IPenProperty(const IPenProperty& other) = default;
		IPenProperty(IPenProperty&& other) = default;
		virtual ~IPenProperty() = default;

		IPenProperty& operator=(const IPenProperty& rhs) = default;
		IPenProperty& operator=(IPenProperty&& rhs) = default;

		const char*			getName() { return this->m_name; }
		PenPropertyType		getType() { return this->m_type; }
		virtual void*		getData() = 0;
	protected:
		PenPropertyType m_type;
		const char* m_name;
	};


	template <typename T>
	class PenProperty : public IPenProperty 
	{
	public:
		PenProperty(const char* propName, PenPropertyType propType, T* data)
		{
			m_name = propName;
			m_type = propType;
			m_data = data;
		}

		void* getData() override 
		{ 
			return static_cast<void*>(dataPointer); 
		}

	private:
		T* m_data;
	};
}