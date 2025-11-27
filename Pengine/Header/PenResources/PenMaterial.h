#pragma once 

#include "PenResources/PenResourcesBase.h"
#include "PenResources/PenShaderProgramBase.h"
#include "PenCore/PenCore.h"                                        //PenCore
#include "PenSerializer/PenSerializer.h"                            //PenSerializer

#include <Vector/Vector3/Vector3.h>

//std
#include <iostream>
#include <fstream>

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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="...texs">DO NOT SEND SOMETHING ELSE THAN TEXTURE PTR</param>
		template<typename... _Texture>
		bool	createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgramBase> prog, _Texture... texs);

		void	setShaderProgram(std::shared_ptr<PenShaderProgramBase> prog);
		void	addTexture(std::shared_ptr<PenTextureBase> tex);
		void	setSpecular(const PenMath::Vector3f& spec);
		void	setShininess(const float shininess);

		const std::shared_ptr<PenShaderProgramBase>&					getShaderProg();
		const std::vector<std::shared_ptr<PenTextureBase>>&				getTextures()	const;
		const PenMath::Vector3f&										getSpecular()	const;
		const float														getShininess()	const;

	private:
		void generateTextures(const std::vector<std::string> texPath);

		std::vector<std::shared_ptr<PenTextureBase>>			m_texture;
		std::shared_ptr<PenShaderProgramBase>					m_shader;

		PenMath::Vector3f m_specular = PenMath::Vector3f{ 0.5f, 0.5f, 0.5f };
		float m_shininess = 64.f;
	};
}
#include "PenMaterial.hpp"
