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
    } else if (receivedNumber == 768) {
        winSound()
    } else if (receivedNumber == 769) {
        loseSound()
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
input.onLogoEvent(TouchButtonEvent.LongPressed, function () {
    loseSound()
})
input.onLogoEvent(TouchButtonEvent.Pressed, function () {
    winSound()
})
function winSound () {
    music.setVolume(255)
    music.playTone(392, music.beat(BeatFraction.Whole))
    music.playTone(494, music.beat(BeatFraction.Whole))
    music.playTone(523, music.beat(BeatFraction.Whole))
}
function loseSound () {
    music.setVolume(255)
    music.playTone(523, music.beat(BeatFraction.Whole))
    music.playTone(392, music.beat(BeatFraction.Whole))
    music.playTone(262, music.beat(BeatFraction.Whole))
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
