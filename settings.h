#pragma once

/**
*	@file settings.h
*/
/// Debug mode (1 - on, 0 - off)
#define DEBUG 0

/// Game details
/// Screen width
#define SCR_W 1920
/// Screen height
#define SCR_H 1080
/// Game fps
#define fps 60

/// Code indexes
/// Number of maxim components in the array
#define maxComponents 30
/// Number of maxim layers in the array
#define LAYERS_NUM 10
/// Number of maxim scenes in the array
#define SCENES_NUM 6

/// Movement
/// Player speed
#define max_speed 0.3f
/// Player jump speed
#define max_jump 0.52f
/// Gravity speed
#define gravity_speed 0.2f

/// Tiles size (64 x 64)
#define TILE_SIZE 64

/// Player width
#define PLAYER_W 45
/// Player height
#define PLAYER_H 63

/// Enemy width
#define ENEMY_W 56
/// Enemy height
#define ENEMY_H 50

/// Egg width
#define EGG_W 20
/// Egg height
#define EGG_H 21

/// Explosion width
#define EXPLOSION_W 200 // cam 3 tileuri
/// Explosion height
#define EXPLOSION_H 200

/// Button source image width
#define BUTTON_SCR_W 74
/// Button source image height
#define BUTTON_SCR_H 58
/// Button width
#define BUTTON_W 148
/// Button height
#define BUTTON_H 116

/// Button back source image width
#define BUTTON_BACK_SCR_W 66
/// Button back source image height
#define BUTTON_BACK_SCR_H 27
/// Button back width
#define BUTTON_BACK_W 132
/// Button back height
#define BUTTON_BACK_H 54

/// Banner source image width
#define BANNER_SCR_W 246
/// Banner source image height
#define BANNER_SCR_H 50
/// Banner width
#define BANNER_W 738
/// Banner height
#define BANNER_H 150

/// Logo source image width
#define LOGO_SCR_W 315
/// Logo source image height
#define LOGO_SCR_H 187
/// Logo width
#define LOGO_W 945
/// Logo height
#define LOGO_H 561

/// Map files location and name
#define lvlMapFormat "GameMaps/lvl_map_"
/// Map file type
#define lvlMapType ".data"
/// Game saving file name and type
#define saveGameInfoFile "save.data"

/// <summary>
///  Game delta time
/// </summary>
const float delta_time = 1000.0f / fps;

