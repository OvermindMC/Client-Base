#pragma once

#include "../../Mem/Mem.h"

class ClientContext;

class BaseHook {
public:
    explicit BaseHook(ClientContext*, std::string, void*) noexcept;
    virtual ~BaseHook() = default;
    
    [[nodiscard]] ClientContext* getContext() const noexcept;
    [[nodiscard]] const std::string& getName() const noexcept;

    void LogReq(std::string) noexcept;
protected:
    ClientContext* ctxPtr;
    std::string mName;
    void* mAddr;
};

template<typename Ret, typename... Args>
class Hook : public BaseHook {
public:
    using Func = Ret(__thiscall*)(Args...);
    using Callback = std::function<Ret(Hook&, Args...)>;

    explicit Hook(ClientContext* ctx, std::string_view name, void* addr, Callback cb) noexcept : BaseHook(ctx, std::move(std::string(name)), addr), callback(std::move(cb)) {
        sInstance = this;

        auto status = MH_CreateHook(
            addr,
            &Detour,
            reinterpret_cast<void**>(&func)
        );

        if (status == MH_OK)
            MH_EnableHook(addr);

        std::ostringstream ss;
        ss << std::hex << mAddr;
        
        LogReq(
            std::string(status == MH_OK ? "Hooked" : "Failed to hook") + " [ " + getName() + " ]-[ " + ss.str() + " ]"
        );
    };

    ~Hook() noexcept override {
        MH_DisableHook(mAddr);
        MH_RemoveHook(mAddr);
        sInstance = nullptr;
    };

    Ret CallOriginal(Args... args) {
        if constexpr (std::is_void_v<Ret>) {
            if(func)
                func(args...);
        } else {
            return func ? func(args...) : Ret{};
        };
    };

private:
    static Ret __fastcall Detour(Args... args) {
        return sInstance->Invoke(args...);
    };

    Ret Invoke(Args... args) {
        if(ClientContext* clientCtx = getContext()) {
            if(!clientCtx->IsShuttingDown()) {
                return callback(*this, args...);
            };
        };
        return reinterpret_cast<Func>(mAddr)(args...);
    };

private:
    inline static Hook* sInstance = nullptr;

    Func func{};
    Callback callback;
};

template<typename T>
struct HookTraits {
    static constexpr std::string_view Name = "";
    static void* GetTarget() { return nullptr; };
};