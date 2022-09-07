--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

---@class UI_Cell
local UI_Cell = Class()

--function UI_Cell:Initialize(Initializer)
--end

--function UI_Cell:PreConstruct(IsDesignTime)
--end

-- function UI_Cell:Construct()
-- end

--function UI_Cell:Tick(MyGeometry, InDeltaTime)
--end

function UI_Cell:OnListItemObjectSet(Item)
    self.Text_ID:SetText(Item.Index)
end

return UI_Cell
