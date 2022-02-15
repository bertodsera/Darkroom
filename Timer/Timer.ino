#include <Arduino.h>
#include <NewEncoder.h>
#include <TM1637Display.h>

// Various debug services, uncomment to enable
#define _DEBUG

enum FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };

class Display { 
  private:
    const TM1637Display _ledpanel;  
    uint8_t _data[4];
    int16_t _right;
    int16_t _highThreshold; // top right value that makes an overflow (60 or 100)
    int16_t _lowThreshold;  // low right value that makes an underflow (-1)
    int16_t _left;
    int16_t _leftMax;       // top displayable left value (99)  

    FlowState Display::getState(int16_t value, boolean rightSide) {
      // intercept attempted boundary violation
      if ((_left == _leftMax) && (value == _highThreshold)) { return violationOfHighBoundary; } 
      if ((_left == _lowThreshold + 1) && (value == _lowThreshold)) { return violationOfLowBoundary; }
      // manage over and underflow
      if (rightSide) {
        if (value == _highThreshold) { return countOverflow; }
        else if (value == _lowThreshold) { return countUnderflow; }
        else { return withinBoundaries; };
      // Left side here  
      } else {
        // only top boundary used for left pair
        return nonRelevant;
      };  
    };

    void Display::rightSetBottom() {
      _right = _lowThreshold + 1;
    };

    void Display::rightSetTop() {
      _right = _highThreshold - 1;
    };

    void Display::printToLedPanel() {
      _ledpanel.showNumberDecEx(_left*100+_right, 0xff, true);
    };
     
  public:
    Display::Display(uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue) : 
      _ledpanel( pinClk, pinDIO),
      _data { 0x00, 0x00, 0x00, 0x00 } {
      _lowThreshold  = lowThresholdValue;
      _highThreshold = highThresholdValue;
      _leftMax       = leftMaxValue;
      this->rightSetBottom();
      _left          = _right;
     };

    void Display::init() {
      Serial.println("    Display starting...");
      #ifdef _DEBUG
        Serial.println("... ... Display::init");
        Serial.print("... ... ... lowThreshold: ");
        Serial.println(_lowThreshold);
        Serial.print("... ... ... highThreshold: ");
        Serial.println(_highThreshold);
        Serial.print("... ... ... leftMax: ");
        Serial.println(_leftMax); 
        Serial.print("... ... ... right: ");
        Serial.println(_right);
        Serial.print("... ... ... left: ");
        Serial.println(_left);    
        delay(1000);                          
      #endif       
      _ledpanel.setBrightness(0x0f);
      // Change all digits to zero, at right, then left
      this->getUpdate(0,true);
      this->getUpdate(0,false);
      this->printToLedPanel();
    };     
     
    void Display::setBrightness(uint8_t value) {            
      _ledpanel.setBrightness(value);  
      _ledpanel.setSegments(_data);
    };      


    void Display::setVisible(boolean targetState) {
    };

    // Update display and return possible settings change for encoder
    // enum FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
    FlowState Display::getUpdate(int16_t value, boolean rightSide) {
      FlowState state = this->getState(value, rightSide);
      #ifdef _DEBUG
        Serial.println("... ... Display::getUpdate");
        Serial.print("... ... ... value: ");
        Serial.println(value);
        Serial.print("... ... ... rightSide: ");
        if (rightSide) { Serial.println("*"); } 
        else { Serial.println(); } 
        // countOverflow, withinBoundaries, countUnderflow, nonRelevant
        Serial.print("... ... ... state: ");
        if (state == countOverflow) { Serial.println("countOverflow"); } 
        else if (state == withinBoundaries) { Serial.println("withinBoundaries"); } 
        else if (state == countUnderflow) { Serial.println("countUnderflow"); }
        else if (state == violationOfHighBoundary) { Serial.println("violationOfHighBoundary"); }   
        else if (state == violationOfLowBoundary) { Serial.println("violationOfLowBoundary"); }                       
        else if (state == nonRelevant) { Serial.println("nonRelevant"); }               
        else { Serial.println("Error"); }           
      #endif

        // normal behaviour right
      if (state == withinBoundaries) {
       _right = value;   
         
        // Normal behaviour left  
      } else if (state == nonRelevant) {
        _left  = value; 
           
        // right is overflowing
      } else if (state == countOverflow) { 
        this->rightSetBottom();
        _left++;       
         
        // right is underflowing
      } else if (state == countUnderflow) {
        this->rightSetTop(); // set to top legal value
        _left--;       

      // NOTE: violationOfHighBoundary and violationOfLowBoundary reset
        //       right value to sit on the boundary
      } else if (state == violationOfHighBoundary) {
        this->rightSetTop(); // set to top legal value    
      } else if (state == violationOfLowBoundary) {   
        this->rightSetBottom(); // set to top legal value                
      }
        
      #ifdef _DEBUG
        Serial.println("... ... ... Exiting function with ");       
        Serial.print("... ... ... left: ");
        Serial.println(_left);    
        Serial.print("... ... ... right: ");
        Serial.println(_right);                  
        Serial.println();
      #endif       

      this->printToLedPanel();
      return state;
   };   
};

