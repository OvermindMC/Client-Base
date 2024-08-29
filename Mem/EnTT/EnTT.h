#pragma once

#include <entt/entity/entity.hpp>

struct EntityId {
    std::uint32_t rawId;

    [[nodiscard]] constexpr bool operator==(const EntityId& other) const = default;

    [[nodiscard]] constexpr operator std::uint32_t() const {
        return this->rawId;
    }
};

struct EntityIdTraits {
    using value_type = EntityId;

    using entity_type = std::uint32_t;
    using version_type = std::uint16_t;

    static constexpr entity_type entity_mask = 0x3FFFF; // lower 18 bits of raw id
    static constexpr entity_type version_mask = 0x3FFF; // upper 14 bits of raw id
};

template<>
struct entt::entt_traits<EntityId> : entt::basic_entt_traits<EntityIdTraits> {
    static constexpr std::size_t page_size = 2048;
};

template<typename Type>
struct entt::storage_type<Type, EntityId> {
    using type = basic_storage<Type, EntityId>;
};

#include <entt/entity/registry.hpp>