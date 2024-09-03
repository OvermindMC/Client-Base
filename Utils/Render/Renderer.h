#pragma once

#include "ImGui/DroidSans.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "SwapChainStub/SwapChainStub.h"

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
    static bool fell, init, initImCtx;

    static IDXGISwapChain3* sc;
    static ID3D11Device* device;
    static ImDrawList* drawList;

    static Microsoft::WRL::ComPtr<ID3D11DeviceContext> ctx;
    static Microsoft::WRL::ComPtr<ID3D11Texture2D> d3dT2d;
    
    static Microsoft::WRL::ComPtr<IDXGISurface> surface;
    static Microsoft::WRL::ComPtr<ID3D11RenderTargetView> tv;
};