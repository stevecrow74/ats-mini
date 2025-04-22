#include "Common.h"
#include "Menu.h"

// CB frequency range
#define MIN_CB_FREQUENCY 26060
#define MAX_CB_FREQUENCY 29665

//
// Named frequencies, sorted by increasing frequency!
//
static const NamedFreq namedFrequencies[] =
{
  {  1089, "TalkSport"  }, {  2616, "WeFax"  }, {  3050, "Weather"  }, {  3105, "Weather" },
  {  3413, "Weather" }, {  4608, "WeFax" }, {  5450, "Weather" }, {  5505, "Weather" },
  {  7878, "WeFax" }, {  8040, "WeFax" }, {  8957, "Weather" }, {  10051, "Weather" },
  {  7165, "SSTV" }, {  7171, "SSTV" }, { 11083, "WeFax"  }, { 14074, "FT8" },
  { 14230, "SSTV" }, { 18100, "FT8"  }, { 21074, "FT8"  },   { 24915, "FT8" },
  { 27700, "SSTV" }, { 28074, "FT8"  }, { 28680, "SSTV" },
};

//
// CB channel mappings
//
static const char *cbChannelNumber[] =
{
  "1",  "2",  "3",  "41",
  "4",  "5",  "6",  "7",  "42",
  "8",  "9",  "10", "11", "43",
  "12", "13", "14", "15", "44",
  "16", "17", "18", "19", "45",
  "20", "21", "22", "23",
  "24", "25", "26", "27",
  "28", "29", "30", "31",
  "32", "33", "34", "35",
  "36", "37", "38", "39",
  "40",
};

//
// RDS program types
//
const char *rdsProgramTypes[32] =
{
  "None", "News", "Information", "Sports",
  "Talk", "Rock", "Classic Rock", "Adult Hits",
  "Soft Rock", "Top 40", "Country", "Oldies",
  "Soft", "Nostalgia", "Jazz", "Classical",
  "R & B", "Soft R & B", "Foreign Language", "Religious Music",
  "Religious Talk", "Personality", "Public", "College",
  0, 0, 0, 0,
  0, "Weather", "TEST", "! ALERT !"
};

static char bufStationName[50]  = "";
static char bufRadioText[100]   = "";
static char bufProgramInfo[100] = "";
static uint16_t piCode = 0x0000;

const char *getStationName()
{
#ifdef THEME_EDITOR
  return("*STATION*");
#else
  return(getRDSMode() & RDS_PS? bufStationName : "");
#endif
}

const char *getRadioText()
{
  return(getRDSMode() & RDS_RT? bufRadioText : "");
}

const char *getProgramInfo()
{
  return(getRDSMode() & RDS_RT? bufProgramInfo : "");
}

uint16_t getRdsPiCode()
{
  return(getRDSMode() & RDS_PI? piCode : 0x0000);
}

void clearStationInfo()
{
  bufStationName[0] = '\0';
  bufProgramInfo[0] = '\0';
  bufRadioText[0]   = '\0'; // Multiline!
  bufRadioText[1]   = '\0';
  piCode = 0x0000;
}

static bool showStationName(const char *stationName)
{
  if(stationName && strcmp(bufStationName, stationName))
  {
    strcpy(bufStationName, stationName);
    return(true);
  }

  return(false);
}

static bool showRadioText(const char *radioText)
{
  int i, j;

  if(radioText && strcmp(bufRadioText, radioText))
  {
    // Terminate at 0x0D, split into lines by 0x0A
    for(i=j=0 ; (i<64) && radioText[i] && radioText[i]!=0x0D ; i++)
      if((radioText[i]==0x0A) || ((radioText[i]==' ') && (j>=32)))
      {
        bufRadioText[i] = '\0';
        j = 0;
      }
      else
      {
        bufRadioText[i] = radioText[i];
        j++;
      }

    // Terminate multitline text with two zeros
    bufRadioText[i] = '\0';
    bufRadioText[i+1] = '\0';

    return(true);
  }

  return(false);
}

