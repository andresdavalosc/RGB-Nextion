#include <Nextion.h>
#include <FastLED.h>
#define pin  7
#define num 120
int flag = 0;
CRGB fade[num];
CRGBArray<num> leds;
NexDSButton bt1  = NexDSButton(1, 4, "bt1");
NexDSButton bt2  = NexDSButton(1, 5, "bt2");
NexDSButton bt3  = NexDSButton(1, 3, "bt3");
NexTouch *nex_listen_list[] =
{
  &bt1,
  &bt2,
  &bt3,
  NULL
};

void prender_bt1(void *ptr) // blauwe led
{
  flag = 1;
  leds = CRGB (0, 0 , 0);
  FastLED.show();
}

void prender_bt2(void *ptr)
{
  uint32_t estado2 = 1;
  bt2.getValue(&estado2);
  if (estado2 == 0)
  {

    leds = CRGB (255, 0 , 0);
    FastLED.show();

  }
  else {
    leds = CRGB (0, 0 , 0);
    FastLED.show();
  }
}

void prender_bt3(void *ptr)
{
  uint32_t estado3 = 1;
  bt3.getValue(&estado3);
  while (estado3 == 0)
  {

    //    leds = CRGB (0, 191, 255);
    //    FastLED.show();
    spel();
    if(flag==1){
      break;
    }
  }
  //  else {
  leds = CRGB (0, 0 , 0);
  FastLED.show();
  //  }
}


void setup() {
  nexInit();
//  pinMode(led, OUTPUT);
  FastLED.addLeds<WS2812, pin, GRB>(leds, num);
  bt1.attachPop(prender_bt1);
  bt2.attachPop(prender_bt2);
  bt3.attachPop(prender_bt3);
}

void spel() {
  static uint8_t hue;
  for (int i = 0; i < num / 2; i++) {
    // fade everything out
    leds.fadeToBlackBy(40);

    // let's set an led value
    leds[i] = CHSV(hue++, 255, 255);

    // now, let's first 20 leds to the top 20 leds,
    leds(num / 2, num - 1) = leds(num / 2 - 1 , 0);
    FastLED.delay(33);
  }
}
void loop() {
  nexLoop(nex_listen_list);
}
