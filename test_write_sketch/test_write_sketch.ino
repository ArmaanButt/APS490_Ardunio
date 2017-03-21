void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Reading from sensors");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("S:");
  for(int i = 0; i < 256; i++)
  {
      Serial.print("a");
      Serial.print(i);
      Serial.print("|");
  }

  for(int i = 0; i < 256; i++)
  {
      Serial.print("b");
      Serial.print(i);
      Serial.print("|");
  }

  for(int i = 0; i < 256; i++)
  {
      Serial.print("c");
      Serial.print(i);
      Serial.print("|");
  }

  for(int i = 0; i < 256; i++)
  {
      Serial.print("d");
      Serial.print(i);
      Serial.print("|");
  }
  Serial.println();
}

