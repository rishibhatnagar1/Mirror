#include <SoftwareSerial.h>
SoftwareSerial RFID(2, 3); // RX and TX
 
int data1 = 0;
int ok = -1;
int yes = 13;
int no = 12;
 
// use first sketch in http://wp.me/p3LK05-3Gk to get your tag numbers
int tag18[19] = {83,78,45,68,69,67,58,48,48,48,54,57,54,49,53,50,51,13,10};
int tag10[19]= {83,78,45,68,69,67,58,48,48,48,54,57,54,55,48,57,51,13,10};
int tag19[19]={83,78,45,68,69,67,58,48,48,48,54,57,52,51,57,48,50,13,10};
int tag15[19]={83,78,45,68,69,67,58,48,48,48,54,57,53,49,52,54,56,13,10};

int newtag[19] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // used for read comparisons
 
void setup()
{
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC 
  pinMode(yes, OUTPUT); // for status LEDs
  pinMode(no, OUTPUT);
}
 
boolean comparetag(int aa[19], int bb[19])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 19 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 19)
  {
    ff = true;
  }
  return ff;
}
 
void checkmytags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made

  
  if (comparetag(newtag, tag18) == true)
  {
    ok++;//ok=1
    //Do something in this condition
    Serial.println("0018");
    Serial.print("*");
    
    
  }
  if (comparetag(newtag, tag15) == true)
  {
    ok++;//ok=1
    //Do something in this condition
    Serial.println("0015");
    Serial.print("*");
    
    
  }
  if (comparetag(newtag, tag19) == true)
  {
    ok++;//ok=1
    //Do something in this condition
    Serial.println("0019");
    Serial.print("*");
    
    
  }
  if (comparetag(newtag, tag10) == true)
  {
    ok++;//ok=1
    //Do something in this condition
    Serial.println("0010");
    Serial.print("*");
    
    
  }
}
 
void readTags()
{
  ok = -1;
 
  if (RFID.available() > 0) 
  {
    // read tag numbers
    delay(100); // needed to allow time for the data to come in from the serial buffer.
 
    for (int z = 0 ; z < 19 ; z++) // read the rest of the tag
    {
      data1 = RFID.read();
      newtag[z] = data1;
    }
    RFID.flush(); // stops multiple reads
 
    // do the tags match up?
    checkmytags();
  }
 
  // now do something based on tag type
  if (ok > 0) // if we had a match
  {
    //Serial.println("Accepted");
    ok = -1;
  }
  else if (ok == 0) // if we didn't have a match
  {
    ok = -1;
  }
}
 
void loop()
{
  readTags();
}

