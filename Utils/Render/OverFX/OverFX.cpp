#include "OverFX.h"
#include "../../Debugger/Debugger.h"

Microsoft::WRL::ComPtr<ID2D1Factory3> d2dFactory;

Microsoft::WRL::ComPtr<ID2D1Device2> d2dDevice;
Microsoft::WRL::ComPtr<ID2D1DeviceContext2> d2dDeviceContext;

Microsoft::WRL::ComPtr<ID2D1Effect> blurEffect;
Microsoft::WRL::ComPtr<ID2D1Effect> colorMatrixEffect;
Microsoft::WRL::ComPtr<ID2D1Effect> hueRotationEffect;
Microsoft::WRL::ComPtr<ID2D1Effect> gammaTransferEffect;

Microsoft::WRL::ComPtr<ID2D1Bitmap1> sourceBitmap;

bool OverFX::init = false;

bool OverFX::NewFrame(ID3D11Device* device, IDXGISurface* idxgiSurface) {
    CleanUp(false);
    if(!d2dFactory) {
        if(FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, d2dFactory.GetAddressOf()))) {
            return false;
        } else {
            Microsoft::WRL::ComPtr<IDXGIDevice> idxgiDevice = nullptr;
            if(SUCCEEDED(device->QueryInterface<IDXGIDevice>(&idxgiDevice)) && SUCCEEDED(d2dFactory->CreateDevice(idxgiDevice.Get(), &d2dDevice))) {
                OverFX::init = true;
            };
        };
    };

    if(d2dFactory) {
        if(SUCCEEDED(d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &d2dDeviceContext))) {
            D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 0.f, 0.f);
            if(SUCCEEDED(d2dDeviceContext->CreateBitmapFromDxgiSurface(idxgiSurface, &bitmapProperties, &sourceBitmap))) {
                return true;
            };
        };
    };

    return false;
};

void OverFX::EndFrame() {
    CleanUp(false);
};

void OverFX::CleanUp(bool cleanAll) {
    blurEffect.Reset();
    hueRotationEffect.Reset();
    gammaTransferEffect.Reset();
    
    sourceBitmap.Reset();
    d2dDeviceContext.Reset();

    if(cleanAll) {
        d2dDevice.Reset();
        d2dFactory.Reset();
        OverFX::init = false;
    };
};

void OverFX::TransformRGB(ImVec4 position, ImColor color) {
    if (!OverFX::init || !d2dDeviceContext || !sourceBitmap)
        return;

    if (sourceBitmap && SUCCEEDED(d2dDeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &colorMatrixEffect))) {
        d2dDeviceContext->SetTarget(sourceBitmap.Get());
        d2dDeviceContext->BeginDraw();

        D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(sourceBitmap->GetPixelFormat());
        Microsoft::WRL::ComPtr<ID2D1Bitmap> targetBitmap;
        HRESULT hr = d2dDeviceContext->CreateBitmap(sourceBitmap->GetPixelSize(), props, &targetBitmap);
        
        if (SUCCEEDED(hr)) {
            auto destPoint = D2D1::Point2U(0, 0);
            auto rect = D2D1::RectU(0, 0, static_cast<UINT32>(position.z), static_cast<UINT32>(position.w));
            targetBitmap->CopyFromBitmap(&destPoint, sourceBitmap.Get(), &rect);

            colorMatrixEffect->SetInput(0, targetBitmap.Get());

            float r = color.Value.x / 255.f; float g = color.Value.y / 255.f; float b = color.Value.z / 255.f; float a = color.Value.w;

            D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(
                r, 0, 0, 0,
                0, g, 0, 0,
                0, 0, b, 0,
                0, 0, 0, a,
                0, 0, 0, 0
            );

            colorMatrixEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);

            D2D1_RECT_F destRect = D2D1::RectF(position.x, position.y, position.z, position.w);
            d2dDeviceContext->DrawImage(colorMatrixEffect.Get(), D2D1::Point2F(position.x, position.y), destRect, D2D1_INTERPOLATION_MODE_LINEAR);

            d2dDeviceContext->Flush();
        };

        d2dDeviceContext->EndDraw();
        
        targetBitmap.Reset();
        colorMatrixEffect.Reset();
    };
};

