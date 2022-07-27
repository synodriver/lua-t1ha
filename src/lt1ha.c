#include <stdlib.h>
#include <stdint.h>

#include "lua.h"
#include "lauxlib.h"

#include "t1ha.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */


static int
lhash(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a data and seed to hash");
    }
    size_t size;
    const void *data = (const void *) luaL_checklstring(L, 1, &size);
    uint64_t seed = (uint64_t) luaL_checkinteger(L, 2);
    uint64_t h = t1ha0(data, size, seed);
    lua_pushinteger(L, (lua_Integer) h);
    return 1;
}

static int
lhash128(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a data and seed to hash");
    }
    size_t size;
    const void *data = (const void *) luaL_checklstring(L, 1, &size);
    uint64_t seed = (uint64_t) luaL_checkinteger(L, 2);
    uint64_t extra; // high 64 bit
    uint64_t h = t1ha2_atonce128(&extra, data, size, seed);
    lua_pushinteger(L, (lua_Integer) extra);
    lua_pushinteger(L, (lua_Integer) h);
    return 2;
}

static int
lnewhasher(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have 2 seeds");
    }
    uint64_t seed_x = (uint64_t) luaL_checkinteger(L, 1);
    uint64_t seed_y = (uint64_t) luaL_checkinteger(L, 2);

    t1ha_context_t *ctx = (t1ha_context_t *) lua_newuserdata(L, sizeof(t1ha_context_t));
    t1ha2_init(ctx, seed_x, seed_y);
    luaL_setmetatable(L, "t1ha.Hash");
    return 1;
}


static int
lupdate(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a string to update");
    }
    t1ha_context_t *ctx = (t1ha_context_t *) luaL_checkudata(L, 1, "t1ha.Hash");
    size_t size;
    void *data = (void *) luaL_checklstring(L, 2, &size);
    t1ha2_update(ctx, data, size);
    return 0;
}

static int
lfinal(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "this method have no param");
    }
    t1ha_context_t *ctx = (t1ha_context_t *) luaL_checkudata(L, 1, "t1ha.Hash");
    uint64_t extra_data;
    uint64_t h = t1ha2_final(ctx, &extra_data);
    lua_pushinteger(L, (lua_Integer) extra_data);
    lua_pushinteger(L, (lua_Integer) h);
    return 2;
}

static luaL_Reg lua_funcs[] = {
        {"newhasher", &lnewhasher},
        {"hash128",   &lhash128},
        {"hash",      &lhash},
        {NULL, NULL}
};

static luaL_Reg lua_hash_methods[] = {
        {"update", &lupdate},
        {"final",  &lfinal},
        {NULL, NULL}
};

DLLEXPORT int luaopen_t1ha(lua_State *L)
{
    if (!luaL_newmetatable(L, "t1ha.Hash"))
    {
        return luaL_error(L, "t1ha.Hash already in register");
    }
    lua_pushvalue(L, -1); // mt mt
    lua_setfield(L, -2, "__index"); // mt
    luaL_setfuncs(L, lua_hash_methods, 0); // mt

    luaL_newlib(L, lua_funcs);
    return 1;
}