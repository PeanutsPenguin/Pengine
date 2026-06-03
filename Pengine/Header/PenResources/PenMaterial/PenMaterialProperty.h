#include "PenResources/PenResourceManager.hpp"


namespace Pengine::Resources
{
    class PenTextureBase;

    template <typename T>
    class PenMaterialProperty
    {
    public:
        PenMaterialProperty() = default;

        PenMaterialProperty(std::shared_ptr<PenTextureBase> ptr, T value)
        {
            this->defaultValue = value;
            this->texture = ptr;
        }

        bool isPropertyValid()
        {
            return texture != nullptr;
        }

        void serializeProperty(std::ofstream& outfile) 
        {
            if(texture)
                PenCore::PenSerializer()->write(outfile, texture->getTexturePath());
            else 
                PenCore::PenSerializer()->write(outfile, "");

            PenCore::PenSerializer()->write(outfile, defaultValue);
        }

        std::shared_ptr<PenTextureBase> texture = nullptr;      //Value of the texture
        T defaultValue;                                         //Fallback value                
    };
}