#include "Common.h"
#include "Themes.h"
#include "Menu.h"

//
// Bands Menu
//
// TO CONFIGURE YOUR OWN BAND PLAN:
// Add new bands by inserting new lines in the table below. Remove
// bands by deleting lines. Change bands by editing lines below.
//
// NOTE:
// You have to RESET EEPROM after adding or removing lines in this
// table. Turn your receiver on with the encoder push button pressed
// at first time to RESET the EEPROM.
//

int bandIdx = 0;

// Band limits are expanded to align with the nearest tuning scale mark
Band bands[] =
{
  {"VHF",  FM_BAND_TYPE, FM,   6400, 10800, 10490, 1, 0, 0},
  // All band. LW, MW and SW (from 150kHz to 30MHz)
  {"LW",    MW_BAND_TYPE,  AM,   150,   283,   252, 1, 0, 0},
  {"MW1",   MW_BAND_TYPE,  AM,   283,  1800,   810, 3, 4, 0},
  {"160M",  MW_BAND_TYPE,  LSB, 1800,  2000,  1900, 0, 4, 0},
  {"SW0",   MW_BAND_TYPE,  LSB, 2000,  2300,  2200, 0, 4, 0},
  {"120M",  MW_BAND_TYPE,  LSB, 2300,  2500,  2400, 0, 4, 0},
  {"SW1",   MW_BAND_TYPE,  LSB, 2500,  3200,  2900, 0, 4, 0},
  {"90B",   SW_BAND_TYPE,  AM,  3200,  3400,  3300, 1, 4, 0},
  {"80M",   SW_BAND_TYPE,  LSB, 3400,  3800,  3500, 1, 4, 0},
  {"75B",   SW_BAND_TYPE,  AM,  3800,  4000,  3950, 1, 4, 0},
  {"SW2",   SW_BAND_TYPE,  AM,  4000,  4700,  4450, 1, 4, 0},
  {"60B",   SW_BAND_TYPE,  AM,  4700,  5100,  4750, 1, 4, 0},
  {"60M",   SW_BAND_TYPE,  LSB, 5100,  5450,  5250, 1, 4, 0},
  {"AIR1",  SW_BAND_TYPE,  USB, 5450,  5900,  5450, 0, 4, 0},
  {"49B",   SW_BAND_TYPE,  AM,  5900,  6525,  6000, 1, 4, 0},
  {"AIR2",  SW_BAND_TYPE,  USB, 6525,  7000,  6700, 0, 4, 0},
  {"40M",   SW_BAND_TYPE,  LSB, 7000,  7200,  7150, 0, 4, 0},
  {"41B",   SW_BAND_TYPE,  AM,  7200,  7450,  7250, 1, 4, 0},
  {"SW3",   SW_BAND_TYPE,  AM,  7450,  8815,  7550, 1, 4, 0},
  {"AIR3",  SW_BAND_TYPE,  USB, 8815,  9040,  8820, 0, 4, 0},
  {"SW4",   SW_BAND_TYPE,  AM,  9040,  9400,  9150, 1, 4, 0},
  {"31B",   SW_BAND_TYPE,  AM,  9400, 10000,  9650, 1, 4, 0},
  {"30M",   SW_BAND_TYPE, LSB, 10000, 10200, 10125, 0, 4, 0},
  {"SW5",   SW_BAND_TYPE,  AM, 10200, 11600, 10300, 1, 4, 0},
  {"25B",   SW_BAND_TYPE,  AM, 11600, 12100, 11850, 1, 4, 0},
  {"SW6",   SW_BAND_TYPE,  AM, 12100, 13570, 12850, 1, 4, 0},
  {"22B",   SW_BAND_TYPE,  AM, 13500, 14000, 13650, 1, 4, 0},
  {"20M",   SW_BAND_TYPE, USB, 14000, 14400, 14100, 0, 4, 0},
  {"19B",   SW_BAND_TYPE, AM,  14100, 15900, 15100, 1, 4, 0},
  {"SW7",   SW_BAND_TYPE, AM,  15900, 17500, 15950, 1, 4, 0},
  {"16B",   SW_BAND_TYPE, AM,  17500, 18000, 17650, 1, 4, 0},
  {"17M",   SW_BAND_TYPE, USB, 18000, 18200, 18115, 0, 4, 0},
  {"SW8",   SW_BAND_TYPE, AM,  18200, 18900, 18250, 1, 4, 0},
  {"15B",   SW_BAND_TYPE, AM,  18900, 19100, 18950, 1, 4, 0},
  {"SW9",   SW_BAND_TYPE, AM,  19100, 21000, 19950, 1, 4, 0},
  {"15M",   SW_BAND_TYPE, USB, 21000, 21500, 21225, 0, 4, 0},
  {"13B",   SW_BAND_TYPE, AM,  21500, 21900, 21650, 1, 4, 0},
  {"SW10",  SW_BAND_TYPE, AM,  21900, 24800, 21950, 1, 4, 0},
  {"12M",   SW_BAND_TYPE, USB, 24800, 25000, 24940, 0, 4, 0},
  {"SW11",  SW_BAND_TYPE, AM,  25000, 25600, 25500, 1, 4, 0},
  {"11B",   SW_BAND_TYPE, AM,  25600, 26100, 25850, 1, 4, 0},
  {"CB",    SW_BAND_TYPE, AM,  26100, 28000, 27135, 0, 4, 0},
  {"10M",   SW_BAND_TYPE, USB, 28000, 30000, 28500, 0, 4, 0}
};
int getTotalBands() { return(ITEM_COUNT(bands)); }
Band *getCurrentBand() { return(&bands[bandIdx]); }

