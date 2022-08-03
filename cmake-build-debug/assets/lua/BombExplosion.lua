
BombExplosion = {}

local numFrame = 22

BombExplosion.Update = function(
    lifetime,
    setApha,
    setFrame,
    setScale,
    destroy
)
    local newAlpha = lifetime * 1000;
    if newAlpha > 255 then newAlpha = 255 end
    setApha(newAlpha)

    local frameDuration = 0.05
    local currFrame = math.floor(lifetime/frameDuration)
    setFrame(currFrame)

    local scale = 0.2 + 0.8 * (currFrame*1.0/numFrame)
    setScale(scale, scale)

    if currFrame > numFrame then
        println("destroy object")
        destroy()
    end

end

