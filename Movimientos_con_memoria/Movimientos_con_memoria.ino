//Definimos las entradas
const int Doblar = A0; 
const int Desdoblar = A1; 
const int Subir = A2; 
const int Bajar = A3; 
const int Memo1 = A4; 
const int Memo2 = A5; 
const int Memo3 = 12; 
//Definimos las salidas
const int Relay_Doblar = 2; 
const int Relay_Desdoblar = 3; 
const int Relay_Subir = 4; 
const int Relay_Bajar = 5; 
//--------------------------------------------
boolean bit0,bit1,bit2,bit3,bit4,bit5,bit6;
int dato=0;
long posicionInclinacion=0;
long posicionElevacion=0;
long tiempoPulsadorMemoria1=0;
long tiempoPulsadorMemoria2=0;
long tiempoPulsadorMemoria3=0;
long memoria1[2];
long memoria2[2];
long memoria3[2];
//----- Fin de declaración de Variables ------

void setup() {
  Serial.begin(9600);
  //Seteamos los Pines como entrada
  pinMode(Doblar,INPUT); 
  pinMode(Desdoblar,INPUT);  
  pinMode(Subir,INPUT);  
  pinMode(Bajar,INPUT);  
  pinMode(Memo1,INPUT);  
  pinMode(Memo2,INPUT); 
  pinMode(Memo3,INPUT);  
  //Seteamos los pines como salida
  pinMode(Relay_Doblar,OUTPUT);  
  pinMode(Relay_Desdoblar,OUTPUT);  
  pinMode(Relay_Subir,OUTPUT);  
  pinMode(Relay_Bajar,OUTPUT); 
  //Ponemos en alto las salida digitas ya que los relays se activan en bajo
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
}

void loop() {

  bit0 = digitalRead(Doblar); 
  bit1 = digitalRead(Desdoblar);
  bit2 = digitalRead(Subir);
  bit3 = digitalRead(Bajar);
  bit4 = digitalRead(Memo1);
  bit5 = digitalRead(Memo2);
  bit6 = digitalRead(Memo3);
  
  dato = (int)bit0 + (int)bit1*2 + (int)bit2*4 + (int)bit3*8 + (int)bit4*16 + (int)bit5*32 + (int)bit6*64;
  
  switch(dato){
    case 1:  
      digitalWrite(Relay_Doblar,LOW);
      posicionInclinacion+=1;
      delay(50);      
    break;
    case 2:
      digitalWrite(Relay_Desdoblar,LOW);
      posicionInclinacion-=1;
      delay(50); 
    break;
    case 4:
      digitalWrite(Relay_Subir,LOW);
      posicionElevacion+=1;
      delay(50); 
    break;
    case 8:
      digitalWrite(Relay_Bajar,LOW);
      posicionElevacion-=1;
      delay(50); 
    break;
    case 16:
      tiempoPulsadorMemoria1+=1;
      delay(50); 
    break;
    case 32:
      tiempoPulsadorMemoria2+=1;
      delay(50); 
    break;
    case 64:
      tiempoPulsadorMemoria3+=1;
      delay(50); 
    break;
    default:
      apagarRelays(); 
  }
}

void apagarRelays(){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  //--- Evaluamos el tiempo que se ha mantenido pulsado el boton de memoria 1 ---
  if(tiempoPulsadorMemoria1 >0 &&  tiempoPulsadorMemoria1 < 80){
      //posicionar cama según memoria1
      posicionarSegunMemoria1();
  }else{
    if (tiempoPulsadorMemoria1 >= 80){
      //guardo en memoria1 posicionInclinacion y posicionElevacion 
      memoria1[0]=posicionInclinacion;
      memoria1[1]=posicionElevacion;
    }
  }
  //--- Evaluamos el tiempo que se ha mantenido pulsado el boton de memoria 2 ---
  if(tiempoPulsadorMemoria2 >0 &&  tiempoPulsadorMemoria2 < 80){
      //posicionar cama según memoria2
      posicionarSegunMemoria2();
  }else{
    if (tiempoPulsadorMemoria2 >= 80){
      //guardo en memoria1 posicionInclinacion y posicionElevacion 
      memoria2[0]=posicionInclinacion;
      memoria2[1]=posicionElevacion;
    }
  }
  //--- Evaluamos el tiempo que se ha mantenido pulsado el boton de memoria 3 ---
  if(tiempoPulsadorMemoria3 >0 &&  tiempoPulsadorMemoria3 < 80){
      //posicionar cama según memoria3
      posicionarSegunMemoria3();
  }else{
    if (tiempoPulsadorMemoria3 >= 80){
      //guardo en memoria1 posicionInclinacion y posicionElevacion 
      memoria3[0]=posicionInclinacion;
      memoria3[1]=posicionElevacion;
    }
  }
  
  tiempoPulsadorMemoria1=0;
  tiempoPulsadorMemoria2=0;
  tiempoPulsadorMemoria3=0; 
}

void posicionarSegunMemoria1(){
  long e;  // error
  long tiempo;
  //posicionamos la inclinación
  e = memoria1[0] - posicionInclinacion;
  if (e > 0){
    digitalWrite(Relay_Doblar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Doblar,HIGH);
    posicionInclinacion = memoria1[0];
  }else{
    digitalWrite(Relay_Desdoblar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Desdoblar,HIGH);
    posicionInclinacion = memoria1[0];
  }
  //posicionamos la elevación
  e = memoria1[1] - posicionElevacion;
  if (e > 0){
    digitalWrite(Relay_Subir,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Subir,HIGH);
    posicionElevacion = memoria1[1];
  }else{
    digitalWrite(Relay_Bajar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Bajar,HIGH);
    posicionElevacion = memoria1[1];
  }
}

void posicionarSegunMemoria2(){
  long e;  // error
  long tiempo;
  //posicionamos la inclinación
  e = memoria2[0] - posicionInclinacion;
  if (e > 0){
    digitalWrite(Relay_Doblar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Doblar,HIGH);
    posicionInclinacion = memoria2[0];
  }else{
    digitalWrite(Relay_Desdoblar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Desdoblar,HIGH);
    posicionInclinacion = memoria2[0];
  }
  //posicionamos la elevación
  e = memoria2[1] - posicionElevacion;
  if (e > 0){
    digitalWrite(Relay_Subir,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Subir,HIGH);
    posicionElevacion = memoria2[1];
  }else{
    digitalWrite(Relay_Bajar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Bajar,HIGH);
    posicionElevacion = memoria2[1];
  }  
}


void posicionarSegunMemoria3(){
  long e;  // error
  long tiempo;
  //posicionamos la inclinación
  e = memoria3[0] - posicionInclinacion;
  if (e > 0){
    digitalWrite(Relay_Doblar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Doblar,HIGH);
    posicionInclinacion = memoria3[0];
  }else{
    digitalWrite(Relay_Desdoblar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Desdoblar,HIGH);
    posicionInclinacion = memoria3[0];
  }
  //posicionamos la elevación
  e = memoria3[1] - posicionElevacion;
  if (e > 0){
    digitalWrite(Relay_Subir,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Subir,HIGH);
    posicionElevacion = memoria3[1];
  }else{
    digitalWrite(Relay_Bajar,LOW);
    tiempo = abs(e*50);
    delay(tiempo);
    digitalWrite(Relay_Bajar,HIGH);
    posicionElevacion = memoria3[1];
  }
} 


