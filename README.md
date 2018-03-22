# RA8875_graphing
Graphing  Mqtt with RA8875 Screen
a TFT grapphing ino for arduino connected to esp or wifi arduino, wemos d3 
 the esp  will listen to the topic and transmit the  data to  arduino to be processed into a visual image on RA8875, 
 you can create graphs vertical and horizontal bars  meter rings and pie charts  based on the  RA8875 driver by sumotoy 
 https://github.com/sumotoy/RA8875
 
 image of the graph displayed 
 
 https://github.com/krywenko/RA8875_graphing/blob/master/DSC04320.JPG

autoconnect... ino ---is the esp wifi connect and sub to mqtt topics to be passed to the arduino ( handles 20 mqtt inputs)
lCD_sSerial_read. ino --- is just a  base example of the serail read command on the arduino fron esp 
LCD_Serial_read_graph.ino--- is the graphing sketch for the  arduino connected to the RA8875  just adjust  serial port to match yours and adjust to graphing to match what you want.. it can handle up to 20 different  inputs from the esp


Touch screen and the weather interface  is based on esp weather station, but  I had to turn off some debuging info in the wundercastforcast.h  if you wish to  use it on this screen you either can use the supplied "**forcast.h" or edit your copy by commentting out the serial print lines with in it 
 there 6 different touch screen pages  to add additional radial meters..  they are cureently coloured  just for easier distinction, each screen butto is located where meter should be ..
