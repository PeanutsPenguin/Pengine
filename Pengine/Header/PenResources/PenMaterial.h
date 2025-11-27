#pragma once 

#include "PenResources/PenResourcesBase.h"

namespace Pengine::Resources
{
	class PenTextureBase;
	class PenShaderProgramBase;

	class PenMaterial : public PenResourcesBase
	{
#pragma region Pubilic
	public:
		PenMaterial() = default;

		PenMaterial(const PenObjectId id) : PenResourcesBase(id) {};

		PenMaterial(const PenMaterial& other) = default;
		PenMaterial(PenMaterial&& other) = default;
		~PenMaterial() override = default;

		PenMaterial& operator=(const PenMaterial& rhs) = default;
		PenMaterial& operator=(PenMaterial&& rhs) = default;

		static std::shared_ptr<PenMaterial> defaultMaterial();

		bool loadResource(const std::string path) override;

		bool createResource(const std::string penfilePath, const std::string sourcePath) override;

		bool createResource(const std::string penfilePath, std::shared_ptr<PenTextureBase> tex);

		bool createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgramBase> prog);

		bool createResource(const std::string penfilePath, std::shared_ptr<PenTextureBase> tex,
													 std::shared_ptr<PenShaderProgramBase> prog);

		void setShaderProgram(std::shared_ptr<PenShaderProgramBase> prog);

		void setTexture(std::shared_ptr<PenTextureBase> tex);

		_NODISCARD std::shared_ptr<PenShaderProgramBase> getShaderProg();

		_NODISCARD std::shared_ptr<PenTextureBase> getTexture();
#pragma endregion

#pragma region Private
	private:
		std::shared_ptr<PenTextureBase> m_texture;
		std::shared_ptr<PenShaderProgramBase> m_shader;
#pragma endregion
	};
}
