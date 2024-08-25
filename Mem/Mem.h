#pragma once

#include <functional>
#include <MinHook.h>
#include <Windows.h>
#include <assert.h>
#include <vector>
#include <memory>
#include <string>
#include <map>

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

#define PI 3.14159265358979323846

class Mem {
public:
    static HMODULE getDll();
};