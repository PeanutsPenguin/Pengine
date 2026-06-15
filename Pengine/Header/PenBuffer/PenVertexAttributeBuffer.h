#pragma once 

namespace Pengine::Buffer
{
    class PenVertexAttributeBuffer
    {
    public:
        PenVertexAttributeBuffer() = default;
        PenVertexAttributeBuffer(const PenVertexAttributeBuffer& other) = delete;
        PenVertexAttributeBuffer(PenVertexAttributeBuffer&& other) = default;
        ~PenVertexAttributeBuffer();

        PenVertexAttributeBuffer& operator=(const PenVertexAttributeBuffer& rhs) = delete;
        PenVertexAttributeBuffer& operator=(PenVertexAttributeBuffer&& rhs) = default;

        void create();
        void destroy();

        void bind() const;
        void unbind() const;

        /// <summary>
        /// Define attributes for the Pengine::Vertex class
        /// </summary>
        /// <param name="index">Index of layout</param>
        /// <param name="vertSize">Size of the vector your defining</param>
        void defineAttribute(size_t index, unsigned int vertSize);

    private:
        unsigned int m_id;
    };
}