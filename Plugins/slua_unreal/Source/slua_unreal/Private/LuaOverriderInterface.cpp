#include "LuaOverriderInterface.h"
#include "LuaOverrider.h"

ULuaOverriderInterface::ULuaOverriderInterface(const class FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

NS_SLUA::LuaVar ILuaOverriderInterface::GetSelfTable(NS_SLUA::LuaState* L/* = nullptr*/) const
{
    NS_SLUA::LuaVar* luaSelfTable = ULuaOverrider::getObjectLuaTable(Cast<UObject>(this), L ? L->getLuaState() : nullptr);
    if (luaSelfTable)
    {
        return *luaSelfTable;
    }
    else
    {
        return NS_SLUA::LuaVar();
    }
}

void ILuaOverriderInterface::PostLuaHook()
{
    static FString PostConstructFunction = TEXT("_PostConstruct");
    CallLuaFunctionIfExist(PostConstructFunction);
}

void ILuaOverriderInterface::TryHook()
{
    UObject* obj = Cast<UObject>(this);
    if (!obj)
    {
        return;
    }

    NS_SLUA::LuaState::hookObject(nullptr, obj, true);
}
