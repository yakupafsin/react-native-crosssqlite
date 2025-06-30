#pragma once

#include "winrt/Microsoft.ReactNative.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Crosssqlite::implementation
{
    struct ReactPackageProvider : winrt::implements<ReactPackageProvider, IReactPackageProvider>
    {
    public:
        void CreatePackage(IReactPackageBuilder const& packageBuilder) noexcept;
    };
}

namespace winrt::Crosssqlite::factory_implementation
{
    struct ReactPackageProvider : ReactPackageProviderT<ReactPackageProvider, implementation::ReactPackageProvider>
    {
    };
}
