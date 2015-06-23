#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__
#pragma once
#include "iostream"
#include "MySpritePoint.h"
using namespace std;
class MyVector
{
public:
	MyVector();
	~MyVector();
	vector<MySpritePoint * > Sprites;
	void init(float sx , float sy , float w , float h);
	void initFromSprite(MySpritePoint * sprite);
	double _ScallX;
	double _ScallY;
	double _height;
	double _width;
	int Singl_ID;
};
#endif

