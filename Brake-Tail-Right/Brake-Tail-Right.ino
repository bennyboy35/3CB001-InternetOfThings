void setup() {
  // put your setup code here, to run once:
const int VoltageTestPin = A0;
Serial.begin(9600);
}

void loop() {
   if(analogRead(A0)<= 10 && analogRead(A1) <= 10){
    Serial.println("Powered Down");
    Serial.write(6);
  }
  
  if(analogRead(A0)>= 50 && analogRead(A1) >= 500){
    Serial.println("Operational");
    Serial.write(3);
  }
  
  if(analogRead(A0)<= 50 && analogRead(A1) >= 500){
    Serial.println("Failed");
    Serial.write(2);
  }                   
}
