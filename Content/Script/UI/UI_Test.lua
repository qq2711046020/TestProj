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
    for i = 1, 10 do
        local Item = self:SpawnListViewObject(i)
        self.ListViewEx_Test:AddItem(Item)
    end
    self.UseA = true
end

function UI_Test:OnGetEntryWidgetClass(Item)
    if self.UseA  then
        return self.ClassA
    else
        return self.ClassB
    end
end

function UI_Test:OnClick_Test()
    self.UseA = not self.UseA 
end

function UI_Test:OnClick_Debug()
    self.ListViewEx_Test:ClearListItems()
    for i = 1, 10 do
        local Item = self:SpawnListViewObject(i)
        self.ListViewEx_Test:AddItem(Item)
    end
end

function UI_Test:OnClick_Exit()
    UE4.UKismetSystemLibrary.QuitGame(self, nil, 0, false)
end

function UI_Test:SpawnListViewObject(i)
    local Item = NewObject(LoadClass("Blueprint'/Game/UI/ListViewLuaObject.ListViewLuaObject_C'"), self)
    Item.Index = i
    return Item
end


return UI_Test