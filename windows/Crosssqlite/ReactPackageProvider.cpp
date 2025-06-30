#include "pch.h"
#include "ReactPackageProvider.h"
#include "NativeCrosssqliteSpec.g.h"

#include "sqlite_bridge.h"
#include "react-native-crosssqlite.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Crosssqlite::implementation
{

struct Crosssqlite : CrosssqliteT<Crosssqlite, IReactModuleBuilder>
{
    using ModuleSpec = CrosssqliteSpec;

    static constexpr auto Name = L"Crosssqlite";

    static void Initialize(ReactContext const&) noexcept
    {
        // Module initialization if needed
    }

    static void multiply(double a, double b, ReactPromise<double> promise) noexcept
    {
        try
        {
            double result = crosssqlite::multiply(a, b);
            promise.Resolve(result);
        }
        catch (...)
        {
            promise.Reject("Failed to multiply");
        }
    }

    static void open(std::string path, ReactPromise<double> promise) noexcept
    {
        try
        {
            int result = open_db(path.c_str());
            promise.Resolve(static_cast<double>(result));
        }
        catch (...)
        {
            promise.Reject("Failed to open database");
        }
    }

    static void exec(std::string sql, ReactPromise<double> promise) noexcept
    {
        try
        {
            int result = exec_sql(sql.c_str());
            promise.Resolve(static_cast<double>(result));
        }
        catch (...)
        {
            promise.Reject("Failed to execute SQL");
        }
    }

    static void close(ReactPromise<void> promise) noexcept
    {
        try
        {
            close_db();
            promise.Resolve();
        }
        catch (...)
        {
            promise.Reject("Failed to close database");
        }
    }

    static void select(std::string sql, ReactPromise<std::string> promise) noexcept
    {
        try
        {
            const char* result = select_json(sql.c_str());
            promise.Resolve(std::string(result));
        }
        catch (...)
        {
            promise.Reject("Failed to select from database");
        }
    }

    static void getJournalMode(ReactPromise<std::string> promise) noexcept
    {
        try
        {
            const char* mode = get_journal_mode();
            promise.Resolve(std::string(mode));
        }
        catch (...)
        {
            promise.Reject("Failed to get journal mode");
        }
    }
};

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const& packageBuilder) noexcept
{
    AddAttributedModules(packageBuilder, true);
}

}

namespace winrt::Crosssqlite::factory_implementation
{

}

extern "C"
{

BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID) noexcept
{
    return TRUE;
}

HRESULT __stdcall DllCanUnloadNow() noexcept
{
#ifdef _WRL_MODULE_H_
    if (!::Microsoft::WRL::Module<::Microsoft::WRL::InProc>::GetModule().Terminate())
    {
        return S_FALSE;
    }
#endif

    if (winrt::get_module_lock())
    {
        return S_FALSE;
    }

    winrt::clear_factory_cache();
    return S_OK;
}

HRESULT __stdcall DllGetActivationFactory(HSTRING classId, IActivationFactory** factory) noexcept
{
    try
    {
        *factory = nullptr;
        wchar_t const* const name = WindowsGetStringRawBuffer(classId, nullptr);

        if (0 == wcscmp(name, L"Crosssqlite.ReactPackageProvider"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::Crosssqlite::factory_implementation::ReactPackageProvider>());
            return S_OK;
        }

        return winrt::hresult_class_not_available().to_abi();
    }
    catch (...)
    {
        return winrt::to_hresult();
    }
}

}
