#include "Common.h"
#include "Themes.h"
#include "Storage.h"
#include "Menu.h"

// Display position control
#define MENU_OFFSET_X    0    // Menu horizontal offset
#define MENU_OFFSET_Y   20    // Menu vertical offset
#define MENU_DELTA_X    10    // Menu width delta
#define METER_OFFSET_X   0    // Meter horizontal offset
#define METER_OFFSET_Y   0    // Meter vertical offset
#define SAVE_OFFSET_X   87    // EEPROM save icon horizontal offset
#define SAVE_OFFSET_Y    0    // EEPROM save icon vertical offset
#define FREQ_OFFSET_X  250    // Frequency horizontal offset
#define FREQ_OFFSET_Y   65    // Frequency vertical offset
#define FUNIT_OFFSET_X 255    // Frequency Unit horizontal offset
#define FUNIT_OFFSET_Y  48    // Frequency Unit vertical offset
#define BAND_OFFSET_X  150    // Band horizontal offset
#define BAND_OFFSET_Y    3    // Band vertical offset
// #define MODE_OFFSET_X   95    // Mode horizontal offset
// #define MODE_OFFSET_Y  114    // Mode vertical offset
#define RDS_OFFSET_X   165    // RDS horizontal offset
#define RDS_OFFSET_Y    94    // RDS vertical offset
#define BATT_OFFSET_X  288    // Battery meter x offset
#define BATT_OFFSET_Y    0    // Battery meter y offset

//
// Show ABOUT screen
//
static void drawAbout()
{
  // About screen
  spr.setTextDatum(TL_DATUM);
  spr.setTextColor(TH.text_muted, TH.bg);
  spr.drawString("ESP32-SI4732 Receiver", 0, 0, 4);
  spr.setTextColor(TH.text, TH.bg);
  spr.drawString(getVersion(), 2, 25, 2);
  spr.drawString("https://github.com/esp32-si4732/ats-mini", 2, 25 + 16, 2);
  spr.drawString("Authors: PU2CLR (Ricardo Caratti),", 2, 70, 2);
  spr.drawString("Volos Projects, Ralph Xavier, Sunnygold,", 2, 70 + 16, 2);
  spr.drawString("Goshante, G8PTN (Dave), R9UCL (Max Arnold),", 2, 70 + 16 * 2, 2);
  spr.drawString("Marat Fayzullin, Stevecrow74", 2, 70 + 16 * 3, 2);

  char text[64];
  sprintf(text, "DID: %08lX  DST: %02X%08lX",
    tft.readcommand32(ST7789_RDDID, 1),
    tft.readcommand8(ST7789_RDDST, 1),
    tft.readcommand32(ST7789_RDDST, 2)
  );
  spr.drawString(text, 2, 144, 2);

  for(int i=0 ; i<8 ; i++)
  {
    uint16_t rgb = (i&1? 0x001F:0) | (i&2? 0x07E0:0) | (i&4? 0xF800:0);
    spr.fillRect(i*40, 160, 40, 20, rgb);
  }

#ifdef ENABLE_HOLDOFF
  // Update if not tuning
  if(!tuning_flag) spr.pushSprite(0, 0);
#else
  // No hold off
  spr.pushSprite(0, 0);
#endif
}

//
// Show "Loading SSB" message
//
void drawLoadingSSB()
{
  if(sleepOn()) return;

  spr.setTextDatum(MC_DATUM);
  spr.fillSmoothRoundRect(80, 40, 160, 40, 4, TH.text);
  spr.fillSmoothRoundRect(81, 41, 158, 38, 4, TH.menu_bg);
  spr.drawString("Loading SSB", 160, 62, 4);
  spr.pushSprite(0, 0);
}

