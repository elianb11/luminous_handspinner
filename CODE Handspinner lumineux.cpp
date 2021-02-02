#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
//define NeoPixel Pin and Number of LEDs
#define PIN 1
#define NUM_LEDS 8

//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_RGB + NEO_KHZ800);

int digitalPin = 3; // linear Hall magnetic sensor digital interface
int digitalVal; // digital readings
unsigned long OnTime;
unsigned long OffTime;
unsigned long timefinal;
unsigned long previousMillis;
unsigned long currentMillis;
int ledRay = 0.0625; // rayon du cercle formé par les LEDS en mètres
int ledWidth = 0.005; // largeur d'une led en mètres
int nbLedPerimeter = 2*PI*ledRay/ledWidth; // Calcul du nombre de LEDS que peut contenir le périmètre du hand-spinner
int delayTime; // en millisecondes
int charBreak; // en millisecondes

// codage des caractères à afficher dans des tableaux de 5 entiers pour un affichage des caractères sur 5 lignes verticales
// chaque entier va être décomposé en binaire et correspond à un allumage bien précis des 5 LEDS
int a[] = {1, 6, 26, 6, 1};
int b[] = {31, 21, 21, 10, 0};
int c2[] = {14, 17, 17, 10, 0};
int d[] = {31, 17, 17, 14, 0};
int e[] = {31, 21, 21, 17, 0};
int f[] = {31, 20, 20, 16, 0};
int g[] = {14, 17, 19, 10, 0};
int h[] = {31, 4, 4, 4, 31};
int i[] = {0, 17, 31, 17, 0};
int j[] = {0, 17, 30, 16, 0};
int k[] = {31, 4, 10, 17, 0};
int l[] = {31, 1, 1, 1, 0};
int m[] = {31, 12, 3, 12, 31};
int n[] = {31, 12, 3, 31, 0};
int o[] = {14, 17, 17, 14, 0};
int p[] = {31, 20, 20, 8, 0};
int q[] = {14, 17, 19, 14, 2};
int r[] = {31, 20, 22, 9, 0};
int s[] = {8, 21, 21, 2, 0};
int t[] = {16, 16, 31, 16, 16};
int u[] = {30, 1, 1, 30, 0};
int v[] = {24, 6, 1, 6, 24};
int w[] = {28, 3, 12, 3, 28};
int x[] = {17, 10, 4, 10, 17};
int y[] = {17, 10, 4, 8, 16};
int z[] = {19, 21, 21, 25, 0};

int eos[] = {0, 1, 0, 0, 0};
int excl[] = {0, 29, 0, 0, 0};
int ques[] = {8, 19, 20, 8, 0};

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  pinMode (digitalPin, INPUT);
  // start the strip and blank it out
  strip.begin(); 
}

void displayLine(int line) // fonction qui commande l'allumage d'une ligne de 5 leds par décomposition binaire d'un entier donné
{
  int myline;
  myline = line;
  if (myline>=16) {strip.setPixelColor(7, 255, 0, 0);strip.show(); myline-=16;} else {strip.setPixelColor(7, 0, 0, 0);strip.show();}
  if (myline>=8)  {strip.setPixelColor(6, 255, 0, 0);strip.show(); myline-=8;}  else {strip.setPixelColor(6, 0, 0, 0);strip.show();}
  if (myline>=4)  {strip.setPixelColor(5, 255, 0, 0);strip.show(); myline-=4;}  else {strip.setPixelColor(5, 0, 0, 0);strip.show();}
  if (myline>=2)  {strip.setPixelColor(4, 255, 0, 0);strip.show(); myline-=2;}  else {strip.setPixelColor(4, 0, 0, 0);strip.show();}
  if (myline>=1)  {strip.setPixelColor(3, 255, 0, 0);strip.show(); myline-=1;}  else {strip.setPixelColor(3, 0, 0, 0);strip.show();}
}

