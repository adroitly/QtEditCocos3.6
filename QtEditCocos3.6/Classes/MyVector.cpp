#include "MyVector.h"


MyVector::MyVector()
{
	try{
		Singl_ID = 0;
		_width = _IN_Width;
		_ScallX = _IN_ScallX;
		_height = _IN_Height;
		_ScallY = _IN_ScallY;
	}
	catch (...){}
	//Sprites = *(new vector<MySpritePoint *>());
}


MyVector::~MyVector()
{
	//delete &Sprites;
}

void MyVector::init(float sx , float sy , float w , float h)
{
	_ScallX = sx;
	_ScallY = sy;
	_width = w;
	_height = h;
}
void MyVector::initFromSprite(MySpritePoint * sprite)
{
	_width = sprite->_width;
	_ScallX = sprite->_ScallX;
	_height = sprite->_height;
	_ScallY = sprite->_ScallY;
}
