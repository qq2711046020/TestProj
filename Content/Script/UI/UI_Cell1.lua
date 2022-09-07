--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

---@class UI_Cell1
local UI_Cell1 = Class()

--function UI_Cell1:Initialize(Initializer)
--end

--function UI_Cell1:PreConstruct(IsDesignTime)
--end

-- function UI_Cell1:Construct()
-- end

--function UI_Cell1:Tick(MyGeometry, InDeltaTime)
--end

function UI_Cell1:OnListItemObjectSet(Item)
    self.Text_ID:SetText(Item.Index)
end

return UI_Cell1
