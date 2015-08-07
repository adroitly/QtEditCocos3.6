#include "DrawLayer.h"
#include "qtedit.h"
#include "SpineIncl.h"
static QtEdit * _QtEdit = NULL;
static DrawLayer * _DrawLayer = NULL;
DrawLayer * DrawLayer::createLayer()
{
	_DrawLayer = DrawLayer::create();
	return _DrawLayer;
}
DrawLayer * DrawLayer::getinstance()
{
	if (_DrawLayer == NULL)
	{
		_DrawLayer = DrawLayer::createLayer();
	}
	return _DrawLayer;
}
bool DrawLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_QtEdit = QtEdit::getInstance();
	_QtEdit->Update_DrawLayer();
	TempNode = DrawNode::create();
	this->addChild(TempNode);
	DrawInitPosi();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	listener->onTouchBegan = CC_CALLBACK_2(DrawLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(DrawLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(DrawLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool DrawLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	selectModel = _QtEdit->selectModel;
	_select_col = _QtEdit->selectCol;
	_select_row = _QtEdit->selectRow;
	Point touchpoint = touch->getLocation();
	Startpoint = Vec2((int)touchpoint.x, (int)touchpoint.y);
	return true;
}

void DrawLayer::onTouchMoved(Touch* touch, Event *event)
{
	if (_QtEdit->ui.PauseButton->text().toStdString() == _Pausetext)
	{
		_QtEdit->pausebuttonclick();
	}
	Point touchpoint = touch->getLocation();
	Endpoint = Vec2((int)touchpoint.x, (int)touchpoint.y);
	if (std::abs(Endpoint.x - Startpoint.x) >= 15 || std::abs(Endpoint.y - Startpoint.y) >= 15)
	{
		//_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
		//this->myupdate();
		Vec2 thispoin(Startpoint.x, Startpoint.y);
		_tempPoints[0].set(thispoin);
		thispoin.x = Endpoint.x;
		_tempPoints[1].set(thispoin);
		thispoin.y = Endpoint.y;
		_tempPoints[2].set(thispoin);
		thispoin.x = Startpoint.x;
		_tempPoints[3].set(thispoin);
		thispoin.y = Startpoint.y;
		_tempPoints[4].set(thispoin);
	}
	else
	{
		Vec2 thispoin(0, 0);
		_tempPoints[0].set(thispoin);
		_tempPoints[1].set(thispoin);
		_tempPoints[2].set(thispoin);
		_tempPoints[3].set(thispoin);
		_tempPoints[4].set(thispoin);
	}
	this->DrawTempRect();
	//this->DoDrawRectNow(TempNode, _tempPoints);
}

void DrawLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Vec2 thispoin(0, 0);
	_tempPoints[0].set(thispoin);
	_tempPoints[1].set(thispoin);
	_tempPoints[2].set(thispoin);
	_tempPoints[3].set(thispoin);
	_tempPoints[4].set(thispoin);
	this->DrawTempRect();
	Point touchpoint = touch->getLocation();
	Endpoint = Vec2((int)touchpoint.x, (int)touchpoint.y);
	if (std::abs(Endpoint.x - Startpoint.x) >= 15 || std::abs(Endpoint.y - Startpoint.y) >= 15)
	{
		if (_select_row < _QtEdit->_allClickButton.size() && _QtEdit->_allClickButton.size() > 0 && _select_row != -1)
		{
			_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
			UpdateToButton();
		}
		//this->myupdate();
	}
}


void DrawLayer::UpdateToButton()
{
	ClickButton * _tempbtn = _QtEdit->_allClickButton.at(_select_row).at(_select_col);
	_tempbtn->_DrawNodeVertices->Rotate = 0.0;
	_tempbtn->setFrame(true);
	_tempbtn->setButtonColor();
	//_tempbtn->_DrawNodeVertices->setVertices(Startpoint, Endpoint);
	_tempbtn->_DrawNodeVertices->setRelativeVertices(Startpoint, Endpoint);
	Vec2 posi(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat());
	//_tempbtn->_DrawNodeVertices->setRelativeVertices(_tempbtn->_DrawNodeVertices->Vertices, posi);
	_tempbtn->_DrawNodeVertices->setVerticeFromRelative(_tempbtn->_DrawNodeVertices->Relativevertices, posi);
	_tempbtn->_DrawNodeVertices->_last_Height = _QtEdit->ui.Height->text().toFloat();
	_tempbtn->_DrawNodeVertices->_last_Width = _QtEdit->ui.Width->text().toFloat();
	_tempbtn->_DrawNodeVertices->_last_ScallX = _QtEdit->ui.ScallX->text().toFloat();
	_tempbtn->_DrawNodeVertices->_last_ScallY = _QtEdit->ui.ScallY->text().toFloat();
	//DoDrawRectInit();
	_QtEdit->_allClickButton.at(_select_row).at(_select_col)->setIsNULL(false);
	_QtEdit->ClickToRepaintBar();
}


void DrawLayer::DrawInitPosi()
{
	QtEdit::getInstance()->ShowMsg("INITDRAW");
	PosiDraw = DrawNode::create();
	Vec2 point1[4];
	point1[0] = Vec2(_IN_Width - 2, _IN_Height - 2);
	point1[1] = Vec2(_IN_Width + 2, _IN_Height - 2);
	point1[2] = Vec2(_IN_Width + 2, _IN_Height + 2);
	point1[3] = Vec2(_IN_Width - 2, _IN_Height + 2);
	PosiDraw->drawPolygon(point1, 4, Color4F(1, 0, 0, 1), 1, Color4F(0, 1, 0, 1));
	this->addChild(PosiDraw, 100);
}

void DrawLayer::DoDrawRectInit()
{
	int i = 0;
	for (i = 0; i < _DrawVectors.size(); i ++)
	{
		this->removeChild(_DrawVectors.at(i));
	}
	_DrawVectors.clear();
	for (i = 0; i < _QtEdit->_allClickButton.size(); i ++)
	{
		ClickButton * _clbtn = _QtEdit->_allClickButton.at(i).at(_select_col);
		DrawNode * _temp = DrawNode::create();
		_DrawVectors.push_back(_temp);
		if (i == _select_row)
		{
			if (_clbtn->_DrawNodeVertices->Rotate != 0.0)
			{
				if (_clbtn->isNULL())
				{
					Vec2 * ve = new Vec2[5];
					DoDrawRectNow(_temp, ve, 0.5, _clbtn->getFrameMode());
					FREE_DEL_VEC(ve);
				}
				else
				{
					DoDrawRectNow(_temp, _clbtn->_DrawNodeVertices->RelativeRotateVertices, 1, _clbtn->getFrameMode());
				}
			}
			else
			{
				if (_clbtn->isNULL())
				{
					Vec2 * ve = new Vec2[5];
					DoDrawRectNow(_temp, ve, 0.5, _clbtn->getFrameMode());
					FREE_DEL_VEC(ve);
				}
				else
				{
					DoDrawRectNow(_temp, _clbtn->_DrawNodeVertices->Relativevertices, 1, _clbtn->getFrameMode());
				}
			}
				
		}
		else
		{
			if (_clbtn->_DrawNodeVertices->Rotate != 0.0)
			{
				if (_clbtn->isNULL())
				{
					Vec2 * ve = new Vec2[5];
					DoDrawRectNow(_temp, ve, 0.5, _clbtn->getFrameMode());
					FREE_DEL_VEC(ve);
				}
				else
				{
					DoDrawRectNow(_temp, _clbtn->_DrawNodeVertices->RelativeRotateVertices, 0.5, _clbtn->getFrameMode());
				}
			}
			else
			{
				if (_clbtn->isNULL())
				{
					Vec2 * ve = new Vec2[5];
					DoDrawRectNow(_temp, ve, 0.5, _clbtn->getFrameMode());
					FREE_DEL_VEC(ve);
				}
				else
				{
					DoDrawRectNow(_temp, _clbtn->_DrawNodeVertices->Relativevertices, 0.5, _clbtn->getFrameMode());
				}
			}
		}
		
	}
}

void DrawLayer::DrawTempRect()
{
	this->removeChild(TempNode);
	TempNode = DrawNode::create();
	//碰撞
	if (selectModel == 1)
	{
		TempNode->drawPoly(_tempPoints, 5, false, Color4F(0, 1, 0, 1));
	}
	//受击
	else if (selectModel == 2)
	{
		TempNode->drawPoly(_tempPoints, 5, false, Color4F(1, 1, 0, 1));
	}
	//攻击
	else if (selectModel == 3)
	{
		TempNode->drawPoly(_tempPoints, 5, false, Color4F(1, 0, 0, 1));
	}
	//特效
	else if (selectModel == 4)
	{
		TempNode->drawPoly(_tempPoints, 5, false, Color4F(1, 1, 1, 1));
	}

	this->addChild(TempNode);
}

void DrawLayer::ButtonClickToRect()
{
	selectModel = _QtEdit->selectModel;
	_select_col = _QtEdit->selectCol;
	_select_row = _QtEdit->selectRow;
	DoDrawRectInit();
}

void DrawLayer::DoDrawRectNow(DrawNode * & _DNode, Vec2 * &posi,float apath , int drawmode /*= -1*/)
{
	if (drawmode == -1)
	{
		//碰撞
		if (selectModel == 1)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(0, 1, 0, apath));
		}
		//受击
		else if (selectModel == 2)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(1, 1, 0, apath));
		}
		//攻击
		else if (selectModel == 3)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(1, 0, 0, apath));
		}
		//特效
		else if (selectModel == 4)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(1, 1, 1, apath));
		}
	}
	else
	{
		//碰撞
		if (drawmode == 1)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(0, 1, 0, apath));
		}
		//受击
		else if (drawmode == 2)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(1, 1, 0, apath));
		}
		//攻击
		else if (drawmode == 3)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(1, 0, 0, apath));
		}
		//特效
		else if (drawmode == 4)
		{
			_DNode->drawPoly(posi, 5, false, Color4F(1, 1, 1, apath));
		}
	}
	this->addChild(_DNode);
}

