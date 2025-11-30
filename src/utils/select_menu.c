#include "maze_c/utils.h"

#include <stdio.h>

void buffer_clear() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void display_menu(const char *list[], int list_size) {
  for (int i = 0; i < list_size; i++) {
    printf("%d. %s\n", i + 1, list[i]);
  }
}

int select_menu(int max) {
  int selected = 0;

  while (1) {
    if (scanf("%d", &selected) != 1) {
      fprintf(stderr, "[ERROR] 숫자를 입력해주세요\n");
      buffer_clear();
      continue;
    }
    if (selected < 1 || selected > max) {
      fprintf(stderr, "[ERROR] 1~%d 정해진 범위 내 번호를 선택해주세요.\n",
              max);
      buffer_clear();
      continue;
    }
    buffer_clear();
    break;
  }

  return selected;
}
