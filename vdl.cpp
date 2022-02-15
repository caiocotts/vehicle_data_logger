/** @file vdl.cpp
 *  @author Caio Cotts
 *  @date Jan 11 2022
 *  @brief Vehicle Data Logger main function
 */

#include "logger.h"
#include <iostream>
#include <ncurses.h>
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

  DlInitialization();
  while (true) {
    move(0, 0);
    reading_s reads = DlGetLoggerReadings();
    DlDisplayLoggerReadings(reads);
    DlSaveLoggerData(reads);
    refresh();
    sleep(2);
  }
}