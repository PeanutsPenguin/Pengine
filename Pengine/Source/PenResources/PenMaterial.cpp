#include "PenResources/PenMaterial/PenMaterial.h"

#include "PenResources/PenResourcesManager.h"                       //PenResourceManager
#include "PenResources/PenTexture.h"                                //PenTexture
#include "PenResources/PenShaderProgram.h"                          //PenShaderProgram

#include "PenBuffer/PenTextureBuffer.h"


using namespace Pengine::Resources;

#pragma region Constructors and destructor
PenMaterial::PenMaterial(const PenObjectId id) : PenResourceBase(id)
{
    this->p_type = E_MATERIAL;
    this->m_albedo = PenMaterialProperty<PenMath::Vector3f>(nullptr, { 1, 1, 1 });
    this->m_metallic = PenMaterialProperty<float>(nullptr, 0);
    this->m_roughness = PenMaterialProperty<float>(nullptr, .6f);
    this->m_ambientOcclusion = PenMaterialProperty<float>(nullptr, 1.f);
}

PenMaterial::~PenMaterial()
{
    std::cout << __FUNCTION__ ": Destryoing with id : " << this->getId() << std::endl;
}
#pragma endregion 

std::shared_ptr<PenMaterial> PenMaterial::defaultMaterial()
{
    return PenCore::ResourcesManager()->loadResourceFromFile<PenMaterial>("Material/DefaultMaterial.penfile");
}

#pragma region Resource
bool PenMaterial::loadResource(const std::string path)
{
    std::cout << __FUNCTION__ "\tLoading Material :" << path << std::endl;

    std::ifstream infile(path, std::ios::binary);

    int type = 0;
    PenCore::Serializer()->read(infile, type);

    //Create variables 
    std::string shaderPath;

    PenCore::Serializer()->read(infile, shaderPath);

    std::string tempPath;

    this->loadAlbedo(infile);
    this->loadMetallic(infile);
    this->loadRoughness(infile);
    this->loadAmbientOcclusion(infile);
    this->loadNormal(infile);

    infile.close();

    std::shared_ptr<PenShaderProgram> shader = nullptr;

    if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
        shader = PenCore::ResourcesManager()->loadResourceFromFile<PenShaderProgram>(shaderPath.c_str());

    if (!shader)
    {
        std::cout << __FUNCTION__ "\t Material loaded with default texture in it\n";
        this->m_shader = PenShaderProgram::defaultShaderProgram();
    }
    else
        this->m_shader = shader;

    this->m_penfilePath = path;

    return true;
}

bool PenMaterial::createResource(const std::string penfilePath, const std::string sourcePath)
{
    std::cout << __FUNCTION__ "\t Can't create a material form a source file for now\n";

    return false;
}

bool PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgram> prog)
{
    return this->createResource(penfilePath, prog, nullptr);
}

bool PenMaterial::createResource(const std::string penfilePath, std::shared_ptr<PenShaderProgram> prog, std::shared_ptr<PenTexture> tex)
{
    std::ofstream outfile(penfilePath, std::ios::binary);

    if (!prog)
    {
        std::cout << __FUNCTION__ "\t Material created with default shader program in it\n";
        this->m_shader = PenShaderProgram::defaultShaderProgram();
    }
    else
        this->m_shader = prog;

    if (!tex)
        std::cout << __FUNCTION__ "\t Given texture for the material creation is null\n";
    else
        this->m_albedo.texture = tex;

    PenCore::Serializer()->write(outfile, (int)this->p_type);
    PenCore::Serializer()->write(outfile, this->m_shader->getResourcePath());

    this->m_albedo.serializeProperty(outfile);
    this->m_metallic.serializeProperty(outfile);
    this->m_roughness.serializeProperty(outfile);
    this->m_ambientOcclusion.serializeProperty(outfile);

    this->saveNormal(outfile);

    this->m_penfilePath = penfilePath;

    return true;
}

void PenMaterial::quickSave()
{
    std::ofstream outfile(this->m_penfilePath, std::ios::binary);

    PenCore::Serializer()->write(outfile, (int)this->p_type);
    PenCore::Serializer()->write(outfile, this->m_shader->getResourcePath());
    this->m_albedo.serializeProperty(outfile);
    this->m_metallic.serializeProperty(outfile);
    this->m_roughness.serializeProperty(outfile);
    this->m_ambientOcclusion.serializeProperty(outfile);

    this->saveNormal(outfile);
}
#pragma endregion

