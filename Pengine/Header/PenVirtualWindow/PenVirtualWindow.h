#pragma once 


/// <summary>
/// Namespace for all things UI related (idk why i prefer write it in lower case, it just looks better to me)
/// </summary>
namespace Pengine::ui
{
	class PenVirtualWindowBase
	{
	public:
		PenVirtualWindowBase() = default;
		PenVirtualWindowBase(const PenVirtualWindowBase& other) = default;
		PenVirtualWindowBase(PenVirtualWindowBase&& other) = default;
		~PenVirtualWindowBase() = default;

		PenVirtualWindowBase& operator=(const PenVirtualWindowBase& rhs) = default;
		PenVirtualWindowBase& operator=(PenVirtualWindowBase&& rhs) = default;

		void render();
	protected:






		const char* m_title = "PenVirtualWindow";
	};
}