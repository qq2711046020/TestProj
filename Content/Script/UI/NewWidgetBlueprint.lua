--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

---@class NewWidgetBlueprint
local NewWidgetBlueprint = Class()

--function NewWidgetBlueprint:Initialize(Initializer)
--end

--function NewWidgetBlueprint:PreConstruct(IsDesignTime)
--end

function NewWidgetBlueprint:Construct()
    self.Btn_Test.OnClicked:Add(self, self.OnClickBtn)
end

function NewWidgetBlueprint:OnClickBtn()
    self.T_Text:SetText("222")
end


return NewWidgetBlueprint
