#include "maze_c/utils.h"

#if defined(_WIN32) || defined(_WIN64) // 윈도우 일때
#include <conio.h>
#include <windows.h>

void init_term() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

void reset_term() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = TRUE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

int kbhit() { return _kbhit(); }

void sleep_ms(int ms) { Sleep(ms); }

#else

#include <termios.h>
#include <unistd.h>

// 실시간 키입력을 위한 termios 라이브러리 함수들
// TODO: 자세한건 나중에 설명

struct termios oldt;

void reset_term() { tcsetattr(STDIN_FILENO, TCSANOW, &oldt); }
void init_term() {
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}
int kbhit() {
  struct timeval tv = {0L, 0L};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  return select(1, &fds, NULL, NULL, &tv);
}
void sleep_ms(int ms) { usleep(ms * 1000); }

#endif