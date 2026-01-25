#pragma once

#include <string>
#include <vector>

class Client;
class Category;
class ClientContext;

struct EventToken;
class EventDispatcher;

class Module {
public:
    explicit Module(Category*, std::string, std::string = "") noexcept;
    ~Module() noexcept;

    [[nodiscard]] Client* getClient() const noexcept;
    [[nodiscard]] Category* getCategory() const noexcept;
    [[nodiscard]] ClientContext* getContext() const noexcept;
    [[nodiscard]] const std::string& getName() const noexcept;
    [[nodiscard]] const std::string& getDesc() const noexcept;

    void setEnabled(bool) noexcept;
    bool isEnabled() const noexcept;
protected:
    virtual void onEnable() {};
    virtual void onDisable() {};
    virtual void onTick() {};

    std::vector<EventToken> mEventTokens;
private:
    Category* catPtr;
    std::string mName;
    std::string mDesc;

    bool mWasEnabled = false, mIsEnabled = false;
};