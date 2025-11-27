#include "PenResources/PenMaterial.h"

#include "PenResources/PenResourcesManager.h"                       //PenResourceManager
#include "PenResources/OpenGl/Private_PenGLTextures.h"              //PenTexture
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"         //PenShaderProgram

using namespace Pengine::Resources;

PenMaterial::~PenMaterial()
{
    std::cout << __FUNCTION__ ": Destryoing with id : " << this->getId() << std::endl;
}

std::shared_ptr<PenMaterial> PenMaterial::defaultMaterial()
{
    return PenCore::ResourcesManager()->loadResourceFromFile<PenMaterial>("Material/DefaultMaterial.penfile");
}

#pragma region Resource
bool PenMaterial::loadResource(const std::string path)
{
    std::cout << __FUNCTION__ "\tLoading Material :" << path << std::endl;

    //Create variables 
    std::vector<std::string> texPaths;
    std::string shaderPath;

    std::ifstream infile(path, std::ios::binary);
    PenCore::PenSerializer()->read(infile, this->m_specular);
    PenCore::PenSerializer()->read(infile, this->m_shininess);
    PenCore::PenSerializer()->read(infile, shaderPath);
    PenCore::PenSerializer()->read(infile, texPaths);
    infile.close();

    std::shared_ptr<PenShaderProgramBase> shader = nullptr;

    if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
        shader = PenCore::ResourcesManager()->loadResourceFromFile<PenGLShaderProgram>(shaderPath.c_str());

    if (!shader)
    {
        std::cout << __FUNCTION__ "\t Material loaded with default texture in it\n";
        this->m_shader = PenShaderProgramBase::defaultShaderProgram();
    }
    else
        this->m_shader = shader;

    this->m_penfilePath = path;
    
    this->generateTextures(texPaths);

    return true;
}

bool PenMaterial::createResource(const std::string penfilePath, const std::string sourcePath)
{
    std::cout << __FUNCTION__ "\t Can't create a material form a source file for now\n";

    return false;
}

bool PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenTextureBase> tex)
{
    return this->createResource(penfilePath, nullptr, tex);
}

bool PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgramBase> prog)
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

    return true;
}
#pragma endregion

#pragma region Getter and Setter
void PenMaterial::setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> prog)
{
    if (prog)
        this->m_shader = prog;
    else
        this->m_shader = PenShaderProgramBase::defaultShaderProgram();
}

void PenMaterial::addTexture(std::shared_ptr<PenTextureBase> tex)
{
    if (tex)
        this->m_texture.push_back(tex);
}

void PenMaterial::setSpecular(const PenMath::Vector3f& spec)
{
    this->m_specular = spec;
}

void PenMaterial::setShininess(const float shininess)
{
    this->m_shininess = shininess;
}


const std::shared_ptr<PenShaderProgramBase>& PenMaterial::getShaderProg()
{
    if(!this->m_shader)
    {
        std::cout << __FUNCTION__ "\t Shader program of material : " << this->getId() << " has not been found, replace it with default shader program\n";
        this->setShaderProgram(nullptr);
    }

    return this->m_shader;
}

const std::vector<std::shared_ptr<PenTextureBase>>& PenMaterial::getTextures() const
{
    return this->m_texture;
}

const PenMath::Vector3f& PenMaterial::getSpecular() const
{
    return this->m_specular;
}

const float PenMaterial::getShininess() const
{
    return this->m_shininess;
}
void PenMaterial::generateTextures(const std::vector<std::string> texPath)
{
    if (texPath.empty())
    {
        this->m_texture.push_back(PenTextureBase::defaultTexture());
        return;
    }

    std::shared_ptr<PenTextureBase> tex = nullptr;

    for (std::string path : texPath)
    {
        if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
            tex = PenCore::ResourcesManager()->loadResourceFromFile<PenGLTexture>(path.c_str());

        if (!tex)
        {
            tex = nullptr;
            continue;
        }

        this->m_texture.push_back(tex);
    }
}
#pragma endregion
