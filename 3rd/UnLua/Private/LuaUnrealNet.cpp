#include "LuaUnrealNet.h"
#include "LuaStackGuard.h"
#include "Misc/Guid.h"
#include "WrapperAsset.h"
#include <string>
#include <vector>
#include <memory>

static int LuaSetConnectionDeadTimespan(lua_State* L)
{
	do
	{
		const int32 ConnectId = UnLua::Get(L, 1, UnLua::TType<int32>());
		const double DeadTimespanSeconds = UnLua::Get(L, 2, UnLua::TType<double>());

		if (IUnrealNet::IsAvailable())
		{
			IUnrealNet::Get().SetConnectionDeadTimespan(ConnectId, FTimespan::FromSeconds(FMath::Max(0.0, DeadTimespanSeconds)));
		}
		else
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetConnectionDeadTimespan function UnrealNet Module unavailable"));
		}
	} while (false);
	return 0;
}

static int LuaSetZipDictionary(lua_State* L)
{
	//do
	//{
	//	const FString ZipDictionaryPath = UnLua::Get(L, 1, UnLua::TType<FString>());
	//	if (ZipDictionaryPath.IsEmpty())
	//	{
	//		UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetZipDictionary function fetch ZipDictionaryPath error"));
	//		break;
	//	}
	//	UWrapperAsset* WrapperAsset = LoadObject<UWrapperAsset>(nullptr, *ZipDictionaryPath);
	//	if (WrapperAsset == nullptr)
	//	{
	//		UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetZipDictionary function load WrapperAsset[%s] failed!"), *ZipDictionaryPath);
	//		break;
	//	}
	//	TArray<uint8> ZipDictionaryData;
	//	WrapperAsset->GetData(ZipDictionaryData);

	//	if (IUnrealNet::IsAvailable())
	//	{
	//		IUnrealNet::Get().SetZipDictionary(ZipDictionaryData);
	//	}
	//	else
	//	{
	//		UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetZipDictionary function UnrealNet Module unavailable"));
	//	}
	//}
	//while (false);
	return 0;
}

static int LuaSetRemotePublicKey(lua_State* L)
{
	do
	{
		const FString KeyPath = UnLua::Get(L, 1, UnLua::TType<FString>());
		if (KeyPath.IsEmpty())
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetRemotePublicKey function fetch KeyPath error"));
			break;
		}
		UWrapperAsset* WrapperAsset = LoadObject<UWrapperAsset>(nullptr, *KeyPath);
		if (WrapperAsset == nullptr)
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetRemotePublicKey function load WrapperAsset[%s] failed!"), *KeyPath);
			break;
		}
		TArray<uint8> KeyData;
		WrapperAsset->GetData(KeyData);

		if (IUnrealNet::IsAvailable())
		{
			IUnrealNet::Get().SetRemotePublicKey(FAsymmetricPublicKey(KeyData));
		}
		else
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetRemotePublicKey function UnrealNet Module unavailable"));
		}
	}
	while (false);
	return 0;
}

static int LuaSetLocalPrivateKey(lua_State* L)
{
	do
	{
		const FString KeyPath = UnLua::Get(L, 1, UnLua::TType<FString>());
		if (KeyPath.IsEmpty())
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetLocalPrivateKey function fetch KeyPath error"));
			break;
		}
		UWrapperAsset* WrapperAsset = LoadObject<UWrapperAsset>(nullptr, *KeyPath);
		if (WrapperAsset == nullptr)
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetLocalPrivateKey function load WrapperAsset[%s] failed!"), *KeyPath);
			break;
		}
		TArray<uint8> KeyData;
		WrapperAsset->GetData(KeyData);

		if (IUnrealNet::IsAvailable())
		{
			IUnrealNet::Get().SetLocalPrivateKey(FAsymmetricPrivateKey(KeyData));
		}
		else
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SetLocalPrivateKey function UnrealNet Module unavailable"));
		}
	}
	while (false);
	return 0;
}

static int LuaCreateClient(lua_State* L)
{
	do
	{
		int32 connect_id = IUnrealNet::Get().CreateClient();
		UnLua::Push(L, connect_id, true);
		return 1;
	} while (false);
	return 0;
}