//
// Main Menu
//

#define MENU_MODE         0
#define MENU_BAND         1
#define MENU_VOLUME       2
#define MENU_STEP         3
#define MENU_MEMORY       4
#define MENU_MUTE         5
#define MENU_BW           6
#define MENU_AGC_ATT      7
#define MENU_AVC          8
#define MENU_SOFTMUTE     9
#define MENU_SETTINGS     10

int8_t menuIdx = MENU_VOLUME;

static const char *menu[] =
{
  "Mode",
  "Band",
  "Volume",
  "Step",
  "Memory",
  "Mute",
  "Bandwidth",
  "AGC/ATTN",
  "AVC",
  "SoftMute",
  "Settings",
};

//
// Settings Menu
//

#define MENU_BRIGHTNESS   0
#define MENU_CALIBRATION  1
#define MENU_THEME        2
#define MENU_RDS          3
#define MENU_SLEEP        4
#define MENU_SLEEPMODE    5
#define MENU_ABOUT        6

int8_t settingsIdx = MENU_BRIGHTNESS;

static const char *settings[] =
{
  "Brightness",
  "Calibration",
  "Theme",
  "RDS",
  "Sleep",
  "Sleep Mode",
  "About",
};

//
// Mode Menu
//

const char *bandModeDesc[] = { "FM", "LSB", "USB", "AM" };

//
// Memory Menu
//

uint8_t memoryIdx = 0;
Memory memories[32];
Memory newMemory;

int getTotalMemories() { return(ITEM_COUNT(memories)); }

//
// RDS Menu
//

uint8_t rdsModeIdx = 0;
static const RDSMode rdsMode[] =
{
  { RDS_PS, "PS"},
  { RDS_PS | RDS_CT, "PS+CT" },
  { RDS_PS | RDS_PI, "PS+PI" },
  { RDS_PS | RDS_PI | RDS_CT, "PS+PI+CT" },
  { RDS_PS | RDS_PI | RDS_RT | RDS_PT, "PS+PI+RT" },
  { RDS_PS | RDS_PI | RDS_RT | RDS_PT | RDS_CT, "ALL (EU)" },
  { RDS_PS | RDS_PI | RDS_RT | RDS_PT | RDS_CT | RDS_RBDS, "ALL (US)" },
};

uint8_t getRDSMode() { return(rdsMode[rdsModeIdx].mode); }

//
// Sleep Mode Menu
//

uint8_t sleepModeIdx = SLEEP_LOCKED;
static const char *sleepModeDesc[] = { "Locked", "Unlocked" }; //  "Light", "Deep"

//
// Step Menu
//

// FM (kHz * 10)
static const Step fmSteps[] =
{
  {   1, "10k"  },
  {   5, "50k"  },
  {  10, "100k" },
  {  20, "200k" },
  { 100, "1M"   },
};

// SSB (Hz)
static const Step ssbSteps[] =
{
  {    10, "10"  },
  {    25, "25"  },
  {    50, "50"  },
  {   100, "100" },
  {   500, "500" },
  {  1000, "1k"  },
  {  5000, "5k"  },
  {  9000, "9k"  },
  { 10000, "10k" },
};

static const uint8_t ssbFastSteps[] =
{
  3, //  10Hz -> 100Hz
  3, //  25Hz -> 100Hz
  4, //  50Hz -> 500Hz
  5, // 100Hz -> 1kHz
  6, // 500Hz -> 5kHz
  6, //  1kHz -> 5kHz
  8, //  5kHz -> 10kHz
  7, //  9kHz -> 9kHz
  8, // 10kHz -> 10kHz
};

