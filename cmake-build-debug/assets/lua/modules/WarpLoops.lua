
WarpLoops = {}

WarpLoops.ProducingDuration = 0.3

function WarpLoops.Update(    
    lifetime,
    setAlpha,
    setPos,
    destroy
)
    local upHeight = 16.0
    local fadeTime = 0.2
    local lifetimeMax = 1.0

    local percent = lifetime / lifetimeMax
    setPos(0, -upHeight * percent)

    setAlpha(255)

    if lifetime > lifetimeMax then
        destroy()
        return
    end
    
end

WarpLoops = require("fixReadonly")(WarpLoops)
