#pragma once

enum { MAP_COUNT = 2 };

// 맵 타입 선택 관리 상수
enum { MAP_CUSTOM = 1, MAP_RANDOM, MAP_EXIT };

int game_loop();