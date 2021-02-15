#include <IRremote.h>

const int RECV_PIN = 2;
const int led = 13;
unsigned int power = 255;
int estadoConfiguracion = 0;
int estadoFoco = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
 // irrecv.blink13(true);
}

void loop() {
 // Serial.println(irrecv.decode(&results));
  
  if (irrecv.decode(&results)) {
    unsigned int value = results.value;
    
    if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    Serial.println(value);
   
    if(value == power && estadoFoco == 0){  // enciende el led si se preciona el boton de power y el estado esta en 0 
      Serial.print("ON ");
     digitalWrite(led, HIGH);
      estadoFoco = 1; // se indica el estado del foco esta encendido
    }else if(value == power && estadoFoco == 1 ){ // apaga el led si se preciona el boton de power y el estado esta en 1 
      Serial.print("OFF ");
      digitalWrite(led, LOW); 
      estadoFoco = 0;     //se indica el estado del foco esta apagado
    }
    if(estadoConfiguracion == 1){ // va a entrar a esta condicion solo cuando se precione el boton que iniciara la configuracion
      power = results.value;    // leera nuevo valor y este sera el nuevo boton de encendido y apagado
      estadoConfiguracion = 0;    // vuelve el estado a 0 para que no entre a esta condicion
      Serial.println("configurando");
    } 
    
    if(value == 12495){       // aqui va el boton que sera el que inicie la configuracion del boton a elegir de encendido y apagado
      estadoConfiguracion = 1; 
      Serial.print("estado");
    }
    
    
    irrecv.resume(); // Receive the next value
    
    
  
  }
  
}
