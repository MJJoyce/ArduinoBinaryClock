////////////////////////////////////////////////////////////////////////////////
//
// Basic Binary Block controlled by an Arduino
//
// Coded by Michael Joyce, December 2011
//
// Take this code and do whatever you please with it.
//
////////////////////////////////////////////////////////////////////////////////

// Pin Declarations
////////////////////////////////////////////////////////////////////////////////
// Pins for all the lights
int minOne1 = 0, minOne2 = 1, minOne4 = 2, minOne8 = 3;
int minTen1 = 4, minTen2 = 5, minTen4 = 6;
int hourOne1 = 7, hourOne2 = 8, hourOne4 = 9, hourOne8 = 10;
int hourTen1 = 11, hourTen2 = 12;
int secondPin = A1;

// Pins for the minute and hour inputs and mode toggle button
int minButton = A5;
int hourButton = A0;
int modeToggle = A3;

// Globals
////////////////////////////////////////////////////////////////////////////////
short seconds = 0, minutes = 0, hours = 0;
unsigned long frameTime = 0;
short minRead1 = 0, minRead2 = 0, minRead = 0;
short hourRead1 = 0, hourRead2 = 0, hourRead = 0;

void setup()
{
    pinMode(minOne1, OUTPUT);
    pinMode(minOne2, OUTPUT);
    pinMode(minOne4, OUTPUT);
    pinMode(minOne8, OUTPUT);
    pinMode(minTen1, OUTPUT);
    pinMode(minTen2, OUTPUT);
    pinMode(minTen4, OUTPUT);
    pinMode(hourOne1, OUTPUT);
    pinMode(hourOne2, OUTPUT);
    pinMode(hourOne4, OUTPUT);
    pinMode(hourOne8, OUTPUT);
    pinMode(hourTen1, OUTPUT);
    pinMode(hourTen2, OUTPUT);
    pinMode(secondPin, OUTPUT);
    pinMode(minButton, INPUT);
    pinMode(hourButton, INPUT);
    pinMode(modeToggle, INPUT);

    initialize();
}

void loop()
{
    // Allow the user to adjust the time on the clock if it is in "set" mode
    if (digitalRead(modeToggle) == HIGH)
    {
        minRead1 = digitalRead(minButton);
        hourRead1 = digitalRead(hourButton);
        delay(10);
        minRead2 = digitalRead(minButton);
        hourRead2 = digitalRead(hourButton);

        minRead = minRead1 && minRead2;
        hourRead = hourRead1 && hourRead2;

        if (minRead == HIGH)
            minutes++;

        if (hourRead == HIGH)
            hours++;

        if (minutes >= 60)
        {
            hours++;
            minutes = 0;
        }

        if (hours >= 24)
        {
            hours = 0;
        }

        resetLights();
        updateLights();
        delay(100);
        return;
    }

    frameTime = millis();

    seconds++;

    if (seconds >= 60)
    {
        minutes++;
        seconds = 0;
    }

    if (minutes >= 60)
    {
        hours++;
        minutes = 0;
    }

    if (hours >= 24)
    {
        hours = 0;
    }

    resetLights();
    updateLights();

    digitalWrite(secondPin, HIGH);
    delay(100);
    digitalWrite(secondPin, LOW);

    delay(1000 - (millis() - frameTime));
}

