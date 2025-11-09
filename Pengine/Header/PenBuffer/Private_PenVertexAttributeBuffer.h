#pragma once 

#include "PenBuffer/PenBufferBase.h"

namespace Pengine::Buffer
{
    class PenVertexAttributeBuffer final : PenBufferBase
    {
    public:
#pragma region Constructors and Destructor
        PenVertexAttributeBuffer() = default;
        PenVertexAttributeBuffer(const PenVertexAttributeBuffer&) = delete;
        PenVertexAttributeBuffer(PenVertexAttributeBuffer&&) noexcept = default;
        PenVertexAttributeBuffer& operator=(PenVertexAttributeBuffer&&) = default;

        ~PenVertexAttributeBuffer() final;
#pragma endregion

#pragma region Functions
        void create();
        void destroy() final;

        void bind() const final;
        void unbind() const final;

        bool defineAttribute(size_t index, unsigned int vertSize);
#pragma endregion
    };
}