// AM (kHz)
static const Step amSteps[] =
{
  {    1, "1k"   },
  {    5, "5k"   },
  {    9, "9k"   },
  {   10, "10k"  },
  {   50, "50k"  },
  {  100, "100k" },
  { 1000, "1M"   },
};

static const Step *steps[4] = { fmSteps, ssbSteps, ssbSteps, amSteps };
static uint8_t stepIdx[4] = { 2, 5, 5, 1 };

const Step *getCurrentStep(bool fast)
{
  uint8_t idx = stepIdx[currentMode];
  return(&steps[currentMode][fast && isSSB()? ssbFastSteps[idx]:idx]);
}

static int getLastStep(int mode)
{
  switch(mode)
  {
    case FM:  return(LAST_ITEM(fmSteps));
    case LSB: return(LAST_ITEM(ssbSteps));
    case USB: return(LAST_ITEM(ssbSteps));
    case AM:  return(LAST_ITEM(amSteps));
  }

  return(0);
}

//
// Bandwidth Menu
//

static const Bandwidth fmBandwidths[] =
{
  { 0, "Auto" }, // Automatic - default
  { 1, "110k" }, // Force wide (110 kHz) channel filter.
  { 2, "84k"  },
  { 3, "60k"  },
  { 4, "40k"  }
};

static const Bandwidth ssbBandwidths[] =
{
  { 4, "0.5k" },
  { 5, "1.0k" },
  { 0, "1.2k" },
  { 1, "2.2k" },
  { 2, "3.0k" },
  { 3, "4.0k" }
};

static const Bandwidth amBandwidths[] =
{
  { 4, "1.0k" },
  { 5, "1.8k" },
  { 3, "2.0k" },
  { 6, "2.5k" },
  { 2, "3.0k" },
  { 1, "4.0k" },
  { 0, "6.0k" }
};

static const Bandwidth *bandwidths[4] =
{
  fmBandwidths, ssbBandwidths, ssbBandwidths, amBandwidths
};

static uint8_t bwIdx[4] = { 0, 4, 4, 4 };

const Bandwidth *getCurrentBandwidth()
{
  return(&bandwidths[currentMode][bwIdx[currentMode]]);
}

static int getLastBandwidth(int mode)
{
  switch(mode)
  {
    case FM:  return(LAST_ITEM(fmBandwidths));
    case LSB: return(LAST_ITEM(ssbBandwidths));
    case USB: return(LAST_ITEM(ssbBandwidths));
    case AM:  return(LAST_ITEM(amBandwidths));
  }

  return(0);
}

static void setBandwidth()
{
  uint8_t idx = getCurrentBandwidth()->idx;

  switch(currentMode)
  {
    case FM:
      rx.setFmBandwidth(idx);
      break;
    case AM:
      rx.setBandwidth(idx, 1);
      break;
    case LSB:
    case USB:
      // Set Audio
      rx.setSSBAudioBandwidth(idx);
      // If audio bandwidth selected is about 2 kHz or below, it is
      // recommended to set Sideband Cutoff Filter to 0.
      rx.setSSBSidebandCutoffFilter(idx==0 || idx==4 || idx==5? 0 : 1);
      break;
  }
}

//
// Utility functions to change menu values
//

static inline int min(int x, int y) { return(x<y? x:y); }

static inline int wrap_range(int v, int dir, int vMin, int vMax)
{
  v += dir;
  v  = v>vMax? vMin + (v - vMax - 1) : v<vMin? vMax - (vMin - v - 1) : v;
  return(v);
}

static inline int clamp_range(int v, int dir, int vMin, int vMax)
{
  v += dir;
  v  = v>vMax? vMax : v<vMin? vMin : v;
  return(v);
}

//
// Encoder input handlers
//

void doVolume(int dir)
{
  if(dir>0) rx.volumeUp(); else if(dir<0) rx.volumeDown();
  volume = rx.getVolume();
}

static void doTheme(int dir)
{
  themeIdx = wrap_range(themeIdx, dir, 0, getTotalThemes() - 1);
}

void doAvc(int dir)
{
  // Only allow for AM and SSB modes
  if(currentCmd==FM) return;

  if(isSSB())
  {
    SsbAvcIdx = wrap_range(SsbAvcIdx, 2*dir, 12, 90);
    rx.setAvcAmMaxGain(SsbAvcIdx);
  }
  else
  {
    AmAvcIdx = wrap_range(AmAvcIdx, 2*dir, 12, 90);
    rx.setAvcAmMaxGain(AmAvcIdx);
  }
}

