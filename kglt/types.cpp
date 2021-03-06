
#include "types.h"

namespace kglt {

kglt::Vec3 operator*(float lhs, const kglt::Vec3& rhs) {
    kglt::Vec3 result;
    kmVec3Scale(&result, &rhs, lhs);
    return result;
}

kglt::Vec3 operator/(float lhs, const kglt::Vec3& rhs) {
    kglt::Vec3 result;
    kmVec3Scale(&result, &rhs, 1.0 / lhs);
    return result;
}

kglt::Vec3 operator-(const kglt::Vec3& vec) {
    return kglt::Vec3(-vec.x, -vec.y, -vec.z);
}

}
