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
    private:
        sol::state m_Lua{};
        void init();
    };

} // inGame

#endif //FILL_TILES_LUAENGINE_H
