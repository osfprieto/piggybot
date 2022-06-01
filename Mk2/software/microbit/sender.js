// reserved signal numbers
// 
// 0-1024 -> Clear analog values; can still be used for other signals.
// 
// 1024-3071 -> Send analog value to primary (P0) after transforming the space.
// 
// 3072-5119 -> Send analog value to secondary (P1) after transforming the space.
// 
// 512 -> Clear signals
// 
// 768 -> Win sound
// 
// 769 -> Lose sound
input.onLogoEvent(TouchButtonEvent.LongPressed, function () {
    basic.showLeds(`
        . # # # .
        # . # . #
        # . # . #
        # . # . #
        . # # # .
        `)
    for (let index = 0; index < 5; index++) {
        radio.setGroup(92)
        radio.sendNumber(769)
    }
    basic.showLeds(`
        . . . . .
        . . # . .
        . # . # .
        . . . . .
        . . . . .
        `)
})
input.onLogoEvent(TouchButtonEvent.Pressed, function () {
    basic.showLeds(`
        . # # # .
        # . # . #
        # . # . #
        # . # . #
        . # # # .
        `)
    for (let index = 0; index < 5; index++) {
        radio.setGroup(92)
        radio.sendNumber(768)
    }
    basic.showLeds(`
        . . . . .
        . . # . .
        . # . # .
        . . . . .
        . . . . .
        `)
})
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
        basic.showLeds(`
            . . # . .
            . # . # .
            . # . # .
            . # . # .
            . . # . .
            `)
        for (let index = 0; index < 5; index++) {
            radio.setGroup(92)
            radio.sendNumber(512)
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
        basic.showLeds(`
            . . # . .
            . # . # .
            . # . # .
            . # . # .
            . . # . .
            `)
        for (let index = 0; index < 5; index++) {
            radio.setGroup(92)
            radio.sendNumber(512)
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
