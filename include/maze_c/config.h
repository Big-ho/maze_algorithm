#pragma once

enum {
  SELECT_GAME_MENU_COUNT = 3,
};

// TODO: 입출구 map에 지정하고 시작
typedef enum {
  TILE_WALL = 0,
  TILE_ROAD = 1,
  TILE_START = 2,
  TILE_EXIT = 3,
} TileType;

typedef enum {
  CUSTOM_GAME = 1,
  RANDOM_GAME = 2,
  EXIT_GAME = 3,
} GameType;
