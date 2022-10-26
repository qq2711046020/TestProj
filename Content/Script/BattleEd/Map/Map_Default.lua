--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

---@class Map_Default
local Map_Default = Class()

--function Map_Default:Initialize(Initializer)
--end

--function Map_Default:UserConstructionScript()
--end

local GridSize = 100
local GridNum = 10
function Map_Default:ReceiveBeginPlay()
    self.GridMap = {}
    local Center = (GridNum + 1) / 2
    local bFlip = false
    local bFlipAfterRow = (GridNum % 2) == 0
    for x = 1, GridNum do
        self.GridMap[x] = {}
        for y = 1, GridNum do
            local PosX = (x - Center) * GridSize
            local PosY = (y - Center) * GridSize
            self.GridMap[x][y] = self:CreateGrid(PosX, PosY)
            if bFlip then
                self.GridMap[x][y]:SetColor(0.3, 0.3, 0.3)
            else
                self.GridMap[x][y]:SetColor(0.7, 0.7, 0.7)
            end
            bFlip = not bFlip
        end
        if bFlipAfterRow then
            bFlip = not bFlip
        end
    end
end

--function Map_Default:ReceiveEndPlay()
--end

-- function Map_Default:ReceiveTick(DeltaSeconds)
-- end

--function Map_Default:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
--end

--function Map_Default:ReceiveActorBeginOverlap(OtherActor)
--end

--function Map_Default:ReceiveActorEndOverlap(OtherActor)
--end

return Map_Default
