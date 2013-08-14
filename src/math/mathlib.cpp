#include <libembryo/mathlib.h>

#include <math.h>

namespace embryo
{
    FORCEINLINE float deg2Rad(float deg)
    {
        return deg * (float)(flPI / 180.f);
    }

    FORCEINLINE float rad2Deg(float rad)
    {
        return rad * (float)(180.f / flPI);
    }

    FORCEINLINE void getSinCos(float rad, float *sine, float *cosine)
    {
        register double __cosr, __sinr;
        __asm("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (rad));
        *sine = __sinr;
        *cosine = __cosr;
    }

    void angleVectors(const vector3 &in_Angles, vector3 &out_FwdVector)
    {
        float sp, sy, cp, cy;

        getSinCos(deg2Rad(in_Angles.y), &sy, &cy); // yaw
        getSinCos(deg2Rad(in_Angles.x), &sp, &cp); // pitch

        out_FwdVector.x = cp*cy;
        out_FwdVector.y = cp*sy;
        out_FwdVector.z = -sp;
    }

    // Out-pointers since args are optional
    void angleVectors(const vector3 &in_Angles, vector3 *out_FwdVector, vector3 *out_RightVector, vector3 *out_UpVector)
    {
        float sr, sp, sy, cr, cp, cy;

        getSinCos(deg2Rad(in_Angles.y), &sy, &cy); // yaw
        getSinCos(deg2Rad(in_Angles.x), &sp, &cp); // pitch
        getSinCos(deg2Rad(in_Angles.z), &sr, &cr); // roll

        if (out_FwdVector)
        {
            out_FwdVector->x = cp*cy;
            out_FwdVector->y = cp*sy;
            out_FwdVector->z = -sp;
        }

        if (out_RightVector)
        {
            out_RightVector->x = (-1*sr*sp*cy+-1*cr*-sy);
            out_RightVector->y = (-1*sr*sp*sy+-1*cr*cy);
            out_RightVector->z = -1*sr*cp;
        }

        if (out_UpVector)
        {
            out_UpVector->x = (cr*sp*cy+-sr*-sy);
            out_UpVector->y = (cr*sp*sy+-sr*cy);
            out_UpVector->z = cr*cp;
        }
    }

    void vectorAngles(const vector3 &in_FwdVector, vector3 &out_Angles)
    {
        float tmp, yaw, pitch;

        if (in_FwdVector.y == 0 && in_FwdVector.x == 0)
        {
            yaw = 0;
            if (in_FwdVector.z > 0) pitch = 270;
            else pitch = 90;
        }
        else
        {
            yaw = atan2(in_FwdVector.y, in_FwdVector.x) * 180.f / flPI;
            if (yaw < 0) yaw += 360.f;
            tmp = sqrtf(in_FwdVector.x*in_FwdVector.x + in_FwdVector.y*in_FwdVector.y);
            pitch = atan2(-in_FwdVector.z, tmp) * 180.f / flPI;
            if (pitch < 0) pitch += 360.f;
        }

        out_Angles.x = pitch;
        out_Angles.y = yaw;
        out_Angles.z = 0;
    }

    void vectorAngles(const vector3 &in_FwdVector, const vector3 &in_UpVector, vector3 &out_Angles)
    {
        vector3 left = in_FwdVector.cross(in_UpVector).normalize();
        float xyDist = sqrtf(in_FwdVector.x*in_FwdVector.x + in_FwdVector.y*in_FwdVector.y);
        if (xyDist > 0.001f)
        {
            out_Angles.y = rad2Deg(atan2f(in_FwdVector.y, in_FwdVector.x));
            out_Angles.x = rad2Deg(atan2f(-in_FwdVector.z, xyDist));
            float up_z = (left.y * in_FwdVector.x) - (left.x * in_FwdVector.y);
            out_Angles.z = rad2Deg(atan2f(left.z, up_z));
        }
        else
        {
            out_Angles.y = rad2Deg(atan2f(-left.x, left.y));
            out_Angles.x = rad2Deg(atan2f(-in_FwdVector.z, xyDist));
            out_Angles.z = 0;
        }
    }
}