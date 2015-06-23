#pragma once
#ifndef _DRAWRECTLAYER_H_
#define _DRAWRECTLAYER_H_
#include "MyDrawNode.h"
#include "MySpritePoint.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
//class SkeletonAnimation;

class DrawRectLayer :public cocos2d::Layer
{
public:
	DrawRectLayer();
	~DrawRectLayer();
	DrawNode * PosiDraw = NULL;
	void DrawInitPosi();
	CREATE_FUNC(DrawRectLayer);
	virtual bool init();
	static DrawRectLayer * createLayer();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch* touch, Event  *event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	void showMsg(char * , float , int);
	void doDraw();
	void DrawTempRect();
	MyDrawNode * injuredNode = NULL;
	MyDrawNode * attackNode = NULL;
	MyDrawNode * bodyNode = NULL;
	MyDrawNode * effefcNode = NULL;
	DrawNode * TempNode = NULL;
	std::vector <MySpritePoint *> spritePoints;
	void myupdate();
	static DrawRectLayer * getInstence();


	void setSpritePosition(float with, float height, float sacllx, float scally);

	void updateMySprite3D(std::string filename , std::string texture , std::string file_animation);
	void updateMySpine(std::string filename , std::string json_name);



	//Spine操作
	float getMySpineDuration();
	float _MySpineDuration = 1;
	void setMySpineAnimation(const char * _name , bool is_re = true);
	void MySpineUnUpdate();
	void updateMySpinePercentage(float dt);



	Sprite3D *sp;
	//;
	//SkeletonAnimation * getMySpine();
	//SkeletonAnimation * MySpine;
	//void update(float);
	//
	void CtrlZ();
	void CtrlY();
	void CtrlD();
	//设置画的区域
	void setDrawPosition();
	//根据帧数设定
	void drawPositionEdit(int);

	MySpritePoint *getChaZhi(MySpritePoint *, MySpritePoint * , int);

	Vec2 * getChaAtt(MySpritePoint *, MySpritePoint *, int);
	Vec2 * getChaInj(MySpritePoint *, MySpritePoint *, int);
	Vec2 * getChaEff(MySpritePoint *, MySpritePoint *, int);
	MySpritePoint * getChaAct(MySpritePoint *, MySpritePoint *, int);
	//删除当前关键帧
	void deleteFrame();

	bool checkFrameData(MySpritePoint *, MySpritePoint*, int posi);
	void ScheduMyUpdate(float dt);
	void StartUpdate();
	void EndUpdate();
	void updataOrInsertFra();
	void removeDrawNode();
	void Input_Change_Update_Box(float _rotate);

	vector<string> getSpineAnimation();
public:

	Animation3D  *animation;
	Animate3D * animate;
	RepeatForever * _RepeatForever;
	MySpritePoint * _myOnePoint;
	MySpritePoint * OneSpritePoint;
	MySpritePoint * _lastSpritePoint;
	MySpritePoint * _nextSpritePoint;
	MySpritePoint * _tempSpritePoint = NULL;
	vector<std::string> SpineAnimationList;
	void actioncallback(Node* pSender);
	int				Single_ID;
	float			mydt;
	double			oneDt;
	bool			Is_Moveto_Add;
	Vec2			Startpoint;
	Vec2			Endpoint;
private:

	Vec2 _LastPoint;
	Vec2 *attpoints;
	Vec2 *injurepoints;
	Vec2 *bodypoints;
	Vec2 *effectpoints;
	Vec2 _tempPoints[5];
	
};

#endif