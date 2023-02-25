#include <U8glib.h>
#include <SpeedData.h>

#define Uno   //Descomente essa linha caso utilizar um Arduino UNO
//#define Mega  //Descomente essa linha caso utilizar um Arduino Mega

#ifdef Uno
#include "SoftwareSerial.h"
SoftwareSerial mySerial(2, 3); // RX, TX
#endif

#ifdef Mega
SpeedData SData(&Serial1);    // Serail 1 Mega
#endif

#ifdef Uno
SpeedData SData(&mySerial);   // SoftwareSerial Uno
#endif
 
char pino_temp = 0;// Pino para a leitura dos valores da tensão Vx  \\ Pode ser suprimida essa linha sem problemas

char pino_comb = 1; //Pino para a leitura dos valores da tensão Vx  \\ Pode ser suprimida essa linha sem problemas

char tempChar[3] = {0}; //variavel para armazenar a temperatura em char padrao valor ambiente

char combChar[3] = {0}; //variavel para armazenar combustivel em char

char RPMChar[3] = {0}; //variavel para armazenar RPM em char

char AFRChar[3] = {0}; //variavel para armazenar RPM em char

char BATChar[3] = {0}; //variavel para armazenar RPM em char

char TempAguaChar[3] = {0}; //variavel para armazenar RPM em char

char TPSChar[3] = {0}; //variavel para armazenar TPS em char

char MAPChar[3] = {0}; //variavel para armazenar MAP em char

int molduraInt = 0; //variavel para armazenar int da moldura

int tempoDelay = 1000; // ms segundo

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

void moldura() 
{
  //Comandos graficos para o display devem ser colocados aqui
  //Texto superior informando os graficos
  u8g.setFont(u8g_font_8x13B);
  //texto da temperatura
  u8g.drawStr( 20, 15, "Temp");
  //texto do combustuvel
  //u8g.drawStr( 75, 15, "Comb");
   //desenha linha do meio para dividir 
  u8g.drawVLine(64,0, 64);
 
}

//funço de leitura de resistencia
int resistencia(int pino_leitura){ 
  int leitura, R, resultado;
  float Vx, calculo;   
  leitura = analogRead(pino_leitura);                    // Variavel leitura recebe o valor lido pela porta serial A0
  Vx = (5.0*leitura)/1023.0;                             // Os valores mapeados pela entrada analogica estabelecem a seguinte relacao (regra de tres simples):
  R = 1000; // resistencia de base de calculo
  calculo = ((5*R)/Vx) - R;// Calculo do resultado utilizando a formula (3)
  resultado = (int) calculo;
  return resultado; 
}

//funçoes de leyaut
void temp() 
{
  int x = resistencia(0);
  //Serial.println(x);
  itoa(x,tempChar, 10); //converte inteiro para char 
  //inicio medidor temperatura
  //bolinha do grau
  u8g.drawCircle(50,42,2);
  // C de graus
  u8g.drawStr( 54, 57, "C");
  //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B);
  //x=70;//parametro para teste no visor
  if(x <= 70){
   // 108 graus 
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,8, 15,64 );
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "108");
  }
  else if(x >= 71 && x <= 72){
    // 105 graus
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,14, 15,64 );
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "105");
  }
  else if(x >= 73 && x <= 81){
    // 100 graus
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,20, 15,64 );
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "100");
  }
  else if(x >= 82 && x <= 111){
    // 90 graus
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,30, 15,64 );
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "90");
  }
  else if(x >= 112 && x <= 127){
    // 80 graus
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,40, 15,64 );
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "80");
  }
  else if(x >= 128 && x <= 200){
    // 70 graus
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,50, 15,64 );
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "70");
  }
  else if(x >= 201 && x <= 300){
    // 40 graus
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,60, 15,64 );
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "40");
  }
  else{
    //frio
  u8g.drawRFrame(0,0, 15,64, 10);
  u8g.drawBox(0,64, 15,64 );
  u8g.drawStr( 20, 57, "<");
  //texto informando a temperatura
  u8g.drawStr( 30, 57, "30");
  }
}
void comb() 
{
  int x = resistencia(1);
  int vazio = 43;
  int pixel = 4;
  int qtLitros = 0;
    /*
  calculo para formatar combustivel segue os seguintes passos
 pega o valor total da resistencia do medidor em ohms exemplo
se o medidor cheio marta 283 ohms e vazio 40 ohms pega o valor de cheio 
diminui o valor do vazio depois pega o total restante divide pelo
tamanho vertical da tela em pixel, com este resultado teremos 
o valor de cada pixo ai  so dividir o resultado da verificaço pelo valor anterir obtido 
exemplo
283 - 40 = 240
243 / 64 = 3,7
pega resultado divide pelo valor aferido menos o valor minimo 
(160 - 40) / 3,7 = 
  */
  x = (x - vazio) / pixel;
  //Serial.println("Combustivel:");
  //Serial.println(x);
  
  itoa(x,combChar, 10); //converte para inteiro para char
  //Rotulo
  u8g.drawStr( 75, 15, "Comb");
  //Desenho nivel combustivel 
  //desenha a linha do retangulo x, y, hidth, hidth, raio
  u8g.drawRFrame(116, 0, 12,64 , 0);
  //desenha o preenchimento do medidor
  u8g.drawBox(117, x, 10,64);
  //fim do desenho de combustivel
  //calculo marcador em litros na tela
   qtLitros = x /4;
  
  
  
 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //linha superior informando o combustivel
  u8g.drawStr( 70, 40, combChar);
  
}

