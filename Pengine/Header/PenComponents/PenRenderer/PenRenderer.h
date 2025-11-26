#pragma once 

#include "PenComponents/PenComponentBase.h"		//PenComponentBase

//Resources
#include "PenResources/PenModel.h"
#include "PenResources/PenMaterial.h"

namespace Pengine::Components
{
	class PenRenderer : public PenComponentBase
	{
#pragma region Public
	public:
		PenRenderer();

		~PenRenderer() override = default;

		void setModel(std::shared_ptr<Pengine::Resources::PenModel> model);

		void setMaterial(std::shared_ptr<Pengine::Resources::PenMaterial> mat);

		void render();

		std::shared_ptr<Pengine::Resources::PenMaterial> getMaterial();
#pragma endregion
#pragma region Private
	private:
		std::shared_ptr<Pengine::Resources::PenModel> m_model;
		std::shared_ptr<Pengine::Resources::PenMaterial> m_material;
#pragma endregion
	};
}