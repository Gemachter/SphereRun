#include "easyscript/SceneManager.hpp"
#include "easyscript/Main.hpp"
#include "LevelManager.hpp"

#include <iostream>


int main(int argc, char **argv) {
    Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context());
    Urho3D::SharedPtr<Game::Main<Game::LevelManager>> application(new Game::Main<Game::LevelManager>(context));
    application->GetEngineParameters()[Urho3D::EP_VSYNC] = true;
    application->Run();
}
