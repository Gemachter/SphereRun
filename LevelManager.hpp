#pragma once

namespace Scatter {
class LevelManager;
}
#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP
#ifndef NDEBUG
#define URHO3D_DEBUG_ASSERT
#endif

#include "easyscript/Namespace.hpp"
#include "easyscript/SceneManager.hpp"

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Core/Variant.h>



namespace Game {
class LevelManager : public SceneManager {
    eastl::string level = "main";

public:
    using SceneManager::SceneManager;

    void reloadLevel() {
        loadScene("Scenes/"+level+".xml");
    }
    void loadLevel(eastl::string nlevel) {
        level = nlevel;
        reloadLevel();
    }

    void Start() {
        Variant v;
        v.SetCustom<LevelManager*>(this);
        app->SetGlobalVar("LevelManager", v);
        reloadLevel();
    }
};
}
#endif // LEVELMANAGER_HPP
