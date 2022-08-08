#include <CallMyFunction.h>

void f() {
    Serial.println("Function called repeatedly every 200ms");
}

void setup() {
    Serial.begin(115200);
    Callf.begin(millis);
    Callf.every(f, 200);
    Serial.println("Program start");
}

void loop() {
    Callf.loop();
}



