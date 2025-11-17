#include "PenWindow/PenWindowBase.h"

//System
#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

using namespace Pengine;

PenWindowBase::~PenWindowBase()
{
    if (this->m_renderSystem)
    {
        this->m_renderSystem.reset();
        this->m_renderSystem = nullptr;
    }
}

void PenWindowBase::render()
{
    if(this->m_renderSystem)
        this->m_renderSystem->render();
}

void PenWindowBase::setRenderSystem(std::shared_ptr<System::PenRendererSystem> system)
{
    this->m_renderSystem = system;
}
