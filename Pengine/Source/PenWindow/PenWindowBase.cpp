#include "PenWindow/PenWindowBase.h"

#include "PenScene/PenScene.h"

using namespace Pengine;

PenWindowBase::PenWindowBase()
{
    this->m_windowScene = std::make_unique<PenScene>();
}

PenWindowBase::~PenWindowBase()
{
    if (!this->m_windowScene)
    {
        this->m_windowScene.reset();
        this->m_windowScene = nullptr;
    }
}

std::unique_ptr<PenScene>& PenWindowBase::getScene()
{
    return this->m_windowScene;
}