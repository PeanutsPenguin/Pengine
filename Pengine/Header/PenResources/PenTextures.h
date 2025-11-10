#pragma once 

#include "PenResources/PenResourcesBase.h"
#include "PengineDefine.h"

#include <string_view>

#pragma region Forward Declarations
namespace Pengine::Buffer
{
	class PenTextureBuffer;
}
#pragma endregion

namespace Pengine::Resources
{
	/// <summary>
	/// Resource to handle Texture on model, contains a custom PenTextureBuffer class
	/// </summary>
	class PenTexture final : public PenResourcesBase
	{
#pragma region Public
	public:
		PenTexture() = default;
		PenTexture(const PenResourcesId& id) : PenResourcesBase(id) {}
		~PenTexture();

		bool loadResource(const char* path) override;

		_NODISCARD const std::string_view getTexturePath() const;

		/// <summary>
		/// Return a const pointer to the Texture buffer so the value can't be changed
		/// </summary>
		_NODISCARD const Pengine::Buffer::PenTextureBuffer* dataPtr() const noexcept;
#pragma endregion

#pragma region PRIVATE
	private :
		Pengine::Buffer::PenTextureBuffer* m_texBuffer = nullptr;	///WOOOOOW need to change this because it's related to openGL im crazy
#pragma endregion
	};
}