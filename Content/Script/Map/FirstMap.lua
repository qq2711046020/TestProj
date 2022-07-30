--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

---@class FirstMap
local FirstMap = Class()

--function FirstMap:Initialize(Initializer)
--end

--function FirstMap:UserConstructionScript()
--end

function FirstMap:ReceiveBeginPlay()
    local WidgetClass = LoadClass("WidgetBlueprint'/Game/UI/UI_Test.UI_Test_C'")
    local Widget = UE4.UWidgetBlueprintLibrary.Create(self, WidgetClass)
    Widget:AddToViewport(0)
end

--function FirstMap:ReceiveEndPlay()
--end

-- function FirstMap:ReceiveTick(DeltaSeconds)
-- end

--function FirstMap:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
--end

--function FirstMap:ReceiveActorBeginOverlap(OtherActor)
--end

--function FirstMap:ReceiveActorEndOverlap(OtherActor)
--end

return FirstMap
