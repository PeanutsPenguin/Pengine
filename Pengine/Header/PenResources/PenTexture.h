#pragma once 

#include "PenResources/PenResourcesBase.h"
#include "Vector/Vector3/Vector3.h"

namespace Pengine::Buffer
{
	class PenTextureBuffer;
}

namespace Pengine::Resources
{
	class PenTexture : public PenResourceBase
	{
	public:
		PenTexture();
		PenTexture(const PengineIds& id);
		PenTexture(const PenTexture& other) = default;
		PenTexture(PenTexture&& other) = default;
		~PenTexture() final;

		PenTexture& operator=(const PenTexture& rhs) = default;
		PenTexture& operator=(PenTexture&& rhs) = default;

		static std::shared_ptr<PenTexture> noTexture();

		bool	loadResource(const std::string path) final;
		bool	createResource(const std::string PenfilePath, const std::string sourcePath) final;
		bool	GPULoad() override;

		_NODISCARD const std::string getTexturePath() const;

		/// <summary>
		/// Return a const pointer to the Texture buffer so the value can't be changed but can be used
		/// </summary>
		_NODISCARD const Pengine::Buffer::PenTextureBuffer* dataPtr() const noexcept;

	private:
		bool initializeTextureBuffer(const char* sourcePath);

		std::string m_sourcePath = "";
		std::unique_ptr<Pengine::Buffer::PenTextureBuffer> m_texBuffer = nullptr;
	};
}