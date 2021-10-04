#define LEDVERDE 2
#define LEDAMARELO 3
#define TRIGGER 5
#define eco 6
#define BUZZER 9
const float som = 34300.0; 
const float porta1 = 30.0;
const float porta2 = 20.0;
const float porta3 = 10.0;
#include <Servo.h>

int pos = 0;

Servo servo_9;
 
void setup() {
  
  servo_9.attach(9);
  Serial.begin(9600);

 
  
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARELO, OUTPUT);
  
  pinMode(eco, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  
  apagarLEDs();

}
void loop() {

   
  for (pos = 0; pos <= 180; pos += 1) {
     
    servo_9.write(pos);
   
    delay(15); 
  }
  for (pos = 180; pos >= 0; pos -= 1) {
   
    servo_9.write(pos);
     
    delay(15);
  }
   
  
  iniciarTrigger();
  
		
  
  float distancia = calcularDistancia();

   apagarLEDs();
 

  if (distancia < porta1) 
 
  {
    
    alertas(distancia);
  }
}

void apagarLEDs()


{
  
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARELO, LOW);
  
}
void alertas(float distancia)

{
  if (distancia < porta1 && distancia >= porta2)
  {
   
    digitalWrite(LEDVERDE, HIGH);
    tone(BUZZER, 2000, 200);
  }
  else if (distancia < porta2 && distancia > porta3)
  {
    
    digitalWrite(LEDAMARELO, HIGH);
    tone(BUZZER, 2500, 200);
  }
  
  
}

float calcularDistancia()

{
 
  unsigned long tempo = pulseIn(eco, HIGH);

 
  float distancia = tempo * 0.000001 * som / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);

  return distancia;
}
void iniciarTrigger()
{
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  
  digitalWrite(TRIGGER, LOW);
}
