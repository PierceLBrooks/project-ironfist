#ifndef LUA_UTILS_H
#define LUA_UTILS_H

extern "C" {
#include "lua/src/lua.h"
#include "lua/src/lualib.h"
#include "lua/src/lauxlib.h"
}

void lua_pusharray_int(lua_State *L, int idx, int i);
void lua_pusharray_nil(lua_State *L, int idx);
void lua_pusharray_str(lua_State *L, int idx, const std::string& str);
void lua_pusharray_str(lua_State *L, int idx, const char* str);
void lua_pusharray(lua_State *L, int idx);
template <typename... Args>
void lua_pusharray(lua_State *L, int idx, int i, Args&&... args) {
	lua_pusharray_int(L, idx, i);
	lua_pusharray(L, idx+1, std::forward<Args>(args)...);
}
template <typename... Args>
void lua_pusharray(lua_State *L, int idx, void* nil, Args&&... args) {
	lua_pusharray_nil(L, idx);
	lua_pusharray(L, idx+1, std::forward<Args>(args)...);
}
template <typename... Args>
void lua_pusharray(lua_State *L, int idx, const std::string& str, Args&&... args) {
	lua_pusharray_str(L, idx, str);
	lua_pusharray(L, idx+1, std::forward<Args>(args)...);
}
template <typename... Args>
void lua_pusharray(lua_State *L, int idx, const char* str, Args&&... args) {
	lua_pusharray_str(L, idx, str);
	lua_pusharray(L, idx+1, std::forward<Args>(args)...);
}

void lua_setconst_int(lua_State *L, const char* nam, int i);
void lua_setconst_nil(lua_State *L, const char* nam);
void lua_setconst_str(lua_State *L, const char* nam, const std::string& str);
void lua_setconst_str(lua_State *L, const char* nam, const char* str);
template <typename... Args>
void lua_setconst_array(lua_State *L, const char* nam, Args&&... args) {
	lua_newtable(L);//https://stackoverflow.com/questions/37854422/how-to-create-table-in-table-in-lua-5-1-using-c-api
	lua_pusharray(L, 0, std::forward<Args>(args)...);
	lua_setglobal(L, nam);
}

void DisplayLuaError(lua_State *L);
int LuaGlobalExists(lua_State *L, const char* nam);

#endif