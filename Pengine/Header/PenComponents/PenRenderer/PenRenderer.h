#pragma once 

#include "PenComponents/PenComponentBase.h"		//PenComponentBase

//Resources
#include "PenResources/PenModel.h"
#include "PenResources/PenMaterial.h"

namespace Pengine::Components
{
	class PenRenderer : public PenComponentBase
	{
	public:
		PenRenderer();
		PenRenderer(const PenRenderer& other) = default;
		PenRenderer(PenRenderer&& other) = default;
		~PenRenderer() final = default;

		PenRenderer& operator=(const PenRenderer& rhs) = default;
		PenRenderer& operator=(PenRenderer&& rhs) = default;

		void setModel(std::shared_ptr<Pengine::Resources::PenModel> model);
		void setMaterial(std::shared_ptr<Pengine::Resources::PenMaterial> mat);

		std::shared_ptr<Pengine::Resources::PenMaterial> getMaterial();
		
		void render();

	private:
		std::shared_ptr<Pengine::Resources::PenModel> m_model;
		std::shared_ptr<Pengine::Resources::PenMaterial> m_material;
	};
}