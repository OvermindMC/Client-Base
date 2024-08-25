#include "Renderer.h"
#include "../Debugger/Debugger.h"

bool Renderer::fell = false, Renderer::init = false, Renderer::initImCtx = false, Renderer::postFrame = false;

ImDrawList* Renderer::drawList = nullptr;
IDXGISwapChain3* Renderer::sc = nullptr;
ID3D11Device* Renderer::device = nullptr;

Microsoft::WRL::ComPtr<ID3D11DeviceContext> Renderer::ctx = nullptr;
Microsoft::WRL::ComPtr<ID3D11Texture2D> Renderer::d3dT2d = nullptr;
Microsoft::WRL::ComPtr<IDXGISurface> Renderer::surface = nullptr;
Microsoft::WRL::ComPtr<ID3D11RenderTargetView> Renderer::tv = nullptr;

bool Renderer::Init(IDXGISwapChain3* SwapChain) {
    Renderer::sc = SwapChain;
    if(!fell) {
        ID3D11Device* d3d11Device = nullptr;
        ID3D12Device* d3d12Device = nullptr;

        if (FAILED(SwapChain->GetDevice(IID_PPV_ARGS(&d3d11Device))) && FAILED(SwapChain->GetDevice(IID_PPV_ARGS(&d3d12Device)))) {
            return false;
        };

        if(d3d12Device) {
            ((ID3D12Device10*)(d3d12Device))->RemoveDevice();
            return false;
        } else if(d3d11Device) {
            Renderer::device = d3d11Device;
            fell = true;
        };
    };

    if(!Renderer::device) {
        return false;
    };

    return Renderer::InitSub();
};

bool Renderer::InitSub() {
    if(!ImGui::GetCurrentContext() && !Renderer::initImCtx) {
        Renderer::initImCtx = true;
        ImGui::CreateContext();
        ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(DroidSans_compressed_data, DroidSans_compressed_size, 18.f);
    };

    if(!Renderer::ctx) {
        device->GetImmediateContext(&Renderer::ctx);
        if(!Renderer::ctx) {
            return false;
        };
    };

    if(FAILED(Renderer::sc->GetBuffer(0, IID_PPV_ARGS(&Renderer::d3dT2d)))) {
        return false;
    };

    if(FAILED(Renderer::sc->GetBuffer(0, IID_PPV_ARGS(&Renderer::surface)))) {
        return false;
    };

    if(FAILED(Renderer::device->CreateRenderTargetView(Renderer::d3dT2d.Get(), nullptr, Renderer::tv.GetAddressOf()))) {
        return false;
    };

    if(!Renderer::init) {
        Renderer::init = true;
        ImGui_ImplWin32_Init((HWND)FindWindowA(nullptr, "Minecraft"));
        ImGui_ImplDX11_Init(Renderer::device, Renderer::ctx.Get());
    };
    
    return true;
};

void Renderer::CleanUp(bool cleanAll) {
    Renderer::init = !cleanAll;

    if(Renderer::ctx) {
        Renderer::ctx->Flush();
    };

    Renderer::ctx.Reset();
    Renderer::d3dT2d.Reset();
    Renderer::surface.Reset();
    Renderer::tv.Reset();

    if(cleanAll && ImGui::GetCurrentContext()) {
        Renderer::drawList = nullptr;
        Renderer::init = false, Renderer::initImCtx = false;

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    };
};

void Renderer::NewFrame() {
    if(!Renderer::init)
        return;
    
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Renderer::drawList = ImGui::GetBackgroundDrawList();
};

void Renderer::EndFrame() {
    if(!Renderer::init)
        return;
    
    ImGui::EndFrame();
    ImGui::Render();

    Renderer::ctx->OMSetRenderTargets(1, Renderer::tv.GetAddressOf(), nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
};

void Renderer::RenderText(ImVec2 textPos, std::string text, float fontSize, ImColor color) {
    if(!Renderer::drawList)
        return;
    
    Renderer::drawList->AddText(
        ImGui::GetFont(), fontSize, textPos,
        ImColor(color.Value.x / 255.f, color.Value.y / 255.f, color.Value.z / 255.f, color.Value.w),
        text.c_str()
    );
};

ImVec2 Renderer::GetTextSize(std::string text, float fontSize) {
    return ImGui::GetFont()->CalcTextSizeA(fontSize, 1000.f, -1.f, text.c_str());
};

void Renderer::FillRectOutline(ImVec4 rectPos, ImColor color, float rounding, float thickness) {
    if(!Renderer::drawList)
        return;
    
    ImDrawFlags flags = 0;
    Renderer::drawList->AddRect(
        ImVec2(
            rectPos.x, rectPos.y
        ),
        ImVec2(
            rectPos.z, rectPos.w
        ),
        ImColor(color.Value.x / 255.f, color.Value.y / 255.f, color.Value.z / 255.f, color.Value.w), rounding, flags, thickness
    );
};

void Renderer::FillRect(ImVec4 rectPos, ImColor color, float rounding) {
    if(!Renderer::drawList)
        return;
    
    Renderer::drawList->AddRectFilled(
        ImVec2(
            rectPos.x, rectPos.y
        ),
        ImVec2(
            rectPos.z, rectPos.w
        ),
        ImColor(color.Value.x / 255.f, color.Value.y / 255.f, color.Value.z / 255.f, color.Value.w), rounding
    );
};