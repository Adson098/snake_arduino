// dir- direction, 1-up,2-down,3-left,4-right;
//Autor: Adrian Śmierciak

// co każd aaklate po kolieji zminiema kierunke każdego chain przeykład 11111111 11111110 11111100 11111000 11110000
//snake[i-1].x = snake[i].x
//snake[i-1].y = snake[i].y
#include <Adafruit_NeoPixel.h>
#include <Keypad.h>
#define PIN        3 
#define NUMPIXELS 64 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const byte ROWS = 2; 
const byte COLS = 3; 
unsigned long nowtime = 0;
unsigned long gametime = 0;
bool isgameover = false;
char keys[ROWS][COLS] = {
  {'l','p','d'},
  {'s','i','u'},
};
byte rowPins[ROWS] = {5,7}; 
byte colPins[COLS] = {10, 11, 12};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int cols = 4;
int rows = 4;
int sdir = 1;
int shead[2] = {4,4};
int len = 0;
int led = 64;
int gamedelay = 500;
char key ;
int l[8][8] ={
           {0,1,2,3,4,5,6,7},
           {15,14,13,12,11,10,9,8},
           {16,17,18,19,20,21,22,23},
           {31,30,29,28,27,26,25,24},
           {32,33,34,35,36,37,38,39},
           {47,46,45,44,43,42,41,40},
           {48,49,50,51,52,53,54,55},
           {63,62,61,60,59,58,57,56}
           };
int k[8][8] ={
           {0,1,2,3,4,5,6,7},
           {15,14,13,12,11,10,9,8},
           {16,17,18,19,20,21,22,23},
           {31,30,29,28,27,26,25,24},
           {32,33,34,35,36,37,38,39},
           {47,46,45,44,43,42,41,40},
           {48,49,50,51,52,53,54,55},
           {63,62,61,60,59,58,57,56}
           };

struct Chain{
  bool visible = false;
  bool frozen = false;
  int x,y,dir;
};

struct Food{
  int x,y;
};

struct Point{
  int x,y;
};
Chain snake[64];
Food food[1]; 
Point point;
  
void setup() {
  pixels.begin(); 
  Serial.begin(9600);
  snake[0].x = 4;
  snake[0].y = 4;
  snake[0].visible = true;
  food[0].x = random(1,7);
  food[0].y = random(1,7);

  
}
void(* resetFunc) (void) = 0; 
void render(){
    for(int i = 0 ;i<=len + 1;i++){
      if(snake[i].visible == true){
      pixels.setPixelColor(l[snake[i].x][snake[i].y], pixels.Color(0,0, 150));
       pixels.setPixelColor(k[food[0].x][food[0].y], pixels.Color(0, 150, 0)); 
      }}}
//void welcome(){
//  for(int i = 0; i<=led;i++){
///    pixels.setPixelColor(i, pixels.Color(random(0,150),random(0,150), random(0,150)));
 //   delay(50);
 //   }
//  }
      
void gameover(){
  for(int a = 0; a<=3;a++){
      pixels.setPixelColor(l[snake[0].x][snake[0].y], pixels.Color(150,0, 0)); 
      pixels.show();
      delay(250);
      pixels.setPixelColor(l[snake[0].x][snake[0].y], pixels.Color(0,0, 150)); 
      pixels.show();

      delay(250);
  }
 delay(500);
 len = 0;
 resetFunc(); 

 Serial.println("reset");
}

void loop() {
  nowtime = millis();
  key = keypad.getKey();
  if(key == 'u' && snake[0].dir !=2){
    snake[0].dir = 1; 
    }
  else if(key == 'd' && snake[0].dir !=1){
    snake[0].dir = 2; 
    }
  else if(key == 'p' && snake[0].dir !=4){
    snake[0].dir = 3; 
    }
  else if(key == 'l' && snake[0].dir !=3){
    snake[0].dir = 4; 
    }
    
   if(nowtime-gametime >= gamedelay && isgameover == false){
  gametime = nowtime;
  
  for(int q = len;q>=1;q--){
    if(snake[1].frozen != true ){
    snake[q].x = snake[q-1].x;
    snake[q].y = snake[q-1].y;
    }
    
  }
   switch(snake[0].dir){
    case 1:
    snake[0].x ++;
      break;
    case 2:
    snake[0].x --;
      break;
    case 3:
    snake[0].y ++;
      break;
    case 4:
    snake[0].y --;
      break;
   }
    for(int i = 1; i<=len + 1;i++){
    snake[i].frozen = false;
   }
    
    if(snake[0].x == food[0].x && snake[0].y == food[0].y){
    len ++;
    food[0].x={random(1,6)};
    food[0].y={random(1,6)};
    snake[len].x = snake[len-1].x;
    snake[len].y = snake[len-1].y;
    snake[len].visible = true;
    snake[len].frozen = true;
    Serial.println(len);
    
    }
    if(len>=4){
    for(int i = 1; i<=len; i++){
    if(snake[0].x==snake[i].x && snake[0].y ==snake[i].y){
      isgameover=true;
      gameover();
      Serial.println("ugryzienie");
      } 
    }
    }
    
    pixels.clear();
    render();
        if(snake[0].x <= 0 || snake[0].x >= 7 || snake[0].y <= 0 || snake[0].y >= 7){
    isgameover=true;
    snake[len].visible = false;
    Serial.println(isgameover);
    gameover();
    }
    pixels.show();
    }

 } 
  
