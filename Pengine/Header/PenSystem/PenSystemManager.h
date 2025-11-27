#pragma once 

#include "PenSystemBase.h"

//std
#include <memory>
#include <unordered_map>

namespace Pengine::System
{
	class PenSystemManager
	{
	public:
		PenSystemManager() = default;
		PenSystemManager(const PenSystemManager& other) = default;
		PenSystemManager(PenSystemManager&& other) = default;
		~PenSystemManager() = default;

		PenSystemManager& operator=(const PenSystemManager& rhs) = default;
		PenSystemManager& operator=(PenSystemManager&& rhs) = default;

		template<typename T>
		std::shared_ptr<T> registerSystem();

		template<typename T>
		_Ret_maybenull_ std::shared_ptr<T> getSystem();

		template<typename T>
		void setSignature(PenComponentSignature signature);

		void PenObjectDestroyed(PenComponentsId entity);
		void PenObjectSignatureChanged(PenObjectId entity, PenComponentSignature entitySignature);

		void onEntityInserted(const PenObjectId newObj);
		void onEntityDestroyed(const PenObjectId newObj);

		void updateAllSystem(double dt);

	private:
		std::unordered_map<const char*, PenComponentSignature>			m_PenComponentSignature;	//Map to handle const char* to Signature
		std::unordered_map<const char*, std::shared_ptr<PenSystemBase>> m_PenSystems;				//Map to handle const char* to System
	};
}	

#include "PenSystem/PenSystemManager.hpp"