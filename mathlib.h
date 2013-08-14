//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#ifndef libembryo_math_h
#define libembryo_math_h

#define __PI 3.14159265358979323846

#include <libembryo/vector3.h>

namespace embryo
{
    const float flPI = (float)__PI;

    enum rotations
    {
        Pitch = 0,
        Yaw,
        Roll
    };

    FORCEINLINE static float deg2Rad(float deg);
    FORCEINLINE static float rad2Deg(float rad);
    FORCEINLINE static void getSinCos(float rad, float *sine, float *cosine);

    static void angleVectors(const vector3 &in_Angles, vector3 &out_FwdVector);
    static void angleVectors(const vector3 &in_Angles, vector3 *out_FwdVector, vector3 *out_RightVector, vector3 *out_UpVector);
    
    static void vectorAngles(const vector3 &in_FwdVector, vector3 &out_Angles);
    static void vectorAngles(const vector3 &in_FwdVector, const vector3 &in_UpVector, vector3 &out_Angles);
}

#endif