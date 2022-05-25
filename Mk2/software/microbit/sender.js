input.onButtonPressed(Button.AB, function () {
    basic.showLeds(`
        . . # . .
        . # . # .
        . # . # .
        . # . # .
        . . # . .
        `)
    radio.setGroup(92)
    radio.sendNumber(0)
})
basic.showLeds(`
    . . . . .
    . . # . .
    . # . # .
    . . . . .
    . . . . .
    `)
basic.forever(function () {
    if (input.buttonIsPressed(Button.A)) {
        basic.showLeds(`
            . # # . .
            . # . # .
            . # # . .
            . # . . .
            . # . . .
            `)
        while (input.buttonIsPressed(Button.A)) {
            radio.setGroup(92)
            radio.sendNumber(1000 + input.acceleration(Dimension.X))
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
            radio.sendNumber(3000 + input.acceleration(Dimension.X))
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
