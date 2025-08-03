#pragma once

#include <Windows.h>
#include <filesystem>

class Logger {
public:
    static inline void init() {
        AllocConsole();
        FILE* f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONIN$", "w", stdin);
        freopen_s(&f, "CONOUT$", "w", stderr);
        SetConsoleTitleA("Logger");
    }

    static inline void shutdown() {
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);

        const auto console = GetConsoleWindow();
        if (console) {
            PostMessage(console, WM_CLOSE, 0, 0);
        }

        FreeConsole();
    }
};




