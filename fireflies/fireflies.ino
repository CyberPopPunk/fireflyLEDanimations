int NUM_PINS = 3;
int LEDS[] = { 3, 5, 6 };

int breakDelay = 10 * 1000;  //seconds of break into millis

int fireflyCount = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("fireflyCount: " + String(fireflyCount));

  // which LED to light up
  int currentLED = LEDS[fireflyCount % 3];

  // a loop to repeat each animation 3x
  for (int i = 0; i < 3; i++) {

    // a switch-case allows me to call certain functions based off one number
    switch (fireflyCount) {
      case 0:
        // this represents a firefly with even smooth on and smooth off animation
        animation(currentLED, 255 - (i * 80), 6, 6, 300 + (i * 75), 0);
        break;
      case 1:
        // this represents a firefly with even smooth on and fast off animation
        animation(currentLED, 255, 9, 1, 500, 0);
        break;
      case 2:
        // this represents a firefly with even slow on and smooth off animation
        animation(currentLED, 255, 24, 1, 0, 0);
        break;
      case 3:
        // this represents a firefly with blink animation
        animation(currentLED, 160, 1, 1, 0, 4);
        break;
      case 4:
        // this represents a firefly with blink on and slow off animation
        animation(currentLED, 255, 0, 10, 0, 4);
        break;
      case 5:
        // this represents a firefly with only blink animation
        //animation(currentLED, 180,  0, 0, 0, 8 );

        // this represents a firefly with random animations :)
        animation(currentLED, random(255), random(40), random(40), random(30), random(10));
        break;
    }
    delay(1000);
  }
  // time inbetween fireflies
  delay(breakDelay);

  fireflyCount++;

  // limit to the 6 provided animations
  if (fireflyCount > 6) {
    fireflyCount = 0;
  }
}

void animation(int ledPin, int brightness, int attack, int decay, int holdTime, int blinkCount) {
  // this is the same function used for all the animations
  // ledPin : the pin to play the animation on
  // brightness: how bright the overall led gets
  // attack: how fast to come to full brightness
  // decay: how fast to dim to complete darkness
  // holdTime: how long to hold before blinking
  // blinkCount: how many times to blink before dimming

  //attack
  for (int i = 0; i < brightness; i++) {
    analogWrite(ledPin, i);
    delay(attack);
    //Serial.println( "animation1 up: " + String(i));
  }

  //hold
  delay(holdTime);

  //blink
  for (int i = 0; i < blinkCount; i++) {
    analogWrite(ledPin, LOW);
    delay(50);
    analogWrite(ledPin, brightness);
    delay(50);
  }

  //decay
  for (int i = brightness; i >= 0; i--) {
    analogWrite(ledPin, i);
    //Serial.println( "animation1 down: " + String(i));
    delay(decay);
  }
}