#pragma region Shader program
void PenMaterial::setShaderProgram(std::shared_ptr<Pengine::Resources::PenShaderProgram> prog)
{
    if (prog)
        this->m_shader = prog;
    else
        this->m_shader = PenShaderProgram::defaultShaderProgram();
}

const std::shared_ptr<PenShaderProgram>& PenMaterial::getShaderProg()
{
    if (!this->m_shader)
    {
        std::cout << __FUNCTION__ "\t Shader program of material : " << this->getId() << " has not been found, replace it with default shader program\n";
        this->setShaderProgram(nullptr);
    }

    return this->m_shader;
}
#pragma endregion

#pragma region Normal
void PenMaterial::setNormal(std::shared_ptr<Pengine::Resources::PenTexture> ptr)
{
    if (ptr)
        this->m_normal = ptr;
}

const std::shared_ptr<PenTexture>& PenMaterial::getNormal()
{
    if (!this->m_normal)
    {
        std::cout << __FUNCTION__ "\t Normal map of material : " << this->getId() << " is null\n";
        return nullptr;
    }

    return this->m_normal;
}

void PenMaterial::loadNormal(std::ifstream& infile)
{
    std::string tempPath;

    PenCore::Serializer()->read(infile, tempPath);

    if (!tempPath.empty())
    {
        if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
            this->m_normal = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>(tempPath.c_str());
    }
}

void PenMaterial::activateNormal()
{
	if (this->m_normal)
	{
		std::shared_ptr<PenTexture> ptr = std::dynamic_pointer_cast<PenTexture>(this->m_normal);
		ptr->dataPtr()->activate(3);
	}
	else
        PenTexture::noTexture()->dataPtr()->activate(3);

	this->m_shader->setUniform("mat.normalMap", 3);
}

void PenMaterial::saveNormal(std::ofstream& outfile)
{
	if (this->m_normal)
		PenCore::Serializer()->write(outfile, this->m_normal->getResourcePath());
	else
		PenCore::Serializer()->write(outfile, std::string(""));
}
#pragma endregion

#pragma region Albedo
void PenMaterial::setAlbedo(const PenMath::Vector3f& albedo)
{
    this->m_albedo.defaultValue = albedo;
}

void PenMaterial::setAlbedo(std::shared_ptr<PenTexture> ptr)
{
    this->m_albedo.texture = ptr;
}

void PenMaterial::setAlbedo(const PenMaterialProperty<PenMath::Vector3f>& prop)
{
    this->m_albedo = prop;
}

const PenMaterialProperty<PenMath::Vector3f>& PenMaterial::getAlbedo() const
{
    return this->m_albedo;
}

void PenMaterial::loadAlbedo(std::ifstream& infile)
{
    std::string tempPath;

    PenCore::Serializer()->read(infile, tempPath);

    if (!tempPath.empty())
    {
        if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
            this->m_albedo.texture = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>(tempPath.c_str());
    }

    PenCore::Serializer()->read(infile, this->m_albedo.defaultValue);
}

void PenMaterial::activateAlbedo()
{
    if (this->m_albedo.texture)
    {
        std::shared_ptr<PenTexture> ptr = std::dynamic_pointer_cast<PenTexture>(this->m_albedo.texture);
        ptr->dataPtr()->activate(0);
    }
    else
    {
        PenTexture::noTexture()->dataPtr()->activate(0);
    }

    this->m_shader->setUniform("mat.albedoMap", 0);
    this->m_shader->setUniform("mat.albedo", this->m_albedo.defaultValue);
}
#pragma endregion

#pragma region Metallic
void PenMaterial::setMetallic(const float metallic)
{
    this->m_metallic.defaultValue = metallic;
}

void PenMaterial::setMetallic(std::shared_ptr<PenTexture> ptr)
{
    this->m_metallic.texture = ptr;
}

void PenMaterial::setMetallic(const PenMaterialProperty<float>& prop)
{
    this->m_metallic = prop;
}

const PenMaterialProperty<float>& PenMaterial::getMetallic() const
{
    return this->m_metallic;
}

