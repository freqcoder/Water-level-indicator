const int total_height = 12; 
const int hold_height = 9;

char cntry_code[] = "+91"; 
char ph[] = "8867282559"; 

const int trigger = 2;
const int echo = 3;
int var_1 = 0;
char input_string[15];

long Time;
int distanceCM;
int resultCM;
int tnk_lvl = 0;
int sensr_to_wtr = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  sensr_to_wtr = total_height - hold_height;

  delay(20000);
  delay(20000);
  delay(20000);
  
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("System is ready to go");
  delay(100);
  Serial.println((char)26);
}


void loop()
  {measure();
  if (tnk_lvl >= 90)
  {  Serial.print("AT+CMGS=");
     Serial.print("\"");
     Serial.print(cntry_code);
     Serial.print(ph);
     Serial.println("\"");
     delay(10000);
     Serial.print("Tank has reached 90% kindly switch off");
     
     Serial.println(" before it reaches 100%");
     delay(10000);
     Serial.println((char)26);
  }
     
}

void measure()
{
  delay(100);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  Time = pulseIn(echo, HIGH);
  distanceCM = Time * 0.034;
  resultCM = distanceCM / 2;
  
  tnk_lvl = map(resultCM, sensr_to_wtr, total_height, 100, 0);
  if (tnk_lvl > 100) tnk_lvl = 100;
  if (tnk_lvl < 0) tnk_lvl = 0;
  

}
