
const int write_EN_bar =  12;
const int read_EN_bar =  11;
const int reset_EN_bar = 10;
const int emptyF_bar = 9;

const int D0 = 8;
const int Q0 = 7;

//XI is tied to GND
//FL/RT_bar is tied to VCC

int i = 0,j=0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(write_EN_bar, OUTPUT);
  pinMode(read_EN_bar, OUTPUT);
  pinMode(reset_EN_bar, OUTPUT);
  pinMode(emptyF_bar, INPUT); 
 
  pinMode(D0, OUTPUT);
  pinMode(Q0, INPUT);

  digitalWrite(write_EN_bar, HIGH);
  digitalWrite(read_EN_bar, HIGH);

  delay(100);
  
  digitalWrite(reset_EN_bar, HIGH);
  delay(100);
  digitalWrite(reset_EN_bar, LOW);
  delay(100);
  digitalWrite(reset_EN_bar, HIGH);
  delay(100);
  Serial.println("Resetted");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

  int val;

   val = digitalRead(emptyF_bar);
  Serial.println("EF");
  Serial.println(val);

  if(i<20){
    digitalWrite(D0, HIGH);
    digitalWrite(write_EN_bar, LOW);
    delay(50);
    digitalWrite(write_EN_bar, HIGH);
    Serial.println("Wrote");

   Serial.println(i);
    i++;
  }
  else{
   digitalWrite( read_EN_bar, LOW);
   delay(50);
   val = digitalRead(Q0);
   digitalWrite( read_EN_bar, HIGH);
   Serial.println("Q0");
   Serial.println(val);

     Serial.println(j);
  j++; 
   
  }

  delay(1000);
}
