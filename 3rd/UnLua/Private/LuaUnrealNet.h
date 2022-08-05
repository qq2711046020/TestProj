#pragma once

#include "CoreMinimal.h"
#include "TcpClientNet.h"
#include "NetConnectionState.h"
#include "UnLua.h"

class FLuaUnrealNet final
{
public:
	FLuaUnrealNet(lua_State* InLuaState);
	FLuaUnrealNet(const FLuaUnrealNet&) = delete;
	FLuaUnrealNet(FLuaUnrealNet&&) = delete;
	~FLuaUnrealNet();
	FLuaUnrealNet& operator=(const FLuaUnrealNet&) = delete;
	FLuaUnrealNet& operator=(FLuaUnrealNet&&) = delete;

private:
	bool CallLuaFunction(int32 InParamsCount, int32 OutParamsCount) const;

	/*callback event deal functions*/
	void OnConnect(int32 connect_id, uint8 status);
	void OnClose(int32 connect_id);
	void OnRecv(int32 connect_id, uint32 msg_type, TArray<uint8> msg);
	void OnRecvTestPing(int32 connect_id, const uint32 ping_in_ms);

	lua_State* _LuaState;
};

