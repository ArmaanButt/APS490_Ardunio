
const int write_EN_bar =  12;
const int read_EN_bar =  11;
const int reset_EN_bar = 10;
const int emptyF_bar = 9;

const int D0 = 8;
const int Q0 = 7;

int i = 0;
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
  
  
  digitalWrite(reset_EN_bar, HIGH);
  digitalWrite(reset_EN_bar, LOW);
  digitalWrite(reset_EN_bar, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  int val;

   val = digitalRead(emptyF_bar);
  Serial.println("EF");
  Serial.println(val);

  if(i==0){
    digitalWrite(D0, HIGH);
    digitalWrite(write_EN_bar, LOW);
    delay(50);
    digitalWrite(write_EN_bar, HIGH);
    i++;
  }
  else{
   digitalWrite( read_EN_bar, LOW);
   delay(50);
   val = digitalRead(Q0);
   digitalWrite( read_EN_bar, HIGH);
   Serial.println("Q0");
   Serial.println(val);
  }
  
  delay(5000);
}
