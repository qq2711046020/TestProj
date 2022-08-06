// Tencent is pleased to support the open source community by making UnLua available.
// 
// Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the MIT License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "UnLuaExtensionsModule.h"
#include "LuaEnv.h"
#include "luasocket.h"
#include "checks.h"
#include "pb.h"

void FUnLuaExtensionsModule::StartupModule()
{
    Handle = UnLua::FLuaEnv::OnCreated.AddStatic(&FUnLuaExtensionsModule::OnLuaEnvCreated);

    for (const auto& Pair : UnLua::FLuaEnv::GetAll())
        OnLuaEnvCreated(*Pair.Value);
}

void FUnLuaExtensionsModule::ShutdownModule()
{
    UnLua::FLuaEnv::OnCreated.Remove(Handle);
}
//extern int luaopen_checks(lua_State*);
//extern int luaopen_pb(lua_State*);
void FUnLuaExtensionsModule::OnLuaEnvCreated(UnLua::FLuaEnv& Env)
{
    Env.AddBuiltInLoader(TEXT("socket"), luaopen_socket_core);
    Env.AddBuiltInLoader(TEXT("socket.core"), luaopen_socket_core);

    static const luaL_Reg ExtendedLibs[] = {
	    {"checks", luaopen_checks},
		{"pb", luaopen_pb},
		{NULL, NULL}
    };

    lua_State* L = Env.GetMainState();
    for (const luaL_Reg* Lib = ExtendedLibs; Lib->func; ++Lib)
    {
        const int32 top = lua_gettop(L);
        luaL_requiref(L, Lib->name, Lib->func, 0);
        lua_settop(L, top);
    }
}

IMPLEMENT_MODULE(FUnLuaExtensionsModule, UnLuaExtensions)
