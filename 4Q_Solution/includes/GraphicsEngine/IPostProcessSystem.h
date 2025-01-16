#pragma once

namespace GE
{
    class IFilter;
    class IBloom;
    class IPostProcessSystem
    {
    protected:
        explicit IPostProcessSystem() = default;
        virtual ~IPostProcessSystem() = default;
        IPostProcessSystem(const IPostProcessSystem&) = delete;
        IPostProcessSystem(IPostProcessSystem&&) = delete;
        IPostProcessSystem& operator=(const IPostProcessSystem&) = delete;
        IPostProcessSystem& operator=(IPostProcessSystem&&) = delete;

    public:
        virtual void AddFilter(const unsigned int layer, IFilter* pFilter) = 0;
        virtual void CreateBloom(IBloom** ppBloom) = 0;
    };
}