// initialize()
//
// Iterate through all the lights in order as a check for proper setup
////////////////////////////////////////////////////////////////////////////////
void initialize()
{
    digitalWrite(secondPin, HIGH);
    delay(100);
    digitalWrite(secondPin, LOW);
    digitalWrite(minOne1, HIGH);
    delay(100);
    digitalWrite(minOne1, LOW);
    digitalWrite(minOne2, HIGH);
    delay(100);
    digitalWrite(minOne2, LOW);
    digitalWrite(minOne4, HIGH);
    delay(100);
    digitalWrite(minOne4, LOW);
    digitalWrite(minOne8, HIGH);
    delay(100);
    digitalWrite(minOne8, LOW);
    digitalWrite(minTen1, HIGH);
    delay(100);
    digitalWrite(minTen1, LOW);
    digitalWrite(minTen2, HIGH);
    delay(100);
    digitalWrite(minTen2, LOW);
    digitalWrite(minTen4, HIGH);
    delay(100);
    digitalWrite(minTen4, LOW);
    digitalWrite(hourOne1, HIGH);
    delay(100);
    digitalWrite(hourOne1, LOW);
    digitalWrite(hourOne2, HIGH);
    delay(100);
    digitalWrite(hourOne2, LOW);
    digitalWrite(hourOne4, HIGH);
    delay(100);
    digitalWrite(hourOne4, LOW);
    digitalWrite(hourOne8, HIGH);
    delay(100);
    digitalWrite(hourOne8, LOW);
    digitalWrite(hourTen1, HIGH);
    delay(100);
    digitalWrite(hourTen1, LOW);
    digitalWrite(hourTen2, HIGH);
    delay(100);
    digitalWrite(hourTen2, LOW);
}

//*** NOTE *** This could be improved by taking into consideration whether the
// minutes and hours need adjusting this second.
// resetLights()
//
// Sets all the light pins to low in preparation for setting the adjusted time.
////////////////////////////////////////////////////////////////////////////////
void resetLights()
{
    digitalWrite(minOne1, LOW);
    digitalWrite(minOne2, LOW);
    digitalWrite(minOne4, LOW);
    digitalWrite(minOne8, LOW);

    digitalWrite(minTen1, LOW);
    digitalWrite(minTen2, LOW);
    digitalWrite(minTen4, LOW);

    digitalWrite(hourOne1, LOW);
    digitalWrite(hourOne2, LOW);
    digitalWrite(hourOne4, LOW);
    digitalWrite(hourOne8, LOW);

    digitalWrite(hourTen1, LOW);
    digitalWrite(hourTen2, LOW);
}

void updateLights()
{
    short minOnes = minutes % 10;
    short minTens = minutes / 10;

    short hourOnes = hours % 10;
    short hourTens = hours / 10;

    //*** NOTE *** This could be improved by only setting the lights if they need to be changed
    // This is done naively for simplicities sake
    // Setting one's column of minutes
    if (minOnes == 1 || minOnes == 3 || minOnes == 5 || minOnes == 7 || minOnes == 9)
        digitalWrite(minOne1, HIGH);
    if (minOnes == 2 || minOnes == 3 || minOnes == 6 || minOnes == 7)
        digitalWrite(minOne2, HIGH);
    if (minOnes == 4 || minOnes == 5 || minOnes == 6 || minOnes == 7)
        digitalWrite(minOne4, HIGH);
    if (minOnes == 8 || minOnes == 9)
        digitalWrite(minOne8, HIGH);

    // Setting the ten's column of minutes
    if (minTens == 1 || minTens == 3 || minTens == 5)
        digitalWrite(minTen1, HIGH);
    if (minTens == 2 || minTens == 3)
        digitalWrite(minTen2, HIGH);
    if (minTens == 4 || minTens == 5)
        digitalWrite(minTen4, HIGH);

    // Setting the ones column of hours
    if (hourOnes == 1 || hourOnes == 3 || hourOnes == 5 || hourOnes == 7 || hourOnes == 9)
        digitalWrite(hourOne1, HIGH);
    if (hourOnes == 2 || hourOnes == 3 || hourOnes == 6 || hourOnes == 7)
        digitalWrite(hourOne2, HIGH);
    if (hourOnes == 4 || hourOnes == 5 || hourOnes == 6 || hourOnes == 7)
        digitalWrite(hourOne4, HIGH);
    if (hourOnes == 8 || hourOnes == 9)
        digitalWrite(hourOne8, HIGH);

    // Setting the ten's column of hours
    if (hourTens == 1)
        digitalWrite(hourTen1, HIGH);
    if (hourTens == 2)
        digitalWrite(hourTen2, HIGH);
}
