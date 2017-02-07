

const int pinCLK = 12;

void setup() {
  // put your setup code here, to run once:
pinMode(pinCLK, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinCLK, HIGH);
  digitalWrite(pinCLK, LOW);
}
