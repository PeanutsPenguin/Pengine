#pragma once 

#include "PenComponents/PenComponentsBase.h"
#include "PenResources/PenModel.h"
#include "PenResources/PenShaderProgramBase.h"

namespace Pengine::Components
{
	class PenRenderer : public PenComponentsBase
	{
	public:
		PenRenderer() = default;

		PenRenderer(const PenComponentsId& id) : PenComponentsBase(id) {};
		
		~PenRenderer() override = default;

		void setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog);

		void setModel(std::shared_ptr<Pengine::Resources::PenModel> model);

		void render() override;
	private:
		std::shared_ptr<Pengine::Resources::PenModel> m_model;
		std::shared_ptr<Pengine::Resources::PenShaderProgramBase> m_shader;
	};
}