class RotaryEncoder {
  private:
    NewEncoder _encoder;
    int16_t    _value;
    int16_t    _minVal;
    int16_t    _maxVal;

  public:
    RotaryEncoder::RotaryEncoder(uint8_t aPin, uint8_t bPin, int16_t minValue, int16_t maxValue, int16_t initialValue, uint8_t type = FULL_PULSE) :
      _encoder(aPin, bPin, minValue, maxValue, initialValue, type) {
      _value  = initialValue;
      _minVal = minValue;
      _maxVal = maxValue; 
    };

    void RotaryEncoder::init () {
      NewEncoder::EncoderState state;
      Serial.println("Starting Encoder");

      if (!_encoder.begin()) {
        Serial.println("  Encoder Failed to Start. Check pin assignments and available interrupts. Aborting.");
        while (1) {
          yield();
        }
      } else {
        _encoder.getState(state);
        Serial.print("  Encoder Successfully Started at value = ");
        _value = state.currentValue;
        Serial.println(_value);
      };
    };


    boolean RotaryEncoder::pollValue () {
      NewEncoder::EncoderState currentEncoderState;

      if (_encoder.getState(currentEncoderState)) {
        if (currentEncoderState.currentValue != _value) {
          _value = currentEncoderState.currentValue; 
          #ifdef _DEBUG
            Serial.println("... ... RotaryEncoder::pollValue");
            Serial.print("... ... ... value: ");
            Serial.println(_value);
            Serial.println();
          #endif
          return true;
        };
      };
      return false;
    };

    boolean RotaryEncoder::newSettings(int16_t newMin, int16_t newMax, int16_t newCurrent) {
      NewEncoder::EncoderState state; 
      #ifdef _DEBUG
        Serial.println("... ... RotaryEncoder::newSettings");
        Serial.print("... ... ... newMin: ");
        Serial.println(newMin);
        Serial.print("... ... ... newMax: ");
        Serial.println(newMax);                  
        Serial.print("... ... ... newCurrent: ");
        Serial.println(newCurrent);
        Serial.println();
      #endif           
      _encoder.newSettings(newMin, newMax, newCurrent, state);
      _value  = newCurrent;
      _minVal = newMin;
      _maxVal = newMax;        
    };

    boolean RotaryEncoder::newValue(int16_t newCurrent) {
      NewEncoder::EncoderState state; 
      #ifdef _DEBUG
        Serial.println("... ... RotaryEncoder::newValue");
        Serial.print("... ... ... newCurrent: ");
        Serial.println(newCurrent);
        Serial.println();
      #endif       
      _encoder.newSettings(_minVal, _maxVal, newCurrent, state);
      _value  = newCurrent;     
    };     

    int16_t RotaryEncoder::getValue () { return _value; };
};

class PushButton {
  private:
    uint8_t       _pin;
    unsigned long _lastPressure = 0;

    boolean PushButton::isBeingPressedUnfiltered() {
      int buttonState = digitalRead(_pin);
      return (buttonState == LOW);
    };
  public:
    PushButton::PushButton(uint8_t pin) {
      _pin = pin;
      // avoid the need for a resistor by using the inbuilt pin resistor
      pinMode(_pin, INPUT_PULLUP); 
    };

