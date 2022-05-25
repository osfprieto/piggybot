function clearPins () {
    setPins(0, 0, 0)
    basic.showLeds(`
        . . # . .
        . # . # .
        . # . # .
        . # . # .
        . . # . .
        `)
}
input.onButtonPressed(Button.A, function () {
    pins.digitalWritePin(DigitalPin.P0, 1)
    pins.analogWritePin(AnalogPin.P1, 512)
    pins.analogWritePin(AnalogPin.P2, 1023)
    basic.showLeds(`
        . . # . .
        . # # . .
        . . # . .
        . . # . .
        . # # # .
        `)
})
function setPins (num: number, num2: number, num3: number) {
    pins.analogWritePin(AnalogPin.P0, num)
    pins.analogWritePin(AnalogPin.P1, num2)
    pins.analogWritePin(AnalogPin.P2, num3)
}
input.onButtonPressed(Button.B, function () {
    clearPins()
})