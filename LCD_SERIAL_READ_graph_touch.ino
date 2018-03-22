

#include <SPI.h>
#include <RA8875.h>

#define RA8875_INT 2 //--touch interface

#define RA8875_CS 10

#define RA8875_RESET 9//any pin or 255 to disable it!

#define ADJ_PIN A0

RA8875 tft = RA8875(RA8875_CS, RA8875_RESET);
//---touch interface--

uint16_t tx, ty;
uint16_t choosenColor = 0;
/*
void interface(){
  tft.fillRect(10,10,40,40,RA8875_WHITE);
  tft.fillRect(10+(40*1)+(10*1),10,40,40,RA8875_BLUE);
  tft.fillRect(10+(40*2)+(10*2),10,40,40,RA8875_RED);
  tft.fillRect(10+(40*3)+(10*3),10,40,40,RA8875_GREEN);
  tft.fillRect(10+(40*4)+(10*4),10,40,40,RA8875_CYAN);
  tft.fillRect(10+(40*5)+(10*5),10,40,40,RA8875_MAGENTA);
  tft.fillRect(10+(40*6)+(10*6),10,40,40,RA8875_YELLOW);
  tft.drawRect(10+(40*7)+(10*7),10,40,40,RA8875_WHITE);
}*/
int Screen =1;

///end of touch 
String weather = "please wait";
String Fhigh;
String Flow;
String Fday;
String Fpop;
uint32_t runTime = -99999;       // time for next update
uint32_t runTime1 = -99999;
int reading = 0; // Value to be displayed

int scan =0; //x step for graphing
int chg =0;  // value for drawing ersase block

int ext1; /// external output so you can use the value outside its function
int ext2;
int ext3;
int ext4;
boolean graph_1 = true; // set  vertical, horizontal,and graph function to redraw
boolean graph_2 = true;
boolean graph_3 = true;
boolean graph_4 = true;
boolean graph_5 = true;
boolean graph_6 = true;
boolean graph_7 = true;
boolean redraw1 = true;
double ox , oy ;/// graph plot ordinates 
double ox2 , oy2 ;

String command; // serial input capture string

char msg2[50];
char msg3[50];

void setup() {
 Serial.begin(115200);
Serial2.begin(115200);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("RA8875 start");

 // pinMode(ADJ_PIN, INPUT);
  tft.begin(RA8875_800x480);
 //double x, y;
 // put your setup code here, to run once:
Serial.println("started");
//touchscreen
tft.useINT(RA8875_INT);
  tft.touchBegin();//enable Touch support!
 // interface();
  tft.enableISR(true);
tft.brightness(50);
}

