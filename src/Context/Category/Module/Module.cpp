#include "Module.h"

#include "../Category.h"
#include "../../../Client.h"
#include "../../ClientContext.h"

Module::Module(Category* cat, std::string name, std::string desc) noexcept : catPtr(cat), mName(std::move(name)), mDesc(std::move(desc)) {
    if(ClientContext* clientCtx = getContext()) {
        mEventTokens.push_back(
            clientCtx->getEvents().Subscribe<Events::OnTick>(
                [&](const Events::OnTick& ev) {
                    if(mIsEnabled) {
                        onTick();
                    };
                }
            )
        );
    };
};

Module::~Module() noexcept {
    if(ClientContext* clientCtx = getContext()) {
        for(auto& t : mEventTokens) {
            clientCtx->getEvents().Unsubscribe(t);
        };
    };
};

Client* Module::getClient() const noexcept {
    if(Client* client = (getContext() ? getContext()->getClient() : nullptr)) {
        return client;
    };
    return nullptr;
};

Category* Module::getCategory() const noexcept {
    return catPtr;
};

ClientContext* Module::getContext() const noexcept {
    if(ClientContext* clientCtx = (catPtr ? catPtr->getContext() : nullptr)) {
        return clientCtx;
    };
    return nullptr;
};

const std::string& Module::getName() const noexcept {
    return mName;
};

const std::string& Module::getDesc() const noexcept {
    return mDesc;
};

void Module::setEnabled(bool state) noexcept {
    mIsEnabled = state;

    if(mWasEnabled != mIsEnabled) {
        if(mIsEnabled) {
            onEnable();
        } else {
            onDisable();
        };
        mWasEnabled = mIsEnabled;
    };
};

bool Module::isEnabled() const noexcept {
    return mIsEnabled;
};