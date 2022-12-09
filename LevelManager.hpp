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

    void ReloadLevel() {
        LoadScene("Scenes/"+level+".xml");
    }
    void LoadLevel(eastl::string nlevel) {
        level = nlevel;
        ReloadLevel();
    }

    void Start() {
        Variant v;
        v.SetCustom<LevelManager*>(this);
        app->SetGlobalVar("LevelManager", v);
        ReloadLevel();
    }
};
}
#endif // LEVELMANAGER_HPP
