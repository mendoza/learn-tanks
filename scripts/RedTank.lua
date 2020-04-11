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
        }
    },
    logicalComponent = {
        update = function ()
            rotate(600)
        end
    }
}