// Define the PWM pins (bottom to top)
const int pwmPins[] = {11, 10, 9};
const int numPins = 3;

// Speed of the scroll (delay in milliseconds between steps)
int scrollSpeed = 5; // Adjust for faster/slower scroll

// Brightness steps for smooth fade
int fadeSteps = 100; // Number of steps to fade in/out

// Crossover/offset: How much the next LED starts fading in before the previous one fades out (0-255)
int crossover = 0; // Adjust for more/less overlap

// Pause duration (milliseconds) after the last LED fades off
int pauseDuration = 2000; // Adjust for longer/shorter pause

void setup() {
  // No setup needed for PWM pins
}

void loop() {
  // Scroll the beam upward smoothly with crossover
  for (int i = 0; i < numPins; i++) {
    // Fade in the current LED
    for (int brightness = 0; brightness <= 255; brightness += (255 / fadeSteps)) {
      analogWrite(pwmPins[i], brightness);

      // Fade out the previous LED if it's still on and brightness is above crossover
      if (i > 0 && brightness >= crossover) {
        int prevBrightness = 255 - (brightness - crossover);
        prevBrightness = constrain(prevBrightness, 0, 255);
        analogWrite(pwmPins[i - 1], prevBrightness);
      }

      delay(scrollSpeed);
    }
  }

  // Fade out the last LED after the beam passes
  for (int brightness = 255; brightness >= 0; brightness -= (255 / fadeSteps)) {
    analogWrite(pwmPins[numPins - 1], brightness);
    delay(scrollSpeed);
  }

  // Pause for the specified duration after the last LED fades off
  delay(pauseDuration);

  // Reset all LEDs to off for the next scroll (redundant here, but ensures clean state)
  for (int i = 0; i < numPins; i++) {
    analogWrite(pwmPins[i], 0);
  }
}
