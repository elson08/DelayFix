#include <iostream>

#include <Windows.h>
#include <thread>

#include "libhat.hpp"
#include "util/Logger.h"
#include "util/MemoryUtil.h"

void entry(LPVOID lParam) {
    Logger::init();

    constexpr hat::fixed_signature pattern = hat::compile_signature<"FF D7 49 8B 06 49 8B CE FF 90 ? ? ? ? 32 DB">();
    auto result = hat::find_pattern(pattern, ".text");

    if (result.has_result()) {
        MemoryUtils::nopBytes(result.get(), 2);
        std::cout << "Successfully injected.\n";
    } else {
        std::cerr << "Failed to scan signature!\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    Logger::shutdown();
    FreeLibraryAndExitThread(static_cast<HMODULE>(lParam), 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(entry), hModule, 0, nullptr);
    }

    return TRUE;
}

