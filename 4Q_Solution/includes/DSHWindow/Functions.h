#pragma once

namespace DSH::Window
{
    EXTERN_C struct DSH_WINDOW_LIBRARY_API CreateSystem
    {
        HRESULT STDMETHODCALLTYPE operator()(
            /* [annotation][out] */
            _Out_ ISystem** ppSystem) const;
    };

    EXTERN_C struct DSH_WINDOW_LIBRARY_API AdjustWindowRect
    {
        HRESULT STDMETHODCALLTYPE operator()(
            /* [annotation][in] */
            _In_ SIZE size,  
            /* [annotation][out] */
            _Out_ RECT* pRect) const;

        HRESULT STDMETHODCALLTYPE operator()(
            /* [annotation][in][out] */
            _Inout_ RECT* pRect) const;
    };
}
