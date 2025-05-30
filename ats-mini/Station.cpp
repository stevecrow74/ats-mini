#include "Common.h"
#include "Themes.h"
#include "Utils.h"
#include "Menu.h"
#include "EIBI.h"

// CB frequency range
#define MIN_CB_FREQUENCY 26060
#define MAX_CB_FREQUENCY 29665

//
// Named frequencies, sorted by increasing frequency!
//
static const NamedFreq namedFrequencies[] =
{
  {  1089, "TalkSport"  }, {  2616, "WeFax"  }, {  3050, "Weather"  }, {  3105, "Weather" },
  {  3413, "Weather" }, {  3955,  "KBS World"  }, {  4608, "WeFax" }, {  5450, "Weather" },
  {  5505, "Weather" },  {  6090,  "Radio Amhara"  }, {  7165, "SSTV" }, {  7171, "SSTV" },
  {  7245,  "China R INT"  }, {  7305,  "China R INT"  }, {  7325,  "Voice of America"  },
  {  7390,  "China R INT"  }, {  7415,  "China R INT"  }, {  7878, "WeFax" }, {  8040, "WeFax" },
  { 11083, "WeFax"  }, {  11975,  "R Romania INT"  },
  {  13670,  "China R INT"  }, { 14230, "SSTV" }, {  15500,  "KSDA"  }, {  17580,  "R Romania INT"  },
  { 27700, "SSTV" }, { 28074, "FT8"  }, { 28680, "SSTV" },
  // Place Holders for future stations
  {  156,  "g"  }, {  1,  "A"  }, {  1,  "A"  }, {  1,  "A"  },
  {  150,  "a"  }, {  151,  "b"  }, {  152,  "c"  }, {  153,  "d"  }, {  154,  "e"  }, {  155,  "f"  },
  {  157,  "h"  }, {  158,  "i"  }, {  159,  "j"  }, {  160,  "k"  }, {  161,  "l"  }, {  162,  "m"  },
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
  0, "News", "Current Affairs", "Information",
  "Sport", "Education", "Drama", "Culture",
  "Science", "Varied", "Pop Music", "Rock Music",
  "Easy Listening", "Light Classical", "Serious Classical", "Other Music",
  "Weather", "Finance", "Children's Program", "Social Affairs",
  "Religion", "Phone-In", "Travel", "Leisure",
  "Jazz Music", "Country Music", "National Music", "Oldies Music",
  "Folk Music", "Documentary", "TEST", "! ALERT !"
};

const char *rbdsProgramTypes[32] =
{
  0, "News", "Information", "Sports",
  "Talk", "Rock", "Classic Rock", "Adult Hits",
  "Soft Rock", "Top 40", "Country", "Oldies",
  "Soft Music", "Nostalgia", "Jazz", "Classical",
  "R & B", "Soft R & B", "Foreign Language", "Religious Music",
  "Religious Talk", "Personality", "Public", "College",
  "Spanish Talk", "Spanish Music", "Hip Hop", 0,
  0, "Weather", "TEST", "! ALERT !"
};

static char bufStationName[50]  = "";
static char bufRadioText[100]   = "";
static char bufProgramInfo[100] = "";
static uint16_t piCode = 0x0000;

const char *getStationName()
{
  if(switchThemeEditor())
    return("*STATION*");
  else
    return(getRDSMode() & RDS_PS? bufStationName : "");
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

static bool showStationName(const char *stationName, bool isLong = false)
{
  if(stationName && strcmp((isLong && bufStationName[0] == 0xFF) ? bufStationName + 1 : bufStationName, stationName))
  {
    // If the name is explicitly marked as long, add 0xFF in front of it
    // This is done to display the EiBi names differently
    if(isLong)
    {
      bufStationName[0] = 0xFF;
      strcpy(bufStationName + 1, stationName);
    }
    else
      strcpy(bufStationName, stationName);
    return(true);
  }

  return(false);
}

static bool showRadioText(const char *radioText, uint8_t width = 32)
{
  bool changed = false;
  int i, j;
  char c;

  // Must have text
  if(!radioText) return(false);

  // Skip leading whitespace
  for(i=0 ; (i<64) && radioText[i] && (radioText[i]<=' ') ; i++);

  // Terminate at 0x0D, split into lines by 0x0A
  for(j=0 ; (i<64) && radioText[i] && (radioText[i]!=0x0D) ; i++)
  {
    if((radioText[i]==0x0A) || ((radioText[i]==' ') && (j>=width)))
    {
      c = '\0';
      j = 0;
    }
    else
    {
      c = radioText[i];
      j++;
    }

    changed |= c!=bufRadioText[i];
    bufRadioText[i] = c;
  }

  // Skip trailing whitespace
  while((i>0) && (bufRadioText[i-1]<=' ')) i--;

  // Check the end of the buffer for changes
  changed |= bufRadioText[i] || bufRadioText[i+1];

  // Terminate multitline text with two zeros
  bufRadioText[i++] = '\0';
  bufRadioText[i++] = '\0';

  // Done
  return(changed);
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

static bool showRdsProgramType(uint8_t pgmType, bool useRBDS = false)
{
  // Use US-based RBDS system if requested
  const char *text =
    useRBDS?
      (pgmType<ITEM_COUNT(rbdsProgramTypes)? rbdsProgramTypes[pgmType] : 0)
    : (pgmType<ITEM_COUNT(rdsProgramTypes)? rdsProgramTypes[pgmType] : 0);

  // Filter out invalid or non-existant RDS program types
  return(showProgramInfo(text? text:""));
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
  // If NTP time available, do not use RDS time
  if(!rdsTime || ntpIsAvailable()) return(false);

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
    needRedraw |= (mode & RDS_PT) && showRdsProgramType(rx.getRdsProgramTypeX(), !!(mode & RDS_RBDS));
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

static const char *findScheduleByFreq(uint16_t freq, bool same)
{
  uint8_t hour, minute;

  if(currentMode==FM) return(0);

  // Must have valid time
  if(!clockGetHM(&hour, &minute)) return(0);

  static uint16_t last_freq = 0;
  static uint8_t last_minute = 255;
  static size_t first_offset = (size_t)-1;
  static size_t last_offset = (size_t)-1;
  const StationSchedule *entry = NULL;

  // Try EIBI lookup at the next offset and same freq
  if(same && freq == last_freq && last_offset != (size_t)-1)
  {
    entry = eibiAtSameFreq(hour, minute, &last_offset, false);

    // Try EIBI lookup at the first offset and same freq
    if(!entry)
    {
      last_offset = first_offset;
      entry = eibiAtSameFreq(hour, minute, &last_offset, true);
    }
  }

  // Try new EIBI lookup if not found or once per minute
  if(!same || (!entry && last_offset != (size_t)-1) || last_minute != minute)
  {
    last_freq = freq;
    last_minute = minute;
    last_offset = (size_t)-1;
    entry = eibiLookup(freq, hour, minute, &last_offset);
    first_offset = last_offset = entry ? last_offset : (size_t)-1;
  }

  // Return just the station name
  return(entry? entry->name : 0);
}

bool identifyFrequency(uint16_t freq, bool same)
{
  const char *name;

  // Do not try look up static names for the same frequency
  if(!same)
  {
    // Try list of named frequencies first
    name = findNameByFreq(freq, namedFrequencies, ITEM_COUNT(namedFrequencies));
    if(name) return(showStationName(name));

    // Try CB channel names
    name = findCBChannelByFreq(freq);
    if(name) return(showStationName(name));
  }

  // Try EIBI schedule
  name = findScheduleByFreq(freq, same);
  return(showStationName(name? name : "", true));
}