void doCal(int dir)
{
  bands[bandIdx].bandCal = clamp_range(bands[bandIdx].bandCal, 10*dir, -MAX_CAL, MAX_CAL);

  // If in SSB mode set the SI4732/5 BFO value
  // This adjusts the BFO while in the calibration menu
  if(isSSB()) updateBFO(currentBFO);
}

void doBrt(int dir)
{

  currentBrt = clamp_range(currentBrt, 5*dir, 10, 255);
  if(!sleepOn()) ledcWrite(PIN_LCD_BL, currentBrt);
}

static void doSleep(int dir)
{
  currentSleep = clamp_range(currentSleep, 5*dir, 0, 255);
}

static void doSleepMode(int dir)
{
  sleepModeIdx = wrap_range(sleepModeIdx, dir, 0, LAST_ITEM(sleepModeDesc));
}

static void doRDSMode(int dir)
{
  rdsModeIdx = wrap_range(rdsModeIdx, dir, 0, LAST_ITEM(rdsMode));
  if(!(getRDSMode() & RDS_CT)) clockReset();
}

bool tuneToMemory(const Memory *memory)
{
  // Must have frequency
  if(!memory->freq) return(false);
  // Must have valid band index
  if(memory->band>=getTotalBands()) return(false);
  // Band must contain frequency and modulation
  if(!isMemoryInBand(&bands[memory->band], memory)) return(false);

  // Save current band settings
  bands[bandIdx].currentFreq    = currentFrequency + currentBFO / 1000;
  bands[bandIdx].currentStepIdx = stepIdx[currentMode];

  // Load frequency and modulation from memory slot
  bands[memory->band].currentFreq = memory->freq;
  bands[memory->band].bandMode    = memory->mode;

  // Enable the new band
  selectBand(memory->band);
  return(true);
}

static void doMemory(int dir)
{
  memoryIdx = wrap_range(memoryIdx, dir, 0, LAST_ITEM(memories));
  if(!tuneToMemory(&memories[memoryIdx])) tuneToMemory(&newMemory);
}

static void clickMemory(uint8_t idx)
{
  // Must have a valid index
  if(idx>LAST_ITEM(memories)) return;

  // If clicking on an empty memory slot, save to it
  if(!memories[idx].freq)
  {
    memories[idx] = newMemory;
    currentCmd = CMD_NONE;
  }
  // If clicking on the same memory slot, delete it
  else if(!memcmp(&memories[idx], &newMemory, sizeof(newMemory)))
  {
    memories[idx].freq = 0;
    currentCmd = CMD_NONE;
  }
  // Do nothing, memory slot already activated in doMemory()
  else
  {
    currentCmd = CMD_NONE;
  }
}

void doStep(int dir)
{
  uint8_t idx = stepIdx[currentMode];

  idx = wrap_range(idx, dir, 0, getLastStep(currentMode));
  bands[bandIdx].currentStepIdx = stepIdx[currentMode] = idx;

  rx.setFrequencyStep(steps[currentMode][idx].step);

  // Max 10kHz for spacing
  if(currentMode!=FM) rx.setSeekAmSpacing(5);
}

void doAgc(int dir)
{
  if(currentMode==FM)
    agcIdx = FmAgcIdx = wrap_range(FmAgcIdx, dir, 0, 27);
  else if(isSSB())
    agcIdx = SsbAgcIdx = wrap_range(SsbAgcIdx, dir, 0, 1);
  else
    agcIdx = AmAgcIdx = wrap_range(AmAgcIdx, dir, 0, 37);

  // Process agcIdx to generate disableAgc and agcIdx
  // agcIdx     0 1 2 3 4 5 6  ..... n    (n:    FM = 27, AM = 37, SSB = 1)
  // agcNdx     0 0 1 2 3 4 5  ..... n -1 (n -1: FM = 26, AM = 36, SSB = 0)
  // disableAgc 0 1 1 1 1 1 1  ..... 1

  // if true, disable AGC; else, AGC is enabled
  disableAgc = agcIdx>0? 1 : 0;
  agcNdx     = agcIdx>1? agcIdx - 1 : 0;

  // Configure SI4732/5 (if agcNdx = 0, no attenuation)
  rx.setAutomaticGainControl(disableAgc, agcNdx);
}

