#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)


int buzzer = 8 ;

int buttonState = 0;     // current state of the button
bool lastbuttonState = false; // previous state of the button
int startPressed = 0;    // the moment the button was pressed
int endPressed = 0;      // the moment the button was released
int holdTime = 0;        // how long the button was hold
int idleTime = 0;        // how long the button was idle
int lastMillis = 0;
String buff = "";


void setup ()
{
    lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display 
  Serial.begin(9600);
  pinMode (buzzer, INPUT) ;
}
void loop() {
  buttonState = digitalRead(buzzer); // read the button input


  if (buttonState == LOW) {
    //if buffer full
    if ((millis() - endPressed) % 65536 > 500) { //letter
      if (buff != "") { 
        Serial.println(retBuf());
        clearBuf();
        lastbuttonState = true;
      }

    }
     if ((millis() - endPressed) % 65536 > 1500) { //word
      if (lastbuttonState == true) {
        Serial.println("SPACE HERE");
        lastbuttonState = false;
      }

    }

  }

  else if (buttonState == HIGH ) { // button state changed
    startPressed = millis();

    updateState();
  }



}

void updateState() {
  // the button has been just pressed


  while (digitalRead(buzzer) == HIGH) {
    endPressed = millis();
  }


  // the button has been just released

  holdTime = endPressed - startPressed;
  Serial.println(holdTime);

  if (holdTime < 500) {
    Serial.println("DIT");
    buff = buff + ".";
  }

  else if (holdTime >= 500) {
    Serial.println("DAH");
    buff = buff + "-";
  }


}


String retBuf() {
  return morseToChar(buff);
}


String morseToChar(const String& morse) {
  static String letters[] = {".-", "-...", "-.-.", "-..", ".",
                             "..-.", "--.", "....", "..", ".---",
                             "-.-", ".-..", "--", "-.", "---",
                             ".--.", "--.-", ".-.", "...", "-",
                             "..-", "...-", ".--", "-..-",
                             "-.--", "--.."
                            };

  for (int k = 0; k < sizeof(letters); k++) {

    if (letters[k] == morse) {
      lcd.print((char) (k + 65));
      return ((String) (k + 65));
    }
  }
  return "ERROR";

}

void clearBuf() {
  buff = "";
}