void displayChar(char c) // fonction qui permet d'afficher un caractère sur le hand-spinner par 5 appels de la fonction displayLine
{
  if (c == 'a'){for (int i = 0; i <5; i++){displayLine(a[i]);delay(delayTime);}displayLine(0);}
  if (c == 'b'){for (int i = 0; i <5; i++){displayLine(b[i]);delay(delayTime);}displayLine(0);}
  if (c == 'c2'){for (int i = 0; i <5; i++){displayLine(c2[i]);delay(delayTime);}displayLine(0);}
  if (c == 'd'){for (int i = 0; i <5; i++){displayLine(d[i]);delay(delayTime);}displayLine(0);}
  if (c == 'e'){for (int i = 0; i <5; i++){displayLine(e[i]);delay(delayTime);}displayLine(0);}
  if (c == 'f'){for (int i = 0; i <5; i++){displayLine(f[i]);delay(delayTime);}displayLine(0);}
  if (c == 'g'){for (int i = 0; i <5; i++){displayLine(g[i]);delay(delayTime);}displayLine(0);}
  if (c == 'h'){for (int i = 0; i <5; i++){displayLine(h[i]);delay(delayTime);}displayLine(0);}
  if (c == 'i'){for (int it = 0; it <5; it++){displayLine(i[it]);delay(delayTime);}displayLine(0);}
  if (c == 'j'){for (int i = 0; i <5; i++){displayLine(j[i]);delay(delayTime);}displayLine(0);}
  if (c == 'k'){for (int i = 0; i <5; i++){displayLine(k[i]);delay(delayTime);}displayLine(0);}
  if (c == 'l'){for (int i = 0; i <5; i++){displayLine(l[i]);delay(delayTime);}displayLine(0);}
  if (c == 'm'){for (int i = 0; i <5; i++){displayLine(m[i]);delay(delayTime);}displayLine(0);}
  if (c == 'n'){for (int i = 0; i <5; i++){displayLine(n[i]);delay(delayTime);}displayLine(0);}
  if (c == 'o'){for (int i = 0; i <5; i++){displayLine(o[i]);delay(delayTime);}displayLine(0);}
  if (c == 'p'){for (int i = 0; i <5; i++){displayLine(p[i]);delay(delayTime);}displayLine(0);}
  if (c == 'q'){for (int i = 0; i <5; i++){displayLine(q[i]);delay(delayTime);}displayLine(0);}
  if (c == 'r'){for (int i = 0; i <5; i++){displayLine(r[i]);delay(delayTime);}displayLine(0);}
  if (c == 's'){for (int i = 0; i <5; i++){displayLine(s[i]);delay(delayTime);}displayLine(0);}
  if (c == 't'){for (int i = 0; i <5; i++){displayLine(t[i]);delay(delayTime);}displayLine(0);}
  if (c == 'u'){for (int i = 0; i <5; i++){displayLine(u[i]);delay(delayTime);}displayLine(0);}
  if (c == 'v'){for (int i = 0; i <5; i++){displayLine(v[i]);delay(delayTime);}displayLine(0);}
  if (c == 'w'){for (int i = 0; i <5; i++){displayLine(w[i]);delay(delayTime);}displayLine(0);}
  if (c == 'x'){for (int i = 0; i <5; i++){displayLine(x[i]);delay(delayTime);}displayLine(0);}
  if (c == 'y'){for (int i = 0; i <5; i++){displayLine(y[i]);delay(delayTime);}displayLine(0);}
  if (c == 'z'){for (int i = 0; i <5; i++){displayLine(z[i]);delay(delayTime);}displayLine(0);}
  if (c == '!'){for (int i = 0; i <5; i++){displayLine(excl[i]);delay(delayTime);}displayLine(0);}
  if (c == '?'){for (int i = 0; i <5; i++){displayLine(ques[i]);delay(delayTime);}displayLine(0);}
  if (c == '.'){for (int i = 0; i <5; i++){displayLine(eos[i]);delay(delayTime);}displayLine(0);}
  delay(charBreak);
}

void displayString(char* s) // fonction qui permet d'appeler la fonction displayChar pour chaque caractère d'une chaine de caractères donnée
{
  for (int i = strlen(s); i>=0; i--)
  {
    displayChar(s[i]);
  }
}

void loop ()
{
  digitalVal = digitalRead(digitalPin) ; // Lecture de l'interface digitale du capteur à effet Hall
    
  previousMillis = millis();
  while(digitalVal == 1) // Quand l'aimant est détecté par le capteur
  {
    digitalVal = digitalRead(digitalPin) ;
  }
  currentMillis=millis();
  OnTime=currentMillis-previousMillis; // Calcul de la durée où le capteur a détecté l'aimant
    
  previousMillis=millis();
  while(digitalVal == 0) // Quand l'aimant n'est pas détecté par le capteur
  {
    digitalVal = digitalRead(digitalPin) ;
  }
  currentMillis=millis();
  OffTime=currentMillis-previousMillis; // Calcul de la durée où le capteur n'a pas détecté l'aimant
    
  timefinal = (OffTime + OnTime); // Calcul de la durée nécessaire au hand-spinner pour réaliser un tour
    
  if(timefinal>30 && timefinal<1000) // Permet d'éviter les mauvaises valeurs lors de l'acquisition de la durée
  {
    delayTime=timefinal/(nbLedPerimeter*1.5); // Calcul du délai entre l'affichage de deux lignes de LEDS verticales pour un affichage lisible
    charBreak=2*delayTime; // Calcul du délai entre l'affichage de deux caractères (pour ne pas que les caractères soient collés)
      
    displayString("ifd!"); // Appel de la fonction permettant l'affichage du mot voulu
  }
}