    boolean PushButton::isBeingPressed() {
      unsigned long currentTime = millis();
      if (this->isBeingPressedUnfiltered() && (currentTime - _lastPressure > 1000)) {
        _lastPressure = currentTime;
        return true;
      };
      return false; 
    };
};

class LedSignal {
  private:
    uint8_t _pin;
  public:
    LedSignal::LedSignal(uint8_t pin) {
      _pin = pin;
      pinMode(_pin, OUTPUT);
    };

    void LedSignal::switchOn() {
      digitalWrite(_pin, HIGH);
    };

    void LedSignal::switchOff() {
      digitalWrite(_pin, LOW);
    };    
};


class Switcher {
  private:
    PushButton _button;
    LedSignal  _led;
    boolean    _isOn = false;
    
  public:
    Switcher::Switcher(uint8_t buttonPin, uint8_t ledPin) :
      _button(buttonPin),
      _led(ledPin) {};

    boolean Switcher::poll() {
      return _button.isBeingPressed();
    };  

    void Switcher::setOn() {
      _led.switchOn();
      _isOn = true;
    };     

    void Switcher::setOff() {
      _led.switchOff();
      _isOn = false;
    };      

    boolean Switcher::isOn() {
      return _isOn;
    };  

    // An ARCHIVE/RESTORE command used to manage the visibility of a switcher's object state.
    //   ON LEDs get switched off to be masked but keep their on state in memory
    //   Masked LEDs that return to visible state get switched back on according to their state in memory
    void Switcher::setVisible(boolean targetState) {
      if (_isOn) {
        if (targetState) { this->_led.switchOn(); }
        else { this->_led.switchOff(); }
      }     
    };   
  
};

enum WhichButton { modeButton, sideButton, noButton};

class FunctionalUnit {
  private:
    Display  _ledDisplay;
    Switcher _mode;
    Switcher _side;
  public:
    FunctionalUnit::FunctionalUnit (uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue,
                                    uint8_t modeButtonPin, uint8_t modeLedPin,
                                    uint8_t sideButtonPin, uint8_t sideLedPin) :
      _ledDisplay(pinClk, pinDIO, lowThresholdValue, highThresholdValue, leftMaxValue),
      _mode(modeButtonPin, modeLedPin),
      _side(sideButtonPin, sideLedPin)  {};

    void FunctionalUnit::init() {  
      _ledDisplay.init();
    };      

    void FunctionalUnit::setBrightness(uint8_t value) {  
      _ledDisplay.setBrightness(value);
    };  

    // NOTE!! This returns whether ANY switcher button in the unit is being pressed,
    //   but it does NOT set the active state for the switcher!! The identity of the 
    //   pressed button is passed back to the function caller, so it can be used.
    // enum WhichButton { modeButton, sideButton, noButton};
    WhichButton FunctionalUnit::poll() {  
      if (_mode.poll()) { return modeButton; }
      else if (_side.poll()) { return sideButton; }
      else { return noButton; }  
    };    

    // This does not alter any value in the unit, it only displays them, or not
    void FunctionalUnit::setVisible( boolean targetState ) {
      _ledDisplay.setVisible(targetState);
      _mode.setVisible(targetState);
      _side.setVisible(targetState);
    };
    
    // FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
    FlowState FunctionalUnit::updateLedDisplay (int16_t value, boolean rightSide) { 
      FlowState state = _ledDisplay.getUpdate(value, rightSide);
      #ifdef _DEBUG
        Serial.println("... ... TimerInterface::updateFromEncoder");
        Serial.println();
      #endif
      return state;
    };         
};


class Buzzer {
    uint8_t _pin;
  public:
    Buzzer::Buzzer( uint8_t pin ) {
      _pin = pin;
    };

    Buzzer::init() {
      pinMode(_pin,OUTPUT);
    }; 

    Buzzer::tic() {
      tone(_pin,50);
      delay(20);
      noTone(_pin);
    }
};


// Module connection pins (Digital Pins ONLY!)
//      Symbol              Pin  // Wire color
// =============================================

