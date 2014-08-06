#include "lua_GameController_auto.hpp"
#include "GameController.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_GameController_GameController_step(lua_State* tolua_S)
{
    int argc = 0;
    GameController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_GameController_GameController_step'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->step(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "step",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_GameController_GameController_step'.",&tolua_err);
#endif

    return 0;
}
int lua_GameController_GameController_run(lua_State* tolua_S)
{
    int argc = 0;
    GameController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_GameController_GameController_run'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->run();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "run",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_GameController_GameController_run'.",&tolua_err);
#endif

    return 0;
}
int lua_GameController_GameController_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        GameController* ret = GameController::getInstance();
        object_to_luaval<GameController>(tolua_S, "GameController",(GameController*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_GameController_GameController_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_GameController_GameController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    GameController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new GameController();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"GameController");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameController",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_GameController_GameController_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_GameController_GameController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameController)");
    return 0;
}

int lua_register_GameController_GameController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"GameController");
    tolua_cclass(tolua_S,"GameController","GameController","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"GameController");
        tolua_function(tolua_S,"step",lua_GameController_GameController_step);
        tolua_function(tolua_S,"run",lua_GameController_GameController_run);
        tolua_function(tolua_S,"new",lua_GameController_GameController_constructor);
        tolua_function(tolua_S,"getInstance", lua_GameController_GameController_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(GameController).name();
    g_luaType[typeName] = "GameController";
    g_typeCast["GameController"] = "GameController";
    return 1;
}
TOLUA_API int register_all_GameController(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_GameController_GameController(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

