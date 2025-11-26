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

		bool loadResource(const char* path) override = 0;

		bool createResource(const char* PenfilePath, const char* sourcePath) override = 0;

		_NODISCARD const char* getTexturePath() const;
#pragma endregion
	};
}