void PenMaterial::loadMetallic(std::ifstream& infile)
{
    std::string tempPath;

    PenCore::Serializer()->read(infile, tempPath);

    if (!tempPath.empty())
    {
        if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
            this->m_metallic.texture = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>(tempPath.c_str());
    }

    PenCore::Serializer()->read(infile, this->m_metallic.defaultValue);
}

void PenMaterial::activateMetallic()
{
    if (this->m_metallic.texture)
    {
        std::shared_ptr<PenTexture> ptr = std::dynamic_pointer_cast<PenTexture>(this->m_metallic.texture);
        ptr->dataPtr()->activate(1);
    }
    else
    {
        PenTexture::noTexture()->dataPtr()->activate(1);
    }

    this->m_shader->setUniform("mat.metallicMap", 1);
    this->m_shader->setUniform("mat.metallic", this->m_metallic.defaultValue);
}

#pragma endregion

#pragma region Roughness
void PenMaterial::setRoughness(const float rough)
{
    this->m_roughness.defaultValue = rough;
}

void PenMaterial::setRoughness(std::shared_ptr<PenTexture> ptr)
{
    this->m_roughness.texture = ptr;
}

void PenMaterial::setRoughness(const PenMaterialProperty<float>& prop)
{
    this->m_roughness = prop;
}

const PenMaterialProperty<float>& PenMaterial::getRoughness() const
{
    return this->m_roughness;
}

void PenMaterial::loadRoughness(std::ifstream& infile)
{
    std::string tempPath;

    PenCore::Serializer()->read(infile, tempPath);

    if (!tempPath.empty())
    {
        if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
            this->m_roughness.texture = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>(tempPath.c_str());
    }

    PenCore::Serializer()->read(infile, this->m_roughness.defaultValue);
}

void PenMaterial::activateRoughness()
{
    if (this->m_roughness.texture)
    {
        std::shared_ptr<PenTexture> ptr = std::dynamic_pointer_cast<PenTexture>(this->m_roughness.texture);
        ptr->dataPtr()->activate(2);
    }
    else
    {
        PenTexture::noTexture()->dataPtr()->activate(2);
    }

    this->m_shader->setUniform("mat.roughnessMap", 2);
    this->m_shader->setUniform("mat.roughness", this->m_roughness.defaultValue);
}
#pragma endregion

#pragma region Ambient occlusion
void PenMaterial::setAmbientOcclusion(const float ao)
{
    this->m_ambientOcclusion.defaultValue = ao;
}

void PenMaterial::setAmbientOcclusion(std::shared_ptr<PenTexture> ptr)
{
    this->m_ambientOcclusion.texture = ptr;
}

void PenMaterial::setAmbientOcclusion(const PenMaterialProperty<float>& prop)
{
    this->m_ambientOcclusion = prop;
}

const PenMaterialProperty<float>& PenMaterial::getAmbientOcclusion() const
{
    return this->m_ambientOcclusion;
}

void PenMaterial::loadAmbientOcclusion(std::ifstream& infile)
{
    std::string tempPath;

    PenCore::Serializer()->read(infile, tempPath);

    if (!tempPath.empty())
    {
        if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
            this->m_ambientOcclusion.texture = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>(tempPath.c_str());
    }

    PenCore::Serializer()->read(infile, this->m_ambientOcclusion.defaultValue);
}

void PenMaterial::activateAmbientOcclusion()
{
    if (this->m_ambientOcclusion.texture)
    {
        std::shared_ptr<PenTexture> ptr = std::dynamic_pointer_cast<PenTexture>(this->m_ambientOcclusion.texture);
        ptr->dataPtr()->activate(3);
    }
    else
    {
        PenTexture::noTexture()->dataPtr()->activate(3);
    }

    this->m_shader->setUniform("mat.aoMap", 3);
    this->m_shader->setUniform("mat.ao", this->m_ambientOcclusion.defaultValue);
}
#pragma endregion

void PenMaterial::shaderActivation()
{
    if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
        GLShaderActivation();
}

void PenMaterial::GLShaderActivation()
{
    this->activateAlbedo();
    this->activateMetallic();
    this->activateRoughness();
    this->activateAmbientOcclusion();
    this->activateNormal();
}