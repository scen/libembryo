#include "vector3.h"

namespace embryo
{
    FORCEINLINE vector3 operator+(float a, const vector3& b) { return b + a; }
    FORCEINLINE vector3 operator-(float a, const vector3& b) { return vector3(_mm_set1_ps(a)) - b; }
    FORCEINLINE vector3 operator*(float a, const vector3& b) { return b * a; }
    FORCEINLINE vector3 operator/(float a, const vector3& b) { return vector3(_mm_set1_ps(a)) / b; }
}