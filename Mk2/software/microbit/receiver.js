radio.onReceivedNumber(function (receivedNumber) {
    basic.showLeds(`
        # # # # #
        # # # # #
        # . # . #
        # # # # #
        # # # # #
        `)
    if (receivedNumber > 1000 && receivedNumber < 3000) {
        integerValue = receivedNumber - 1000
        if (integerValue > 1000) {
            integerValue = 1000
        }
        p0 = 1023 * integerValue / 1000
    } else if (receivedNumber > 3000) {
        integerValue2 = receivedNumber - 3000
        if (integerValue2 > 1000) {
            integerValue2 = 1000
        }
        p1 = 1023 * integerValue2 / 1000
    }
    setPins(p0, p1)
    basic.showLeds(`
        # # # # #
        # . # . #
        # . # . #
        # . # . #
        # # # # #
        `)
})
function clearPins () {
    setPins(0, 0)
}
input.onButtonPressed(Button.A, function () {
    clearPins()
})
function setPins (p0: number, p1: number) {
    pins.analogWritePin(AnalogPin.P0, p0)
    pins.analogWritePin(AnalogPin.P1, p1)
}
let p1 = 0
let integerValue2 = 0
let p0 = 0
let integerValue = 0
basic.showLeds(`
    # # # # #
    # . # . #
    # . # . #
    # . # . #
    # # # # #
    `)
basic.forever(function () {
    radio.setGroup(92)
})
