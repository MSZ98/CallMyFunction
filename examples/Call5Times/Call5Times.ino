#include <CallMyFunction.h>

void f() {
    Serial.println("Function called 5 times only");
}

void setup() {
    Serial.begin(115200);
    Callf.begin(millis);
    Callf.every(f, 0, 5);
    Serial.println("Program start");
}

void loop() {
    Callf.loop();
}



