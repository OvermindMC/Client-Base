#include "TestMod.h"
#include "../../../../ClientContext.h"
#include "../../../../../Client.h"

TestMod::TestMod(Category* c) noexcept : Module(c, "TestMod", "Module for developer testing") {
    this->setEnabled(true);

    if(ClientContext* clientCtx = getContext()) {
        mEventTokens.push_back(
            clientCtx->getEvents().Subscribe<Events::OnUIRenderCtx>(
                [&](const Events::OnUIRenderCtx& ev) {
                    static bool once = false;
                    if(!once) {
                        once = true;
                        
                        std::ostringstream ss;
                        ss << "Ctx CI: " << ev.ctx->clientInstance << "\n";
                        ss << "SDK CI: " << MC::getClientInstance() << "\n";

                        if(Client* client = getClient()) {
                            client->PushReq(
                                Client::ClientRequest::Log(
                                    ss.str()
                                )
                            );
                        };
                    };

                    static int c = 0;
                    c++;

                    if(c >= 5000) {
                        if(Client* client = getClient()) {
                            int errCode = 0; // 0-1
                            client->PushReq(
                                Client::ClientRequest::ShutDown(
                                    errCode, errCode > 0 ? "Shutdown by Ctx!" : ""
                                )
                            );
                        };
                    };

                    static int mobCount = -1;

                    Minecraft* mc = ev.ctx->clientInstance->mc;
                    auto ents = mc->getEntities();

                    if(mobCount != ents.size()) {
                        mobCount = ents.size();

                        if(Client* client = getClient()) {
                            client->PushReq(
                                Client::ClientRequest::Log(
                                    std::to_string(
                                        mobCount
                                    )
                                )
                            );
                        };
                    };
                }
            )
        );
    };
};

void TestMod::onEnable() {
    if(Client* client = getClient()) {
        client->PushReq(
            Client::ClientRequest::Log(
                "OnEnable"
            )
        );
    };
};

void TestMod::onDisable() {
    //
};

void TestMod::onTick() {
    ClientInstance* ci = MC::getClientInstance();

    static int c = 0;
    c++;

    if(c >= 5000) {
        ci->grabMouse();
        if(Client* client = getClient()) {
            client->PushReq(
                Client::ClientRequest::Log(
                    "Released Mouse!"
                )
            );
        };
    };
};