void doMode(int dir)
{
  // This is our current mode for the current band
  currentMode = bands[bandIdx].bandMode;

  // Cannot change away from FM mode
  if(currentMode==FM) return;

  // Change AM/LSB/USB modes, do not allow FM mode
  do
    currentMode = wrap_range(currentMode, dir, 0, LAST_ITEM(bandModeDesc));
  while(currentMode==FM);

  // Save current band settings
  bands[bandIdx].currentFreq = currentFrequency + currentBFO / 1000;
  bands[bandIdx].currentStepIdx = stepIdx[currentMode];
  bands[bandIdx].bandMode = currentMode;

  // Enable the new band
  selectBand(bandIdx);
}

void doSoftMute(int dir)
{
  // Nothing to do if FM mode
  if(currentMode==FM) return;

  if(isSSB())
    softMuteMaxAttIdx = SsbSoftMuteIdx = wrap_range(SsbSoftMuteIdx, dir, 0, 32);
  else
    softMuteMaxAttIdx = AmSoftMuteIdx = wrap_range(AmSoftMuteIdx, dir, 0, 32);

  rx.setAmSoftMuteMaxAttenuation(softMuteMaxAttIdx);
}

void doBand(int dir)
{
  // Save current band settings
  bands[bandIdx].currentFreq = currentFrequency + currentBFO / 1000;
  bands[bandIdx].currentStepIdx = stepIdx[currentMode];
  bands[bandIdx].bandMode = currentMode;

  // Change band
  bandIdx = wrap_range(bandIdx, dir, 0, LAST_ITEM(bands));

  // Enable the new band
  selectBand(bandIdx);
}

void doBandwidth(int dir)
{
  uint8_t idx = bwIdx[currentMode];

  idx = wrap_range(idx, dir, 0, getLastBandwidth(currentMode));
  bands[bandIdx].bandwidthIdx = bwIdx[currentMode] = idx;
  setBandwidth();
}

//
// Handle encoder input in menu
//

static void doMenu(int dir)
{
  menuIdx = wrap_range(menuIdx, dir, 0, LAST_ITEM(menu));
}

static void clickMenu(int cmd)
{
  // No command yet
  currentCmd = CMD_NONE;

  switch(cmd)
  {
    case MENU_STEP:     currentCmd = CMD_STEP;      break;
    case MENU_MODE:     currentCmd = CMD_MODE;      break;
    case MENU_BW:       currentCmd = CMD_BANDWIDTH; break;
    case MENU_AGC_ATT:  currentCmd = CMD_AGC;       break;
    case MENU_BAND:     currentCmd = CMD_BAND;      break;
    case MENU_SETTINGS: currentCmd = CMD_SETTINGS;  break;

    case MENU_MEMORY:
      currentCmd = CMD_MEMORY;
      newMemory.freq = currentFrequency + currentBFO / 1000;
      newMemory.mode = currentMode;
      newMemory.band = bandIdx;
      doMemory(0);
      break;

    case MENU_SOFTMUTE:
      // No soft mute in FM mode
      if(currentMode!=FM) currentCmd = CMD_SOFTMUTE;
      break;

    case MENU_AVC:
      // No AVC in FM mode
      if(currentMode!=FM) currentCmd = CMD_AVC;
      break;

    case MENU_VOLUME:
      // Unmute sound when changing volume
      muteOn(false);
      currentCmd = CMD_VOLUME;
      break;

    case MENU_MUTE:
      muteOn(!muteOn());
      break;
  }
}

static void doSettings(int dir)
{
  settingsIdx = wrap_range(settingsIdx, dir, 0, LAST_ITEM(settings));
}

static void clickSettings(int cmd)
{
  // No command yet
  currentCmd = CMD_NONE;

  switch(cmd)
  {
    case MENU_BRIGHTNESS: currentCmd = CMD_BRT; break;
    case MENU_CALIBRATION:
      if(isSSB()) currentCmd = CMD_CAL;
      break;
    case MENU_THEME:      currentCmd = CMD_THEME;     break;
    case MENU_RDS:        currentCmd = CMD_RDS;       break;
    case MENU_SLEEP:      currentCmd = CMD_SLEEP;     break;
    case MENU_SLEEPMODE:  currentCmd = CMD_SLEEPMODE; break;
    case MENU_ABOUT:      currentCmd = CMD_ABOUT;     break;
  }
}

