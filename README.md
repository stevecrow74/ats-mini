# ATS Mini

![](docs/source/_static/esp32-si4732-ui-theme.jpg)

This firmware is for use on the SI4732 (ESP32-S3) Mini/Pocket Receiver

Based on the following sources:

* Volos Projects:    https://github.com/VolosR/TEmbedFMRadio
* PU2CLR, Ricardo:   https://github.com/pu2clr/SI4735
* Ralph Xavier:      https://github.com/ralphxavier/SI4735
* Goshante:          https://github.com/goshante/ats20_ats_ex
* G8PTN, Dave:       https://github.com/G8PTN/ATS_MINI

## Releases

Check out the [Releases](https://github.com/esp32-si4732/ats-mini/releases) page.

## Documentation

The hardware, software and flashing documentation is available at <https://esp32-si4732.github.io/ats-mini/>

## Stevecrow74 Release

In my release I have edited the bands to include all frequencies from 150Hz to 30Mhz.

I'm also going to slowly add station names to broadcast bands, that will appear where the RDS station name appears for non-VHF FM stations.

below is the bands and frequencies they cover.

<code>
band         Modulation         frequency range
VHF          FM,               6400, 10800,
LW           AM,                150,   283,
MW1          AM,                283,  1800,
160M         LSB,              1800,  2000,
SW0          LSB,              2000,  2300,
120M         LSB,              2300,  2500,
SW1          LSB,              2500,  3200,
90M          AM,               3200,  3400,
80M          LSB,              3400,  3800,
75M          AM,               3800,  4000,
SW2          AM,               4000,  4700,
60B          AM,               4700,  5100,
60M          LSB,              5100,  5450,
AIR1         USB,              5450,  5900,
49B          AM,               5900,  6525,
AIR2         USB,              6525,  7000,
40M          LSB,              7000,  7200,
41B          AM,               7200,  7450,
SW3          AM,               7450,  8815,
AIR3         USB,              8815,  9040,
SW4          AM,               9040,  9400,
31B          AM,               9400, 10000,
30M          LSB,             10000, 10200,
SW5          AM,              10200, 11600,
25B          AM,              11600, 12100,
SW6          AM,              12100, 13570,
22B          AM,              13500, 14000,
20M          USB,             14000, 14400,
19B          AM,              14100, 15900,
SW7          AM,              15900, 17500,
16B          AM,              17500, 18000,
17M          USB,             18000, 18200,
SW8          AM,              18200, 18900,
15B          AM,              18900, 19100,
SW9          AM,              19100, 21000,
15M          USB,             21000, 21500,
13B          AM,              21500, 21900,
SW10         AM,              21900, 24800,
12M          USB,             24800, 25000,
SW11         AM,              25000, 25600,
11B          AM,              25600, 26100,
CB           AM,              26100, 28000,
10M          USB,             28000, 30000,
</code>

## Stations

Here's a current list of stations.
<code>
frequency        Station Name
1089,            "TalkSport"
2616,            "WeFax"
3050,            "Weather"
3105,            "Weather"
3413,            "Weather"
3955,            "KBS World"
4608,            "WeFax"
5450,            "Weather"
5505,            "Weather"
6090,            "Radio Amhara"
7165,            "SSTV"
7171,            "SSTV"
7245,            "China R INT"
7305,            "China R INT"
7325,            "Voice of America"
7390,            "China R INT"
7415,            "China R INT"
7878,            "WeFax"
8040,            "WeFax"
11083,           "WeFax"
11975,           "R Romania INT"
13670,           "China R INT"
14230,           "SSTV"
15500,           "KSDA"
17580,           "R Romania INT"
27700,           "SSTV"
28680,           "SSTV"
</code>
