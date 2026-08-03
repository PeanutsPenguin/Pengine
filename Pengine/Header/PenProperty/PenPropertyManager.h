#pragma once 

#include <unordered_map>
#include "PenDefine/PengineDefine.h"
#include "PenProperty.h"

namespace Pengine
{
	/// <summary>
	/// WARNING: This file also include the "PenProperty" header
	/// </summary>
	class PenPropertyManager
	{
	public: 
		PenPropertyManager() = default;
		PenPropertyManager(const PenPropertyManager& other) = default;
		PenPropertyManager(PenPropertyManager&& other) = default;
		~PenPropertyManager();

		PenPropertyManager& operator=(const PenPropertyManager& rhs) = default;
		PenPropertyManager& operator=(PenPropertyManager&& rhs) = default;

		template<typename T>
		void addProperty(PengineIds id, const char* name, PenPropertyType type, T* data)
		{
			this->m_propertyArray[id].push_back(new PenProperty<T>(name, type, data));
		}

		std::vector<IPenProperty*>& getProperties(const PengineIds id);

	private:
		std::unordered_map<PengineIds, std::vector<IPenProperty*>> m_propertyArray;
	};
}