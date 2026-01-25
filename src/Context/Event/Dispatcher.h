#pragma once

#include <unordered_map>
#include <functional>
#include <typeindex>
#include <algorithm>
#include <vector>
#include <atomic>
#include <mutex>

struct EventToken {
    std::type_index type;
    size_t id;
};

class EventDispatcher {
public:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;

    template <typename Event>
    EventToken Subscribe(std::function<void(const Event&)> handler) {
        std::lock_guard<std::mutex> lock(mMutex);

        size_t id = mNextId.fetch_add(1, std::memory_order_relaxed);

        mHandlers[typeid(Event)].push_back({
            id,
            [fn = std::move(handler)](const void* ev) {
                fn(*static_cast<const Event*>(ev));
            }
        });

        return { typeid(Event), id };
    };

    template <typename Event>
    void Dispatch(const Event& event) const {
        std::vector<RawHandler> handlersCopy;

        {
            std::lock_guard<std::mutex> lock(mMutex);
            auto it = mHandlers.find(typeid(Event));
            if (it == mHandlers.end())
                return;

            for (auto& h : it->second)
                handlersCopy.push_back(h.fn);
        };

        for (auto& handler : handlersCopy)
            handler(&event);
    };

    void Unsubscribe(const EventToken& token) noexcept {
        std::lock_guard<std::mutex> lock(mMutex);

        auto it = mHandlers.find(token.type);
        if (it == mHandlers.end())
            return;

        auto& vec = it->second;
        vec.erase(
            std::remove_if(vec.begin(), vec.end(),
                [&](const HandlerEntry& h) { return h.id == token.id; }),
            vec.end()
        );
    };

    void Clear() noexcept {
        std::lock_guard<std::mutex> lock(mMutex);
        mHandlers.clear();
    };

private:
    mutable std::mutex mMutex;

    using RawHandler = std::function<void(const void*)>;

    struct HandlerEntry {
        size_t id;
        RawHandler fn;
    };

    std::unordered_map<std::type_index, std::vector<HandlerEntry>> mHandlers;
    std::atomic<size_t> mNextId{0};
};