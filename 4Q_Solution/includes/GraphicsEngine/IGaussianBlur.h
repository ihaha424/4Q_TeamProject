#pragma once
#include "IFilter.h"

namespace GE
{
    struct GAUSSIAN_BLUR_DESC
    {
        float weight;
    };

    class IGaussianBlur : public IFilter
    {
    protected:
        explicit IGaussianBlur() = default;
        virtual ~IGaussianBlur() = default;
        IGaussianBlur(const IGaussianBlur&) = delete;
        IGaussianBlur(IGaussianBlur&&) = delete;
        IGaussianBlur& operator=(const IGaussianBlur&) = delete;
        IGaussianBlur& operator=(IGaussianBlur&&) = delete;

    public:
        virtual void GetDesc(GAUSSIAN_BLUR_DESC* pOutDesc) = 0;
        virtual void SetDesc(GAUSSIAN_BLUR_DESC* pInDesc) = 0;
    };
}