void loop() 
{

   if(Serial2.available())
   {
      char c = Serial2.read();
    
      if (c == ')')
      {
       
        parseCommand(command);
        
        command="";
      }
      else
      {
       command += c;
      }
  }
//touch-interface///////////
 if (tft.touched()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      if (ty >= 0 && ty <= 55){ //interface area
        if ((tx > 10 && tx < (10+120))){
          choosenColor = RA8875_WHITE;
         // interface();
         Screen =1;
          tft.fillRect(0,0,800,120,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
        } 
        else if ((tx > 10+(120*1)+(10*1) && tx < 10+(120*2)+(10*1))){
          choosenColor = RA8875_BLUE;
          //interface();
          Screen = 2;
           tft.fillRect(0,0,800,120,ORANGE);
       
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
        } 
        else if ((tx > 10+(120*2)+(10*2) && tx < 10+(120*3)+(10*2))){
          choosenColor = RA8875_RED;  
         // interface();
         Screen =3;
          tft.fillRect(0,0,800,120,RA8875_PURPLE);
        
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
        } 
        else if ((tx > 10+(120*3)+(10*3) && tx < 10+(120*4)+(10*3))){
          choosenColor = RA8875_GREEN;  
          //interface();
          Screen=4;
           tft.fillRect(0,0,800,120,RA8875_YELLOW);
        
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
        } 
        else if ((tx > 10+(120*4)+(10*4) && tx < 10+(120*5)+(10*4))){
          choosenColor = RA8875_CYAN;  
          //interface();
          Screen=5;
           tft.fillRect(0,0,800,120,RA8875_GREEN);
    
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
        } 
        else if ((tx > 10+(120*5)+(10*5) && tx < 10+(120*6)+(10*5))){
          choosenColor = RA8875_MAGENTA;  
          //interface();
          Screen=6;
           tft.fillRect(0,0,800,120,RA8875_BLUE);
        
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
        } 
      } 
  } 
/////////////////////////////
}

////////// Parse serial string and graphs them////////////
////////////////////////////////////////////////////////// 

void parseCommand(String com)
{
 //--graphing variables 
    int16_t xpos = 0;
    int16_t ypos = 0;
    uint16_t radius = 65;
    int16_t distance = 14;

//--com variables  
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  //int test = part1.toInt();
  Serial.print(part1);
  Serial.println("#");
  part2 = com.substring(com.indexOf("(")+1);
  Serial.println(part2);

//--input and graphing 
//////////////////////  

//Serial.print("SCREEN  "); Serial.println(Screen);
  if (part1 == "1")
  {
    
   // Serial.print("recieved 1 ");
    String raw_CMD;
    float input1 = part2.toFloat();
    raw_CMD=input1;
//Serial.println(input1);
    }
  if (part1== "2")
    {
      
    //Serial.print("recieved 2 ");
    String raw_CMD;
    float input2 = part2.toFloat();
    raw_CMD=input2;
//Serial.println(input2);
reading = input2;
 DrawBarChartV(tft, 10,  440, 10, 120, -40, 40 , 20, reading , 4 , 0, DKORANGE, BLACK, BLUE, WHITE, BLACK, "TEMP", graph_2);
 int Cntr = 30; if (input2 > 999) Cntr = 20; //if(input2<100) Cntr=40;
 int Gnum = 4;
 if (Screen ==1){
tft.ringMeter(input2,-40,40,xpos+ (radius * Gnum) + (distance*2),ypos,radius,"none",3,tft.htmlTo565(0x848482),110,10);
tft.setFontScale(1);tft.setTextColor(RA8875_BLUE, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+30,ypos+40);tft.print("TEMP");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+Cntr,ypos+80);tft.print(reading);
 }
tft.setFontScale(0);  
    }
 if (part1 == "3")
    {
      
    //Serial.print("recieved 3 ");
    String raw_CMD;
    float input3 = part2.toFloat();
    raw_CMD=input3;
int Gnum = 3;   //graph number  
int Cntr = 30; if (input3 > 999) Cntr = 20;
if (Screen ==1){
tft.ringMeter(input3,0,100,xpos+ (radius * Gnum) + (distance*2),ypos,radius,"none",7,tft.htmlTo565(0x848482),110,10);
tft.setFontScale(1);tft.setTextColor(RA8875_BLUE, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+30,ypos+40);tft.print(" RH%");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+Cntr,ypos+80);tft.print("50");
}
tft.setFontScale(0);  
    
   // Serial.println(input3);
    
  }

  if (part1 == "4")
  {
    
    //Serial.print("recieved 4 ");
    String raw_CMD;
     float input4 = part2.toInt();
    ext1 = input4;
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =2;
if (Screen==1){
tft.setFontScale(1);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + distance+30,ypos+40);tft.print("SOLAR");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + distance+Cntr,ypos+80);tft.print(ext1);tft.print("   ");
tft.ringMeter(input4,-10,2000,xpos+ (radius * Gnum) + distance,ypos,radius,"none",5,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0);    
//Serial.println(ext1);
    }
    //Serial.print(ext1);
     //Serial.println("   ext1");
  if (part1== "5")
    {
      
    //Serial.print("recieved 5 ");
    String raw_CMD;
    float input5 = part2.toInt();
    //input5 = input5/1000;
    int Cntr = 30;
        
   // if (input5 > 999){ Cntr = 20; if (chg > 0) chg=0;}
    //if (input5 < 999){ Cntr = 30;if (chg < 2 ){tft.fillRect(xpos+15,ypos+30,75,25,RA8875_BLACK);chg++;}}
if (Screen==1){    
tft.setFontScale(1);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.setCursor(xpos+30,ypos+40);tft.print("GRID");tft.setFontScale(1);tft.setCursor(xpos+Cntr,ypos+80);tft.print(ext2);tft.print("   ");
  
tft.ringMeter(input5,-1,8000,xpos,ypos,radius,"none",4,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0);
//tft.fillRect(10,30,80,25,RA8875_GREEN);
  ext2=input5;
//Serial.println(input5);
screenPie(ext1,ext2,160); 
    }
 if (part1 == "6")
    {
      
    Serial.print("recieved 6 ");
    String raw_CMD;
    float input6 = part2.toFloat();
    raw_CMD=input6;
    Serial.println(input6);
    
  }


  if (part1 == "7")
  {
    
    Serial.print("recieved 7 ");
    String raw_CMD;
    float input7 = part2.toFloat();
    raw_CMD=input7;
Serial.println(input7);
    }
  if (part1== "8")
    {
      
    Serial.print("recieved 8 ");
    String raw_CMD;
    float input8 = part2.toFloat();
    raw_CMD=input8;
Serial.println(input8);

    }
 if (part1 == "9")
    {
      
    Serial.print("recieved 9 ");
    String raw_CMD;
    float input9 = part2.toFloat();
    raw_CMD=input9;
    Serial.println(input9);
    
  }
  
  if (part1 == "10")
  {
    
    Serial.print("recieved 10 ");
    String raw_CMD;
    float input10 = part2.toFloat();
    raw_CMD=input10;
Serial.println(input10);
    }
      
  if (part1== "11")
    {
      
    Serial.print("recieved 11 ");
    String raw_CMD;
    float input11 = part2.toFloat();
    raw_CMD=input11;
Serial.println(input11);

    }
  if (part1== "12")
    {
      
    Serial.print("recieved 12 ");
    String raw_CMD;
    float input12 = part2.toFloat();
    raw_CMD=input12;
Serial.println(input12);

    }
 if (part1 == "13")
    {
      
    Serial.print("recieved 13 ");
    String raw_CMD;
    float input13 = part2.toFloat();
    raw_CMD=input13;
    Serial.println(input13);
    
  }
  
  if (part1 == "14")
  {
    
    Serial.print("recieved 14 ");
    String raw_CMD;
    float input14 = part2.toFloat();
    raw_CMD=input14;
Serial.println(input14);
    }
  
  if (part1== "15")
    {
      
    Serial.print("recieved 15 ");
    String raw_CMD;
    float input15 = part2.toFloat();
    raw_CMD=input15;
Serial.println(input15);

    }
    
  if (part1== "16")
    {
      
    Serial.print("recieved 16 ");
    String raw_CMD;
    float input16 = part2.toFloat();
    raw_CMD=input16;
Serial.println(input16);

    }
 if (part1 == "17")
    {
      
    Serial.print("recieved 17 ");
    String raw_CMD;
    float input17 = part2.toFloat();
    raw_CMD=input17;
    Serial.println(input17);
    
  }
  
  if (part1 == "18")
  {
    
    Serial.print("recieved 18 ");
    String raw_CMD;
    float input18 = part2.toFloat();
    raw_CMD=input18;
Serial.println(input18);
    }
  if (part1== "19")
    {
      
    Serial.print("recieved 19 ");
    String raw_CMD;
    float input19 = part2.toFloat();
    raw_CMD=input19;
Serial.println(input19);

    }
 if (part1 == "20")
    {
      
    Serial.print("recieved 20 ");
    String raw_CMD;
    float input20 = part2.toFloat();
    raw_CMD=input20;
    Serial.println(input20);
    
  }
if (part1 == "21")
    {

    String raw_CMD;
   weather=part2;

  }

if (part1 == "22")
    {
    String raw_CMD;
   Flow=part2;
    Serial.println(part2);
  }

  if (part1 == "23")
    {
    String raw_CMD;
   Fhigh=part2;
    Serial.println(part2);
  }
if (part1 == "24")
    {
    String raw_CMD;
   Fday=part2;
    Serial.println(part2);
  }
if (part1 == "25")
    {
    String raw_CMD;
   Fpop=part2;
    Serial.println(part2);
  }
if (Screen==1){
tft.setFontScale(1);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(505, 40);tft.print(Fhigh);tft.setFontScale(0);tft.print(" C ");tft.setFontScale(1);tft.setCursor(430, 40);tft.print("High");
 tft.setFontScale(1);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(505, 70);tft.print(Flow);tft.setFontScale(0);tft.print(" C ");tft.setFontScale(1);tft.setCursor(430, 70);tft.print("Low");
 tft.setFontScale(1);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(570, 10);tft.print(Fday);tft.setCursor(430, 10);tft.setFontScale(1);tft.print("Forecast");
  tft.setFontScale(1);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(505, 100);tft.print(Fpop);tft.setFontScale(0);tft.print(" % ");tft.setFontScale(1);tft.setCursor(430, 100);tft.print("PoP ");
 tft.setFontScale(0);}
 
 if(Screen==6){
  tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLUE);tft.setCursor(320, 0);tft.print(weather);tft.setFontScale(1);tft.setCursor(0, 0);tft.setTextColor(RA8875_GREEN, RA8875_BLUE);tft.print("TODAY'S FORECAST - ");
 tft.setFontScale(0);
 
 }
 
   ///---- GRaphing_----

