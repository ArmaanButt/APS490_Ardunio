const int pin_CLK = 9;
const int reset_bar = 10;
const int QA = 8;
const int QB = 7;
const int QC = 6;
const int QD = 5;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(pin_CLK, OUTPUT);
pinMode(reset_bar, OUTPUT);
pinMode(QA, INPUT);
pinMode(QB, INPUT);
pinMode(QC, INPUT);
pinMode(QD, INPUT);

digitalWrite(pin_CLK, LOW);
delay(50);
digitalWrite(reset_bar, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
digitalWrite(pin_CLK, LOW);
digitalWrite(pin_CLK, HIGH);

int val = digitalRead(QA);
Serial.print(val);
val = digitalRead(QB);
Serial.print(val);
val = digitalRead(QC);
Serial.print(val);
val = digitalRead(QD);
Serial.println(val);
delay(1000);
  
}
