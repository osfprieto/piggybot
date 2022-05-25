basic.showLeds(`
    . . . . .
    . . # . .
    . # . # .
    . . . . .
    . . . . .
    `)
basic.forever(function () {
    if (input.buttonIsPressed(Button.AB)) {
        basic.showLeds(`
            . . # . .
            . # . # .
            . # . # .
            . # . # .
            . . # . .
            `)
        while (input.buttonIsPressed(Button.AB)) {
            radio.setGroup(92)
            radio.sendNumber(512)
        }
    } else if (input.buttonIsPressed(Button.A)) {
        basic.showLeds(`
            . # # . .
            . # . # .
            . # # . .
            . # . . .
            . # . . .
            `)
        while (input.buttonIsPressed(Button.A)) {
            radio.setGroup(92)
            radio.sendNumber(2048 + input.acceleration(Dimension.X))
        }
    } else if (input.buttonIsPressed(Button.B)) {
        basic.showLeds(`
            . . # # .
            . # . . .
            . . # . .
            . . . # .
            . # # . .
            `)
        while (input.buttonIsPressed(Button.B)) {
            radio.setGroup(92)
            radio.sendNumber(2048 + 2048 + input.acceleration(Dimension.Y))
        }
    }
    basic.showLeds(`
        . . . . .
        . . # . .
        . # . # .
        . . . . .
        . . . . .
        `)
})
