#include "PenSerializer/PenSerializer.h"

using namespace Pengine::Serialize;

void PenSerializer::write(std::ostream& out, const std::string& s)
{
    uint64_t size = s.size();
    write(out, size);
    out.write(s.data(), size);
}

void PenSerializer::read(std::istream& in, std::string& s)
{
    uint64_t size = 0;
    read(in, size);
    s.resize(size);
    in.read(&s[0], size);
}

void PenSerializer::write(std::ostream& out, const PenMath::Vector3f& s)
{
    write(out, s.x);
    write(out, s.y);
    write(out, s.z);
}

void PenSerializer::read(std::istream& in, PenMath::Vector3f& s)
{
    read(in, s.x);
    read(in, s.y);
    read(in, s.z);
}

void PenSerializer::write(std::ostream& out, const PenMath::Quaternion& q)
{
    write(out, q.x);
    write(out, q.y);
    write(out, q.z);
    write(out, q.w);
}

void PenSerializer::read(std::istream& in, PenMath::Quaternion& q)
{
    read(in, q.x);
    read(in, q.y);
    read(in, q.z);
    read(in, q.w);
}
