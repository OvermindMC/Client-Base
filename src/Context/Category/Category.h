#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <memory>

class ClientContext;
class Module;

class Category {
public:
    explicit Category(ClientContext*, std::string) noexcept;
    ~Category() noexcept;

    [[nodiscard]] ClientContext* getContext() const noexcept;
    [[nodiscard]] const std::string& getName() const noexcept;

    void addModule(std::unique_ptr<Module>) noexcept;
    [[nodiscard]] const std::vector<std::unique_ptr<Module>>& getModules() const noexcept;
private:
    ClientContext* ctxPtr;
    std::string mName;

    std::vector<std::unique_ptr<Module>> mModules;
};