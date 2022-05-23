input.onButtonPressed(Button.A, function () {
    while (input.buttonIsPressed(Button.A)) {
        radio.sendValue("primary", input.acceleration(Dimension.X))
    }
})
input.onButtonPressed(Button.AB, function () {
    radio.sendValue("clear", 0)
})
input.onButtonPressed(Button.B, function () {
    while (input.buttonIsPressed(Button.B)) {
    	
    }
})