static int LuaConnect(lua_State* L)
{
	do
	{
		const int32 ConnectId = UnLua::Get(L, 1, UnLua::TType<int32>());
		const FString Host = UnLua::Get(L, 2, UnLua::TType<FString>());
		if (Host.IsEmpty())
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet Connect function fetch Host error"));
			break;
		}

		const int32 Port = UnLua::Get(L, 3, UnLua::TType<int32>());		

		if (IUnrealNet::IsAvailable())
		{
			//char host[32] = { 0 };
			//size_t host_len = 0;
			//wcstombs_s(&host_len, host, *Host, Host.Len());
			IUnrealNet::Get().Connect(ConnectId, TCHAR_TO_UTF8(*Host), Port);
			return 0;
		}
		else
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet Connect function UnrealNet Module unavailable"));
		}
	}
	while (false);
	return 0;
}

static int LuaClose(lua_State* L)
{
	do
	{
		const int connect_id = UnLua::Get(L, 1, UnLua::TType<int>());
		if (connect_id < 0)
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet Close function fetch ConnectionGuid error"));
			break;
		}

		if (IUnrealNet::IsAvailable())
		{
			IUnrealNet::Get().Close(connect_id);
		}
		else
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet Close function UnrealNet Module unavailable"));
		}
	}
	while (false);
	return 0;
}

static int LuaSendMessage(lua_State* L)
{
	do
	{
		const int connect_id = UnLua::Get(L, 1, UnLua::TType<int>());
		if (connect_id < 0)
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet Close function fetch ConnectionGuid error"));
			break;
		}
		const uint32 MessageType = UnLua::Get(L, 2, UnLua::TType<uint32>());
		std::size_t Length = 0;
		const char* pMessage = luaL_checklstring(L, 3, &Length);
		if (pMessage == nullptr)
		{
			Length = 0;
		}
		const TArray<uint8> Message(reinterpret_cast<const uint8*>(pMessage), static_cast<int32>(Length));

		if (IUnrealNet::IsAvailable())
		{
			IUnrealNet::Get().SendMessage(connect_id, MessageType, Message);
		}
		else
		{
			UE_LOG(LogUnLua, Error, TEXT("Lua UnrealNet SendMessage function UnrealNet Module unavailable"));
		}
	}
	while (false);
	return 0;
}

static int luaopen_UnrealNet(lua_State* L)
{
	luaL_Reg libs[] = {
		{"SetConnectionDeadTimespan", LuaSetConnectionDeadTimespan},
		{ "SetZipDictionary", LuaSetZipDictionary },
		{ "SetRemotePublicKey", LuaSetRemotePublicKey },
		{ "SetLocalPrivateKey", LuaSetLocalPrivateKey },
		{ "CreateClient", LuaCreateClient },
		{ "Connect", LuaConnect },
		{ "Close", LuaClose },
		{ "SendMessage", LuaSendMessage },
		{ NULL, NULL }
	};
	luaL_newlib(L, libs);
	return 1;
}

static int LuaError(lua_State* L)
{
	luaL_traceback(L, L, lua_tostring(L, -1), 1);

	const char* ErrorInfoWithStack = lua_tostring(L, -1);
	UE_LOG(LogUnLua, Error, TEXT("%s"), UTF8_TO_TCHAR(ErrorInfoWithStack));

	return 1;
}

FLuaUnrealNet::FLuaUnrealNet(lua_State* InLuaState)
{
	_LuaState = InLuaState;
	FLuaStackGuard LuaStackGuard(_LuaState);
	luaL_requiref(_LuaState, "UnrealNet", luaopen_UnrealNet, 0);

	if (!IUnrealNet::IsAvailable())
	{
		UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet constructor UnrealNet Module unavailable"));
	}
	else
	{
		IUnrealNet::Get().GetOnConnect().AddRaw(this, &FLuaUnrealNet::OnConnect);
		IUnrealNet::Get().GetOnClose().AddRaw(this, &FLuaUnrealNet::OnClose);
		IUnrealNet::Get().GetOnRecv().AddRaw(this, &FLuaUnrealNet::OnRecv);
		IUnrealNet::Get().GetOnRecvTestPing().AddRaw(this, &FLuaUnrealNet::OnRecvTestPing);
	}
}

FLuaUnrealNet::~FLuaUnrealNet()
{
	if (IUnrealNet::IsAvailable())
	{
		IUnrealNet::Get().GetOnConnect().RemoveAll(this);
		IUnrealNet::Get().GetOnClose().RemoveAll(this);
		IUnrealNet::Get().GetOnRecv().RemoveAll(this);
		IUnrealNet::Get().GetOnRecvTestPing().RemoveAll(this);
	}
}

