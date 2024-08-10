#include <stdio.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

int main(int args, char* arg[])
{
    lua_State* lua = luaL_newstate();

    luaL_openlibs(lua);
    luaL_dofile(lua, "./scripts/factorial.lua");

    lua_close(lua);

    return 0;
}