static bool showProgramInfo(const char *programInfo)
{
  if(programInfo && strcmp(bufProgramInfo, programInfo))
  {
    strcpy(bufProgramInfo, programInfo);
    return(true);
  }

  return(false);
}

static bool showRdsProgramType(uint8_t rdsProgramType)
{
  // Filter out invalid or non-existant RDS program types
  const char *text =
    rdsProgramType >= ITEM_COUNT(rdsProgramTypes)? ""
  : !rdsProgramTypes[rdsProgramType]? ""
  : rdsProgramTypes[rdsProgramType];

  return(showProgramInfo(text));
}

static bool showRdsPiCode(uint16_t rdsPiCode)
{
  if(rdsPiCode!=piCode)
  {
    piCode = rdsPiCode;
    return(true);
  }

  return(false);
}

static bool showRdsTime(const char *rdsTime)
{
  if(!rdsTime) return(false);

  // The standard RDS time format is “HH:MM”.
  // or sometimes more complex like “DD.MM.YY,HH:MM”.
  const char *timeField = strstr(rdsTime, ":");

  // If we find a valid time format...
  if(timeField && (timeField>=rdsTime+2) && timeField[1] && timeField[2])
  {
    // Extract hours and minutes
    int hours = (timeField[-2] - '0') * 10 + timeField[-1] - '0';
    int mins  = (timeField[1] - '0') * 10 + timeField[2] - '0';

    // If hours and minutes are valid, update clock
    if(hours>=0 && hours<24 && mins>=0 && mins<60)
      return(clockSet(hours, mins));
  }

  // No time
  return(false);
}

bool checkRds()
{
  bool needRedraw = false;
  uint8_t mode = getRDSMode();

  rx.getRdsStatus();

  if(rx.getRdsReceived() && rx.getRdsSync() && rx.getRdsSyncFound())
  {
    needRedraw |= (mode & RDS_PS) && showStationName(rx.getRdsStationName());
    needRedraw |= (mode & RDS_RT) && showRadioText(rx.getRdsVersionCode()? rx.getRdsText2B() : rx.getRdsText2A());
    needRedraw |= (mode & RDS_PI) && showRdsPiCode(rx.getRdsPI());
    needRedraw |= (mode & RDS_CT) && showRdsTime(rx.getRdsTime());
    needRedraw |= (mode & RDS_PT) && showRdsProgramType(rx.getRdsProgramType());
  }

  // Return TRUE if any RDS information changes
  return(needRedraw);
}

static const char *findCBChannelByFreq(uint16_t freq)
{
  const int column_step = 450; // In kHz
  const int row_step    = 10;
  const int max_columns = 8;   // A-H
  const int max_rows    = 45;
  static char buf[50];

  if(freq<MIN_CB_FREQUENCY || freq>MAX_CB_FREQUENCY) return(0);

  int offset = freq - MIN_CB_FREQUENCY;
  char type  = 'R';
  if((offset%10) == 5)
  {
    type = 'E';
    offset -= 5;
  }

  int column_index = offset / column_step;
  int remainder    = offset % column_step;
  if((column_index>=max_columns) || (remainder%row_step)) return(0);

  int row_number = remainder / row_step;
  if((row_number>=max_rows) || (row_number<0)) return(0);

  sprintf(buf, "%c%s%c", 'A' + column_index, cbChannelNumber[row_number], type);
  return(buf);
}

static const char *findNameByFreq(uint16_t freq, const NamedFreq *db, uint16_t dbSize)
{
  int r, l;

  for(l=0, r=dbSize-1 ; l <= r ; )
  {
    int m = (l + r) >> 1;
    if(db[m].freq < freq)      l = m + 1;
    else if(db[m].freq > freq) r = m - 1;
    else return(db[m].name);
  }

  return(0);
}

bool identifyFrequency(uint16_t freq)
{
  const char *name;

  // Try list of named frequencies first
  name = findNameByFreq(freq, namedFrequencies, ITEM_COUNT(namedFrequencies));

  // Try CB channel names
  name = name? name : findCBChannelByFreq(freq);

  // Done
  return(showStationName(name? name : ""));
}
