Tank = {
    movableGraphicComponent = {
        spriteName = "RedTank",
        spriteFilepath = "assets/Sprites/RedTank.png",
        sped = 5,
        scale = {
            width = 1,
            height = 1
        },
        origin = {
            x = 32,
            y = 32
        },
        position = {
            x = 200,
            y = 200
        },
        spriteOrientation = {
            x = 0,
            y = 1
        }
    },
    logicalComponent = {
        update = function ()
            rotate(90)
            stop()
        end
    }
}