#pragma once 

#include "PenResources/PenResourcesBase.h"

#include <Vector/Vector3/Vector3.h>

namespace Pengine::Resources
{
	class PenTextureBase;
	class PenShaderProgramBase;

	class PenMaterial final: public PenResourcesBase
	{
	public:
		PenMaterial() = default;
		PenMaterial(const PenObjectId id) : PenResourcesBase(id) {};
		PenMaterial(const PenMaterial& other) = default;
		PenMaterial(PenMaterial&& other) = default;
		~PenMaterial() final;

		PenMaterial& operator=(const PenMaterial& rhs) = default;
		PenMaterial& operator=(PenMaterial&& rhs) = default;

		static std::shared_ptr<PenMaterial> defaultMaterial();
		
		bool	loadResource(const std::string path) final;
		bool	createResource(const std::string penfilePath, const std::string sourcePath) final;
		bool	createResource(const std::string penfilePath, std::shared_ptr<PenTextureBase> tex);
		bool	createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgramBase> prog);
		bool	createResource(const std::string penfilePath, std::shared_ptr<PenTextureBase> tex, std::shared_ptr<PenShaderProgramBase> prog);

		void												setShaderProgram(std::shared_ptr<PenShaderProgramBase> prog);
		void												setTexture(std::shared_ptr<PenTextureBase> tex);
		_NODISCARD std::shared_ptr<PenShaderProgramBase>	getShaderProg();
		_NODISCARD std::shared_ptr<PenTextureBase>			getTexture();

		const PenMath::Vector3f&								getAmbient();
		const PenMath::Vector3f&								getDiffuse();
		const PenMath::Vector3f&								getSpecular();
		const float												getShininess();

	private:
		std::shared_ptr<PenTextureBase>			m_texture;
		std::shared_ptr<PenShaderProgramBase>	m_shader;

		PenMath::Vector3f m_ambient = { 1.0f, 0.5f, 0.31f };
		PenMath::Vector3f m_diffuse = { 1.0f, 0.5f, 0.31f };
		PenMath::Vector3f m_specular = { 0.5f, 0.5f, 0.5f };
		float m_shininess = 32.f;
	};
}
