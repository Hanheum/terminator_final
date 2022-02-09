#include <Servo.h>
Servo servo[12];
//int deg[12] = {48, 42, 60, 120, 55, 57, 57, 82, 148, 80, 45, 57};
//int deg[12] = {50, 57, 60, 100, 55, 55, 58, 61, 148, 95, 45, 57};
int deg[12] = {50, 50, 100, 90, 55, 57, 57, 83, 178, 110, 45, 57};
int dir[12] = {1, 1, 1, 1, 1, 1, 1, -1, -1, -1, 1, 1};
float newdeg[12];
float gap[12];
float halfnewdeg[12];

const int toplength = 11;
const int legtoplength = 4;
const int doublemotor = 3;
const float upperleg = 8.5;
const float lowerleg = 8;
const int doublefoot = 6;

void setup() {
  servo[0].attach(2);
  servo[1].attach(3);
  servo[2].attach(4);
  servo[3].attach(5);
  servo[4].attach(6);
  servo[5].attach(7);
  servo[6].attach(8);
  servo[7].attach(9);
  servo[8].attach(10);
  servo[9].attach(11);
  servo[10].attach(12);
  servo[11].attach(13);
  Serial.begin(9600);
}
void delaymaker(int a, int i, int b) {
  float thedelay = 25 * (cos((radians(360) / a) * i) + 1) + b;
  delay(thedelay);
  //Serial.println(thedelay);
}

