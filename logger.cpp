/** @file logger.cpp
 *  @brief Logger functions.
 *  @author Caio Cotts
 *  @date Feb 14 2022
 */

#include "logger.h"
#include "cursesMatrix.h"
#include "font.h"
#include "sensehat.h"
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <regex>
#include <signal.h>
#include <string>

// Global Objects
SenseHat sh;

using namespace std;

/** @brief Initialize data logger.
 *  @author Caio Cotts
 *  @date Feb 14 2022
 *  @return 0 if initialization successful.
 */
int DlInitialization(void) {
  mvprintw(0, 0, "Caio Cotts' CENG252 Vehicle Data Logger\n");
  printw("Data Logger Initialization\n");
  refresh();
  for (int i = 0; i <= 30; i++) {
    printw("#");
    usleep(100000);
    refresh();
  }
  cursDisplayPattern(0, 70, patterns[0]);
  return 0;
}

/** @brief Get serial number of the Raspberry Pi.
 *  @author Caio Cotts
 *  @date Feb 14 2022
 *  @return Unsigned long long
 */
uint64_t DlGetSerial(void) {
  regex rgx("Serial.+: ([0-9]+)");
  smatch match;
  FILE *fp;
  ifstream t("/proc/cpuinfo");
  stringstream buffer;
  buffer << t.rdbuf();
  string buf = buffer.str();
  regex_search(buf, match, rgx);
  uint64_t serial = stoull(match.str(1));

  return serial;
}

/** @brief Get sensor readings.
 *  @author Caio Cotts
 *  @date Feb 14 2022
 *  @return reading_s object
 */
reading_s DlGetLoggerReadings(void) {
  reading_s creads{0};
  creads.rtime = time(NULL);

#if SENSEHAT
  creads.temperature = sh.GetTemperature();
  creads.humidity = sh.GetHumidity();
  creads.pressure = sh.GetPressure();
  sh.GetAcceleration(creads.xa, creads.ya, creads.za);
  usleep(IMUDELAY);
  sh.GetOrientation(creads.pitch, creads.roll, creads.yaw);
  usleep(IMUDELAY);
  sh.GetMagnetism(creads.xm, creads.ym, creads.zm);
  usleep(IMUDELAY);
  creads.latitude = DLAT;
  creads.longitude = DLONG;
  creads.altitude = DALT;
  creads.speed = DSPEED;
  creads.heading = DHEADING;

#else

  creads.temperature = DTEMP;
  creads.humidity = DHUMID;
  creads.pressure = DPRESS;
  creads.xa = DXA;
  creads.ya = DYA;
  creads.za = DZA;
  creads.pitch = DPITCH;
  creads.roll = DROLL;
  creads.yaw = DYAW;
  creads.xm = DXM;
  creads.ym = DYM;
  creads.zm = DZM;
  creads.latitude = DLAT;
  creads.longitude = DLONG;
  creads.altitude = DALT;
  creads.speed = DSPEED;
  creads.heading = DHEADING;

#endif

  return creads;
}

/** @brief Print sensor readings to standard out.
 *  @author Caio Cotts
 *  @date Feb 14 2022
 *  @return void
 */
void DlDisplayLoggerReadings(reading_s lreads) {
  printw("Unit: %Li", DlGetSerial());
  printw(" %s\n", ctime(&lreads.rtime));
  printw("T: %.1fC\t\tH: %.0f%\t\t\tP: %.1fkPa\n", lreads.temperature,
         lreads.humidity, lreads.pressure);
  printw("Xa: %fg\t\tYa: %fg\t\tZa: %fg\n", lreads.xa, lreads.ya, lreads.za);
  printw("Pitch: %f \tRoll: %f\t\tYaw: %f\n", lreads.pitch, lreads.roll,
         lreads.yaw);
  printw("Xm: %f\t\tYm: %f\t\tZm: %f\n", lreads.xm, lreads.ym, lreads.zm);
  printw("Latitude: %f\tLongitude: %f\tAltitude: %f\n", lreads.latitude,
         lreads.longitude, lreads.altitude);
  printw("Speed: %f\tHeading: %f\n\n", lreads.speed, lreads.heading);
}

/** @brief Save sensor readings.
 *  @author Caio Cotts
 *  @date Feb 14 2022
 *  @return 0 if data was saved successfuly
 */
int DlSaveLoggerData(reading_s creads) {
  mvprintw(15, 70, "Saving Logger Data...\n\n");
  return 0;
}
void DlDisplayLogo() {
  uint16_t logo[8][8] = {
      HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HW, HB, HB, HW, HB, HY,
      HB, HB, HW, HB, HB, HW, HY, HY, HB, HB, HW, HB, HB, HW, HY, HY,
      HB, HB, HW, HW, HW, HW, HY, HY, HB, HB, HW, HY, HY, HW, HY, HY,
      HB, HY, HW, HY, HY, HW, HY, HY, HY, HY, HY, HY, HY, HY, HY, HY,
  };
  sh.WipeScreen();
  sh.ViewPattern(logo);
}
void DlUpdateLevel(float xa, float ya) {
  int x = (int)(ya * -30.0 + 4);
  int y = (int)(xa * -30.0 + 4);
  sh.WipeScreen();
  if (x < 0) {
    x = 0;
  } else if (x > 6) {
    x = 6;
  }

  if (y < 0) {
    y = 0;
  } else if (y > 6) {
    y = 6;
  }

  sh.LightPixel(x, y, HY);
  sh.LightPixel(x + 1, y, HY);
  sh.LightPixel(x, y + 1, HY);
  sh.LightPixel(x + 1, y + 1, HY);
}

void interruptHandler() {}