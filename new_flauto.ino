#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319


const int pressurePin = 2;      // pressure sensor
const int octavePin   = 8;      // octave selector
const int buzzerPin   = 9;      // speaker


const int notePins[] = {7, 5, 6, 12, 11, 10}; 
const int numNotes = sizeof(notePins) / sizeof(notePins[0]);


const int freLow[] = {
  NOTE_A4,  // pin 7
  NOTE_F4,  // pin 5
  NOTE_G4, // pin 6
  NOTE_E4,  // pin 12
  NOTE_D4,  // pin 11
  NOTE_C4   // pin 10
};


const int freHigh[] = {
  NOTE_A5,
  NOTE_F5,
  NOTE_G5,
  NOTE_E5,
  NOTE_D5,
  NOTE_C5
};

int currentFreq = 0;

void setup() {
  pinMode(pressurePin, INPUT_PULLUP);
  pinMode(octavePin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < numNotes; i++) {
    pinMode(notePins[i], INPUT_PULLUP);
  }
}

void loop() {
  bool pressurePressed = (digitalRead(pressurePin) == LOW);
  bool highOctave = (digitalRead(octavePin) == LOW);

  int requestedFreq = 0;

  if (pressurePressed) {
    for (int i = 0; i < numNotes; i++) {
      if (digitalRead(notePins[i]) == LOW) {
        requestedFreq = highOctave ? freHigh[i] : freLow[i];
        break;
      }
    }
  }

  if (requestedFreq != currentFreq) {
    if (requestedFreq == 0) {
      noTone(buzzerPin);
    } else {
      tone(buzzerPin, requestedFreq);
    }
    currentFreq = requestedFreq;
  }

  delay(10); //debounce
}
