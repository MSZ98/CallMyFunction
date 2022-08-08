#include <CallMyFunction.h>

unsigned long time;

void f() {
    Serial.println(String(millis() - time) + "ms from start");
}

void setup() {
    Serial.begin(115200);
    Callf.begin(millis);
    Callf.four(f, 0, 2);
    Serial.println("Program start");
    time = millis();
}

void loop() {
    Callf.loop();
}