void OverFX::TransferGamma(ImVec4 position, float strength) {
    if (!OverFX::init || !d2dDeviceContext || !sourceBitmap)
        return;
    
    if (sourceBitmap && SUCCEEDED(d2dDeviceContext->CreateEffect(CLSID_D2D1GammaTransfer, &gammaTransferEffect))) {
        d2dDeviceContext->SetTarget(sourceBitmap.Get());
        d2dDeviceContext->BeginDraw();

        D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(sourceBitmap->GetPixelFormat());
        Microsoft::WRL::ComPtr<ID2D1Bitmap> targetBitmap;
        HRESULT hr = d2dDeviceContext->CreateBitmap(sourceBitmap->GetPixelSize(), props, &targetBitmap);
        
        if (SUCCEEDED(hr)) {
            auto destPoint = D2D1::Point2U(0, 0);
            auto rect = D2D1::RectU(0, 0, static_cast<UINT32>(position.z), static_cast<UINT32>(position.w));
            targetBitmap->CopyFromBitmap(&destPoint, sourceBitmap.Get(), &rect);

            gammaTransferEffect->SetInput(0, targetBitmap.Get());
            gammaTransferEffect->SetValue(D2D1_GAMMATRANSFER_PROP_RED_EXPONENT, strength);
            gammaTransferEffect->SetValue(D2D1_GAMMATRANSFER_PROP_BLUE_EXPONENT, strength);
            gammaTransferEffect->SetValue(D2D1_GAMMATRANSFER_PROP_GREEN_EXPONENT, strength);

            D2D1_RECT_F destRect = D2D1::RectF(position.x, position.y, position.z, position.w);
            d2dDeviceContext->DrawImage(gammaTransferEffect.Get(), D2D1::Point2F(position.x, position.y), destRect, D2D1_INTERPOLATION_MODE_LINEAR);

            d2dDeviceContext->Flush();
        };

        d2dDeviceContext->EndDraw();
        
        targetBitmap.Reset();
        gammaTransferEffect.Reset();
    };
};

void OverFX::CreateBlur(ImVec4 position, float strength) {
    if (!OverFX::init || !d2dDeviceContext || !sourceBitmap)
        return;
    
    if (sourceBitmap && SUCCEEDED(d2dDeviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &blurEffect))) {
        d2dDeviceContext->SetTarget(sourceBitmap.Get());
        d2dDeviceContext->BeginDraw();

        D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(sourceBitmap->GetPixelFormat());
        Microsoft::WRL::ComPtr<ID2D1Bitmap> targetBitmap;
        HRESULT hr = d2dDeviceContext->CreateBitmap(sourceBitmap->GetPixelSize(), props, &targetBitmap);
        
        if (SUCCEEDED(hr)) {
            auto destPoint = D2D1::Point2U(0, 0);
            auto rect = D2D1::RectU(0, 0, static_cast<UINT32>(position.z), static_cast<UINT32>(position.w));
            targetBitmap->CopyFromBitmap(&destPoint, sourceBitmap.Get(), &rect);

            blurEffect->SetInput(0, targetBitmap.Get());
            blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, strength * 10);

            D2D1_RECT_F destRect = D2D1::RectF(position.x, position.y, position.z, position.w);
            d2dDeviceContext->DrawImage(blurEffect.Get(), D2D1::Point2F(position.x, position.y), destRect, D2D1_INTERPOLATION_MODE_LINEAR);

            d2dDeviceContext->Flush();
        };

        d2dDeviceContext->EndDraw();
        
        targetBitmap.Reset();
        blurEffect.Reset();
    };
};

void OverFX::RotateHue(ImVec4 position, float rotation) {
    if (!OverFX::init || !d2dDeviceContext || !sourceBitmap)
        return;
    
    if (sourceBitmap && SUCCEEDED(d2dDeviceContext->CreateEffect(CLSID_D2D1HueRotation, &hueRotationEffect))) {
        d2dDeviceContext->SetTarget(sourceBitmap.Get());
        d2dDeviceContext->BeginDraw();

        D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(sourceBitmap->GetPixelFormat());
        Microsoft::WRL::ComPtr<ID2D1Bitmap> targetBitmap;
        HRESULT hr = d2dDeviceContext->CreateBitmap(sourceBitmap->GetPixelSize(), props, &targetBitmap);
        
        if (SUCCEEDED(hr)) {
            auto destPoint = D2D1::Point2U(0, 0);
            auto rect = D2D1::RectU(0, 0, static_cast<UINT32>(position.z), static_cast<UINT32>(position.w));
            targetBitmap->CopyFromBitmap(&destPoint, sourceBitmap.Get(), &rect);

            hueRotationEffect->SetInput(0, targetBitmap.Get());
            hueRotationEffect->SetValue(D2D1_HUEROTATION_PROP_ANGLE, rotation);

            D2D1_RECT_F destRect = D2D1::RectF(position.x, position.y, position.z, position.w);
            d2dDeviceContext->DrawImage(hueRotationEffect.Get(), D2D1::Point2F(position.x, position.y), destRect, D2D1_INTERPOLATION_MODE_LINEAR);

            d2dDeviceContext->Flush();
        };

        d2dDeviceContext->EndDraw();
        
        targetBitmap.Reset();
        hueRotationEffect.Reset();
    };
};