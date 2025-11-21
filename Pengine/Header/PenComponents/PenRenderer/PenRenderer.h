#pragma once 

#include "PenComponents/PenComponentBase.h"
#include "PenResources/PenModel.h"
#include "PenResources/PenShaderProgramBase.h"

namespace Pengine::Components
{
	class PenRenderer : public PenComponentBase
	{
#pragma region Public
	public:
		PenRenderer(); 

		~PenRenderer() override;

		void setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog);

		void setModel(std::shared_ptr<Pengine::Resources::PenModel> model);

		void render();

		std::shared_ptr<Pengine::Resources::PenShaderProgramBase> getShaderProgram();
#pragma endregion
#pragma region Private
	private:
		std::shared_ptr<Pengine::Resources::PenModel> m_model;
		std::shared_ptr<Pengine::Resources::PenShaderProgramBase> m_shader;
#pragma endregion
	};
}