const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;
const int buttonPin = 2;

unsigned char lookup_7seg[] = {0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x80};

unsigned char shake_dice[] = {0x63, 0x5C};

unsigned char roll_dice[] = {0x1C, 0x58, 0x54, 0x4C};

int rand_seed;
int rand_num = 0;
unsigned char shake_toggle = 0;
int index = 0;
int shake_speed;

void setup() {
  pinMode(latchPin, OUTPUT);

  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, lookup_7seg[6]);
  digitalWrite(latchPin, HIGH);
  randomSeed(analogRead(0));
}

void loop() {
  if(digitalRead(buttonPin)){
    shake_speed = 150;
    delay(30);

    while (digitalRead(buttonPin)) {
      rand_seed++;

      if (shake_toggle) {
        AnimateDice(0, shake_dice);
        shake_toggle = 0;
        }
        else {
          AnimateDice(1, shake_dice);
          shake_toggle = 1;
        }
      
      for (int rolls = 0; rolls < (rand_seed % 10 + 14); rolls++) {
        AnimateDice(index, roll_dice);
        delay((1 + rolls) * 20);
        index++;
        if (index > 3){
          index = 0;
          }
        }
        rand_num = random(0, 6);
        DiceNumber(rand_num);
      }
    }
}
void DiceNumber(unsigned char num) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, lookup_7seg[num]);
  digitalWrite (latchPin, HIGH);
}

void AnimateDice(int seg, unsigned char *table) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, table[seg]);
  digitalWrite(latchPin, HIGH);
}