#pragma once 

#include <memory>

#include "Vector/Vector2/Vector2.h"

#pragma region Forward declarations
namespace Pengine
{
	class PenScene;
}
#pragma endregion

namespace Pengine
{
	class PenWindowBase
	{
#pragma region Public
	public:
		PenWindowBase();

		virtual ~PenWindowBase();

		virtual bool init(const char* name, const PenMath::Vector2f& size) = 0;

		/// <summary>
		/// Edit the private value "size" of this object and the window
		/// </summary>
		/// <param name="size">The new Size</param>
		/// <param name="resizeWindow">True if you want to rescale the window</param>
		virtual void setWindowSize(const PenMath::Vector2f& size, bool resizeWindow = true) = 0;

		std::unique_ptr<PenScene>& getScene();

		virtual void render() = 0;
#pragma endregion

#pragma region Protected
	protected:
		PenMath::Vector2f m_windowSize;

		//In the futur i'd like to just have a pointer here to keep scene loaded when i want (will make an issue about it)
		std::unique_ptr<PenScene> m_windowScene;
#pragma endregion
	};
}