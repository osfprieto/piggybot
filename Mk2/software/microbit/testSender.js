input.onButtonPressed(Button.AB, function () {
    basic.showLeds(`
        . . # . .
        . # . # .
        . # . # .
        . # . # .
        . . # . .
        `)
    radio.setGroup(92)
    radio.sendNumber(4)
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
            radio.sendNumber(2)
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
            radio.sendNumber(3)
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