//
// Draw band and mode indicators
//
static void drawBandAndMode(const char *band, const char *mode, int x, int y)
{
  spr.setTextDatum(TC_DATUM);
  spr.setTextColor(TH.band_text, TH.bg);
  uint16_t band_width = spr.drawString(band, x, y);

  spr.setTextDatum(TL_DATUM);
  spr.setTextColor(TH.mode_text, TH.bg);
  uint16_t mode_width = spr.drawString(mode, x + band_width / 2 + 12, y + 8, 2);

  spr.drawSmoothRoundRect(x + band_width / 2 + 7, y + 7, 4, 4, mode_width + 8, 17, TH.mode_border, TH.bg);
}

//
// Draw radio text
//
static void drawRadioText(int y, int ymax)
{
  const char *rt = getRadioText();

  // Draw potentially multi-line radio text
  spr.setTextDatum(TC_DATUM);
  spr.setTextColor(TH.rds_text, TH.bg);
  for(; *rt && (y<ymax) ; y+=15, rt+=strlen(rt)+1)
    spr.drawString(rt, 160, y, 2);

  // Show program info if we have it and there is enough space
  if((y<ymax) && *getProgramInfo())
    spr.drawString(getProgramInfo(), 160, y, 2);
}

//
// Draw frequency
//
static void drawFrequency(uint32_t freq, int x, int y, int ux, int uy)
{
  spr.setTextDatum(MR_DATUM);
  spr.setTextColor(TH.freq_text, TH.bg);

  if(currentMode==FM)
  {
    // FM frequency
    spr.drawFloat(freq/100.00, 2, x, y, 7);
    spr.setTextDatum(ML_DATUM);
    spr.setTextColor(TH.funit_text, TH.bg);
    spr.drawString("MHz", ux, uy);
  }
  else
  {
    if(isSSB())
    {
      // SSB frequency
      char text[32];
      freq = freq * 1000 + currentBFO;
      sprintf(text, "%3.3lu", freq / 1000);
      spr.drawString(text, x, y, 7);
      spr.setTextDatum(ML_DATUM);
      sprintf(text, ".%3.3lu", freq % 1000);
      spr.drawString(text, 5+x, 15+y, 4);
    }
    else
    {
      // AM frequency
      spr.drawNumber(freq, x, y, 7);
      spr.setTextDatum(ML_DATUM);
      spr.drawString(".000", 5+x, 15+y, 4);
    }

    // SSB/AM frequencies are measured in kHz
    spr.setTextColor(TH.funit_text, TH.bg);
    spr.drawString("kHz", ux, uy);
  }
}

//
// Draw tuner scale
//
static void drawScale(uint32_t freq)
{
  spr.fillTriangle(156, 120, 160, 130, 164, 120, TH.scale_pointer);
  spr.drawLine(160, 130, 160, 169, TH.scale_pointer);

  spr.setTextDatum(MC_DATUM);
  spr.setTextColor(TH.scale_text, TH.bg);

  // Scale offset
  int16_t offset = (freq % 10) / 10.0 * 8;

  // Start drawing frequencies from the left
  freq = freq / 10 - 20;

  // Get band edges
  const Band *band = getCurrentBand();
  uint32_t minFreq = band->minimumFreq / 10;
  uint32_t maxFreq = band->maximumFreq / 10;

  for(int i=0 ; i<41 ; i++, freq++)
  {
    int16_t x = i * 8 - offset;
    if(freq >= minFreq && freq <= maxFreq)
    {
      uint16_t lineColor =
        i == 20 && (offset == 0 || ((freq % 5) == 0 && offset == 1)) ?
          TH.scale_pointer : TH.scale_line;

      if((freq % 10) == 0)
      {
        spr.drawLine(x, 169, x, 150, lineColor);
        spr.drawLine(x + 1, 169, x + 1, 150, lineColor);
        if(currentMode == FM)
          spr.drawFloat(freq / 10.0, 1, x, 140, 2);
        else if(freq >= 100)
          spr.drawFloat(freq / 100.0, 3, x, 140, 2);
        else
          spr.drawNumber(freq * 10, x, 140, 2);
      }
      else if((freq % 5) == 0 && (freq % 10) != 0)
      {
        spr.drawLine(x, 169, x, 155, lineColor);
        spr.drawLine(x + 1, 169, x + 1, 155, lineColor);
      }
      else
      {
        spr.drawLine(x, 169, x, 160, lineColor);
      }
    }
  }
}

