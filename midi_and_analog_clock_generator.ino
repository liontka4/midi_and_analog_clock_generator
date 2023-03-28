//midi_and_analog_clock_generator by liontka4

int v;
int v2;
int count = 0;
float val = 61000;
void setup(){
  Serial.begin(31250); // MIDI start (I use ready MIDI-out module)
  pinMode(A0, INPUT); // Potentiometer for change tempo
  pinMode(9, OUTPUT); // Audio output (use a 1 kΩ resistor) 
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = val;
  TCCR1B |= (1 << CS10)|(1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();                        
}
ISR(TIMER1_OVF_vect){
TCNT1 = val;
if (count == 0){
      digitalWrite(9,HIGH);
      digitalWrite(9,LOW);}
  Serial.write(0xf8);
  Serial.write(0xfb);
  count = count + 1;
  if (count == 6){
      count = 0;}
}
void loop() {
  v = analogRead(A0);
  v2 = map(v, 0, 1023, 65527, 61000);
  val = float(v2); 
}
