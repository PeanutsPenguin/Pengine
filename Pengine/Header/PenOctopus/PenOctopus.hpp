#pragma once 

#include "PenOctopus/PenOctopus.h"


namespace Pengine
{
	template<typename T>
	inline void PenOctopus::registerComponent()
	{
		m_PenComponentManager->registerComponent<T>();
	}

	template<typename T>
	inline void PenOctopus::addComponent(PenObjectId obj, T component)
	{
		this->m_PenComponentManager->addComponent<T>(obj, component);

		PenComponentSignature signature = m_PenObjectManager->getSignature(obj);
		signature.set(m_PenComponentManager->getComponentType<T>(), true);
		m_PenObjectManager->setSignature(obj, signature);

		if(this->m_mainScene->isObjectInScene(obj))
			m_PenSystemManager->PenObjectSignatureChanged(obj, signature);
	}

	template<typename T>
	inline void PenOctopus::removeComponent(PenObjectId obj)
	{
		m_PenComponentManager->removeComponent<T>(obj);

		PenComponentSignature signature = m_PenObjectManager->getSignature(obj);
		signature.set(m_PenComponentManager->getComponentType<T>(), false);
		m_PenObjectManager->setSignature(obj, signature);

		if (this->m_mainScene->isObjectInScene(obj))
			m_PenSystemManager->PenObjectSignatureChanged(obj, signature);
	}

#pragma region Getter
	template<typename T>
	inline T& PenOctopus::getComponent(PenObjectId obj)
	{
		return m_PenComponentManager->getComponent<T>(obj);
	}

	template<typename T>
	inline PenComponentType PenOctopus::getComponentType()
	{
		return m_PenComponentManager->getComponentType<T>();
	}

	template<typename T>
	inline std::shared_ptr<T> PenOctopus::getSystem()
	{
		return this->m_PenSystemManager->getSystem<T>();
	}
#pragma endregion

	template<typename T>
	inline std::shared_ptr<T> PenOctopus::registerSystem()
	{
		return m_PenSystemManager->registerSystem<T>();
	}

	template<typename T>
	inline void PenOctopus::setSystemSignature(PenComponentSignature signature)
	{
		this->m_PenSystemManager->setSignature<T>(signature);
	}
}