///////////Graphing Charts///////////
  
    double x, y;
    double Tinc = 3600;
    double Tinc2 = 3600;
    Tinc = (Tinc/3);//time delay compensation
    Tinc2 = (Tinc2/3);
    double Time= 28800;
    Time =(Time/3 ) ;//timedelay compensation
    // ivT = 60; /// time interval 1 seconds 60 min ets
  if (millis() - runTime >= 1550L) { // Execute every 1s
    runTime = millis();
        scan++;
        x=scan;
     y = ext2;  
     Graph(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc, 0, 7000, 1000, "kw", "hrs", "Solar/Grid", DKBLUE, RED, GREEN, WHITE, BLACK, graph_3);
     y= ext1;
     Graph2(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc2, 0, 7000, 1000, "kw", "hrs", "", DKBLUE, RED, YELLOW, WHITE, BLACK, graph_4);
   
   if (scan == Time) {
    tft.fillRect(320,440,480,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(320,400,480,40,RA8875_BLACK);
    tft.fillRect(320,360,480,40,RA8875_BLACK);
    tft.fillRect(320,320,480,40,RA8875_BLACK);
    tft.fillRect(320,280,480,40,RA8875_BLACK); 
    tft.fillRect(320,240,480,40,RA8875_BLACK);
    tft.fillRect(320,200,480,40,RA8875_BLACK);
    tft.fillRect(320,160,480,40,RA8875_BLACK); 
    tft.fillRect(320,120,480,40,RA8875_BLACK); 
    tft.fillRect(320,80,480,40,RA8875_BLACK);
//tft.fillRect(320,200,460,40,RA8875_BLACK);
//utft.fillRect(320,160,460,40,RA8875_BLACK); 
  
    graph_3=true;graph_4=true;scan=0;}
  
} 

    }

