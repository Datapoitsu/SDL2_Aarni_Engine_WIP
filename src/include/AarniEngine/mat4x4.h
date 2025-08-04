#ifndef _MAT4X4H_
#define _MAT4X4H_

#include <AarniEngine/vector.h>

struct Mat4x4{
    float m[4][4] = {0}; //row by column

    Mat4x4& operator+=(const Mat4x4& other)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int k = 0; k < 4; k++)
            {
                m[i][k] += other.m[i][k];
            }
        }
        return *this;
    }

    friend Mat4x4 operator+(Mat4x4 m1, const Mat4x4& m2)
    {
        return m1 += m2;
    }

    static Mat4x4 AddMatricies(Mat4x4 &a, Mat4x4 &b)
    {
        Mat4x4 result = {};
        for(int i = 0; i < 4; i++)
        {
            for(int k = 0; k < 4; k++)
            {
                result.m[i][k] = a.m[i][k] + b.m[i][k];
            }
        }
        return result;
    }

    static void MultiplyMatrixVector(Vector3 &inputVector, Vector3 &outputVector, Mat4x4 &matrix)
    {
        for(int i = 0; i < 3; i++)
        {
            outputVector.x = inputVector.x * matrix.m[0][i] + inputVector.y * matrix.m[1][i] + inputVector.z * matrix.m[2][i] + matrix.m[3][i];
        }
        float w = inputVector.x * matrix.m[0][3] + inputVector.y * matrix.m[1][3] +  inputVector.z * matrix.m[2][3] + matrix.m[3][3];
        if(w != 0.0f)
        {
            outputVector /= w;
        }
    }
};
#endif