#include "lua_ForAlive_LUAAI_auto.hpp"
#include "AI.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_ForAlive_LUAAI_AI_cleanInstructions(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_cleanInstructions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ins_tpye arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "AI:cleanInstructions");
        if(!ok)
            return 0;
        cobj->cleanInstructions(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:cleanInstructions",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_cleanInstructions'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_getHoverTime(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_getHoverTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getHoverTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:getHoverTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_getHoverTime'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_stopInstructions(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_stopInstructions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ins_tpye arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "AI:stopInstructions");
        if(!ok)
            return 0;
        cobj->stopInstructions(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:stopInstructions",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_stopInstructions'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_addInstruction(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_addInstruction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Instruction* arg0;

        ok &= luaval_to_object<Instruction>(tolua_S, 2, "Instruction",&arg0);
        if(!ok)
            return 0;
        cobj->addInstruction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:addInstruction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_addInstruction'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_a_hover(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_a_hover'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "AI:a_hover");
        if(!ok)
            return 0;
        cobj->a_hover(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:a_hover",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_a_hover'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_stopAllInstructions(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_stopAllInstructions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->stopAllInstructions();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:stopAllInstructions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_stopAllInstructions'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_popInstruction(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_popInstruction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ins_tpye arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "AI:popInstruction");
        if(!ok)
            return 0;
        cobj->popInstruction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:popInstruction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_popInstruction'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_cleanAllInstructions(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_cleanAllInstructions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->cleanAllInstructions();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:cleanAllInstructions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_cleanAllInstructions'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_update(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "AI:update");
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_update'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_finishInstruction(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_finishInstruction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
            return 0;
        cobj->finishInstruction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:finishInstruction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_finishInstruction'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_getHoverPoint(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_getHoverPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Vec2& ret = cobj->getHoverPoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:getHoverPoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_getHoverPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_setHoverPoint(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_setHoverPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "AI:setHoverPoint");
        if(!ok)
            return 0;
        cobj->setHoverPoint(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:setHoverPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_setHoverPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_init(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Biology* arg0;

        ok &= luaval_to_object<Biology>(tolua_S, 2, "Biology",&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:init",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_init'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_insertInstruction(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_insertInstruction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Instruction* arg0;

        ok &= luaval_to_object<Instruction>(tolua_S, 2, "Instruction",&arg0);
        if(!ok)
            return 0;
        cobj->insertInstruction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:insertInstruction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_insertInstruction'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_runInstruction(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_runInstruction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ins_tpye arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "AI:runInstruction");
        if(!ok)
            return 0;
        cobj->runInstruction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:runInstruction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_runInstruction'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_InformationUpdate(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_InformationUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        bool arg0;
        Biology* arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "AI:InformationUpdate");

        ok &= luaval_to_object<Biology>(tolua_S, 3, "Biology",&arg1);
        if(!ok)
            return 0;
        cobj->InformationUpdate(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:InformationUpdate",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_InformationUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_setHoverTime(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ForAlive_LUAAI_AI_setHoverTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "AI:setHoverTime");
        if(!ok)
            return 0;
        cobj->setHoverTime(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:setHoverTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_setHoverTime'.",&tolua_err);
#endif

    return 0;
}
int lua_ForAlive_LUAAI_AI_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AI",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        Biology* arg0;
        ok &= luaval_to_object<Biology>(tolua_S, 2, "Biology",&arg0);
        if(!ok)
            return 0;
        AI* ret = AI::create(arg0);
        object_to_luaval<AI>(tolua_S, "AI",(AI*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "AI:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_create'.",&tolua_err);
#endif
    return 0;
}
int lua_ForAlive_LUAAI_AI_constructor(lua_State* tolua_S)
{
    int argc = 0;
    AI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new AI();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"AI");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AI:AI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_ForAlive_LUAAI_AI_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_ForAlive_LUAAI_AI_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AI)");
    return 0;
}

int lua_register_ForAlive_LUAAI_AI(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"AI");
    tolua_cclass(tolua_S,"AI","AI","InformationCollecter",nullptr);

    tolua_beginmodule(tolua_S,"AI");
        tolua_function(tolua_S,"new",lua_ForAlive_LUAAI_AI_constructor);
        tolua_function(tolua_S,"cleanInstructions",lua_ForAlive_LUAAI_AI_cleanInstructions);
        tolua_function(tolua_S,"getHoverTime",lua_ForAlive_LUAAI_AI_getHoverTime);
        tolua_function(tolua_S,"stopInstructions",lua_ForAlive_LUAAI_AI_stopInstructions);
        tolua_function(tolua_S,"addInstruction",lua_ForAlive_LUAAI_AI_addInstruction);
        tolua_function(tolua_S,"a_hover",lua_ForAlive_LUAAI_AI_a_hover);
        tolua_function(tolua_S,"stopAllInstructions",lua_ForAlive_LUAAI_AI_stopAllInstructions);
        tolua_function(tolua_S,"popInstruction",lua_ForAlive_LUAAI_AI_popInstruction);
        tolua_function(tolua_S,"cleanAllInstructions",lua_ForAlive_LUAAI_AI_cleanAllInstructions);
        tolua_function(tolua_S,"update",lua_ForAlive_LUAAI_AI_update);
        tolua_function(tolua_S,"finishInstruction",lua_ForAlive_LUAAI_AI_finishInstruction);
        tolua_function(tolua_S,"getHoverPoint",lua_ForAlive_LUAAI_AI_getHoverPoint);
        tolua_function(tolua_S,"setHoverPoint",lua_ForAlive_LUAAI_AI_setHoverPoint);
        tolua_function(tolua_S,"init",lua_ForAlive_LUAAI_AI_init);
        tolua_function(tolua_S,"insertInstruction",lua_ForAlive_LUAAI_AI_insertInstruction);
        tolua_function(tolua_S,"runInstruction",lua_ForAlive_LUAAI_AI_runInstruction);
        tolua_function(tolua_S,"InformationUpdate",lua_ForAlive_LUAAI_AI_InformationUpdate);
        tolua_function(tolua_S,"setHoverTime",lua_ForAlive_LUAAI_AI_setHoverTime);
        tolua_function(tolua_S,"create", lua_ForAlive_LUAAI_AI_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(AI).name();
    g_luaType[typeName] = "AI";
    g_typeCast["AI"] = "AI";
    return 1;
}
TOLUA_API int register_all_ForAlive_LUAAI(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_ForAlive_LUAAI_AI(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

