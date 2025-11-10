#pragma once 

#include "PenBuffer/PenBufferBase.h"

namespace Pengine::Buffer
{
    /// <summary>
    /// VAO class for OpenGl draw
    /// </summary>
    class PenVertexAttributeBuffer final : public PenBufferBase
    {
#pragma region Public
    public:
        PenVertexAttributeBuffer() = default;
        PenVertexAttributeBuffer(const PenVertexAttributeBuffer&) = delete;
        PenVertexAttributeBuffer(PenVertexAttributeBuffer&&) noexcept = default;
        PenVertexAttributeBuffer& operator=(PenVertexAttributeBuffer&&) = default;

        ~PenVertexAttributeBuffer() final;

        void create();
        void destroy() final;

        void bind() const final;
        void unbind() const final;

        /// <summary>
        /// Define attributes for the Pengine::Vertex class
        /// </summary>
        /// <param name="index">Index of layout</param>
        /// <param name="vertSize">Size of the vector your defining</param>
        /// <returns>True if the attribute has been succesfully defined</returns>
        bool defineAttribute(size_t index, unsigned int vertSize);
#pragma endregion
    };
}