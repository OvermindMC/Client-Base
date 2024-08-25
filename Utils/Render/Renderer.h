#pragma once

#include "ImGui/DroidSans.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

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
#include <string>

class Renderer {
public:
    static bool Init(IDXGISwapChain3*);
    
    static bool InitSub();
    static void CleanUp(bool);

    static void NewFrame();
    static void EndFrame();

    static void RenderText(ImVec2, std::string, float, ImColor);
    static ImVec2 GetTextSize(std::string, float);

    static void FillRectOutline(ImVec4, ImColor, float, float);
    static void FillRect(ImVec4, ImColor, float);
private:
    static bool fell, init, initImCtx, postFrame;

    static IDXGISwapChain3* sc;
    static ID3D11Device* device;
    static ImDrawList* drawList;

    static Microsoft::WRL::ComPtr<ID3D11DeviceContext> ctx;
    static Microsoft::WRL::ComPtr<ID3D11Texture2D> d3dT2d;
    
    static Microsoft::WRL::ComPtr<IDXGISurface> surface;
    static Microsoft::WRL::ComPtr<ID3D11RenderTargetView> tv;
};