extern "C" {
#include "lua/src/lua.h"
#include "lua/src/lualib.h"
#include "lua/src/lauxlib.h"
}

#include "gui/dialog.h"
#include "scripting/lua_utils.h"

void lua_pusharray_int(lua_State *L, int idx, int i) {
	lua_pushinteger(L, i);
	lua_rawseti(L, -2, idx);
}

void lua_pusharray_nil(lua_State *L, int idx) {
	lua_pushnil(L);
	lua_rawseti(L, -2, idx);
}

void lua_pusharray_str(lua_State *L, int idx, const std::string& str) {
	lua_pusharray_str(L, idx, str.c_str());
}

void lua_pusharray_str(lua_State *L, int idx, const char* str) {
	lua_pushstring(L, str);
	lua_rawseti(L, -2, idx);
}

void lua_pusharray(lua_State *L, int idx) {

}

void lua_setconst_int(lua_State *L, const char* nam, int i) {
	lua_pushinteger(L, i);
	lua_setglobal(L, nam);
}

void lua_setconst_nil(lua_State *L, const char* nam) {
	lua_pushnil(L);
	lua_setglobal(L, nam);
}

void lua_setconst_str(lua_State *L, const char* nam, const std::string& str) {
	lua_setconst_str(L, nam, str.c_str());
}

void lua_setconst_str(lua_State *L, const char* nam, const char* str) {
	lua_pushstring(L, str);
	lua_setglobal(L, nam);
}

void DisplayLuaError(lua_State *L) {
  const char* msg = luaL_checkstring(L, -1);
  DisplayError(msg, "Script Error");
  lua_pop(L, 1);
}

int LuaGlobalExists(lua_State *L, const char* nam) {
  int t = lua_getglobal(L, nam);
  lua_pop(L, 1);
  return t != LUA_TNIL;
}