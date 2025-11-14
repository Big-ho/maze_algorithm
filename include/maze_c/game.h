#pragma once

// 차원 수, 맵 타입 수 (게임 수와 같음 2*2)
enum { DIMENSION_FUNCS_SIZE = 2, MAP_FUNCS_SIZE = 2 };
// 차원 선택 관리 상수
enum { DIMENSION_TWO = 1, DIMENSION_THREE, DIMENSION_EXIT };
// 맵 타입 선택 관리 상수
enum { MAP_CUSTOM = 1, MAP_RANDOM, MAP_EXIT };

int game_loop();