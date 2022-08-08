#include <CallMyFunction.h>

Task *t;

// Some functions
void f() {
    Serial.println("Function called repeatedly every 200ms");
}

void g() {
	Serial.println("Function called repeatedly every 500ms");
}

// Function which stops Task t and starts new one
void change() {
	Callf.stop(t);
	Callf.every(g, 500);
}

// f() is called every 200ms, then after 2s, change occurs
// and g() is called every 500ms
void setup() {
    Serial.begin(115200);
    Callf.begin(millis);
	t = Callf.every(f, 200);
    Callf.after(s, 2000);
    Serial.println("Program start");
}

void loop() {
    Callf.loop();
}