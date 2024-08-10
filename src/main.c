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

int main(int args, char* arg[])
{
    // lua_example_dofile();
    lua_example_getvar();
    return 0;
}