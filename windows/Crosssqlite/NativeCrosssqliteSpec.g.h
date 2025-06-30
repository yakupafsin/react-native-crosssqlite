#pragma once

#include "winrt/Microsoft.ReactNative.h"

using namespace winrt::Microsoft::ReactNative;

REACT_MODULE(Crosssqlite)
struct CrosssqliteSpec
{
    REACT_INIT(Initialize)
    static void Initialize(ReactContext const& reactContext) noexcept;

    REACT_METHOD(multiply)
    static void multiply(double a, double b, ReactPromise<double> promise) noexcept;

    REACT_METHOD(open)
    static void open(std::string path, ReactPromise<double> promise) noexcept;

    REACT_METHOD(exec)
    static void exec(std::string sql, ReactPromise<double> promise) noexcept;

    REACT_METHOD(close)
    static void close(ReactPromise<void> promise) noexcept;

    REACT_METHOD(select)
    static void select(std::string sql, ReactPromise<std::string> promise) noexcept;

    REACT_METHOD(getJournalMode)
    static void getJournalMode(ReactPromise<std::string> promise) noexcept;
};

template<typename TModule>
struct CrosssqliteT : TModule
{
    using TModule::TModule;
};
