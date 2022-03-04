#include "Player.hpp"
#include "../LevelManager.hpp"

#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/OctreeQuery.h>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/UI/UI.h>



namespace Game {
void Player::Start() {
    head = GetNode()->GetChild("Head");
    handP = head->GetChild("Hand");
    levelManager = GetGlobalVar("LevelManager").GetCustom<LevelManager*>();
    kinematicController = GetNode()->CreateComponent<KinematicCharacterController>();
    kinematicController->SetHeight(1.85f);
    kinematicController->SetCollisionLayerAndMask(1, 1);
    head->SetPosition({0.0f, kinematicController->GetHeight()*0.75f, 0.0f});

    auto* renderer = GetSubsystem<Renderer>();

    // Set viewport camera
    SharedPtr<Viewport> viewport(new Viewport(context_, GetScene(), head->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);

    // Set audio audio listener
    GetSubsystem<Audio>()->SetListener(head->GetComponent<SoundListener>());
}

void Player::FixedUpdate(float timeStep) {
    auto input = GetSubsystem<Input>();

    // Escape key handling
    if (input->GetKeyDown(Key::KEY_ESCAPE)) {
        exit(0);
    }

    // Kinematic character stuff
    {
        // Update movement
        Vector3 moveDir = moveDir.ZERO;

        if (input->GetKeyDown(Key::KEY_W)) {
            moveDir += moveDir.FORWARD;
        }
        if (input->GetKeyDown(Key::KEY_S)) {
            moveDir += moveDir.BACK;
        }
        if (input->GetKeyDown(Key::KEY_A)) {
            moveDir += moveDir.LEFT;
        }
        if (input->GetKeyDown(Key::KEY_D)) {
            moveDir += moveDir.RIGHT;
        }

        // Normalize move vector so that diagonal strafing is not faster
        if (moveDir.LengthSquared() > 0.0f) {
            moveDir.Normalize();
        }

        // Walk
        kinematicController->SetWalkIncrement(GetNode()->GetRotation() * moveDir * walkSpeed / 60.0f);
    }
}

void Player::Update(float timeStep) {
    auto* input = GetSubsystem<Input>();

    // Camera
    auto mMove = input->GetMouseMove();
    if (mMove.x_ || mMove.y_) {
        { // Head rotation
            auto headRot = head->GetRotation().EulerAngles();
            headRot.x_ = Max(Min(headRot.x_ + mMove.y_ / 8.0f, 80), -80);
            head->SetRotation(Quaternion(headRot));
        }
        { // Body rotation
            GetNode()->Rotate({0, mMove.x_ / 4.0f, 0});
        }
    }
}
}
