#pragma once 

#include "PengineDefine.h"
#include "PenSystemBase.h"

#include <memory>
#include <unordered_map>

namespace Pengine::System
{
	class PenSystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> registerSystem();

		template<typename T>
		void setSignature(PenComponentSignature signature);

		void PenObjectDestroyed(PenComponentsId entity);

		void PenObjectSignatureChanged(PenObjectId entity, PenComponentSignature entitySignature);

	private:
		std::unordered_map<const char*, PenComponentSignature> m_PenComponentSignature;		//Map to handle const char* to Signature
		std::unordered_map<const char*, std::shared_ptr<PenSystemBase>> m_PenSystems;			//Map to handle const char* to System
	};
}	