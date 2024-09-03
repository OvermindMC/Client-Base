#pragma once

#include <dxgi.h>
#include <d2d1.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d2d1_3.h>
#include <d2d1_3.h>
#include <dxgi1_6.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

#include <wrl/client.h>

class SwapChainStub {
public:
    static void init();
    static void free();
    static unsigned long long get(size_t);
private:
    static unsigned long long* table;
};