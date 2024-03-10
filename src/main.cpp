#include <Arduino.h>

/**
 * @Hardwares: M5AtomS3
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5AtomS3: https://github.com/m5stack/M5AtomS3
 */

#include "M5AtomS3.h"
#include "UNIT_HBRIDGE.h"

UNIT_HBRIDGE driver;

//#define FAN1        1
//#define PWM_CH_FAN  1
//#define PWM_RES     8
//const int MAX_DC = (int)(pow(2, PWM_RES) - 1);

int button_step = 0;

void setup() {

  // PWM CH 1 (FAN)
  // 5 kHz freq
  // 8 bit resolution
  // attached to GPIO 1
  //ledcSetup(PWM_CH_FAN, 5000, PWM_RES);
  //ledcAttachPin(FAN1, PWM_CH_FAN);
    
    Wire.begin(2,1);
    auto cfg = M5.config();
    AtomS3.begin(cfg);
    driver.begin(&Wire, HBRIDGE_ADDR, 2, 1, 100000L); //NOTE: Update Unit H-bridge.h for the correct i2c PINs

    AtomS3.Display.setTextColor(GREEN);
    AtomS3.Display.setTextDatum(middle_center);
    AtomS3.Display.setFont(&fonts::Orbitron_Light_24);
    AtomS3.Display.setTextSize(1);
    AtomS3.Display.drawString("Click!", AtomS3.Display.width() / 2,
                              AtomS3.Display.height() / 2);
    Serial.println("Click BtnA to Test");
}

void loop() {
    AtomS3.update();
    if (AtomS3.BtnA.wasPressed()) {
        AtomS3.Display.clear();
        AtomS3.Display.drawString("Pressed", AtomS3.Display.width() / 2,
                                  AtomS3.Display.height() / 2);
        button_step = button_step + 1;
        if (button_step == 5) 
        {
        button_step = 0; 
                               
        }

        Serial.println("Pressed");
    }
    if (AtomS3.BtnA.wasReleased()) {
        AtomS3.Display.clear();
        //AtomS3.Display.drawString("Released", AtomS3.Display.width() / 2, AtomS3.Display.height() / 2);
        AtomS3.Display.drawString(String(button_step,DEC), AtomS3.Display.width() / 2,
                                  AtomS3.Display.height() / 2);
    
        driver.setDriverDirection(1);
        driver.setDriverPWMFreq(100);

    if (button_step == 0) 
        {
        driver.setDriverSpeed8Bits(0);                    
        } 

    if (button_step == 1) 
        {
        driver.setDriverSpeed8Bits(100);                    
        } 
    if (button_step == 2) 
        {
        driver.setDriverSpeed8Bits(128);                    
        }     
    if (button_step == 3) 
        {
        driver.setDriverSpeed8Bits(160);                    
        }  
    if (button_step == 4) 
        {
        driver.setDriverSpeed8Bits(255);                    
        }  
        //driver.setDriverSpeed8Bits(140);
    
    //ledcWrite(PWM_CH_FAN, 255);
    //delay(10);                                
    
        Serial.println("Released");
    }
}
