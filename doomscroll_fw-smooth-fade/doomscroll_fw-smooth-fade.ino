// Define the PWM pins (bottom to top)
const int pwmPins[] = {11, 10, 9};
const int numPins = 3;

// Speed of the fade (delay in milliseconds between steps)
int fadeSpeed = 5; // Adjust for faster/slower fade

// Offset (X) between the start of each LED's fade-up (in milliseconds)
int offset = 500; // Adjust for more/less delay between LED starts

// Pause duration (milliseconds) after all LEDs fade down
int pauseDuration = 1000; // Adjust for longer/shorter pause

void setup() {
  // Initialize all LEDs to off
  for (int i = 0; i < numPins; i++) {
    analogWrite(pwmPins[i], 0);
  }
}

void loop() {
  // Start fading up each LED with the specified offset
  unsigned long startTimes[numPins];
  bool fadingUp[numPins] = {true, true, true};
  bool fadingDown[numPins] = {false, false, false};

  for (int i = 0; i < numPins; i++) {
    startTimes[i] = millis() + (i * offset);
  }

  unsigned long cycleStart = millis();
  bool cycleComplete = false;

  while (!cycleComplete) {
    unsigned long currentTime = millis() - cycleStart;

    for (int i = 0; i < numPins; i++) {
      unsigned long ledTime = currentTime - (i * offset);

      if (ledTime < 255 * fadeSpeed) {
        // Fade up
        int brightness = map(ledTime, 0, 255 * fadeSpeed, 0, 255);
        brightness = constrain(brightness, 0, 255);
        analogWrite(pwmPins[i], brightness);
      } else if (ledTime < 510 * fadeSpeed) {
        // Fade down
        int brightness = map(ledTime, 255 * fadeSpeed, 510 * fadeSpeed, 255, 0);
        brightness = constrain(brightness, 0, 255);
        analogWrite(pwmPins[i], brightness);
      } else {
        // LED is off
        analogWrite(pwmPins[i], 0);
      }
    }

    // Check if all LEDs have completed their fade down
    if (currentTime >= (numPins - 1) * offset + 510 * fadeSpeed) {
      cycleComplete = true;
    }

    delay(fadeSpeed);
  }

  // Pause after all LEDs are off
  delay(pauseDuration);
}