//
// Draw S-meter
//
static void drawSMeter(int strength, int x, int y)
{
  spr.drawTriangle(x + 1, y + 1, x + 11, y + 1, x + 6, y + 6, TH.smeter_icon);
  spr.drawLine(x + 6, y + 1, x + 6, y + 14, TH.smeter_icon);

  for(int i=0 ; i<strength ; i++)
  {
    if(i<10)
      spr.fillRect(15+x + (i*4), 2+y, 2, 12, TH.smeter_bar);
    else
      spr.fillRect(15+x + (i*4), 2+y, 2, 12, TH.smeter_bar_plus);
  }
}

//
// Draw RDS station name (also CB channel, etc)
//
static void drawStationName(const char *name, int x, int y)
{
  spr.setTextDatum(TC_DATUM);
  spr.setTextColor(TH.rds_text, TH.bg);
  spr.drawString(name, x, y, 4);
}

//
// Draw screen according to given command
//
void drawScreen()
{
  if(sleepOn()) return;

  // Clear screen buffer
  spr.fillSprite(TH.bg);

  // Draw EEPROM write request icon
  drawEepromIndicator(SAVE_OFFSET_X, SAVE_OFFSET_Y);

  // About screen is a special case
  if(currentCmd==CMD_ABOUT)
  {
    drawAbout();
    return;
  }

  // Set font we are going to use
  spr.setFreeFont(&Orbitron_Light_24);

  // Draw band and mode
  drawBandAndMode(
    getCurrentBand()->bandName,
    bandModeDesc[currentMode],
    BAND_OFFSET_X, BAND_OFFSET_Y
  );

#ifdef THEME_EDITOR
  spr.setTextDatum(TR_DATUM);
  spr.setTextColor(TH.text_warn, TH.bg);
  spr.drawString("WARN", 319, RDS_OFFSET_Y, 4);
#endif

  // Draw frequency and units
  drawFrequency(
    currentFrequency,
    FREQ_OFFSET_X, FREQ_OFFSET_Y,
    FUNIT_OFFSET_X, FUNIT_OFFSET_Y
  );

  // Draw left-side menu/info bar
  // @@@ FIXME: Frequency display (above) intersects the side bar!
  drawSideBar(currentCmd, MENU_OFFSET_X, MENU_OFFSET_Y, MENU_DELTA_X);

  // Draw S-meter
  drawSMeter(getStrength(rssi), METER_OFFSET_X, METER_OFFSET_Y);

  // Indicate FM pilot detection
#ifndef THEME_EDITOR
  if((currentMode==FM) && rx.getCurrentPilot())
#endif
    spr.fillRect(15 + METER_OFFSET_X, 7+METER_OFFSET_Y, 4*17-2, 2, TH.bg);

  // Show station or channel name, if present
  if(*getStationName())
    drawStationName(getStationName(), RDS_OFFSET_X, RDS_OFFSET_Y);

  // Show radio text if present, else show frequency scale
  if(*getRadioText() || *getProgramInfo())
    drawRadioText(135, 160);
  else
    drawScale(isSSB()? (currentFrequency + currentBFO/1000) : currentFrequency);

#ifdef ENABLE_HOLDOFF
  // Update if not tuning
  if(!tuning_flag)
  {
    drawBattery(BATT_OFFSET_X, BATT_OFFSET_Y);
    spr.pushSprite(0, 0);
  }
#else
  // No hold off
  drawBattery(BATT_OFFSET_X, BATT_OFFSET_Y);
  spr.pushSprite(0, 0);
#endif
}
