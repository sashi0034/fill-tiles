//
// Created by sashi0034 on 2022/07/28.
//

#include "string"
#include "../gameEngine/gameEngine.h"
#include "LuaEngine.h"


namespace inGame
{

    LuaEngine::LuaEngine()
    {
        m_Lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::string, sol::lib::os, sol::lib::math,
                             sol::lib::table, sol::lib::debug, sol::lib::bit32, sol::lib::io, sol::lib::ffi, sol::lib::utf8);

        init();
    }

    void LuaEngine::init()
    {
        sol::protected_function_result result = m_Lua.safe_script_file(R"(assets/script/Test.lua)", &sol::script_pass_on_error);
        if (!result.valid())
        {
            sol::error error = result;
            LOG_ERR << error.what() << std::endl;
        }
        std::string str = m_Lua["Test"]();
        std::cout << str << "\n";
    }

    sol::state &LuaEngine::GetState()
    {
        return m_Lua;
    }
} // inGame