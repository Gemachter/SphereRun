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
    levelManager = GetGlobalVar("LevelManager").GetCustom<LevelManager*>();

    auto* renderer = GetSubsystem<Renderer>();

    // Set viewport camera
    SharedPtr<Viewport> viewport(new Viewport(context_, GetScene(), GetNode()->GetChild("Camera")->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);

    // Set audio audio listener
    GetSubsystem<Audio>()->SetListener(GetNode()->GetComponent<SoundListener>());
}

void Player::FixedUpdate(float timeStep) {
    auto input = GetSubsystem<Input>();

    // Escape key handling
    if (input->GetKeyDown(Key::KEY_ESCAPE)) {
        exit(0);
    }
}

void Player::Update(float timeStep) {
    auto* input = GetSubsystem<Input>();

    // Camera
    auto mMove = input->GetMouseMove();
    if (mMove.x_ || mMove.y_) {
        { // Head rotation
            auto headRot = GetNode()->GetChild("Camera")->GetRotation().EulerAngles();
            headRot.x_ = Max(Min(headRot.x_ + mMove.y_ / 8.0f, 80), -80);
            GetNode()->GetChild("Camera")->SetRotation(Quaternion(headRot));
        }
        { // Body rotation
            GetNode()->Rotate({0, mMove.x_ / 4.0f, 0});
        }
    }
}
}
