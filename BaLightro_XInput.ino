#include <XInput.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int buttonPins[] = {6, 7, 8, 9, 4};
const int motorPin = 5;
bool altMode = false;
bool testRumble = false;

const int deadZone = 1000;
int16_t axOffset, ayOffset;

void calibrateMPU6050() {
    axOffset = mpu.getAccelerationX();
    ayOffset = mpu.getAccelerationY();
}

int mapJoystickValue(int16_t value, int16_t offset) {
    int mappedValue = map(value - offset, -16000, 16000, -32767, 32767);
    if (abs(mappedValue) < deadZone) return 0;
    return constrain(mappedValue, -32767, 32767);
}

void setup() {
    Serial.begin(9600);
    
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }
    calibrateMPU6050();

    for (int i = 0; i < 5; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    pinMode(motorPin, OUTPUT);
    analogWrite(motorPin, 0);

    XInput.begin();
}

void loop() {
    int16_t ax = mpu.getAccelerationX();
    int16_t ay = mpu.getAccelerationY();
    int joystickX = mapJoystickValue(ax, axOffset);
    int joystickY = mapJoystickValue(ay, ayOffset);
    XInput.setJoystickX(XInputControl::JOY_LEFT, joystickX);
    XInput.setJoystickY(XInputControl::JOY_LEFT, joystickY);

    bool modeButton = !digitalRead(buttonPins[4]);
    if (modeButton) altMode = !altMode;
    delay(200);

    if (altMode == false) {
      XInput.setButton(BUTTON_A, !digitalRead(buttonPins[0]));
      XInput.setButton(BUTTON_B, !digitalRead(buttonPins[1]));
      XInput.setButton(BUTTON_X, !digitalRead(buttonPins[2]));
      XInput.setButton(BUTTON_Y, !digitalRead(buttonPins[3]));
    }
    if (altMode == true) {
      XInput.setButton(BUTTON_LB, !digitalRead(buttonPins[0]));
      XInput.setButton(BUTTON_RB, !digitalRead(buttonPins[1]));
      XInput.setButton(BUTTON_START, !digitalRead(buttonPins[2]));
      XInput.setButton(BUTTON_BACK, !digitalRead(buttonPins[3]));
    }


    if (!digitalRead(buttonPins[0]) && !digitalRead(buttonPins[1]) && !digitalRead(buttonPins[2])) {
        analogWrite(motorPin, 255);
        delay(500);
        analogWrite(motorPin, 0);
    }

    int rumble = XInput.getRumble();
    analogWrite(motorPin, map(rumble, 0, 255, 0, 255));

    XInput.send();

    delay(10);
}
