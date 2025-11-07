#pragma once 

#include "PenBuffer/PenBufferBase.h"

namespace Pengine::Buffer
{
    class PenVertexBuffer final : PenBufferBase
    {
    public:
#pragma region Constructors and Destructor
        PenVertexBuffer() = default;
        PenVertexBuffer(const PenVertexBuffer&) = delete;
        PenVertexBuffer(PenVertexBuffer&&) noexcept = default;
        PenVertexBuffer& operator=(PenVertexBuffer&&) = default;

        ~PenVertexBuffer() final;
#pragma endregion

#pragma region Functions
        void create(const void* data, size_t size);
        void destroy() final;

        void bind() const final;
        void unbind() const final;
#pragma endregion
    };
}