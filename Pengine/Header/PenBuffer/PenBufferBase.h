#pragma once 

namespace Pengine::Buffer
{
	/// <summary>
	/// Base class for buffers (Contains a private unigned int member plus bind, unbind, destroy and generate function.
	/// </summary>
	class PenBufferBase
	{
#pragma region Public
	public:
		PenBufferBase() = default;

		PenBufferBase(const PenBufferBase&) = delete;

		PenBufferBase(PenBufferBase&&) noexcept = default;

		virtual ~PenBufferBase() = default;

		virtual void destroy();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		[[nodiscard]] const unsigned int& id() const noexcept;
		[[nodiscard]] bool valid() const noexcept;
#pragma endregion

#pragma region Protected
	protected:
		unsigned int m_id = 0;

		void generateBuffer();
#pragma endregion
	};
}