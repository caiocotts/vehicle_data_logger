/** @file vdl.cpp
 *  @author Caio Cotts
 *  @date Jan 11 2022
 *  @brief Vehicle Data Logger main function
 */
#include "vdl.h"
#include "logger.h"
#include <iostream>
#include <unistd.h>
using namespace std;

/** @brief Vehicle Data Logger main function
 *  @author Caio Cotts
 *  @date Jan 11 2022
 *  @return int program status
 *
 */
int main() {
  while (true) {
    reading_s reads = DlGetLoggerReadings();
    DlDisplayLoggerReadings(reads);
    DlSaveLoggerData(reads);
    sleep(5);
  }
}