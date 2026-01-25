#pragma once

#include "../../../../Mem/Mem.h"

struct EntityRegistry : std::enable_shared_from_this<EntityRegistry> {
    std::string name;
    entt::basic_registry<EntityId> registry;
    uint32_t id;
};

struct EntityContext {
    EntityRegistry& registry;
    entt::basic_registry<EntityId>& enttRegistry;
    EntityId entity;

    template<typename... T>
    auto tryGetComponent() const {
        if constexpr(sizeof...(T) == 1u) {
            return this->enttRegistry.try_get<std::tuple_element_t<0, std::tuple<T...>>>(this->entity);
        } else {
            return std::make_tuple(this->enttRegistry.try_get<T>(this->entity)...);
        };
    };

    template<typename... T>
    bool hasComponent() const {
        return (this->enttRegistry.all_of<T>(this->entity) || ...);
    };

    template<typename T, typename... Args>
    auto addComponent(Args&&... args) -> decltype(auto) {
        this->enttRegistry.emplace_or_replace<T>(this->entity, std::forward<Args>(args)...);
    };

    template<typename... T>
    void removeComponent() const {
        (void)std::initializer_list<int>{
            (this->enttRegistry.any_of<T>(this->entity) ? (this->enttRegistry.remove<T>(this->entity), 0) : 0)...
        };
    };
};