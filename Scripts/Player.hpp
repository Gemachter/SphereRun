#pragma once

namespace Game {
class Player;
}
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "../easyscript/Namespace.hpp"

#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/KinematicCharacterController.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>



namespace Game {
class RoomBoundary;
class LevelManager;
class Door;

class Player final : public LogicComponent {
    URHO3D_OBJECT(Player, LogicComponent);

    static constexpr float walkSpeed = 1.6f;

    LevelManager *levelManager;
    Node *head;
    Node *handP;
    Node *hand = nullptr;

    CollisionShape* collisionShape;
    KinematicCharacterController* kinematicController;

public:
    using LogicComponent::LogicComponent;

    void Start() override;
    void FixedUpdate(float timeStep) override;
    void Update(float timeStep) override;

    Node *getHand() {
        return hand;
    }
    Node *getHead() {
        return head;
    }
};
}
#endif // PLAYER_HPP