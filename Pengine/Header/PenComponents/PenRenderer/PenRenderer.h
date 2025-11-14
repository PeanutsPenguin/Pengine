#pragma once 

#include "PenComponents/PenComponentsBase.h"
#include "PenResources/PenModel.h"
#include "PenResources/PenShaderProgramBase.h"

namespace Pengine::Components
{
	class PenRenderer
	{
	public:
//#pragma region Public
//		PenRenderer() = default;
//
//		PenRenderer(const PenComponentsId& id) : PenComponentsBase(id) {};
//		
//		~PenRenderer() override;
//
//		void setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog);
//
//		void setModel(std::shared_ptr<Pengine::Resources::PenModel> model);
//
//		void render() override;
//#pragma endregion

#pragma region Private
	private:
		std::shared_ptr<Pengine::Resources::PenModel> m_model;
		std::shared_ptr<Pengine::Resources::PenShaderProgramBase> m_shader;
#pragma endregion
	};
}