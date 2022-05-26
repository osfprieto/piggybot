radio.onReceivedNumber(function (receivedNumber) {
    basic.showLeds(`
        # # # # #
        # # # # #
        # . # . #
        # # # # #
        # # # # #
        `)
    p0 = 0
    p1 = 0
    if (receivedNumber > 1023 && receivedNumber < 1024 * 3) {
        p0 = receivedNumber - 1024
        if (p0 < 0) {
            p0 = 0
        }
        if (p0 >= 1024 * 2) {
            p0 = 1024 * 2 - 1
        }
        p0 = p0 / 2
    } else if (receivedNumber >= 1024 * 3) {
        p1 = receivedNumber - 1024 * 3
        if (p1 < 0) {
            p1 = 0
        }
        if (p1 >= 1024 * 2) {
            p1 = 1024 * 2 - 1
        }
        p1 = p1 / 2
    }
    // serial.writeNumber(p0)
    // serial.writeLine("")
    setPins(p0, p1)
    basic.showLeds(`
        # # # # #
        # . # . #
        # . # . #
        # . # . #
        # # # # #
        `)
})
function setPins (p0: number, p1: number) {
    pins.analogWritePin(AnalogPin.P0, p0)
    pins.analogWritePin(AnalogPin.P1, p1)
}
let p1 = 0
let p0 = 0
let integerValue2 = 0
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
