radio.onReceivedNumber(function (receivedNumber) {
    basic.showLeds(`
        # # # # #
        # # # # #
        # . # . #
        # # # # #
        # # # # #
        `)
    basic.showString("raw " + receivedNumber)
    basic.showLeds(`
        # # # # #
        # . # . #
        # . # . #
        # . # . #
        # # # # #
        `)
})
function clearPins () {
    setPins(0, 0, 0)
}
input.onButtonPressed(Button.A, function () {
    clearPins()
})
function setPins (num: number, num2: number, num3: number) {
    pins.analogWritePin(AnalogPin.P0, num)
    pins.analogWritePin(AnalogPin.P1, num2)
    pins.analogWritePin(AnalogPin.P2, num3)
}
radio.onReceivedValue(function (name, value) {
    basic.showLeds(`
        # # # # #
        # # # # #
        # . # . #
        # # # # #
        # # # # #
        `)
    if (name == "primary") {
        setPins(1, 1, 1)
    } else if (name == "secondary") {
        setPins(1, 1, 1)
    } else {
        clearPins()
    }
    basic.showString("composed: " + name + ": " + value)
    basic.showLeds(`
        # # # # #
        # . # . #
        # . # . #
        # . # . #
        # # # # #
        `)
})
basic.showLeds(`
    # # # # #
    # . # . #
    # . # . #
    # . # . #
    # # # # #
    `)