bool FLuaUnrealNet::CallLuaFunction(int32 InParamsCount, int32 OutParamsCount) const
{
	lua_pushcfunction(_LuaState, LuaError);
	const int32 LuaErrorFunctionIndex = lua_absindex(_LuaState, -(InParamsCount + 2));
	lua_insert(_LuaState, LuaErrorFunctionIndex);

	if (LUA_OK != lua_pcall(_LuaState, InParamsCount, OutParamsCount, LuaErrorFunctionIndex))
	{
		lua_remove(_LuaState, LuaErrorFunctionIndex);
		return false;
	}

	lua_remove(_LuaState, LuaErrorFunctionIndex);
	return true;
}

void FLuaUnrealNet::OnConnect(int32 connect_id, uint8 status)
{
	do
	{
		FLuaStackGuard LuaStackGuard(_LuaState);
		luaL_requiref(_LuaState, "UnrealNet", luaopen_UnrealNet, 0);
		const int FieldType = lua_getfield(_LuaState, -1, "OnConnect");
		if (FieldType == LUA_TNIL)
		{
			UE_LOG(LogUnLua, Warning, TEXT("LuaUnrealNet OnConnect unhandled"));
			break;
		}
		if (FieldType != LUA_TFUNCTION)
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet OnConnect should be lua function"));
			break;
		}
		int32 InParamsCount = UnLua::Push(_LuaState, connect_id, true);
		InParamsCount += UnLua::Push(_LuaState, status, true);
		if (!CallLuaFunction(InParamsCount, 0))
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet call lua function OnConnect fail"));
			break;
		}
	} while (false);
}

void FLuaUnrealNet::OnClose(int32 connect_id)
{
	do
	{
		FLuaStackGuard LuaStackGuard(_LuaState);
		luaL_requiref(_LuaState, "UnrealNet", luaopen_UnrealNet, 0);
		const int FieldType = lua_getfield(_LuaState, -1, "OnClose");
		if (FieldType == LUA_TNIL)
		{
			UE_LOG(LogUnLua, Warning, TEXT("LuaUnrealNet OnClose unhandled"));
			break;
		}
		if (FieldType != LUA_TFUNCTION)
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet OnClose should be lua function"));
			break;
		}
		int32 InParamsCount = UnLua::Push(_LuaState, connect_id, true);
		if (!CallLuaFunction(InParamsCount, 0))
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet call lua function OnClose fail"));
			break;
		}
	} while (false);
}

void FLuaUnrealNet::OnRecv(int32 connect_id, uint32 msg_type, TArray<uint8> msg)
{
	do
	{
		FLuaStackGuard LuaStackGuard(_LuaState);
		luaL_requiref(_LuaState, "UnrealNet", luaopen_UnrealNet, 0);
		const int FieldType = lua_getfield(_LuaState, -1, "OnRecv");
		if (FieldType == LUA_TNIL)
		{
			UE_LOG(LogUnLua, Warning, TEXT("LuaUnrealNet OnRecv unhandled"));
			break;
		}
		if (FieldType != LUA_TFUNCTION)
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet OnRecv should be lua function"));
			break;
		}
		int32 InParamsCount = UnLua::Push(_LuaState, connect_id, true);
		InParamsCount += UnLua::Push(_LuaState, msg_type, true);
		InParamsCount += UnLua::Push(_LuaState, msg, true);
		if (!CallLuaFunction(InParamsCount, 0))
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet call lua function OnRecv fail"));
			break;
		}
	} while (false);
}

void FLuaUnrealNet::OnRecvTestPing(int32 connect_id, const uint32 ping_in_ms)
{
	do
	{
		FLuaStackGuard LuaStackGuard(_LuaState);
		luaL_requiref(_LuaState, "UnrealNet", luaopen_UnrealNet, 0);
		const int FieldType = lua_getfield(_LuaState, -1, "OnRecvTestPing");
		if (FieldType == LUA_TNIL)
		{
			UE_LOG(LogUnLua, Warning, TEXT("LuaUnrealNet OnRecvTestPing unhandled"));
			break;
		}
		if (FieldType != LUA_TFUNCTION)
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet OnRecvTestPing should be lua function"));
			break;
		}
		int32 InParamsCount = UnLua::Push(_LuaState, connect_id, true);
		InParamsCount += UnLua::Push(_LuaState, ping_in_ms, true);
		if (!CallLuaFunction(InParamsCount, 0))
		{
			UE_LOG(LogUnLua, Error, TEXT("LuaUnrealNet call lua function OnRecvTestPing fail"));
			break;
		}
	} while (false);
}

