#include "cursesMatrix.h"
#include "logger.h"
#include <ncurses.h>
#include <unistd.h>

using namespace std;

void cursDisplayPattern(int yOffset, int xOffset,
                        const uint64_t pattern[8][8]) {

  for (int y = yOffset; y <= 14 + yOffset; y += 2) {
    for (int x = xOffset; x <= 28 + xOffset; x += 4) {
      attron(pattern[(y - yOffset) / 2][(x - xOffset) / 4]);
      mvprintw(y, x, "  ");
      attroff(pattern[(y - yOffset) / 2][(x - xOffset) / 4]);
    }
  }
  refresh();
}

void cursUpdateLevel(int yOffset, int xOffset, float xa, float ya) {
  cursDisplayPattern(yOffset, xOffset, patterns[1]);
  int x = (int)(xa * -30.0 + 4);
  int y = (int)(ya * -30.0 + 4);
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
  int virtualY = ((y * 2) + yOffset);
  int virtualX = ((x * 4) + xOffset);

  attron(CYELLOW);
  mvprintw(virtualY, virtualX, "  ");
  mvprintw(virtualY, virtualX + 4, "  ");
  mvprintw(virtualY + 2, virtualX, "  ");
  mvprintw(virtualY + 2, virtualX + 4, "  ");
  //   printw("(%d, %d), virtual(%d, %d)", x, y, virtualX, virtualY);
  attroff(CYELLOW);
}