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
end

function UI_Test:OnClick_Test()
    self.Text_Test:SetText("Testing")
end

function UI_Test:OnClick_Debug()
    require("LuaPanda").start("192.168.0.105")
end

function UI_Test:OnClick_Exit()
    UE4.UKismetSystemLibrary.QuitGame(self, nil, 0, false)
end

return UI_Test
