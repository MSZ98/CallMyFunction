#include <CallMyFunction.h>

unsigned long t;

void f() {
    Serial.println(String(millis() - t) + "ms from start");
}

void setup() {
    Serial.begin(115200);
    Callf.begin(millis);
    Callf.four(f, 0, 2);
    Serial.println("Program start");
    t = millis();
}

void loop() {
    Callf.loop();
}
