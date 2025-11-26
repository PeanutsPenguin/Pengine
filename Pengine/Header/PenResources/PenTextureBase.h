#pragma once 

#include "PenResources/PenResourcesBase.h"

namespace Pengine::Resources
{
	class PenTextureBase : public PenResourcesBase
	{
#pragma region Pubilic
	public:
		PenTextureBase() = default;

		PenTextureBase(const PenObjectId& id) : PenResourcesBase(id) {}

		PenTextureBase(const PenTextureBase& other) = default;
		PenTextureBase(PenTextureBase&& other) = default;
		~PenTextureBase() override = default;

		PenTextureBase& operator=(const PenTextureBase& rhs) = default;
		PenTextureBase& operator=(PenTextureBase&& rhs) = default;

		bool loadResource(const std::string path) override = 0;

		bool createResource(const std::string PenfilePath, const std::string sourcePath) override = 0;

		static std::shared_ptr<PenTextureBase> defaultTexture();

		_NODISCARD const std::string getTexturePath() const;
#pragma endregion
	};
}