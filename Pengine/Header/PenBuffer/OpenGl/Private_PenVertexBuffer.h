#pragma once 

#include "PenBuffer/OpenGl/Private_PenGLBuferBase.h"

namespace Pengine::Buffer
{
    /// <summary>
    /// VBO for OpenGl draw
    /// </summary>
    class PenVertexBuffer final : public PenGLBufferBase
    {
#pragma region Public
    public:
        PenVertexBuffer() = default;
        PenVertexBuffer(const PenVertexBuffer& other) = delete;
        PenVertexBuffer(PenVertexBuffer&& other) = default;
        ~PenVertexBuffer() final;

        PenVertexBuffer& operator=(const PenVertexBuffer& rhs) = delete;
        PenVertexBuffer& operator=(PenVertexBuffer&& rhs) = default;

        void create(const void* data, size_t size);
        void destroy() final;

        void bind() const final;
        void unbind() const final;
#pragma endregion
    };
}