#pragma once

#include "Game/Minecraft.h"
#include "Utils/Utils.h"
#include "Mem/Mem.h"

class ClientContext;

class Client {
public:
    Client();
    ~Client();

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;
    
    struct ClientRequest {
        struct LogMessageData { std::string message; };
        struct ShutDownCode { int code; std::string errOutput; };
        
        enum class ClientReqType {
            LogMessage, Shutdown
        };
        
        using ClientRequestData = std::variant<LogMessageData, ShutDownCode>;
        
        ClientReqType type;
        ClientRequestData data;
        
        static ClientRequest Log(std::string message) {
            return {
                ClientReqType::LogMessage,
                LogMessageData{ std::move(message) }
            };
        };
        
        static ClientRequest ShutDown(int code, std::string errOutput = "") {
            return {
                ClientReqType::Shutdown,
                ShutDownCode{ code, errOutput }
            };
        };
    };
    
    bool IsRunning() const noexcept;
    void PushReq(ClientRequest) noexcept;
private:
    std::atomic<bool> mIsRunning{true};
    std::unique_ptr<ClientContext> clientCtx;
    
    std::mutex mReqMutex;
    std::condition_variable mReqCond;
    std::deque<ClientRequest> mRequests;
    
    void BaseTick();
    void HandleRequest(ClientRequest);
};