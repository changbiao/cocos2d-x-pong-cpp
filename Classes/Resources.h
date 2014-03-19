#ifndef RESOURCES_H
#define RESOURCES_H

#include <cstdint>

#include "cocos2d.h"

using namespace cocos2d;


#pragma mark - Types

typedef std::uint8_t enum_t;


#pragma mark - Font names

static const char FONT_NAME[] =
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
"04b03"
#else
"Fonts/04b03.ttf"
#endif
;


#pragma mark - Font sizes

static const int FONT_SIZE_TITLE = 112;
static const int FONT_SIZE_MENU  = 32;
static const int FONT_SIZE_SCORE = 64;


#pragma mark - Strings

static const char STR_APP[]        = "Copong";

static const char STR_TITLE[]      = "COPONG";
static const char STR_MENU_START[] = "START NEW GAME";


#pragma mark - Sprites

static const char SPRITE_WALL[]   = "Wall.png";
static const char SPRITE_BALL[]   = "Ball.png";
static const char SPRITE_PADDLE[] = "Paddle.png";


#pragma mark - Sounds

static const char SOUND_COLLISION[] = "Sounds/Pong.wav";
static const char SOUND_POINT[]     = "Sounds/Point.wav";

#endif
