#pragma once 

#include "PenResources/PenResourcesBase.h"
#include "PenCore/PenCore.h"                                        //PenCore
#include "PenSerializer/PenSerializer.h"                            //PenSerializer
#include "PenMaterialProperty.h"
#include "PenColor/PenColor.h"

#include <Vector/Vector3/Vector3.h>

//std
#include <iostream>
#include <fstream>

namespace Pengine::Resources
{
	class PenTexture;
	class PenTexture;
	class PenShaderProgram;

	class PenMaterial final: public PenResourceBase
	{
	public:
		PenMaterial() = default;
		PenMaterial(const PenObjectId id);
		PenMaterial(const PenMaterial& other) = default;
		PenMaterial(PenMaterial&& other) = default;
		~PenMaterial() final;

		PenMaterial& operator=(const PenMaterial& rhs) = default;
		PenMaterial& operator=(PenMaterial&& rhs) = default;

		static std::shared_ptr<PenMaterial> defaultMaterial();
		
		//Resource
		bool	loadResource(const std::string path) final;
		bool	createResource(const std::string penfilePath, const std::string sourcePath) final;
		bool	createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgram> prog);
		bool	createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgram> prog, std::shared_ptr<PenTexture> tex);
		bool	save() override;

		void shaderActivation();
		void GLShaderActivation();

		void quickSave();

		//Shader Program
		void	setShaderProgram(std::shared_ptr<PenShaderProgram> prog);

		//Normal
		void	setNormal(std::shared_ptr<PenTexture> ptr);
		void	saveNormal(std::ofstream& outfile);
		void	loadNormal(std::ifstream& infile);
		void	activateNormal();

		//Albedo
		void	setAlbedo(const PenMath::Vector3f& spec);
		void	setAlbedo(const PenColor& albedo);
		void	setAlbedo(std::shared_ptr<PenTexture> ptr);
		void    setAlbedo(const PenMaterialProperty<PenMath::Vector3f>& prop);
		void	loadAlbedo(std::ifstream& infile);
		void	activateAlbedo();

		//Metallic
		void	setMetallic(const float shininess);
		void	setMetallic(std::shared_ptr<PenTexture> ptr);
		void	setMetallic(const PenMaterialProperty<float>& prop);
		void	loadMetallic(std::ifstream& infile);
		void	activateMetallic();

		//Roughness
		void	setRoughness(const float roughness);
		void	setRoughness(std::shared_ptr<PenTexture> ptr);
		void	setRoughness(const PenMaterialProperty<float>& prop);
		void	loadRoughness(std::ifstream& infile);
		void	activateRoughness();

		//AmbientOclusion
		void	setAmbientOcclusion(const float ao);
		void	setAmbientOcclusion(std::shared_ptr<PenTexture> ptr);
		void	setAmbientOcclusion(const PenMaterialProperty<float>& prop);
		void	loadAmbientOcclusion(std::ifstream& infile);
		void	activateAmbientOcclusion();

		//Getter
		const std::shared_ptr<PenShaderProgram>&				getShaderProg();
		const std::shared_ptr<PenTexture>&						getNormal();
		PenMaterialProperty<PenMath::Vector3f>&					getAlbedo();
		PenMaterialProperty<float>&								getMetallic();
		PenMaterialProperty<float>&								getRoughness();
		PenMaterialProperty<float>& 							getAmbientOcclusion();

	private:
		PenMaterialProperty<PenMath::Vector3f>					m_albedo;
		PenMaterialProperty<float>								m_metallic;
		PenMaterialProperty<float>								m_roughness;
		PenMaterialProperty<float>								m_ambientOcclusion;

		std::shared_ptr<PenShaderProgram>					m_shader;
		std::shared_ptr<PenTexture>							m_normal;
	};
}