// Cable A
//  LED Displays and encoder
// =========================
#define ROTARYENCODERPINA    2    // Brown
#define ROTARYENCODERPINB    3    // Black 
#define TIMERCLK             8    // White
#define TIMERDIO             9    // Grey
#define SOURCECLK           10    // Purple
#define SOURCEDIO           11    // Blue
#define TARGETCLK           12    // Green
#define TARGETDIO           13    // Yellow

// Cable B
//  Buttons signals 
// ================
#define TIMERMODEBUTTONPIN  22    // Orange
#define TIMERSIDEBUTTONPIN  24    // Red
#define SOURCEMODEBUTTONPIN 26    // Brown
#define SOURCESIDEBUTTONPIN 28    // Black
#define TARGETMODEBUTTONPIN 30    // White
#define TARGETSIDEBUTTONPIN 32    // Grey
#define BRIGHTNESSBUTTONPIN 34    // Purple
#define EXECUTEBUTTONPIN    36    // Blue

// Cable C
//  LED signals
// ================
#define TIMERMODEBUTTONLED  25    // Black
#define TIMERSIDEBUTTONLED  27    // White
#define SOURCEMODEBUTTONLED 29    // Grey
#define SOURCESIDEBUTTONLED 31    // Brown
#define TARGETMODEBUTTONLED 33    // Blue
#define TARGETSIDEBUTTONLED 35    // Green
#define BRIGHTNESSBUTTONLED 37    // Yellow

#define BEEPER              53    // Orange (internal short cable)
#define RELAYENLARGER       52    // (internal short cable)

// Cable D
//  LED grounds (just a collector that eventually lands into ground)

// Cable E
//  Various grounds (just a collector that eventually lands into ground)
//  and Power
//        5V      Red
//        3,3V    Brown
//        Ground  Black

// Settings
#define TIMERENCODERMIN    -1
#define TIMERENCODERMAX    60
#define TIMERENCODERSTART   0
#define SIZEENCODERMIN     -1
#define SIZEENCODERMAX    100
#define SIZERENCODERSTART   0
#define ENCODERLEFTMAX     99

// array addresses
#define TIMER_UI       0
#define SOURCE_UI      1
#define TARGET_UI      2


enum FocusTarget { timerUI, sourceUI, targetUI, brightnessUI };

class TimerInterface {
  private:
    FunctionalUnit _functionalUnit[3];
    RotaryEncoder  _encoderObj;
    FocusTarget   _focus = timerUI;
    boolean       _rightSegment = true;
    PushButton    _execute;
    Buzzer        _sound;
    
  public:
    TimerInterface::TimerInterface() : 
      // Init array of Display objects according to their constructor
      // Display::Display(uint8_t pinClk, uint8_t pinDIO, int lowThreshold, int highThreshold, int leftMaxValue) : 
      _functionalUnit{ FunctionalUnit(TIMERCLK,  TIMERDIO,  TIMERENCODERMIN, TIMERENCODERMAX, ENCODERLEFTMAX,
                                      TIMERMODEBUTTONPIN, TIMERMODEBUTTONLED,
                                      TIMERSIDEBUTTONPIN, TIMERSIDEBUTTONLED), 
                       FunctionalUnit(SOURCECLK, SOURCEDIO, SIZEENCODERMIN,  SIZEENCODERMAX,  ENCODERLEFTMAX,
                                      SOURCEMODEBUTTONPIN, SOURCEMODEBUTTONLED,
                                      SOURCESIDEBUTTONPIN, SOURCESIDEBUTTONLED), 
                       FunctionalUnit(TARGETCLK, TARGETDIO, SIZEENCODERMIN,  SIZEENCODERMAX,  ENCODERLEFTMAX,
                                      TARGETMODEBUTTONPIN, TARGETMODEBUTTONLED,
                                      TARGETSIDEBUTTONPIN, TARGETSIDEBUTTONLED) },
      _encoderObj(ROTARYENCODERPINA, ROTARYENCODERPINB, TIMERENCODERMIN, TIMERENCODERMAX, TIMERENCODERSTART, FULL_PULSE),
      _execute(EXECUTEBUTTONPIN),
      _sound(BEEPER) {};