void MolduraInt(char titulo[50], int x ) 
{
  char molduraChar[30] = {0}; //variavel para armazenar char da moldura
  itoa(x,molduraChar, 10); //converte inteiro para char
 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 75, 15, titulo);
  //Dados
  u8g.drawStr( 70, 40, molduraChar);  
}

void MolduraBoasVindas() 
{
 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 0, 15, "Ola Davi e Arthur");
  u8g.drawStr( 0, 40, "Papai ama voces");  
}

void MolduraRPM(int intRPM) 
{
  itoa(intRPM,RPMChar, 10); //converte para inteiro para char
 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 75, 15, "RPM");
  //Dados
  u8g.drawStr( 70, 40, RPMChar);  
}

void MolduraAFR(float intAFR) 
{

  itoa(intAFR,AFRChar, 10); //converte para inteiro para char

 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 75, 15, "AFR");
  //Dados
  u8g.drawStr( 70, 40, AFRChar);
  
}


void MolduraBateria(float intBAT) 
{

  itoa(intBAT,BATChar, 10); //converte para inteiro para char

 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 75, 15, "Bat.");
  //Dados
  u8g.drawStr( 70, 40, BATChar);
  
}


void MolduraTPS(float intTPS) 
{

  itoa(intTPS,TPSChar, 10); //converte para inteiro para char

 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 75, 15, "TPS");
  //Dados
  u8g.drawStr( 70, 40, TPSChar);
  
}


void MolduraMAP(float intMAP) 
{

  itoa(intMAP,MAPChar, 10); //converte para inteiro para char

 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 75, 15, "MAP");
  //Dados
  u8g.drawStr( 70, 40, MAPChar);
  
}


void MolduraTempAgua(int intTempAgua) 
{

  itoa(intTempAgua,TempAguaChar, 10); //converte para inteiro para char

 //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B); 
  //Rotulo
  u8g.drawStr( 75, 15, "Temp.");
  //Dados
  u8g.drawStr( 70, 40, TempAguaChar);
  
}

void setup() 
{
  #ifdef Uno
  mySerial.begin(115200); //Serial dedicada ao acesso Can do Speeduino via Serial3
  Serial.begin(115200); 
  #endif

  #ifdef Mega
  Serial.begin(115200); 
  Serial1.begin(115200);  //Deletar essa linha caso esteja usando um ARDUINO UNO ou similar
  #endif

  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  pinMode(pino_temp, INPUT); // Configuraçao do pino de leitura como entrada de dados \\ também pode ser suprimida essa linha
  pinMode(pino_comb, INPUT); // Configuraçao do pino de leitura como entrada de dados \\ também pode ser suprimida essa linha

}
 
void loop() 
{
 
int RPM = SData.getRPM(500);
float AFR = SData.getActualAFR(100);
float BATERIA = SData.getBattVoltage(200);
int TEMP_AGUA = SData.getWaterTemp(100);
int TPS = SData.getTPS(100);
int MAP = SData.getMAP(100);

  Serial.println(RPM);
  Serial.println(AFR);
  Serial.println(BATERIA);
  Serial.println(TEMP_AGUA);
  Serial.println(TPS);
  Serial.println(MAP);
  
    u8g.firstPage();  
  do
  {
    MolduraBoasVindas();
    //moldura();
    //temp();
    //comb();    
  } while( u8g.nextPage() );

delay(3000);

  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    comb();    
  } while( u8g.nextPage() );

delay(tempoDelay);

  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    //comb();
    MolduraRPM(RPM);
  } while( u8g.nextPage() );
   
  delay(tempoDelay);

  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    //comb();
    MolduraAFR(AFR);
  } while( u8g.nextPage() );
   
  delay(tempoDelay);

  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    //comb();
    MolduraBateria(BATERIA);
  } while( u8g.nextPage() );
   
delay(tempoDelay);

  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    //comb();
    MolduraTempAgua(TEMP_AGUA);
  } while( u8g.nextPage() );

delay(tempoDelay);

  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    //comb();
    MolduraTPS(TPS);
  } while( u8g.nextPage() );
delay(tempoDelay);


  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    //comb();
    MolduraMAP(MAP);
  } while( u8g.nextPage() );
delay(tempoDelay);


  u8g.firstPage();  
  do
  {
    moldura();
    temp();
    //comb();
    MolduraInt("teste2", MAP);
  } while( u8g.nextPage() );
delay(tempoDelay);



}
