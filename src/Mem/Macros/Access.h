#pragma once
#include <cstdint>
#include <cstddef>
#include <type_traits>

template <class T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename Ret, typename Base>
inline Ret& direct_access(Base* base, std::ptrdiff_t offset) noexcept {
    auto addr = reinterpret_cast<std::uintptr_t>(base) + static_cast<std::uintptr_t>(offset);
    return *reinterpret_cast<Ret*>(addr);
};

template <typename Ret, typename Base>
inline const Ret& direct_access(const Base* base, std::ptrdiff_t offset) noexcept {
    auto addr = reinterpret_cast<std::uintptr_t>(base) + static_cast<std::uintptr_t>(offset);
    return *reinterpret_cast<const Ret*>(addr);
};

#define AS_FIELD(type, name, getter, setter) \
    __declspec(property(get = getter, put = setter)) type name

#define BUILD_ACCESS(type, name, offset)                                              \
    using __prop_##name##_t = type;                                                   \
    __declspec(property(get = get##name, put = set##name)) __prop_##name##_t& name;   \
    __prop_##name##_t& get##name() noexcept {                                         \
        return direct_access<__prop_##name##_t>(this, offset);                        \
    }                                                                                \
    void set##name(const __prop_##name##_t& v) noexcept {                             \
        direct_access<__prop_##name##_t>(this, offset) = v;                           \
    }

template <typename Ret, typename Base>
inline Ret* direct_ptr_access(Base* base, std::ptrdiff_t offset) noexcept {
    auto addr = reinterpret_cast<std::uintptr_t>(base) + offset;
    return *reinterpret_cast<Ret**>(addr);
}

template <typename Ret, typename Base>
inline const Ret* direct_ptr_access(const Base* base, std::ptrdiff_t offset) noexcept {
    auto addr = reinterpret_cast<std::uintptr_t>(base) + offset;
    return *reinterpret_cast<Ret* const*>(addr);
}

#define BUILD_PTR_ACCESS(type, name, offset) \
    __declspec(property(get = get##name)) type* name; \
    type* get##name() noexcept { return direct_ptr_access<type>(this, offset); } \
    const type* get##name() const noexcept { return direct_ptr_access<type>(this, offset); }