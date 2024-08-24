#pragma once

#include <libhat/Scanner.hpp>
#include <string_view>
#include <string>

class BaseSig {
public:
    ~BaseSig() = default;
    virtual std::string getName() const = 0;

    enum class Type : int {
        Function = 1, VTable = 2
    };

    template<typename T>
    T find(std::string pattern, Type type, std::string tModule = "Minecraft.Windows.exe") {
        hat::signature parsed = hat::parse_signature(pattern).value();
        hat::signature_view sig_view = hat::signature_view(parsed);

        hat::scan_result result = hat::find_pattern(sig_view, tModule.length() > 0 ? hat::process::get_module(tModule) : hat::process::get_process_module());

        if(type == Type::Function) {
            return result.has_result() ? (T)result.get() : T{};
        } else if(type == Type::VTable) {
            if(result.has_result()) {
                uintptr_t ptr = (uintptr_t)(result.get());
                
                int offset = *(int*)(ptr + 3);
                return (T)(ptr + offset + 7);
            };
        };

        return T{};
    };
};

template<typename T>
class Sig : public BaseSig {
public:
    Sig(std::string name, std::string pattern, BaseSig::Type type, std::string tModule = "Minecraft.Windows.exe") {
        this->target = this->find<T>(pattern, type, tModule);
        this->sigName = name.c_str();
    };

    std::string getName() const override {
        return this->sigName;
    };

    T get() {
        return this->target;
    };
private:
    T target = T{};
    std::string sigName;
};