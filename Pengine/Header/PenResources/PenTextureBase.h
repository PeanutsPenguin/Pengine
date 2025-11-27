#pragma once 

#include "PenResources/PenResourcesBase.h"

namespace Pengine::Resources
{
	class PenTextureBase : public PenResourcesBase
	{
	public:
		PenTextureBase() = default;
		PenTextureBase(const PenObjectId& id) : PenResourcesBase(id) {}
		PenTextureBase(const PenTextureBase& other) = default;
		PenTextureBase(PenTextureBase&& other) = default;
		virtual ~PenTextureBase() override = default;

		PenTextureBase& operator=(const PenTextureBase& rhs) = default;
		PenTextureBase& operator=(PenTextureBase&& rhs) = default;

		static std::shared_ptr<PenTextureBase> defaultTexture();

		virtual bool	loadResource(const std::string path) override = 0;
		virtual bool	createResource(const std::string PenfilePath, const std::string sourcePath) override = 0;

		_NODISCARD const std::string getTexturePath() const;
	};
}