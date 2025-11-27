#pragma once 

#include "PenResources/PenMaterial.h"



namespace Pengine::Resources
{
	template<typename ..._Texture>
	inline bool Pengine::Resources::PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgramBase> prog, _Texture ...texs)
	{
		std::ofstream outfile(penfilePath, std::ios::binary);

		PenCore::PenSerializer()->write(outfile, this->m_specular);
		PenCore::PenSerializer()->write(outfile, this->m_shininess);

		if (!prog)
		{
			std::cout << __FUNCTION__ "\t Material created with default shader program in it\n";
			this->m_shader = PenShaderProgramBase::defaultShaderProgram();
		}
		else
			this->m_shader = prog;

		PenCore::PenSerializer()->write(outfile, this->m_shader->getResourcePath());

		this->m_penfilePath = penfilePath;

		std::vector<std::string> texPaths;
		((texPaths.push_back(texs->getResourcePath())), ...);

		PenCore::PenSerializer()->write(outfile, texPaths);

		return true;
	}
}
