#pragma once
#include "spine/spine-cocos2dx.h"
using namespace spine;
class MySpine : public spine::SkeletonAnimation
{
public:
	MySpine();
	MySpine(const std::string& skeletonDataFile, const std::string& atlasFile, float scale);
	~MySpine();
	//static MySpine * getinstance();
	void UpdateMySpineOnDetail(MySpine * _temp , float mydt);
	static MySpine* createWithFile(const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
	spAnimationState* self;
private:

};

