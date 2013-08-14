//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

// Modified from http://fastcpp.blogspot.com/2011/12/simple-vector3-class-with-sse-support.html

#ifndef libembryo_vector3_h
#define libembryo_vector3_h

#include <smmintrin.h>

#define FORCEINLINE __attribute__((always_inline))
#define ALIGN16 __attribute__((aligned (16)))

namespace embryo
{
    class ALIGN16 vector3
    {
    public:
        FORCEINLINE vector3() : mmvalue(_mm_setzero_ps()) {}
        FORCEINLINE vector3(float x, float y, float z) : mmvalue(_mm_set_ps(0, z, y, x)) {}
        FORCEINLINE vector3(__m128 m) : mmvalue(m) {}
        
        FORCEINLINE vector3 operator+(const vector3& b) const { return _mm_add_ps(mmvalue, b.mmvalue); }
        FORCEINLINE vector3 operator-(const vector3& b) const { return _mm_sub_ps(mmvalue, b.mmvalue); }
        FORCEINLINE vector3 operator*(const vector3& b) const { return _mm_mul_ps(mmvalue, b.mmvalue); }
        FORCEINLINE vector3 operator/(const vector3& b) const { return _mm_div_ps(mmvalue, b.mmvalue); }
        
        FORCEINLINE vector3& operator+=(const vector3& b) { mmvalue = _mm_add_ps(mmvalue, b.mmvalue); return *this; }
        FORCEINLINE vector3& operator-=(const vector3& b) { mmvalue = _mm_sub_ps(mmvalue, b.mmvalue); return *this; }
        FORCEINLINE vector3& operator*=(const vector3& b) { mmvalue = _mm_mul_ps(mmvalue, b.mmvalue); return *this; }
        FORCEINLINE vector3& operator/=(const vector3& b) { mmvalue = _mm_div_ps(mmvalue, b.mmvalue); return *this; }
        
        FORCEINLINE vector3 operator+(float b) const { return _mm_add_ps(mmvalue, _mm_set1_ps(b)); }
        FORCEINLINE vector3 operator-(float b) const { return _mm_sub_ps(mmvalue, _mm_set1_ps(b)); }
        FORCEINLINE vector3 operator*(float b) const { return _mm_mul_ps(mmvalue, _mm_set1_ps(b)); }
        FORCEINLINE vector3 operator/(float b) const { return _mm_div_ps(mmvalue, _mm_set1_ps(b)); }
        
        FORCEINLINE vector3& operator+=(float b) { mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(b)); return *this; }
        FORCEINLINE vector3& operator-=(float b) { mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(b)); return *this; }
        FORCEINLINE vector3& operator*=(float b) { mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(b)); return *this; }
        FORCEINLINE vector3& operator/=(float b) { mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(b)); return *this; }

        FORCEINLINE float operator[](int i) const { return ((float *)this)[i]; }
        FORCEINLINE float &operator[](int i) { return ((float *)this)[i]; }
        
        FORCEINLINE vector3 cross(const vector3& b) const
        {
            return _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
                              _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 0, 2, 1))));
        }
        
        FORCEINLINE float dot(const vector3& b) const { return _mm_cvtss_f32(_mm_dp_ps(mmvalue, b.mmvalue, 0x71)); }
        FORCEINLINE float length() const { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x71))); }
        FORCEINLINE float rlength() const { return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x71))); }
        FORCEINLINE vector3 normalize() const { return _mm_mul_ps(mmvalue, _mm_rsqrt_ps(_mm_dp_ps(mmvalue, mmvalue, 0x7F))); }

        FORCEINLINE void* operator new[](size_t x) { register void *ret; posix_memalign(&ret, 16, x); return ret; }
        FORCEINLINE void operator delete[](void* x) { if (x) free(x); }
        
        union
        {
            struct { float x, y, z; };
            __m128 mmvalue;
        };
    };
}

#endif