#pragma once 

namespace Pengine::Buffer
{
	class PenBufferBase
	{
	public:
#pragma region Constructors and Destructor
		PenBufferBase() = default;

		PenBufferBase(const PenBufferBase&) = delete;

		PenBufferBase(PenBufferBase&&) noexcept = default;

		virtual ~PenBufferBase() = default;
#pragma endregion

#pragma region Functions
		virtual void destroy();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		[[nodiscard]] const unsigned int& id() const noexcept;
		[[nodiscard]] bool valid() const noexcept;
#pragma endregion
	protected:
		unsigned int m_id = 0;

		void generateBuffer();
	};
}