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

struct CollisionFlagComponent : public EntityComponent {};
struct VerticalCollisionFlagComponent : public EntityComponent {};
struct HorizontalCollisionFlagComponent : public EntityComponent {};

struct MobIsJumpingFlagComponent : public EntityComponent {};

struct WasInWaterFlagComponent : public EntityComponent {};
struct WasInLavaFlagComponent : public EntityComponent {};

struct ActorIsImmobileFlagComponent : public EntityComponent {};
struct JumpFromGroundRequestComponent : public EntityComponent {};