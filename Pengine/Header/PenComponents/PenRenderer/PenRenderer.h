#pragma once 

#include "PenComponents/PenComponentBase.h"
#include "PenResources/PenModel.h"
#include "PenResources/PenShaderProgramBase.h"

namespace Pengine::Components
{
	class PenRenderer : public PenComponentBase
	{
	public:

		~PenRenderer() override;
#pragma region Private
	private:
		std::shared_ptr<Pengine::Resources::PenModel> m_model;
		std::shared_ptr<Pengine::Resources::PenShaderProgramBase> m_shader;
#pragma endregion
	};
}