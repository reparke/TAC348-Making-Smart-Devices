 void setup()
 {
   pinMode(D2, OUTPUT);
   pinMode(D3, OUTPUT);
 }

 void loop() {
  //  digitalWrite(D2, HIGH);
   analogWrite(D2, 255);
   analogWrite(D3, 0);
 }