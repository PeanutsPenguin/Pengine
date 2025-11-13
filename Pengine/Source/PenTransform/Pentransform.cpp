#include "PenTransform/Pentransform.h"

using namespace Pengine;

const PenMath::Transform& PenTransform::getLocalTransform()
{
	return this->m_localTranform;
}

const PenMath::Transform& PenTransform::getGobalTransform()
{
	return this->m_globalTransform;
}
