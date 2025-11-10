#pragma once 

#include "PenBuffer/PenBufferBase.h"

namespace Pengine::Buffer
{
    /// <summary>
    /// VBO for OpenGl draw
    /// </summary>
    class PenVertexBuffer final : public PenBufferBase
    {
#pragma region Public
    public:
        PenVertexBuffer() = default;
        PenVertexBuffer(const PenVertexBuffer&) = delete;
        PenVertexBuffer(PenVertexBuffer&&) noexcept = default;
        PenVertexBuffer& operator=(PenVertexBuffer&&) = default;

        ~PenVertexBuffer() final;

        void create(const void* data, size_t size);
        void destroy() final;

        void bind() const final;
        void unbind() const final;
#pragma endregion
    };
}