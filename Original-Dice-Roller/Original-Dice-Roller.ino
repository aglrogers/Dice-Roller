/*
 * Small program for my microcontroller powered dice roller.
 * User presses a button, and the dice roller displays a value from 1 to 6.
 * This program uses a custom library to handle the button input.
 */

// My custom button library
#include <A_Lib_Button.h>

// Initialise a push button with pin number 7 and debounce value of 50ms
PushButton go_button(7, 50);

void setup()
{
  // Set pin modes
  DDRA = B01111111;
  delay(100);

  // Flash all LEDs
  PORTA = B01111111;
  delay(400);
  PORTA = B00001000;
  delay(100);
}

void loop()
{
  switch (go_button.scan())
  {
    // Clear the display when button is held down
    case SINGLE_PRESSED:
      PORTA = B00000000;
      break;

    // Run the program when the button is released
    case SINGLE_RELEASED:
      display_result();
      break;
  }
}

// Play a little animation and display a random value
void display_result()
{
  int delay_value = 20;

  // The random value is chosen
  int random_value = random(1, 7);

  // All of this just cycles through each pin in
  // PORT A to create a little animated effect
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      digitalWrite(j, HIGH);
      delay(delay_value);

      digitalWrite(j, LOW);

      delay_value += 2;
    }

    delay_value += 10;
  }

  // Quick suspensful delay
  delay(220);

  // Display a graphical output depending on the random value.
  // So,
  //
  //    Lets say the random value = 4
  //    Light up LEDs in following arrangment to display the number 4:
  //      X   x
  //      - - -
  //      X   X
  //
  //    Random value = 6
  //    Light up LEDs as follows:
  //      X   x
  //      X - X
  //      X   X
  switch (random_value)
  {
    case 1:
      PORTA = B00001000;
      break;

    case 2:
      PORTA = B01000001;
      break;

    case 3:
      PORTA = B01001001;
      break;

    case 4:
      PORTA = B01010101;
      break;

    case 5:
      PORTA = B01011101;
      break;

    case 6:
      PORTA = B01110111;
      break;
  }

  delay(100);
}
