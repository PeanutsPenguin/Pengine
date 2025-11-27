#pragma once 

#include "PenResources/PenTextureBase.h"

#pragma region Forward Declarations
namespace Pengine::Buffer
{
	class PenTextureBuffer;
}
#pragma endregion

namespace Pengine::Resources
{
	class PenGLTexture : public PenTextureBase
	{
#pragma region Public
	public:
		PenGLTexture();

		PenGLTexture(const PenObjectId& id);

		PenGLTexture(const PenGLTexture& other) = default;
		PenGLTexture(PenGLTexture&& other) = default;
		~PenGLTexture() override;

		PenGLTexture& operator=(const PenGLTexture& rhs) = default;
		PenGLTexture& operator=(PenGLTexture&& rhs) = default;

		bool loadResource(const std::string path) override;

		bool createResource(const std::string PenfilePath, const std::string sourcePath) override;

		/// <summary>
		/// Return a const pointer to the Texture buffer so the value can't be changed but can be used
		/// </summary>
		_NODISCARD const Pengine::Buffer::PenTextureBuffer* dataPtr() const noexcept;
#pragma endregion

#pragma region PRIVATE
	private :

		bool initializeTextureBuffer(const char* sourcePath);

		std::unique_ptr<Pengine::Buffer::PenTextureBuffer> m_texBuffer = nullptr;
#pragma endregion
	};
}