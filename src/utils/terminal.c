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

struct termios oldt;

/*
tcsetattr 터미널 속성 설정
STDIN_FILENO - 키보드 표준입력
TCSANOW - 즉시 변경
oldt 백업 설정
*/
void reset_term() { tcsetattr(STDIN_FILENO, TCSANOW, &oldt); }
void init_term() {
  struct termios newt;              // 새로운 설정
  tcgetattr(STDIN_FILENO, &oldt);   // 기존 설정 가져오기
  newt = oldt;                      // 기존 설정 넣기
  newt.c_lflag &= ~(ICANON | ECHO); // 엔터 기다림, 입력 문자 출력 기능 끄기
  newt.c_cc[VMIN] = 1;              // 1바이트가 들어오면 읽음
  newt.c_cc[VTIME] = 0;             // 시간 제한없음
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 설정
}
int kbhit() {
  struct timeval tv = {0L, 0L};            // 대기 시간 0
  fd_set fds;                              // 파일 디스크립터
  FD_ZERO(&fds);                           // 초기화
  FD_SET(STDIN_FILENO, &fds);              // 키보드를 감시 대상
  return select(1, &fds, NULL, NULL, &tv); // 입력 들어왔는지 감시
}
void sleep_ms(int ms) { usleep(ms * 1000); }

#endif