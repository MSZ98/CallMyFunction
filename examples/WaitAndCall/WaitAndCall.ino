#include <CallMyFunction.h>

void f() {
    Serial.println("Function called after 1000ms");
}

void setup() {
    Serial.begin(115200);
    Callf.begin(millis);
    Callf.after(f, 1000);
    Serial.println("Program start");
}

void loop() {
    Callf.loop();
}