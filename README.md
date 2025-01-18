# BaLightro
If people want to make the weird fleshlight that works as a Balatro controller that I posted about. (You will need a soldering iron for this.)

Parts List:
- Solderless Breadboard 3.25in
- Sparkfun Pro Micro (control board)
- MPU6050 Accel/Gyro sensor
- 5 x 6x6x5 mm push button switches
- jumper wires (various sizes)
- glue (you'll likely need less than me and I don't want to say how much I used. it was a lot)
- rumble motor (you can break open a controller and get one, or find a replacement on Amazon)
- Breadvolt Breadboard power supply (you can also use a 3x AA battery pack)
- A male masturbator (just go on Amazon and search for one. I used the cheapest one on the site. You'll have to trim off the back end to fit the ... sleeve)

Circuit diagram and finished product image:


The rest is kinda just hooking it all up, uploading the sketch to the control board, and going for it. 
Key notes: You'll have to get the XInput Arduino Library, the correct Arduino AVR Boards, and ensure that you are using the correct A32U spec (3.3V or 5V, make sure it matches with your board) in the Arduino IDE.
Links to the XInupt info: https://github.com/dmadison/ArduinoXInput
