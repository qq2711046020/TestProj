--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

---@class UI_Test
local UI_Test = Class()
local checks = require("checks")
--function UI_Test:Initialize(Initializer)
--end

--function UI_Test:PreConstruct(IsDesignTime)
--end

--function UI_Test:Tick(MyGeometry, InDeltaTime)
--end

function UI_Test:Construct()
    self.Btn_Test.OnClicked:Add(self, self.OnClick_Test)
    self.Btn_Debug.OnClicked:Add(self, self.OnClick_Debug)
    self.Btn_Exit.OnClicked:Add(self, self.OnClick_Exit)
    self.HorizontalBoxEx_108.BP_IsMirrorChanged:Add(self, self.OnIsMirrorChanged)
end

function UI_Test:OnClick_Test()
    --self.Text_Test:SetText("Testing")
    --self.HorizontalBoxEx_108:SetIsMirror(true)
    --self:Test(1, "aa")
    local s = UE4.UTestProjLibrary.GetConfig("TestSection", "TestKey", "cjh20220810.ini")
    print(s)
end

function UI_Test:Test(num, str)
    checks("table", "number", "string")
    local pb = require("pb")
    print("check over")
end

function UI_Test:OnClick_Debug()
    UE4.UTestProjLibrary.SetConfig("TestSection", "TestKey", "123123", "cjh20220810.ini")
    print("Set")
    --require("LuaPanda").start("192.168.0.105")
    --self.HorizontalBoxEx_108:SetIsMirror(false)
end

function UI_Test:OnIsMirrorChanged(bIsMirror)
    self.Image_2:SetRenderScale(UE4.FVector2D(bIsMirror and -1 or 1, 1))
end

function UI_Test:OnClick_Exit()
    UE4.UKismetSystemLibrary.QuitGame(self, nil, 0, false)
end

return UI_Test