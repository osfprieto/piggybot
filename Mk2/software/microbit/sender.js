input.onButtonPressed(Button.AB, function () {
    basic.showLeds(`
        . . # . .
        . # . # .
        . # . # .
        . # . # .
        . . # . .
        `)
    radio.sendValue("clear", 0)
})
basic.showLeds(`
    . . . . .
    . . # . .
    . # . # .
    . . . . .
    . . . . .
    `)
basic.forever(function () {
    while (input.buttonIsPressed(Button.A)) {
        basic.showLeds(`
            . # # . .
            . # . # .
            . # # . .
            . # . . .
            . # . . .
            `)
        radio.sendValue("primary", 1)
    }
    while (input.buttonIsPressed(Button.B)) {
        basic.showLeds(`
            . . # # .
            . # . . .
            . . # . .
            . . . # .
            . # # . .
            `)
        radio.sendValue("secondary", 0.5)
    }
    basic.showLeds(`
        . . . . .
        . . # . .
        . # . # .
        . . . . .
        . . . . .
        `)
})
