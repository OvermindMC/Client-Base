#pragma once

#include "../../../../../Mem/Mem.h"

struct EntityComponent {};

class ActorOwnerComponent : public EntityComponent {
public:
    class Actor* mActor;
};

struct RuntimeIDComponent : public EntityComponent {
    uint64_t mRuntimeId;
};

struct ActorTypeComponent : public EntityComponent {
    uint8_t mTypeId;
};

struct StateVectorComponent : public EntityComponent {
    Vec3<float> mPos;
    Vec3<float> mPosOld;
    Vec3<float> mMotion;
};

struct SneakingComponent : public EntityComponent {
    float mSneakSpeed;
};

struct MovementSpeedComponent : public EntityComponent {
    float mSpeed;
};

struct ActorRotationComponent : public EntityComponent {
    Vec2<float> mRot, mOldRot;
};

struct MaxAutoStepComponent : public EntityComponent {
    float stepHeight;

    MaxAutoStepComponent(const float& v) : stepHeight(v) {};
};

struct ActorSetPositionRequestComponent : public EntityComponent {
    Vec3<float> mPos;

    ActorSetPositionRequestComponent(const Vec3<float>& position) : mPos(position) {};
};

struct ItemInUseComponent : public EntityComponent {};
struct BlockMovementSlowdownMultiplierComponent : public EntityComponent {};

struct CollisionFlagComponent : public EntityComponent {};
struct VerticalCollisionFlagComponent : public EntityComponent {};
struct HorizontalCollisionFlagComponent : public EntityComponent {};

struct MobIsJumpingFlagComponent : public EntityComponent {};

struct WasInWaterFlagComponent : public EntityComponent {};
struct WasInLavaFlagComponent : public EntityComponent {};

struct ActorIsImmobileFlagComponent : public EntityComponent {};
struct JumpFromGroundRequestComponent : public EntityComponent {};

enum class AbilitiesIndex : size_t {
    CanBuild = 0,
    CanMine,
    UseDoorsAndSwitches,
    CanOpenContainers,
    AttackPlayers,
    AttackMobs,
    OperatorCommands,
    Teleport,
    Invulnerable,
    Flying,
    MayFly,
    Instabuild,
    Lightning,
    FlySpeed,
    WalkSpeed,
    Muted,
    WorldBuilder,
    NoClip,
    PrivilegedBuilder
};

struct AbilitiesComponent : public EntityComponent {
    char pad[0xEC];

    template<typename T>
    T* getAbility(AbilitiesIndex ability) {
        size_t offset = 0xEC + static_cast<size_t>(ability) * (1 + 0xB);
        return reinterpret_cast<T*>(reinterpret_cast<char*>(this) + offset);
    };

    void setAbility(AbilitiesIndex ability, bool value) {
        *this->getAbility<bool>(ability) = value;
    };

    void setAbility(AbilitiesIndex ability, float value) {
        *this->getAbility<float>(ability) = value;
    };
};