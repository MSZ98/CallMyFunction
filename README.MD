# 1. CallMyFunction
Arduino library to call function with time restrictions

## 2. Supported boards
Should work on most of the boards, tested on UNO, ESP32 and ESP8266

## 3. Usage
### 3.1 Example - Call function 5 times
```
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
```

### 3.2 Example - Call function every 200ms
```
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
```

### 3.3 Example - Call function after 1000ms
```
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
```

### 3.4 Example - Loop function for 2ms
```
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
```

# 4. Description
## 4.1 Callf.begin()
`void begin(unsigned long (*timef)())`</br>
Before you start using Callf, you must give it a function by Callf.begin()
to measure the time, just like millis(). It can obviously be any other function
that returns constantly incrementing value, like micros() or nanos() or whatever,
but the unit of returned time value will be inherited by all Callf methods. 
## 4.2 Callf.loop()
`void loop()`</br>
Callf.loop() has to be called as often as it's possible. Best in an infinite loop.
It checks time and calls given functions.
## 4.3 Callf.every()
There are two declarations of this method:
 * `Task* every(void (*func)(), unsigned long period, int n)`
 * `Task* every(void (*func)(), unsigned long period)`

It's used to call given function repeatedly, once in the given period of time
and no more than n times. When n is less than 0 (e.g. -1), n doesn't count and
function is called endlessly. Second declaration of Callf.every is the same
as first, but n = -1.

It also returns pointer to object of type Task. It's like action id.
You can for example turn of the task with Callf.stop(task) and function
will not be called anymore.
## 4.4 Callf.after()
`Task* after(void (*func)(), unsigned long time)`</br>
Function is called after given time.
## 4.5 Callf.four()
`Task* four(void (*func)(), unsigned long period, unsigned long time)`</br>
Sorry, for is reserved word in C++, so it has to be four.
It works very similar as every(), but instead of specifying amount of calls to do
you have to specify amount of time for execution.
In other words, function is called repeatedly for specified amount of time.
## 4.6 Callf.done()
`bool done(Task *task)`</br>
Returns true if task is completed and function will not be called anymore
or false if function is going to be called.
## 4.7 Callf.len()
`int len()`</br>
Returns a number of running tasks.
## 4.8 Callf.stop()
`void stop(Task *task)`</br>
Forces task to stop immediately.
## 4.9 General description
 * When you call method Callf.begin(millis), you provide Callf with a function to measure the time
 * When you call method Callf.every(), Callf.after() or Callf.four(), new Task object is created
   dynamically and added to a list of tasks, so you can have multiple tasks running at once.
 * When you call method Callf.loop(), every task in the list of tasks is processed and decision
   is made whether function should be called, task should be deleted or nothing should be done.
 * Some minor methods like Callf.len(), Callf.done() or Callf.stop() give you more flexibility
   for using library.

 
 
 
 
 
 
