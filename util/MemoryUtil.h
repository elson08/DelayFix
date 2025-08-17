#pragma once

#include <Windows.h>

class MemoryUtils {
public:
    static inline void nopBytes(void* dst, unsigned int size) {
        DWORD oldProtect;
        VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
        memset(dst, 0x90, size);
        VirtualProtect(dst, size, oldProtect, &oldProtect);
    }
};