void DrawLayer::setSpriteRotate3D(float _x , float _y , float _z)
{
	Vec3 sprotate(_x, _y, _z);
	_sprite->setRotation3D(sprotate);
}

void DrawLayer::setSpritePosition(float with, float height, float sacllx, float scally)
{
	Vec2 posi(with, height);
	if (1 == _QtEdit->SpiteS_Model)
	{
		VisiNode->setPosition(posi);
		VisiNode->setScaleX(sacllx);
		VisiNode->setScaleY(scally);
	}
	else if (2 == _QtEdit->SpiteS_Model)
	{
		//_MySpine->setPosition(posi);
		//_MySpine->setScaleX(sacllx);
		//_MySpine->setScaleY(scally);
		SpineIncl::getinstance()->setSpritePosition(with, height, sacllx, scally);
	}
}

void DrawLayer::updateMySprite3D(std::string filename, std::string texture, std::string file_animation)
{
	VisiNode = Node::create();
	mydt = 0.0;
	_sprite = Sprite3D::create(filename, texture);
	Vec3 sprotate(0, 90, 0);
	_sprite->setRotation3D(sprotate);
	//sp->setAnchorPoint(ccp(0.5, 0.5));
	_sprite->setCullFaceEnabled(false);
	animation = Animation3D::getOrCreate(file_animation);
	if (animation != NULL)
	{
		animate = Animate3D::create(animation);
		animate->is_auto_update = false;
		_RepeatForever = RepeatForever::create(animate);
		_sprite->runAction(_RepeatForever);
	}
	VisiNode->addChild(_sprite);
	this->addChild(VisiNode);
	//this->addChild(_sprite);
}

