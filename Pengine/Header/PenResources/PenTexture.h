#pragma once 

#include "PenResources/PenResourcesBase.h"

namespace Pengine::Buffer
{
	class PenTextureBuffer;
}

namespace Pengine::Resources
{
	class PenTexture : public PenResourcesBase
	{
	public:
		PenTexture();
		PenTexture(const PenObjectId& id);
		PenTexture(const PenTexture& other) = default;
		PenTexture(PenTexture&& other) = default;
		~PenTexture() final = default;

		PenTexture& operator=(const PenTexture& rhs) = default;
		PenTexture& operator=(PenTexture&& rhs) = default;

		static std::shared_ptr<PenTexture> defaultTexture();

		static std::shared_ptr<PenTexture> noTexture();

		bool	loadResource(const std::string path) final;
		bool	createResource(const std::string PenfilePath, const std::string sourcePath) final;

		_NODISCARD const std::string getTexturePath() const;

		/// <summary>
		/// Return a const pointer to the Texture buffer so the value can't be changed but can be used
		/// </summary>
		_NODISCARD const Pengine::Buffer::PenTextureBuffer* dataPtr() const noexcept;
	
	private:
		bool initializeTextureBuffer(const char* sourcePath);

		std::unique_ptr<Pengine::Buffer::PenTextureBuffer> m_texBuffer = nullptr;
	};
}