#include "Hook.h"
#include "../ClientContext.h"
#include "../../Client.h"

BaseHook::BaseHook(ClientContext* ctx, std::string name, void* addr) noexcept : ctxPtr(ctx), mName(std::move(name)), mAddr(addr) {
    //
};

ClientContext* BaseHook::getContext() const noexcept {
    return ctxPtr;
};

const std::string& BaseHook::getName() const noexcept {
    return mName;
};

void BaseHook::LogReq(std::string message) noexcept {
    if(Client* client = (getContext() ? getContext()->getClient() : nullptr)) {
        if(client->IsRunning()) {
            client->PushReq(
                Client::ClientRequest::Log(
                    message
                )
            );
        };
    };
};