#pragma once 

#include "PenComponents/PenComponentBase.h"		//PenComponentBase

//Resources
#include "PenResources/PenModel.h"
#include "PenResources/PenMaterial/PenMaterial.h"

namespace Pengine::Components
{
	class PenRenderer : public PenComponentBase
	{
	public:

		constexpr static std::string_view ID = "PenRenderer";

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

		void registerProperty(PenPropertyManager* manager) override;
		bool serialize(std::ostream& out) final;
		void load(std::ifstream& infile) final;

	private:
		std::shared_ptr<Pengine::Resources::PenModel> m_model;
		std::shared_ptr<Pengine::Resources::PenMaterial> m_material;
	};
}