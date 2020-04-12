Tank = {
    graphicComponent = {
        spriteName = "RedTank",
        spriteFilepath = "assets/Sprites/RedTank.png",
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
        }
    },
    logicalComponent = {
        update = function ()
            move()
        end
    }
}