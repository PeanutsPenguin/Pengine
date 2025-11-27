#include "PenResources/PenMaterial.h"

#include "PenResources/OpenGl/Private_PenGLTextures.h"  //PenTexture
#include "PenCore/PenCore.h"                            //PenCore
#include "PenSerializer/PenSerializer.h"                //PenSerializer
#include "PenResources/PenResourcesManager.h"           //PenResourceManager
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"          //PenShaderProgram

//std
#include <iostream>
#include <fstream>

using namespace Pengine::Resources;

std::shared_ptr<PenMaterial> PenMaterial::defaultMaterial()
{
    return PenCore::ResourcesManager()->loadResourceFromFile<PenMaterial>("Material/DefaultMaterial.penfile");
}


bool PenMaterial::loadResource(const std::string path)
{
    std::cout << __FUNCTION__ "\tLoading Material :" << path << std::endl;

    //Create variables 
    std::string texPath;
    std::string shaderPath;

    std::ifstream infile(path, std::ios::binary);
    PenCore::PenSerializer()->read(infile, texPath);
    PenCore::PenSerializer()->read(infile, shaderPath);
    infile.close();

    std::shared_ptr<PenTextureBase> tex = nullptr;

    if(PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
        tex = PenCore::ResourcesManager()->loadResourceFromFile<PenGLTexture>(texPath.c_str());

    if (!tex)
    {
        std::cout << __FUNCTION__ "\t Material loaded with default texture in it\n";
        this->m_texture = PenTextureBase::defaultTexture();
    }
    else
        this->m_texture = tex;

    std::shared_ptr<PenShaderProgramBase> shader = nullptr;

    if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
        shader = PenCore::ResourcesManager()->loadResourceFromFile<PenGLShaderProgram>(shaderPath.c_str());

    if (!tex)
    {
        std::cout << __FUNCTION__ "\t Material loaded with default texture in it\n";
        this->m_shader = PenShaderProgramBase::defaultShaderProgram();
    }
    else
        this->m_shader = shader;

    this->m_penfilePath = path;

    return true;
}

bool PenMaterial::createResource(const std::string penfilePath, const std::string sourcePath)
{
    std::cout << __FUNCTION__ "\t Not ready yet.\n";

    return createResource(penfilePath, nullptr, nullptr);
}

bool PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenTextureBase> tex)
{
    return this->createResource(penfilePath, tex, nullptr);
}

bool PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgramBase> tex)
{
    return this->createResource(penfilePath, nullptr, tex);
}

bool PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenTextureBase> tex,
                                                          std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog)
{
    std::ofstream outfile(penfilePath, std::ios::binary);

    if (!tex)
    {
        std::cout << __FUNCTION__ "\t Material created with default texture in it\n";
        this->m_texture = PenTextureBase::defaultTexture();
    }
    else
        this->m_texture = tex;

    PenCore::PenSerializer()->write(outfile, this->m_texture->getResourcePath());

    if (!prog)
    {
        std::cout << __FUNCTION__ "\t Material created with default shader program in it\n";
        this->m_shader = PenShaderProgramBase::defaultShaderProgram();
    }
    else
        this->m_shader = prog;

    PenCore::PenSerializer()->write(outfile, this->m_shader->getResourcePath());

    outfile.close();

    this->m_penfilePath = penfilePath;

    return true;
}

void PenMaterial::setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog)
{
    if (prog)
        this->m_shader = prog;
    else
        this->m_shader = PenShaderProgramBase::defaultShaderProgram();
}

void PenMaterial::setTexture(std::shared_ptr<PenTextureBase> tex)
{
    if (tex)
        this->m_texture = tex;
    else
        this->m_texture = PenTextureBase::defaultTexture();
}

std::shared_ptr<PenShaderProgramBase> PenMaterial::getShaderProg()
{
    return this->m_shader;
}

std::shared_ptr<PenTextureBase> Pengine::Resources::PenMaterial::getTexture()
{
    return this->m_texture;
}
