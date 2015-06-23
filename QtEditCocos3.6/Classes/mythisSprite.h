
#ifndef __MYTHISSPRITE_H__
#define __MYTHISSPRITE_H__
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class mythisSprite
{
public:
	mythisSprite();
	~mythisSprite();
	Sprite * _Sprite;
	Vec2 downpoint;
	Vec2 uppoint;
	Vec2 position;
	double ScallX;
	double ScallY;
};
#endif
