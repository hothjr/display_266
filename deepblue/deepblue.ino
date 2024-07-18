/*
* LAB Name: Arduino 2.9" E-Paper Display (GxEPD2 Library) - Text Example
* Author: Khaled Magdy
* For More Info Visit: www.DeepBlueMbedded.com
*/
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
 
#define EPD_SS 10
#define EPD_DC 9
#define EPD_RST 8
#define EPD_BUSY 7
#define MAX_DISPLAY_BUFFER_SIZE 800
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) /(EPD::WIDTH / 8))
#define TEXT_LINES 3
 
GxEPD2_3C<GxEPD2_266c, MAX_HEIGHT(GxEPD2_266c)>
display(GxEPD2_266c(EPD_SS, EPD_DC, EPD_RST, EPD_BUSY));
uint16_t TextCursors[2][TEXT_LINES];
const char* MSG[TEXT_LINES] = {
  "E-Ink / E-Paper Display",
  "Hallo, Sarah",
  "MAGNOTHERM"
};
 
void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing The E-Paper...");
  display.init();
  Serial.println("Initialization Done!");
  // Serial.println("Printing Messages, Please Wait...");
  // PrintMessages();
  display.fillScreen(GxEPD_RED);
  Serial.println("Printing Done! E-Paper Is Hibernating!");

  display.hibernate();
}
 
void loop()
{
  // Nothing To Do Here!
}
 
void PrintMessages()
{
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.setRotation(3);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_WHITE);
  for(int i=0; i<TEXT_LINES; i++)
  {
    display.getTextBounds(MSG[i], 0, 0, &tbx, &tby, &tbw, &tbh);
    TextCursors[0][i] = (display.width() - tbw) / 2;
    TextCursors[1][i] = ((display.height()*(i+1)) /(TEXT_LINES+1)) + (tbh/2);
  }
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_RED);
    display.setCursor(TextCursors[0][0], TextCursors[1][0]);
    display.print(MSG[0]);
    display.setCursor(TextCursors[0][1], TextCursors[1][1]);
    display.print(MSG[1]);
    display.setCursor(TextCursors[0][2], TextCursors[1][2]);
    display.print(MSG[2]);
  }
  while(display.nextPage());
}