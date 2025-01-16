#pragma once
#include "IBash.h"

namespace GE
{
    struct MATRIX_DESC
    {
        union
        {
            struct
            {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;
            };
            float m[4][4];
        };
    };

    class IMatrix : public IBase
    {
    protected:
        explicit IMatrix() = default;
        virtual ~IMatrix() = default;
        IMatrix(const IMatrix&) = delete;
        IMatrix(IMatrix&&) = delete;
        IMatrix& operator=(const IMatrix&) = delete;
        IMatrix& operator=(IMatrix&&) = delete;

    public:
        virtual void GetDesc(MATRIX_DESC* pDesc) = 0;
        virtual void SetDesc(MATRIX_DESC* pDesc) = 0;
        virtual void Multiply(MATRIX_DESC* in0, MATRIX_DESC* in1, MATRIX_DESC* out) = 0;
        virtual void CreateScaleMatrix(MATRIX_DESC* out, float x, float y, float z) = 0;
        virtual void CreateTranslateMatrix(MATRIX_DESC* out, float x, float y, float z) = 0;
        virtual void CreateRotationMatrix(MATRIX_DESC* out, float x, float y, float z) = 0;
    };
}