void motormove(int a, float b) {
  servo[a].write(newdeg[a] + dir[a]*b);
  halfnewdeg[a] = newdeg[a]+dir[a]*b;
}
void degremem() {
  for(int i=0; i<12; i++){
    newdeg[i] = halfnewdeg[i];
  }
}
void Still(){
  for(int i=0; i<12; i++){
    servo[i].write(deg[i]);
    newdeg[i] = deg[i];
    delay(5);
  }
}
void gapdet(int a){
  gap[a] = deg[a]-newdeg[a];
}
void leg(int a, int b, int c, int d){
  float func1[5] = {180, 115, 115, 115, 130};
  float func2[5] = {83, 33, 33, 33, 105};
  float func3[5] = {150, 140, 120, 100, 75};
  motormove(a, func1[d]-func1[0]);
  motormove(b, func2[d]-func2[0]);
  motormove(c, -func3[d]+func3[0]);
  delay(30);
}
void leg2(int a, int b, int c, int d){
  int base1 = 170;
  int base2 = 63;
  int base3 = 150;
  newdeg[a] = deg[a];
  newdeg[b] = deg[b];
  newdeg[c] = deg[c];
  float func1[6] = {220, 165, 155, 115, 115, 130};
  float func2[6] = {88, 33, 33, 33, 33, 105};
  float func3[6] = {165, 165, 140, 120, 100, 75};
  motormove(a, func1[d]-base1);
  motormove(b, func2[d]-base2);
  motormove(c, -func3[d]+base3);
  delay(80);
}
void leg3(int a, int b, int c, int d){
  int base1 = 170;
  int base2 = 63;
  int base3 = 150;
  newdeg[a] = deg[a];
  newdeg[b] = deg[b];
  newdeg[c] = deg[c];
  float func1[6] = {220, 165, 155, 115, 115, 130};
  float func2[6] = {88, 33, 33, 33, 33, 105};
  float func3[6] = {165, 165, 140, 120, 100, 75};
  motormove(a, func1[d]-base1);
  motormove(b, func2[d]-base2);
  motormove(c, -func3[d]+base3);
  delay(50);
}
void forward1(){
  for(int i=0; i<6; i++){
    motormove(0, i);
    motormove(4, i);
    motormove(6, i);
    motormove(7, i);
    delaymaker(5, i, 20);
  }
  degremem();
  for(int i=0; i<16; i++){
    motormove(6, i);
    motormove(1, i*10/15);
    motormove(2, i*10/15);
    delaymaker(15, i, 20);
  }
  degremem();
  /*for(int i=0; i<11; i++){
    motormove(1, -i);
    motormove(2, -i);
    delaymaker(11, i, 5);
  }
  degremem();
  */
  for(int i=0; i<5; i++){
    leg(1, 2, 3, i);
  }
  
  degremem();
  
  gapdet(3);
  gapdet(2);
  gapdet(1);
  for(int i=0; i<16; i++){
    motormove(3, i*gap[3]/15);
    motormove(2, i*gap[2]/15);
    motormove(1, i*gap[1]/15);
    motormove(9, -i*43/15);
    motormove(8, i*20/15);
    motormove(7, i*52/15);
    motormove(0, -i*10/15);
    motormove(4, -i*10/15);
    motormove(6, -i*25/15);
    motormove(10, -i*10/15);
    delaymaker(15, i, 20);
  }
  degremem();
}
void forward2(){
  int force1[4] = {-5, -13, -5, 0};
  int force2[4] = {2, 2, 2, 0};
  int force3[4] = {20, 40, 20, 0};
  int force4[4] = {-8, -10, -12, -15};
  for(int i=0; i<4; i++){
    motormove(7, force1[i]);
    motormove(8, force2[i]);
    motormove(9, force3[i]);
    motormove(0, force4[i]);
    delay(5);
  }
  degremem();
  /*for(int i=0; i<16; i++){
    motormove(0, -i);
    motormove(7, -i*13/15);
    motormove(8, i*2/15);
    motormove(9, i*40/15);
    delaymaker(15, i, 5);
  }
  degremem();
  for(int i=0; i<16; i++){
    motormove(7, i*13/15);
    motormove(8, -i*2/15);
    motormove(9, -i*40/15);
    delaymaker(11, i, 5);
  }
  degremem();*/
  for(int i=0; i<6; i++){
    leg2(7, 8, 9, i);
  }
  degremem();
  gapdet(9);
  gapdet(8);
  gapdet(7);
  for(int i=0; i<16; i++){
    motormove(9, -i*gap[9]/15);
    motormove(8, -i*gap[8]/15);
    motormove(7, -i*gap[7]/15);
    motormove(3, -i*43/15);
    motormove(2, i*20/15);
    motormove(1, i*52/15);
    motormove(0, i*25/15);
    motormove(4, i*10/15);
    motormove(6, i*10/15);
    motormove(10, i*10/15);
    delaymaker(15, i, 30);
  }
  degremem();

  int force5[4] = {-5, -13, -5, 0};
  int force6[4] = {2, 2, 2, 0};
  int force7[4] = {20, 40, 20, 0};
  int force8[4] = {-8, -10, -12, -15};
  for(int i=0; i<4; i++){
    motormove(1, force5[i]);
    motormove(2, force6[i]);
    motormove(3, force7[i]);
    motormove(6, -force8[i]);
    delay(5);
  }
  degremem();
  /*
  for(int i=0; i<16; i++){
    motormove(6, i);
    motormove(1, -i*13/15);
    motormove(2, i*2/15);
    motormove(3, i*40/15);
    delaymaker(15, i, 20);
  }
  degremem();
  for(int i=0; i<16; i++){
    motormove(1, i*13/15);
    motormove(2, -i*2/15);
    motormove(3, -i*40/15);
    delaymaker(11, i, 20);
  }
  degremem();
  */
  
  for(int i=0; i<6; i++){
    leg3(1, 2, 3, i);
  }
  degremem();
  gapdet(3);
  gapdet(2);
  gapdet(1);
  for(int i=0; i<16; i++){
    motormove(3, i*gap[3]/15);
    motormove(2, i*gap[2]/15);
    motormove(1, i*gap[1]/15);
    motormove(9, -i*43/15);
    motormove(8, i*20/15);
    motormove(7, i*52/15);
    motormove(0, -i*10/15);
    motormove(4, -i*10/15);
    motormove(6, -i*25/15);
    motormove(10, -i*10/15);
    delaymaker(15, i, 30);
  }
  degremem();
}
void right(){
  int legup1[5] = {0, -30, -55, -30, 0};
  int legup2[5] = {0, -15, -30, -15, 0};
  int legup3[5] = {0, -15, -30, -15, 0};
  int rot[5] = {0, 0, 25, 25, 25};
  for(int i=0; i<16; i++){
    motormove(0, i);
    motormove(4, i);
    motormove(6, i);
    motormove(10, i);
    delaymaker(16, i, 30);
  }
  degremem();
  for(int i=0; i<5; i++){
    motormove(1, legup1[i]);
    motormove(2, legup2[i]);
    motormove(3, legup3[i]);
    motormove(5, rot[i]);
    delay(20);
  }
  degremem();
  for(int i=0; i<31; i++){
    motormove(0, -i);
    motormove(4, -i);
    motormove(6, -i);
    motormove(10, -i);
    delaymaker(40, i, 30);
  }
  degremem();
  for(int i=0; i<16; i++){
    motormove(5, -i*25/15);
    motormove(11, -i*25/15);
    motormove(7, i*15/15);
    motormove(9, -i*15/15);
    delaymaker(15, i, 30);
  }
  degremem();
  int legup4[5] = {15, -30, -55, -30, 0};
  int legup5[5] = {0, -15, -30, -15, 0};
  int legup6[5] = {-15, -15, -30, -15, 0};
  newdeg[7] = deg[7];
  newdeg[8] = deg[8];
  newdeg[9] = deg[9];
  for(int i=0; i<5; i++){
    motormove(7, legup1[i]);
    motormove(8, legup2[i]);
    motormove(9, legup3[i]);
    motormove(11, rot[i]);
    delay(30);
  }
  degremem();
  for(int i=0; i<16; i++){
    motormove(0, i);
    motormove(4, i);
    motormove(6, i);
    motormove(10, i);
    delaymaker(16, i, 50);
  }
  degremem();
}
void left(){
  int legup1[5] = {0, -10, -10, -10, 0};
  int legup2[5] = {0, -15, -30, -15, 0};
  int legup3[5] = {0, -15, -30, -15, 0};
  int rot[5] = {0, 0, -25, -25, -25};
  for(int i=0; i<16; i++){
    motormove(0, -i);
    motormove(4, -i);
    motormove(6, -i);
    motormove(10, -i);
    delaymaker(15, i, 30);
  }
  degremem();
  for(int i=0; i<5; i++){
    motormove(7, legup1[i]);
    motormove(8, legup2[i]);
    motormove(9, legup3[i]);
    motormove(11, rot[i]);
    delay(20);
  }
  degremem();
  for(int i=0; i<31; i++){
    motormove(0, i);
    motormove(4, i);
    motormove(6, i);
    motormove(10, i);
    delaymaker(40, i, 30);
  }
  degremem();
  for(int i=0; i<16; i++){
    motormove(5, i*25/15);
    motormove(11, i*25/15);
    motormove(1, i*15/15);
    motormove(3, -i*15/15);
    delaymaker(15, i, 30);
  }
  degremem();
  int legup4[5] = {15, -30, -55, -30, 0};
  int legup5[5] = {0, -15, -30, -15, 0};
  int legup6[5] = {-15, -15, -30, -15, 0};
  newdeg[1] = deg[1];
  newdeg[2] = deg[2];
  newdeg[3] = deg[3];
  for(int i=0; i<5; i++){
    motormove(1, legup4[i]);
    motormove(2, legup5[i]);
    motormove(3, legup6[i]);
    motormove(5, rot[i]);
    delay(30);
  }
  degremem();
  for(int i=0; i<16; i++){
    motormove(0, -i);
    motormove(4, -i);
    motormove(6, -i);
    motormove(10, -i);
    delaymaker(15, i, 50);
  }
  degremem();
}
void Stop(){
  newdeg[7] = deg[7];
  newdeg[8] = deg[8];
  newdeg[9] = deg[9];
  int legup1[5] = {52, 10, -20, -45, -55};
  int legup2[5] = {20, 0, -10, -20, -30};
  int legup3[5] = {-43, -40, -35, -33, -30};
  int legdown1[3] = {-55, -30, -0};
  int legdown2[3] = {-30, -15, -0};
  int legdown3[3] = {-30, -15, -0};
  
  int base1 = 170;
  int base2 = 63;
  int base3 = 150;
  //newdeg[a] = deg[a];
  //newdeg[b] = deg[b];
  //newdeg[c] = deg[c];
  float func1[6] = {220, 165, 155, 115, 115, 130};
  float func2[6] = {88, 33, 33, 33, 33, 105};
  float func3[6] = {165, 165, 140, 120, 100, 75};
  //motormove(a, func1[d]-base1);
  //motormove(b, func2[d]-base2);
  //motormove(c, -func3[d]+base3);
  delay(50);
  for(int i=0; i<3; i++){
    motormove(7, func1[i]-base1);
    motormove(8, func2[i]-base2);
    motormove(9, -func3[i]+base3);
    delaymaker(3, i, 20);
  }
  degremem();
  
  int force1[4] = {-5, -13, -5, 0};
  int force2[4] = {2, 2, 2, 0};
  int force3[4] = {20, 40, 20, 0};
  int force4[4] = {-8, -10, -12, -15};
  for(int i=0; i<4; i++){
    motormove(7, force1[i]);
    motormove(8, force2[i]);
    motormove(9, force3[i]);
    motormove(0, force4[i]);
    delay(5);
  }
  degremem();
  
  for(int i=0; i<3; i++){
    gapdet(7);
    gapdet(8);
    gapdet(9);
    motormove(7, -gap[7]);
    motormove(8, -gap[8]);
    motormove(9, -gap[9]);
    delaymaker(3, i, 20);
  }
  degremem();
  gapdet(0);
  gapdet(4);
  gapdet(6);
  gapdet(10);
  motormove(0, gap[0]);
  motormove(4, gap[4]);
  motormove(6, gap[6]);
  motormove(10, gap[10]);
  degremem();
}
void loop(){
  for (int i = 0; i < 12; i++) {
    servo[i].write(deg[i]);
    newdeg[i] = deg[i];
    halfnewdeg[i] = deg[i];
    delay(5);
  }
  Still();
  char data = Serial.read();
  if(data=='f'){
    forward1();
    forward2();
    Stop();
  }else if(data=='r'){
    right();
  }else if(data=='l'){
    left();
  }else if(data=='s'){
    Still();
  }
}
