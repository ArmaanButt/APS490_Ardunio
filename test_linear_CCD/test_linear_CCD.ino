//----------------------------------------------------------
//based on code from http://playground.arduino.cc/Main/TSL1402R

//Known Issues:
//modified to read data serially as opposed to parallel
//Cannot scope clk, causes failure in analog output. Output fine without scope probe

//Usage:
//Connect pins as described below. Note the variable assignment value is the pin on the Arduino, the comment next to the variable has the appropriate pin on the sensor
//Ensure the VDD and GND pins are connected to the Arduino at the 5V and GND pins respectively


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


void setup() 
{
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

  Serial.begin(115200);
}

void loop() 
{  

          
      
      //arrays where the readout of the photodiodes is stored, as 16-bit integers
      int S1Data[256];
      int S2Data[256];
      int S3Data[256];
      int S4Data[256]; 
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
          ClockPulse(); 
      }

      // Next, stop the ongoing integration of light quanta from each photodiode by clocking in a
      // SI pulse:
      digitalWrite(SIpin, HIGH);
      ClockPulse(); 
      digitalWrite(SIpin, LOW);
      delay(1000);
      // Next, send the measurement stored in the array to host computer using serial (rs-232).
      // communication. This takes ~80 ms during whick time no clock pulses reaches the sensor. 
      // No integration is taking place during this time from the photodiodes as the integration 
      // begins first after the 18th clock pulse after a SI pulse is inserted:

      Serial.print("S1:");
      for(int i = 0; i < 256; i++)
      {
          Serial.print(S1Data[i]); Serial.print("|");
      }
      Serial.print(";");
      Serial.print("S2:");
      for(int i = 0; i < 256; i++)
      {
          Serial.print(S2Data[i]); Serial.print("|");
      }
      Serial.print(";");
            Serial.print("S3:");
      for(int i = 0; i < 256; i++)
      {
          Serial.print(S3Data[i]); Serial.print("|");
      }
      Serial.print(";");
            Serial.print("S4:");
      for(int i = 0; i < 256; i++)
      {
          Serial.print(S4Data[i]); Serial.print("|");
      }
      Serial.print(";");
      
      
      
      
      Serial.println(""); // <-- Send a linebreak to indicate the measurement is transmitted.

      // Next, a new measuring cycle is starting once 18 clock pulses have passed. At  
      // that time, the photodiodes are once again active. We clock out the SI pulse through
      // the 256 bit register in order to be ready to halt the ongoing measurement at our will
      // (by clocking in a new SI pulse):
      for(int i = 0; i < 260; i++)
      {
//          if(i==18)
//          {
//              // Now the photodiodes goes active..
//              // An external trigger can be placed here
//          }
          ClockPulse(); 
      }    

      // The integration time of the current program / measurement cycle is ~3ms. If a larger time
      // of integration is wanted, uncomment the next line:
      // delay(15);// <-- Add 15 ms integration time
}

// This function generates an outgoing clock pulse from the Arduino digital pin 'CLKpin'. This clock
// pulse is fed into pin 3 of the linear sensor:
void ClockPulse()
{
  delayMicroseconds(1);
  digitalWrite(CLKpin, HIGH);
  digitalWrite(CLKpin, LOW);
}

