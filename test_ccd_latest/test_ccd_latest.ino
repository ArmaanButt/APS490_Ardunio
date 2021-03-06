// Define various ADC prescaler:
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
uint8_t CLKpin = 4;    // <-- Arduino pin delivering the clock pulses to pin 3 (CLK) of all TSL1402R 
uint8_t SIpin = 5;     // <-- Arduino pin delivering the SI (start/stop integration) pulse to pin 2 of all TSL1402R 

//Arduino pins for each connected to AO1/AO2 to each of the TSL1402R
uint8_t S1APin = 0;     
uint8_t S2APin = 1;
uint8_t S3APin = 2;
uint8_t S4APin = 3;
uint8_t S5APin = 4;
uint8_t S6APin = 5;
uint8_t S7APin = 6;
uint8_t S8APin = 7;
uint8_t S9APin = 8;
uint8_t S10APin = 9;
uint8_t S11APin = 10;
uint8_t S12APin = 11;

int S1Data[256];
int S2Data[256];
int S3Data[256];
int S4Data[256];
int S5Data[256];
int S6Data[256];
int S7Data[256];
int S8Data[256];
int S9Data[256];
int S10Data[256];
int S11Data[256];
int S12Data[256];

void setup() {
  // put your setup code here, to run once:
  // Initialize two Arduino pins as digital output:
  pinMode(CLKpin, OUTPUT); 
  pinMode(SIpin, OUTPUT);  

  // To set up the ADC, first remove bits set by Arduino library, then choose 
  // a prescaler: PS_16, PS_32, PS_64 or PS_128:
  ADCSRA &= ~PS_128;  
  ADCSRA |= PS_32; // <-- Using PS_32 makes a single ADC conversion take ~30 us

  // Next, assert default setting:
  analogReference(DEFAULT);

  // Set all IO pins low:
  for( int i=0; i< 14; i++ )
  {
      digitalWrite(i, LOW);  
  }

  // Clock out any existing SI pulse through the ccd register:
  for(int i=0;i< 260;i++)
  {
      ClockPulse(); 
  }

  // Create a new SI pulse and clock out that same SI pulse through the sensor register:
  digitalWrite(SIpin, HIGH);
  ClockPulse(); 
  digitalWrite(SIpin, LOW);
  for(int i=0;i< 260;i++)
  {
      ClockPulse(); 
  }
  
//  Serial.begin(115200);
  Serial.begin(250000);
  Serial.println("Reading from sensors");
}

void loop() {
  int lastVal;
  int paddingOne = 64;
  int paddingTwo = 64;
  // put your main code here, to run repeatedly:
  //arrays where the readout of the photodiodes is stored, as 16-bit integers
    
  // Stop the ongoing integration of light quanta from each photodiode by clocking in a SI pulse 
  // into the sensors register:
  digitalWrite(SIpin, HIGH);
  ClockPulse();
  digitalWrite(SIpin, LOW);

  // Next, read all 256 pixels in parallell. Store the result in the array. Each clock pulse 
  // causes a new pixel to expose its value on the two outputs:
  for(int i=0; i < 256; i++)
  {
      delayMicroseconds(20);// <-- We add a delay to stabilize the AO output from the sensor
      S1Data[i] = analogRead(S1APin);
      S2Data[i] = analogRead(S2APin);
      S3Data[i] = analogRead(S3APin);
      S4Data[i] = analogRead(S4APin);
      S5Data[i] = analogRead(S5APin);
      S6Data[i] = analogRead(S6APin);
      S7Data[i] = analogRead(S7APin);
      S8Data[i] = analogRead(S8APin);
      S9Data[i] = analogRead(S9APin);
      S10Data[i] = analogRead(S10APin);
      S11Data[i] = analogRead(S11APin);
      S12Data[i] = analogRead(S12APin);
      
      ClockPulse(); 
  }

  // Next, stop the ongoing integration of light quanta from each photodiode by clocking in a
  // SI pulse:
  digitalWrite(SIpin, HIGH);
  ClockPulse(); 
  digitalWrite(SIpin, LOW);
  
  
  Serial.print("X:");

  for(int i = 0; i < 256; i++)
  {
//      Serial.print("a");
      Serial.print(S1Data[i]);
      Serial.print("|");
  }
//  lastVal = S1Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }


  
  for(int i = 0; i < 256; i++)
  {
//      Serial.print("b");
      Serial.print(S2Data[i]);
      Serial.print("|");
  }
//  lastVal = S2Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }



  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S3Data[i]);
      Serial.print("|");
  }
//  lastVal = S3Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }



  for(int i = 0; i < 256; i++)
  {
//      Serial.print("d");
      Serial.print(S4Data[i]);
      Serial.print("|");
  }
//  lastVal = S4Data[250];
//  for(int i = 0; i < paddingTwo; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }

  

  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S5Data[i]);
      Serial.print("|");
  }
//  lastVal = S5Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }
  


  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S6Data[i]);
      Serial.print("|");
  }
//  lastVal = S6Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }



  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S7Data[i]);
      Serial.print("|");
  }
//  lastVal = S7Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }

  

  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S8Data[i]);
      Serial.print("|");
  }
//  lastVal = S8Data[250];
//  for(int i = 0; i < paddingTwo; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }

  

  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S9Data[i]);
      Serial.print("|");
  }
//  lastVal = S9Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }

  

  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S10Data[i]);
      Serial.print("|");
  }
//  lastVal = S10Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }

  

  for(int i = 0; i < 256; i++)
  {
//      Serial.print("c");
      Serial.print(S11Data[i]);
      Serial.print("|");
  }
//  lastVal = S11Data[250];
//  for(int i = 0; i < paddingOne; i++)
//  {
////      Serial.print("a");
//      Serial.print(lastVal);
//      Serial.print("|");
//  }

//  for(int i = 0; i < 256; i++)
//  {
////      Serial.print("c");
//      Serial.print(S12Data[i]);
//      Serial.print("|");
//  }
  
  Serial.println();


  // Next, a new measuring cycle is starting once 18 clock pulses have passed. At  
  // that time, the photodiodes are once again active. We clock out the SI pulse through
  // the 256 bit register in order to be ready to halt the ongoing measurement at our will
  // (by clocking in a new SI pulse):
  for(int i = 0; i < 260; i++)
  {
      ClockPulse(); 
  }    

  // The integration time of the current program / measurement cycle is ~3ms. If a larger time
  // of integration is wanted, uncomment the next line:
  // delay(15);// <-- Add 15 ms integration 
}

// This function generates an outgoing clock pulse from the Arduino digital pin 'CLKpin'. This clock
// pulse is fed into pin 3 of the linear sensor:
void ClockPulse()
{
  delayMicroseconds(1);
  digitalWrite(CLKpin, HIGH);
  digitalWrite(CLKpin, LOW);
}


