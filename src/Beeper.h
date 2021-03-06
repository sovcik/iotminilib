#ifndef __BEEPER_H__
#define __BEEPER_H__

#include <Arduino.h>
#include "tones.h"
#include <BinaryOut.h>
#include <Looper.h>

class Beeper : public Looper {
    protected:
        bool enabled;
        
        uint16_t beepDurationOn;    // duration of beeping phase
        uint16_t beepDurationOff;   // duration of silence between beeps
        uint32_t phaseStart;        // time when specific beeping phase started
        uint32_t phaseDuration;
        int8_t phase;
        int8_t beepCount;
    
    public:
        Beeper();
        virtual ~Beeper();

        /**
         * Set beep duration (in ms)
         * 
         * @durationOn - beep duration
         * @durationOff - pause between beeps
         */
        void setDuration(uint16_t durationOn, uint16_t durationOff);

        /**
         * Request beeper to beep. 
         * Beeping itself has to be executed by calling loop() or doBeep() methods.
         * 
         * @count beep count
         */
        void beep(int8_t count);

        virtual void soundOn();
        virtual void soundOff();
        void enable();
        void disable();
        bool isEnabled();

        /**
         * Execute beeping - blocking other code until beeping finishes.
         */
        void doBeep();                 // do all beeping - blocks all other code until beeping is finished

        /**
         * Execute beeping - non-blocking
         */
        void loop() override;          // non-blocking beeping
    
};

/**
 * Beeper connected to a digital pin.
 * Simple on/off beeping.
 */
class PinBeeper : public Beeper {
    protected:
        uint8_t beeperPin;

    public:
        PinBeeper(uint8_t pin);
        virtual void soundOn() override;
        virtual void soundOff() override;
};

/**
 * Beeper connected to PWM pin. 
 * Allows setting tone pitch. See method setPitch()
 */
class PWMBeeper : public PinBeeper {
    protected:
        uint16_t beepPitch;

    public:
        PWMBeeper(uint8_t pin);
        void setPitch(uint16_t pitch);
        virtual void soundOn() override;
        virtual void soundOff() override;
};


/**
 * Pin beeper conneced to shift register
 */
class SHO_Beeper : public BOut_ShReg, public Beeper {
    public:
        SHO_Beeper(ShiftOutRegister* reg, uint8_t bit);
        virtual void soundOn() override;
        virtual void soundOff() override;

};

#endif