//////////// Pie Chart ///////////
/////////////////////////////////

int screenPie(int inp1,int inp2 ,int inp3)
{
  const uint16_t x = 89;
  const uint16_t y = 219;
  const uint16_t radius = 80;
  //Serial.println("sgraph");
  //Serial.println(inp1);
 // Serial.println(inp2);
  //Serial.println("Egraph");
  if (inp1 <0){inp1 =0;}
  if (inp2 <0) {inp2 =0;}
  if (inp3 <0){inp3 - 0;}
  float vx = inp1+inp2 +inp3;
  float t1= inp1/vx;
  float t2 = inp2/vx;
  float t3 = inp3/vx;
int d1 = 360*t1;
int d2 = d1+(360*t2);
int d3 = 360*t3;
int t1a = t1;
int t2a =t2;
int t3a = t3;
int t1b;
int t2b;
int t3b;
 // tft.clearScreen();
  tft.drawArc(x , y , radius, radius, 0, d1, tft.Color565(198, 255, 13));
  tft.drawArc(x , y , radius , radius , d1,d2 , tft.Color565(255, 0, 54));
  tft.drawArc(x , y , radius, radius, d2, 360, tft.Color565(0, 255, 241));

  //tft.fillRect(180,180,10,10,RA8875_BLUE);
  tft.setFontScale(1);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(180, 150);tft.print(100*t3);tft.print("% ");tft.setFontScale(0);tft.setCursor(180, 130);tft.print("DIVERTER");
 // tft.fillRect(180,240,10,10,RA8875_RED);
  tft.setFontScale(1);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.setCursor(180, 210);tft.print(100*t2);;tft.print("% ");tft.setFontScale(0);tft.setCursor(180, 190);tft.print("GRID");
 // tft.fillRect(180,280,10,10,RA8875_GREEN);
    tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(180, 270);tft.print(100*t1);tft.print("% ");tft.setFontScale(0);tft.setCursor(180, 250);tft.print("SOLAR");
 tft.setFontScale(3);tft.setTextColor(LTBLUE, RA8875_BLACK);tft.setCursor(90, 350);tft.print(inp1+inp2);tft.print(" ");tft.setFontScale(1);tft.setCursor(90, 310);tft.print("TOTAL");
  
  t1b = ext1;
  t2b =ext2;
  t3b = t3a;
  
  tft.setFontScale(0);
}

///////////Vertical Charts///////////////
/////////////////////////////////////////

