#pragma once

#include "../Manager.h"

class BaseHook {
public:
    virtual ~BaseHook() = default;
    virtual std::string getName() const = 0;
};

template<typename T, typename... Args>
class Hook : public BaseHook {
public:
    using Func = T(__thiscall*)(Args...);
    Func func = nullptr;

    static inline std::function<T(Args...)> callback = [&](Args... args) -> T { return T{}; };
    static T detourCallback(Args... args) {
        return callback ? callback(args...) : T{};
    };

    Hook(Manager* mgr, std::string name, void* targetFunc, std::function<T(Args...)> hook_callback) : mgrPtr(mgr), hookName(name), tAddr(targetFunc) {
        this->callback = hook_callback;

        MH_STATUS hS = MH_CreateHook(targetFunc, &detourCallback, (LPVOID*)&func);
        std::ostringstream ss;

        ss << name << " " << std::hex << targetFunc;
        Debugger::log("Hook " + 
            std::string(hS == MH_OK ? "Success" : "Failed") + " " + ss.str()
        );

        if(hS == MH_OK)
            MH_EnableHook(targetFunc);
    };

    ~Hook() override {
        MH_DisableHook(this->tAddr);
        MH_RemoveHook(this->tAddr);
        this->tAddr = nullptr;
    };

    std::string getName() const override {
        return this->hookName;
    };

    Manager* getMgr() const {
        return this->mgrPtr;
    };
private:
    Manager* mgrPtr = nullptr;
    void* tAddr = nullptr;
    std::string hookName;
};