    void TimerInterface::init() {
      Serial.println("Starting Displays ");
      for(int k=0; k <= 2; k++) {
        Serial.print("  Display: ");
        Serial.println(k);
        _functionalUnit[k].init();
      }
      // _encoderObj.init();
    };                            

    void TimerInterface::setBrightness(uint8_t value) {  
      for(int k=0; k <= 2; k++) {
        _functionalUnit[k].setBrightness(value);
      }  
    };

    // enum WhichButton { modeButton, sideButton, noButton};
    void TimerInterface::pollButtons () {  
      WhichButton whichPressed = noButton;
      for (int k=0; k <= 2; k++) {
        whichPressed = _functionalUnit[k].poll();
        if (whichPressed != noButton) {
          // manage the button pressure
          _sound.tic();
          #ifdef _DEBUG
            Serial.println("... ... TimerInterface::pollButtons");
            if (k==TIMER_UI) { 
              Serial.print("... ... ... TIMER ");               
              if (whichPressed==modeButton) { Serial.println("mode"); 
              } else { Serial.println("side"); };
              
            } else if (k==SOURCE_UI) { 
              Serial.print("... ... ... SOURCE "); 
              if (whichPressed==modeButton) { Serial.println("mode"); 
              } else { Serial.println("side"); };
              
            } else if (k==TARGET_UI) { 
              Serial.print("... ... ... TARGET ");
              if (whichPressed==modeButton) {Serial.println("mode"); 
              } else { Serial.println("side"); };
            };
            Serial.println("======================================================");
          #endif
        };
      };  
    };    


    // This function updates the display and returns information on potential
    //   further operations to be performed on the encoder object
    //   ref: FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
    void TimerInterface::updateFromEncoder (uint8_t target, boolean rightSide) { 
      // Act only if there's a new value
      if (_encoderObj.pollValue()) {
        int16_t value = _encoderObj.getValue(); 
        FlowState state = _functionalUnit[target].updateLedDisplay(value, rightSide);

        #ifdef _DEBUG
          Serial.println("... ... TimerInterface::updateFromEncoder");
          Serial.println();
        #endif   

        // Manage the encoder, if any modificagtion is needed
        if ((state == countOverflow) || (state == violationOfLowBoundary)) {
          // setting right counter on its min legal value
          if (target == TIMER_UI) {
            _encoderObj.newValue(TIMERENCODERMIN + 1); 
          } else {
            _encoderObj.newValue(SIZEENCODERMIN + 1);         
          }
        } else if ((state == countUnderflow) || (state == violationOfHighBoundary)) {
          // setting right counter on its top legal value
          if (target == TIMER_UI) {
            _encoderObj.newValue(TIMERENCODERMAX - 1); 
          } else {
            _encoderObj.newValue(SIZEENCODERMAX - 1);         
          }
        };
        #ifdef _DEBUG
          Serial.println("===============================================================");
        #endif            
      };     
    };

    // enum FocusTarget { timerUI, sourceUI, targetUI, brightnessUI };
    void TimerInterface::focusEncoderOn (FocusTarget destination, boolean rightSide) {
      _focus = destination;

      // input from encoder, output on timer LED panel, format hh:mm or mm:ss
      //   source and destination panels are off
      if (destination==timerUI) {
        if (rightSide) {
        } else {
        }
      // input from encoder, output on target LED panel, format in mm., from 0 to 9999 (~10m)
      //   timer is off
      //   source and destination are on  
      } else if (destination==sourceUI) {
        if (rightSide) {
        } else {
        }      
      // input from encoder, output on target LED panel, format in mm., from 0 to 9999 (~10m)
      //   timer is off
      //   source and destination are on         
      } else if (destination==targetUI) {
        if (rightSide) {
        } else {
        }     
      // input from encoder, output on LED panels' brightness
      //   timer, source and destination are on   
      //   rightSide is meaningless for this context       
      } else if (destination==brightnessUI) {
      };
    };
};


TimerInterface userInterface;
  
void setup()
{
  Serial.begin(57600); // open the serial port at 57600 bps:
  Serial.println("Serial started");
  delay(500);
  userInterface.init();
}

void loop()
{
  userInterface.pollButtons();
  delay(100);
}