void DrawLayer::updateMySpine(std::string filename, std::string json_name)
{
	SpineIncl * _SpineIncl = SpineIncl::getinstance();
	_SpineIncl->updateSpine(filename, json_name, this);

}

float DrawLayer::getMySpineDuration()
{
	_MySpineDuration = SpineIncl::getinstance()->getMySpineDuration();
	return _MySpineDuration;
}

void DrawLayer::setMySpineAnimation(const char * _name, bool is_re /*= true*/)
{
	SpineIncl::getinstance()->setMySpineAnimation(_name,is_re);
}
vector<string> DrawLayer::getSpineAnimation(){
	SpineAnimationList = SpineIncl::getinstance()->SpineAnimationList;
	return SpineAnimationList;
}

void DrawLayer::MySpineUnUpdate()
{
	SpineIncl::getinstance()->MySpineUnUpdate();
}

void DrawLayer::updateMySpinePercentage(float dt)
{
	SpineIncl::getinstance()->updateMySpinePercentage(dt);
}

void DrawLayer::ButtonClick(ClickButton * &_ClickButton)
{
	if (_ClickButton->isFrame())
	{

	}
	else
	{

	}
}


void DrawLayer::ScheduMyUpdate(float dt)
{
	if (_QtEdit->_allClickButton.size() > 0)
	{
		int per_value = _QtEdit->ui.PencentageSlider->value();
		per_value++;
		if (per_value > _QtEdit->FPX)
		{
			per_value = 1;
		}

		_QtEdit->ui.PencentageSlider->setValue(per_value);
	}
}

float oneDt;
/************************************************************************/
/*开启自动                                                              */
/************************************************************************/
void DrawLayer::StartUpdate()
{
	//mydt = 0.0;
	////float _this_dt = 1.0;
	//float All_Time = 0.0;
	//if (1 == _QtEdit->SpiteS_Model)
	//{
	//	All_Time = animate->getDuration();
	//}
	//else
	//{
	//	All_Time = _MySpineDuration;
	//}
	//oneDt = All_Time / (All_Time * oneFPX);
	//float pe = All_Time / oneFPX;
	this->schedule(schedule_selector(DrawLayer::ScheduMyUpdate), 0.05);
}
/************************************************************************/
/* 关闭自动                                                             */
/************************************************************************/
void DrawLayer::EndUpdate()
{
	this->unschedule(schedule_selector(DrawLayer::ScheduMyUpdate));
}
