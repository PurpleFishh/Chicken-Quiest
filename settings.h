#pragma once

#define DEBUG 1

// Game details
#define SCR_W 1920
#define SCR_H 1080
#define fps 60

// Code indexes
#define maxComponents 30
#define LAYERS_NUM 10
#define SCENES_NUM 6

// Movement
#define max_speed 0.3f
#define max_jump 0.52f
#define gravity_speed 0.2f

//Tiles
#define TILE_SIZE 64

#define PLAYER_W 45
#define PLAYER_H 63

#define ENEMY_W 56
#define ENEMY_H 50

#define EGG_W 20
#define EGG_H 21

#define EXPLOSION_W 200 // cam 3 tileuri
#define EXPLOSION_H 200

#define BUTTON_SCR_W 74
#define BUTTON_SCR_H 58
#define BUTTON_W 148
#define BUTTON_H 116

#define BUTTON_BACK_SCR_W 66
#define BUTTON_BACK_SCR_H 27
#define BUTTON_BACK_W 132
#define BUTTON_BACK_H 54

#define BANNER_SCR_W 246
#define BANNER_SCR_H 50
#define BANNER_W 738
#define BANNER_H 150

#define LOGO_SCR_W 315
#define LOGO_SCR_H 187
#define LOGO_W 945
#define LOGO_H 561

#define lvlMapFormat "lvl_map_"
#define lvlMapType ".data"

const float delta_time = 1000.0f / fps;

