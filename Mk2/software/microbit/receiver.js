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
    basic.showString(name)
    basic.showString("" + (value))
    basic.showLeds(`
        # # # # #
        # # # # #
        # . # . #
        # # # # #
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
