/** @file logger.h
 *  @brief Logger constants, structs, and function types.
 *  @author Caio Cotts
 *  @date  24 jan 22
 */

#include "logger.h"
#include "sensehat.h"
#include <cinttypes>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unistd.h>

// Global Objects
SenseHat sh;

using namespace std;

int DlInitialization(void) {
  cout << "Caio Cotts' CENG252 Vehicle Data Logger\n";
  cout << "Data Logger Initialization\n\n";
  return 0;
}

string DlGetSerial(void) {
  regex rgx("Serial.+: ([0-9]+)");
  smatch match;
  FILE *fp;
  ifstream t;
  stringstream buffer;
  t.open("/proc/cpuinfo");
  buffer << t.rdbuf();
  string buf = buffer.str();

  regex_search(buf, match, rgx);

  return match.str(1);
}

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

void DlDisplayLoggerReadings(reading_s lreads) {
  cout << "Unit: " << DlGetSerial();
  printf(" %s\n", ctime(&lreads.rtime));
  printf("T: %.1fC\t\tH: %.0f%\t\t\tP: %.1fkPa\n", lreads.temperature,
         lreads.humidity, lreads.pressure);
  printf("Xa: %fg\t\tYa: %fg\t\tZa: %fg\n", lreads.xa, lreads.ya, lreads.za);
  printf("Pitch: %f\tRoll: %f\t\tYaw: %f\n", lreads.pitch, lreads.roll,
         lreads.yaw);
  printf("Xm: %f\t\tYm: %f\t\tZm: %f\n", lreads.xm, lreads.ym, lreads.zm);
  printf("Latitude: %f\tLongitude: %f\tAltitude: %f\n", lreads.latitude,
         lreads.longitude, lreads.altitude);
  printf("Speed: %f\tHeading: %f\n\n", lreads.speed, lreads.heading);
}

int DlSaveLoggerData(reading_s creads) {
  puts("Saving Logger Data\n");
  return 0;
}