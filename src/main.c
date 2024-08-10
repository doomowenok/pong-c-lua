#include <stdio.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

void lua_example_dofile(void)
{
    lua_State* lua = luaL_newstate();

    luaL_openlibs(lua);
    luaL_dofile(lua, "./scripts/factorial.lua");

    lua_close(lua);
}

void lua_example_getvar(void)
{
    lua_State* lua = luaL_newstate();

    luaL_dostring(lua, "some_var = 486");
    lua_getglobal(lua, "some_var");
    lua_Number some_var_in_c = lua_tonumber(lua, -1);

    printf("The value of some_var insise C is: %d\n", (int)some_var_in_c);

    lua_close(lua);
}

void lua_example_stack(void)
{
    lua_State* lua = luaL_newstate();

    lua_pushnumber(lua, 286);   // stack [1] or stack [-3]
    lua_pushnumber(lua, 386);   // stack [2] or stack [-2]
    lua_pushnumber(lua, 486);   // stack [3] or stack [-1]

    lua_Number element;
    element = lua_tonumber(lua, -1);
    printf("The last added element in position 3 of the stack is %d\n", (int)element);

    lua_remove(lua, 2);
    element = lua_tonumber(lua, 2);
    printf("The last added element in position 2 of the stack is %d\n", (int)element);

    lua_close(lua);
}

void lua_example_call_lua_function(void)
{
    lua_State* lua = luaL_newstate();

    // Error handling from Lua.
    if(luaL_dofile(lua, "./scripts/pythagoras.lua") != LUA_OK)
    {
        luaL_error(lua, "Error: %s\n", lua_tostring(lua, -1));
        return;
    }

    lua_getglobal(lua, "pythagoras");

    if(lua_isfunction(lua, -1))
    {
        lua_pushnumber(lua, 3); // 1st function argument, a
        lua_pushnumber(lua, 4); // 2nd function argument, b

        const int NUM_ARGS = 2;
        const int NUM_RETURNS = 1;

        // Error handling from Lua.
        if(lua_pcall(lua, NUM_ARGS, NUM_RETURNS, 0) != LUA_OK)
        {
            luaL_error(lua, "Error: %s\n", lua_tostring(lua, -1));
            return;
        }

        lua_Number pythagoras_result = lua_tonumber(lua, -1);
        printf("Pythagoras is %f", (float)pythagoras_result);
    }

    lua_close(lua);
}

int native_pythagoras(lua_State* L)
{
    lua_Number b = lua_tonumber(L, -1); // get the last added parameter from the stack, b
    lua_Number a = lua_tonumber(L, -2); // get the first added parameter from the stack, a
    lua_Number result = a * a + b * b;
    lua_pushnumber(L, result);
    return 1;   // return how many values the function is returning to the stack
}

void lua_example_call_c_function(void)
{
    lua_State* lua = luaL_newstate();

    lua_pushcfunction(lua, native_pythagoras);
    lua_setglobal(lua, "native_pythagoras");

    luaL_dofile(lua, "./scripts/pythagoras-native.lua");
    lua_getglobal(lua, "pythagoras");

    if(lua_isfunction(lua, -1))
    {
        lua_pushnumber(lua, 3);
        lua_pushnumber(lua, 4);

        const int NUM_ARGS = 2;
        const int NUM_RETURNS = 1;
        lua_pcall(lua, NUM_ARGS, NUM_RETURNS, 0);
        lua_Number pythagoras_result = lua_tonumber(lua, -1);
        printf("Native pythagoras is: %f", (float)pythagoras_result);
    }

    lua_close(lua);
}

int main(int args, char* arg[])
{
    // lua_example_dofile();
    // lua_example_getvar();
    // lua_example_stack();
    // lua_example_call_lua_function();
    lua_example_call_c_function();
    return 0;
}