#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <Arduino.h>
#include "Timer.h"
#include <Looper.h>

class Button : public Looper {
    protected:
        Timer upTimer = Timer(1000);
        Timer longTimer = Timer(5000);
        int pushCount;
        bool btnDown = false;
        char* id;
        char* label;
        bool enabled = true;   // enable/disable
        
    public:
        Button(const char* id, bool enabled = true);
        virtual ~Button();
        virtual const char* getId();
        virtual const char* getLabel();
        virtual bool isEnabled() const;
        virtual void disable();
        virtual void enable();
        virtual void setStatus(bool status);
        virtual bool isPressed() const =0;
        virtual bool wasPushed(bool clear = false);
        virtual unsigned long getPushDuration() const;
        virtual int getPushCount() const;
        void loop() override;
        virtual void setLabel(const char* label);
};

class AnalogButton : public Button {
    protected:
        int pin;
        int threshold; // value above which button is considered as "pushed down"

    public:
        AnalogButton(const char* id, int pin, int threshold=500) : Button(id) {
            this->pin = pin;
            this->threshold = threshold;
            pinMode(pin, INPUT);
        }
        virtual bool isPressed() const override {return analogRead(pin) > threshold;};
        
};

class DigitalButton : public Button {
    protected:
        int pin;

    public:
        DigitalButton(const char* id, int pin) : Button(id) {
            this->pin = pin;
            pinMode(pin, INPUT);
        }
        virtual bool isPressed() const override {return digitalRead(pin);};
        
};

#ifdef ESP32

class TouchButton : public Button {
    protected:
        int pin;
        int threshold; // value BELOW which button is considered as "pushed down"

    public:
        TouchButton(const char* id, int pin, int threshold=20) : Button(id) {
            this->pin = pin;
            this->threshold = threshold;
            pinMode(pin, INPUT);
        }
        virtual bool isPressed() const override {return touchRead(pin) < threshold;};
        
};

#endif

#endif

