Tank = {
    movableGraphicComponent = {
        spriteName = "BlueTank",
        spriteFilepath = "assets/Sprites/BlueTank.png",
        speed = 5,
        scale = {
            width = 1,
            height = 1
        },
        origin = {
            x = 32,
            y = 32
        },
        position = {
            x = 400,
            y = 400
        },
        spriteOrientation = {
            x = 0,
            y = 1
        }
    },
    logicalComponent = {
        update = function ()
            rotate(10)
            -- backward()
            -- stop()
        end
    }
}