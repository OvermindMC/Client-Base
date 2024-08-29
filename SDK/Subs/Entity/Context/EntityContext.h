#pragma once

#include "Subs/Components.h"

struct EntityRegistry : std::enable_shared_from_this<EntityRegistry> {
    std::string name;
    entt::basic_registry<EntityId> registry;
    uint32_t id;
};

struct EntityContext {
    EntityRegistry& registry;
    entt::basic_registry<EntityId>& enttRegistry;
    EntityId entity;

    template<std::derived_from<EntityComponent> T>
    T* tryGetComponent() {
        return this->enttRegistry.try_get<T>(this->entity);
    };

    template<std::derived_from<EntityComponent> T>
    const T* tryGetComponent() const {
        return this->enttRegistry.try_get<T>(this->entity);
    };

    template<std::derived_from<EntityComponent>... T>
    bool hasComponent() const {
        if constexpr (sizeof...(T) > 0) {
            return (this->enttRegistry.any_of<T>(this->entity) && ...);
        } else {
            return false;
        };
    };

    template<std::derived_from<EntityComponent> T, typename... Args>
    auto addComponent(Args&&... args) -> decltype(auto) {
        return this->enttRegistry.get_or_emplace<T>(this->entity, std::forward<Args>(args)...);
    };

    template<std::derived_from<EntityComponent>... T>
    void removeComponent() const {
        (void)std::initializer_list<int>{
            (this->enttRegistry.any_of<T>(this->entity) ? (this->enttRegistry.remove<T>(this->entity), 0) : 0)...
        };
    };
};