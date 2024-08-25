#pragma once

/*
        FX for Dx11 SwapChain - Based on ImFX by DisabledMallis
*/

#include "../Renderer.h"

class OverFX {
public:
    static bool NewFrame(ID3D11Device*, IDXGISurface*);
    static void EndFrame();
    
    static void CleanUp(bool);

    static void TransformRGB(ImVec4, ImColor);
    static void TransferGamma(ImVec4, float);
    static void CreateBlur(ImVec4, float);
    static void RotateHue(ImVec4, float);
private:
    static bool init;
};