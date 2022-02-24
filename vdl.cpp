/** @file vdl.cpp
 *  @author Caio Cotts
 *  @date Jan 11 2022
 *  @brief Vehicle Data Logger main function
 */

#include "cursesMatrix.h"
#include "logger.h"
#include <iostream>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

/** @brief Vehicle Data Logger main function
 *  @author Caio Cotts
 *  @date Jan 11 2022
 *  @return int program status
 *
 */

int main() {
  initscr();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_BLUE);

  DlInitialization();
  DlDisplayLogo();
  refresh();
  sleep(2);
  clear();
  int tc = 0;
  while (true) {
    reading_s reads = DlGetLoggerReadings();
    DlDisplayLoggerReadings(reads);
    cursUpdateLevel(0, 70, reads.xa, reads.ya);
    DlUpdateLevel(reads.xa, reads.ya);
    if (tc == LOGCOUNT) {
      DlSaveLoggerData(reads);
      tc = 0;
      sleep(0.5);
      refresh();
      clear();
      continue;
    }
    tc++;
    move(0, 0);
    refresh();
    sleep(0.5);
  }
}