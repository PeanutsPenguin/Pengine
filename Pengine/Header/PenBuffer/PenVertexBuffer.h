#pragma once 

namespace Pengine::Buffer
{
    class PenVertexBuffer 
    {
    public:
        PenVertexBuffer() = default;
        PenVertexBuffer(const PenVertexBuffer& other) = delete;
        PenVertexBuffer(PenVertexBuffer&& other) = default;
        ~PenVertexBuffer();

        PenVertexBuffer& operator=(const PenVertexBuffer& rhs) = delete;
        PenVertexBuffer& operator=(PenVertexBuffer&& rhs) = default;

        void create(const void* data, size_t size);
        void destroy();

        void bind() const;
        void unbind() const;

        bool isValid();

    private:
        unsigned int m_id = 0;
    };
}