bool doSideBar(uint16_t cmd, int dir)
{
  // Ignore idle encoder
  if(!dir) return(false);

  switch(cmd)
  {
    case CMD_MENU:      doMenu(dir);break;
    case CMD_MODE:      doMode(dir);break;
    case CMD_STEP:      doStep(dir);break;
    case CMD_AGC:       doAgc(dir);break;
    case CMD_BANDWIDTH: doBandwidth(dir);break;
    case CMD_VOLUME:    doVolume(dir);break;
    case CMD_SOFTMUTE:  doSoftMute(dir);break;
    case CMD_BAND:      doBand(dir);break;
    case CMD_AVC:       doAvc(dir);break;
    case CMD_SETTINGS:  doSettings(dir);break;
    case CMD_BRT:       doBrt(dir);break;
    case CMD_CAL:       doCal(dir);break;
    case CMD_THEME:     doTheme(dir);break;
    case CMD_RDS:       doRDSMode(dir);break;
    case CMD_MEMORY:    doMemory(dir);break;
    case CMD_SLEEP:     doSleep(dir);break;
    case CMD_SLEEPMODE: doSleepMode(dir);break;
    case CMD_ABOUT:     return(true);
    default:            return(false);
  }

  // Encoder input handled
  return(true);
}

bool clickSideBar(uint16_t cmd)
{
  switch(cmd)
  {
    case CMD_MENU:     clickMenu(menuIdx);break;
    case CMD_SETTINGS: clickSettings(settingsIdx);break;
    case CMD_MEMORY:   clickMemory(memoryIdx);break;
    default:           return(false);
  }

  // Encoder input handled
  return(true);
}

void clickVolume()
{
  clickMenu(MENU_VOLUME);
}

//
// Selecting given band
//

void selectBand(uint8_t idx, bool drawLoadingSSB)
{
  // Set band and mode
  bandIdx = min(idx, LAST_ITEM(bands));
  currentMode = bands[bandIdx].bandMode;

  // Set tuning step
  stepIdx[currentMode] = bands[bandIdx].currentStepIdx;
  rx.setFrequencyStep(getCurrentStep()->step);

  // Load SSB patch as needed
  if(isSSB())
    loadSSB(getCurrentBandwidth()->idx, drawLoadingSSB);
  else
    unloadSSB();

  // Set bandwidth for the current mode
  setBandwidth();

  // Switch radio to the selected band
  useBand(&bands[bandIdx]);
}

//
// Draw functions
//

static void drawCommon(const char *title, int x, int y, int sx)
{
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_hdr, TH.menu_bg);
  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.menu_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.menu_bg);

  spr.drawString(title, 40+x+(sx/2), 12+y, 2);
  spr.drawLine(1+x, 23+y, 76+sx, 23+y, TH.menu_border);

  spr.setTextFont(0);
  spr.setTextColor(TH.menu_item, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_hl_bg);
}

