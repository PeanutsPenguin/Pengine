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
	class PenTexture final : public PenResourcesBase
	{
	public:
#pragma region Constructors and Destructor
		PenTexture() = default;
		PenTexture(const PenResourcesId& id) : PenResourcesBase(id) {}
		~PenTexture();
#pragma endregion

#pragma region Functions
		bool loadResource(const char* path) override;

		_NODISCARD const std::string_view getTexturePath() const;

		/// <summary>
		/// Return a const pointer to the Texture buffer so the value can't be changed
		/// </summary>
		_NODISCARD const Pengine::Buffer::PenTextureBuffer* dataPtr() const noexcept;

#pragma endregion
	private :
		Pengine::Buffer::PenTextureBuffer* m_texBuffer = nullptr;	///WOOOOOW need to change this because it's related to openGL im crazy
	};
}