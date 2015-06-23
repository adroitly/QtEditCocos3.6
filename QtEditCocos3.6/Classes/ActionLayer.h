#pragma once
#ifndef _ACTIONLAYER_H_
#define _ACTIONLAYER_H_
#include "cocos2d.h"
#include "LinesPoint.h"
USING_NS_CC;
class ActionLayer :public cocos2d::Layer
{
public:
	static ActionLayer * createLayer();
	CREATE_FUNC(ActionLayer);
	virtual bool init();
	Size visibleSize;
	Vec2 orginSize;
	ActionLayer();
	~ActionLayer();

	std::vector<LinesPoint *>lines;
};
#endif