static void drawMenu(int x, int y, int sx)
{
  spr.setTextDatum(MC_DATUM);

  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.menu_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.menu_bg);
  spr.setTextColor(TH.menu_hdr, TH.menu_bg);

  spr.drawString("Menu", 40+x+(sx/2), 12+y, 2);
  spr.drawLine(1+x, 23+y, 76+sx, 23+y, TH.menu_border);

  spr.setTextFont(0);
  spr.setTextColor(TH.menu_item, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_hl_bg);

  int count = ITEM_COUNT(menu);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(menu[abs((menuIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawSettings(int x, int y, int sx)
{
  spr.setTextDatum(MC_DATUM);

  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.menu_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.menu_bg);
  spr.setTextColor(TH.menu_hdr, TH.menu_bg);
  spr.drawString("Settings", 40+x+(sx/2), 12+y, 2);
  spr.drawLine(1+x, 23+y, 76+sx, 23+y, TH.menu_border);

  spr.setTextFont(0);
  spr.setTextColor(TH.menu_item, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_hl_bg);

  int count = ITEM_COUNT(settings);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(settings[abs((settingsIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawMode(int x, int y, int sx)
{
  drawCommon(menu[MENU_MODE], x, y, sx);

  int count = ITEM_COUNT(bandModeDesc);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    if((currentMode!=FM) || (i==0))
      spr.drawString(bandModeDesc[abs((currentMode+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawStep(int x, int y, int sx)
{
  int count = getLastStep(currentMode) + 1;
  int idx   = stepIdx[currentMode] + count;

  drawCommon(menu[MENU_STEP], x, y, sx);

  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(steps[currentMode][abs((idx+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawBand(int x, int y, int sx)
{
  drawCommon(menu[MENU_BAND], x, y, sx);

  int count = ITEM_COUNT(bands);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(bands[abs((bandIdx+count+i)%count)].bandName, 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawBandwidth(int x, int y, int sx)
{
  int count = getLastBandwidth(currentMode) + 1;
  int idx   = bwIdx[currentMode] + count;

  drawCommon(menu[MENU_BW], x, y, sx);

  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(bandwidths[currentMode][abs((idx+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawSleepMode(int x, int y, int sx)
{
  drawCommon(settings[MENU_SLEEPMODE], x, y, sx);

  int count = ITEM_COUNT(sleepModeDesc);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(sleepModeDesc[abs((sleepModeIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawTheme(int x, int y, int sx)
{
  drawCommon(settings[MENU_THEME], x, y, sx);

  int count = getTotalThemes();
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(theme[abs((themeIdx+count+i)%count)].name, 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawRDSMode(int x, int y, int sx)
{
  drawCommon(settings[MENU_RDS], x, y, sx);

  int count = ITEM_COUNT(rdsMode);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    spr.drawString(rdsMode[abs((rdsModeIdx+count+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawMemory(int x, int y, int sx)
{
  char label_memory[16];
  sprintf(label_memory, "%s %2.2d", menu[MENU_MEMORY], memoryIdx + 1);
  drawCommon(label_memory, x, y, sx);

  int count = ITEM_COUNT(memories);
  for(int i=-2 ; i<3 ; i++)
  {
    int j = abs((memoryIdx+count+i)%count);

    if(i==0)
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    else
      spr.setTextColor(TH.menu_item, TH.menu_bg);

    char buf[16];
    const char *text = buf;

    if(i==0 && !memories[j].freq)
      text = "Add";
    else if(i==0 && !memcmp(&memories[j], &newMemory, sizeof(newMemory)))
      text = "Delete";
    else if(!memories[j].freq)
      text = "- - -";
    else if(memories[j].mode==FM)
      sprintf(buf, "%3.2f %s", memories[j].freq / 100.0, bandModeDesc[memories[j].mode]);
    else
      sprintf(buf, "%5d %s", memories[j].freq, bandModeDesc[memories[j].mode]);

    spr.drawString(text, 40+x+(sx/2), 64+y+(i*16), 2);
  }
}

static void drawVolume(int x, int y, int sx)
{
  drawCommon(menu[MENU_VOLUME], x, y, sx);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_bg);
  spr.drawNumber(volume, 40+x+(sx/2), 66+y, 7);
}

static void drawAgc(int x, int y, int sx)
{
  drawCommon(menu[MENU_AGC_ATT], x, y, sx);

  for(int i=-2 ; i<3 ; i++)
  {
    spr.setTextColor(TH.menu_param, TH.menu_bg);
    spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_bg);
    // G8PTN: Read back value is not used
    // rx.getAutomaticGainControl();
    if(!agcNdx && !agcIdx)
    {
      spr.setFreeFont(&Orbitron_Light_24);
      spr.drawString("AGC", 40+x+(sx/2), 48+y);
      spr.drawString("On", 40+x+(sx/2), 72+y);
      spr.setTextFont(0);
    }
    else
    {
      char text[16];
      sprintf(text, "%2.2d", agcNdx);
      spr.drawString(text, 40+x+(sx/2), 60+y, 7);
    }
  }
}

static void drawSoftMuteMaxAtt(int x, int y, int sx)
{
  drawCommon(menu[MENU_SOFTMUTE], x, y, sx);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_bg);
  spr.drawString("Max Attn", 40+x+(sx/2), 32+y, 2);
  spr.drawNumber(softMuteMaxAttIdx, 40+x+(sx/2), 60+y, 4);
  spr.drawString("dB", 40+x+(sx/2), 90+y, 4);
}

static void drawCal(int x, int y, int sx)
{
  drawCommon(menu[MENU_CALIBRATION], x, y, sx);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_bg);
  spr.drawNumber(getCurrentBand()->bandCal, 40+x+(sx/2), 60+y, 4);
  spr.drawString("Hz", 40+x+(sx/2), 90+y, 4);
}

static void drawAvc(int x, int y, int sx)
{
  drawCommon(menu[MENU_AVC], x, y, sx);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_bg);
  spr.drawString("Max Gain", 40+x+(sx/2), 32+y, 2);

  // Only show AVC for AM and SSB modes
  if(currentMode!=FM)
  {
    int currentAvc = isSSB()? SsbAvcIdx : AmAvcIdx;
    spr.drawNumber(currentAvc, 40+x+(sx/2), 60+y, 4);
    spr.drawString("dB", 40+x+(sx/2), 90+y, 4);
  }
}

static void drawBrt(int x, int y, int sx)
{
  drawCommon(settings[MENU_BRIGHTNESS], x, y, sx);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_bg);
  spr.drawNumber(currentBrt, 40+x+(sx/2), 60+y, 4);
}

static void drawSleep(int x, int y, int sx)
{
  drawCommon(settings[MENU_SLEEP], x, y, sx);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_bg);
  spr.drawNumber(currentSleep, 40+x+(sx/2), 60+y, 4);
}

static void drawInfo(int x, int y, int sx)
{
  char text[16];

  // Info box
  spr.setTextDatum(ML_DATUM);
  spr.setTextColor(TH.box_text, TH.box_bg);
  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.box_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.box_bg);

  spr.drawString("Step:", 6+x, 64+y+(-3*16), 2);
  spr.drawString(getCurrentStep()->desc, 48+x, 64+y+(-3*16), 2);

  spr.drawString("BW:", 6+x, 64+y+(-2*16), 2);
  spr.drawString(getCurrentBandwidth()->desc, 48+x, 64+y+(-2*16), 2);

  if(!agcNdx && !agcIdx)
  {
    spr.drawString("AGC:", 6+x, 64+y+(-1*16), 2);
    spr.drawString("On", 48+x, 64+y+(-1*16), 2);
  }
  else
  {
    sprintf(text, "%2.2d", agcNdx);
    spr.drawString("Att:", 6+x, 64+y+(-1*16), 2);
    spr.drawString(text, 48+x, 64+y+(-1*16), 2);
  }

  spr.drawString("Vol:", 6+x, 64+y+(0*16), 2);
  if(muteOn())
  {
    //spr.setTextDatum(MR_DATUM);
    spr.setTextColor(TH.box_off_text, TH.box_off_bg);
    spr.drawString("Muted", 48+x, 64+y+(0*16), 2);
    spr.setTextColor(TH.box_text, TH.box_bg);
  }
  else
  {
    spr.setTextColor(TH.box_text, TH.box_bg);
    spr.drawNumber(volume, 48+x, 64+y+(0*16), 2);
  }

  // Draw RDS PI code, if present
  uint16_t piCode = getRdsPiCode();
  if(piCode && currentMode == FM)
  {
    sprintf(text, "%04X", piCode);
    spr.drawString("PI:", 6+x, 64+y + (1*16), 2);
    spr.drawString(text, 48+x, 64+y + (1*16), 2);
  }
  else
  {
    spr.drawString("AVC:", 6+x, 64+y + (1*16), 2);

    if(currentMode==FM)
      sprintf(text, "n/a");
    else if(isSSB())
      sprintf(text, "%2.2ddB", SsbAvcIdx);
    else
      sprintf(text, "%2.2ddB", AmAvcIdx);

    spr.drawString(text, 48+x, 64+y + (1*16), 2);
  }

  // Draw current time
  if((getRDSMode() & RDS_CT) && clockGet())
  {
    spr.drawString("Time:", 6+x, 64+y+(2*16), 2);
    spr.drawString(clockGet(), 48+x, 64+y+(2*16), 2);
  }
}

//
// Draw side bar (menu or information)
//
void drawSideBar(uint16_t cmd, int x, int y, int sx)
{
  if(sleepOn()) return;

  switch(cmd)
  {
    case CMD_MENU:      drawMenu(x, y, sx);      break;
    case CMD_SETTINGS:  drawSettings(x, y, sx);  break;
    case CMD_MODE:      drawMode(x, y, sx);      break;
    case CMD_STEP:      drawStep(x, y, sx);      break;
    case CMD_BAND:      drawBand(x, y, sx);      break;
    case CMD_BANDWIDTH: drawBandwidth(x, y, sx); break;
    case CMD_THEME:     drawTheme(x, y, sx);     break;
    case CMD_VOLUME:    drawVolume(x, y, sx);    break;
    case CMD_AGC:       drawAgc(x, y, sx);       break;
    case CMD_SOFTMUTE:  drawSoftMuteMaxAtt(x, y, sx);break;
    case CMD_CAL:       drawCal(x, y, sx);       break;
    case CMD_AVC:       drawAvc(x, y, sx);       break;
    case CMD_BRT:       drawBrt(x, y, sx);       break;
    case CMD_RDS:       drawRDSMode(x, y, sx);   break;
    case CMD_MEMORY:    drawMemory(x, y, sx);    break;
    case CMD_SLEEP:     drawSleep(x, y, sx);     break;
    case CMD_SLEEPMODE: drawSleepMode(x, y, sx); break;
    default:            drawInfo(x, y, sx);      break;
  }
}
