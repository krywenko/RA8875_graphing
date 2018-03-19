
String command;

char msg2[50];
char msg3[50];

void setup() {
 Serial.begin(115200);
Serial2.begin(115200);

 
 // put your setup code here, to run once:
Serial.println("started");
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
 
}

void parseCommand(String com)
{
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  //int test = part1.toInt();
  //Serial.print(part1);
  //Serial.println("#");
  part2 = com.substring(com.indexOf("(")+1);
  //Serial.println(part2);

  
  if (part1 == "1")
  {
    
    Serial.print("recieved 1 ");
    String raw_CMD;
    float input1 = part2.toFloat();
    raw_CMD=input1;
Serial.println(input1);
    }
  if (part1== "2")
    {
      
    Serial.print("recieved 2 ");
    String raw_CMD;
    float input2 = part2.toFloat();
    raw_CMD=input2;
Serial.println(input2);

    }
 if (part1 == "3")
    {
      
    Serial.print("recieved 3 ");
    String raw_CMD;
    float input3 = part2.toFloat();
    raw_CMD=input3;
    Serial.println(input3);
    
  }


  if (part1 == "4")
  {
    
    Serial.print("recieved 4 ");
    String raw_CMD;
    float input4 = part2.toFloat();
    raw_CMD=input4;
Serial.println(input4);
    }
  if (part1== "5")
    {
      
    Serial.print("recieved 5 ");
    String raw_CMD;
    float input5 = part2.toFloat();
    raw_CMD=input5;
Serial.println(input5);

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
    }  
