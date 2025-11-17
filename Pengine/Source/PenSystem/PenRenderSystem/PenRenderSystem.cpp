#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenOctopus/PenOctopus.h"

#include "PenCore/PenCore.h"

using namespace Pengine::System;

PenRendererSystem::~PenRendererSystem()
{
}

void PenRendererSystem::render()
{
	for(PenObjectId objId : m_PenObject)
	{
		Components::PenRenderer& renderComp = PenCore::PenOctopus()->getComponent<Components::PenRenderer>(objId);

		if(renderComp.IsState(Components::PenComponentState::ENABLE))
			renderComp.render();
	}
}