void DrawBarChartV(RA8875 & d, double x , double y , double w, double h , double loval , double hival , double inc , double curval ,  int dig , int dec, unsigned int barcolor, unsigned int voidcolor, unsigned int bordercolor, unsigned int textcolor, unsigned int backcolor, String label, boolean & redraw)
{

  double stepval, range;
  double my, level;
  double i, data;
  // draw the border, scale, and label once
  // avoid doing this on every update to minimize flicker
  if (redraw == true) {
    redraw = false;

    d.drawRect(x - 1, y - h - 1, w + 2, h + 2, bordercolor);
    d.setTextColor(textcolor, backcolor);
    //d.setFontScale(1);
    d.setCursor(x , y + 10);
    d.println(label);
    // step val basically scales the hival and low val to the height
    // deducting a small value to eliminate round off errors
    // this val may need to be adjusted
    stepval = ( inc) * (double (h) / (double (hival - loval))) - .001;
    for (i = 0; i <= h; i += stepval) {
      my =  y - h + i;
      d.drawFastHLine(x + w + 1, my,  5, textcolor);
      // draw lables
    //  d.setFontScale(0);
      d.setTextColor(textcolor, backcolor);
      d.setCursor(x + w + 12, my - 3 );
      data = hival - ( i * (inc / stepval));
      d.println(Format(data, dig, dec));
    }
  }
  // compute level of bar graph that is scaled to the  height and the hi and low vals
  // this is needed to accompdate for +/- range
  level = (h * (((curval - loval) / (hival - loval))));
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  d.fillRect(x, y - h, w, h - level,  voidcolor);
  d.fillRect(x, y - level, w,  level, barcolor);
  // write the current value
  d.setTextColor(textcolor, backcolor);
  //d.setFontScale(1);
  d.setCursor(x , y - h - 23);
  d.println(Format(curval, dig, dec));

}


//////////////Horizontal Charts////////////
//////////////////////////////////////////

void DrawBarChartH(RA8875 & d, double x , double y , double w, double h , double loval , double hival , double inc , double curval ,  int dig , int dec, unsigned int barcolor, unsigned int voidcolor, unsigned int bordercolor, unsigned int textcolor, unsigned int backcolor, String label, boolean & redraw)
{
  double stepval, range;
  double mx, level;
  double i, data;

  // draw the border, scale, and label once
  // avoid doing this on every update to minimize flicker
  // draw the border and scale
  if (redraw == true) {
    redraw = false;
    d.drawRect(x , y , w, h, bordercolor);
    d.setTextColor(textcolor, backcolor);
   // d.setFontScale(1);
    d.setCursor(x , y - 20);
    d.println(label);
    // step val basically scales the hival and low val to the width
    stepval =  inc * (double (w) / (double (hival - loval))) - .00001;
    // draw the text
    for (i = 0; i <= w; i += stepval) {
      d.drawFastVLine(i + x , y + h + 1,  5, textcolor);
      // draw lables
     // d.setFontScale(0);
      d.setTextColor(textcolor, backcolor);
      d.setCursor(i + x , y + h + 10);
      // addling a small value to eliminate round off errors
      // this val may need to be adjusted
      data =  ( i * (inc / stepval)) + loval + 0.00001;
      d.println(Format(data, dig, dec));
    }
  }
  // compute level of bar graph that is scaled to the width and the hi and low vals
  // this is needed to accompdate for +/- range capability
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  level = (w * (((curval - loval) / (hival - loval))));
  d.fillRect(x + level + 1, y + 1, w - level - 2, h - 2,  voidcolor);
  d.fillRect(x + 1, y + 1 , level - 1,  h - 2, barcolor);
  // write the current value
  d.setTextColor(textcolor, backcolor);
 // d.setFontScale(1);
  d.setCursor(x + w + 10 , y + 5);
  d.println(Format(curval, dig, dec));
}


String Format(double val, int dec, int dig ) {
  int addpad = 0;
  char sbuf[20];
  String condata = (dtostrf(val, dec, dig, sbuf));


  int slen = condata.length();
  for ( addpad = 1; addpad <= dec + dig - slen; addpad++) {
    condata = " " + condata;
  }
  return (condata);

}

///////////////Graphs /////////////////
//////////////////////////////////////

void Graph(RA8875 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {
//if (redraw1==true){redraw=true;}
  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      int strip =i;
      d.println(strip);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
     //int strip =(i/.66666666666666666666);
     int strip=(i*3)/3600;
      d.println(strip);
    }

    //now draw the labels
    d.setFontScale(0);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}
void Graph2(RA8875 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {
//if (redraw1==true){redraw=true;}
  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox2 = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy2 = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      int strip =i;
      d.println(strip);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
     //int strip =(i/.66666666666666666666);
     int strip=(i*3)/3600;
      d.println(strip);
    }

    //now draw the labels
    d.setFontScale(0);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox2, oy2, x, y, pcolor);
  d.drawLine(ox2, oy2 + 1, x, y + 1, pcolor);
  d.drawLine(ox2, oy2 - 1, x, y - 1, pcolor);
  ox2 = x;
  oy2= y;

}

