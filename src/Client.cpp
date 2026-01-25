#include "Client.h"
#include "Context/ClientContext.h"

Client::Client() : mIsRunning(true) {
    Debugger::Init();
    Debugger::Log("Initialising Client");

    clientCtx = std::make_unique<ClientContext>(this);
    this->BaseTick();
};

Client::~Client() {
    mIsRunning.store(false, std::memory_order_release);
    mReqCond.notify_all();
    
    clientCtx.reset();
    Debugger::Destroy();
};

bool Client::IsRunning() const noexcept {
    return mIsRunning.load(std::memory_order_acquire);
};

void Client::PushReq(ClientRequest request) noexcept {
    {
        std::unique_lock<std::mutex> lock(mReqMutex);
        this->mRequests.push_back(request);
    };
    
    this->mReqCond.notify_one();
};

void Client::BaseTick() {
    constexpr auto tickInterval = std::chrono::milliseconds(16);

    while(mIsRunning.load(std::memory_order_acquire)) {
        ClientRequest req;
        bool hasReq = false;
        
        {
            std::unique_lock<std::mutex> lock(mReqMutex);

            mReqCond.wait_for(lock, tickInterval, [&]() {
                return !mRequests.empty() || !mIsRunning.load();
            });

            if(!mIsRunning.load() && mRequests.empty())
                break;

            if(!mRequests.empty()) {
                req = std::move(mRequests.front());
                mRequests.pop_front();
                hasReq = true;
            };
        };

        if(hasReq) {
            HandleRequest(req);
        };

        if(clientCtx && mIsRunning.load(std::memory_order_acquire)) {
            clientCtx->getEvents().Dispatch<Events::OnTick>({});
        };
    };
};

void Client::HandleRequest(ClientRequest request) {
    if(request.type == ClientRequest::ClientReqType::LogMessage) {
        const auto& data = std::get<ClientRequest::LogMessageData>(request.data);
        Debugger::Log(data.message);
    } else if(request.type == ClientRequest::ClientReqType::Shutdown) {
        const auto& data = std::get<ClientRequest::ShutDownCode>(request.data);

        std::string message =
            "Shutting down, err code: " + std::to_string(data.code);

        if (data.code > 0 && !data.errOutput.empty())
            message += "\nReason: " + data.errOutput;

        Debugger::Log(message);

        Sleep(data.code > 0 ? 5000 : 1000);

        mIsRunning.store(false, std::memory_order_release);
        mReqCond.notify_all();
    };
};