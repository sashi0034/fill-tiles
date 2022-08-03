//
// Created by sashi0034 on 2022/07/28.
//

#ifndef FILL_TILES_LUAENGINE_H
#define FILL_TILES_LUAENGINE_H

#include "sol.hpp"

namespace inGame
{

    class LuaEngine
    {
    public:
        LuaEngine();
        sol::state& GetState();
        void ReloadAllFiles();
    private:
        const std::string  directoryPath = "assets/lua";
        sol::state m_Lua{};
        bool tryInit();
    };

} // gameEngine

#endif //FILL_TILES_LUAENGINE_H
