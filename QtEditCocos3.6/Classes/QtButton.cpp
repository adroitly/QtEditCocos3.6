#include "QtButton.h"
#include "QtEdit.h"
static QtEdit *_QtEdit;
Vec2 Zeor(0, 0);
void QtButton::keyPressEvent(QKeyEvent *e)
{
	_QtEdit = QtEdit::getInstance();
	size = _QtEdit->sliderButton.count();
	if (Qt::Key_A== e->key())
	{
		//emit leftButtonClicked();
		CheckButton(1);
	}
	else if (Qt::Key_D == e->key())
	{
		//emit rightButtonClicked();
		CheckButton(2);
	}
	else if (Qt::Key_Control == e->key())
	{
		_QtEdit->Ctrl_Is_On = true;
	}
	else if (Qt::Key_Shift == e->key())
	{
		_QtEdit->Shift_is_ON = true;
	}
	else if (Qt::Key_S == e->key())
	{
		if (_QtEdit->Ctrl_Is_On)
		{
			_QtEdit->saveAllData();
		}
	}
	else if (Qt::Key_Space == e->key())
	{
		_QtEdit->Space_is_ON = true;
	}

}
void QtButton::keyReleaseEvent(QKeyEvent *e)
{
	_QtEdit = QtEdit::getInstance();
	if (Qt::Key_Control == e->key())
	{
		_QtEdit->Ctrl_Is_On = false;
	}
	else if (Qt::Key_Shift == e->key())
	{
		_QtEdit->Shift_is_ON = false;
	}
	else if (Qt::Key_Space == e->key())
	{
		_QtEdit->Space_is_ON = false;
	}
}
void QtButton::CheckButton(int k)
{
	for (i = 0; i <= _QtEdit->FPX; i ++)
	{
		_QtButton = _QtEdit->sliderButton.at(i);
		if (_QtButton->Is_Click)
		{
			if (1 == k && 0 != i)
			{
				_QtEdit->btn = _QtEdit->sliderButton.at(i - 1);
			}
			else if (2 == k && _QtEdit->FPX != i)
			{
				_QtEdit->btn = _QtEdit->sliderButton.at(i + 1);
			}
			//_QtEdit->_lastButton = _QtButton;
			_QtEdit->ui.PencentageSlider->setValue(_QtEdit->btn->Singl_ID);
			//_QtEdit->AnimationSlderChange();
			//_QtEdit->SlderAnimationAction();
			break;
		}
	}
}

void QtButton::mousePressEvent(QMouseEvent *e)
{
	_QtEdit = QtEdit::getInstance();
	if (e->button() ==  Qt::RightButton && this_button_id <= _QtEdit->FPX)
	{
		//if (Is_AttFra || Is_InjFra || Is_ActFra || Is_BodyFra)
		if (_QtEdit->is_import)
		{
			_QtEdit->_DrawRectLayer->EndUpdate();
			if (_QtEdit->is_import)
			{
				//_QtEdit->_DrawRectLayer->unscheduleUpdate();
				_QtEdit->_DrawRectLayer->EndUpdate();
				_QtEdit->ui.PauseButton->setText("Start");
				_QtEdit->pu = -1;
				//_DrawRectLayer->drawPositionEdit(btn->Singl_ID);
			}
			_QtEdit->btn = this;
			_QtEdit->SlderAnimationAction();
			popMenu = new QMenu(this);
			if (Is_ActFra)
			{
				DeleteActAction = new QAction(this);
				DeleteActAction->setObjectName(QStringLiteral("mydeleteAction"));
				DeleteActAction->setText(QStringLiteral("删除动作关键帧"));
				QObject::connect(DeleteActAction, SIGNAL(triggered()), this, SLOT(deleteAct()));
				popMenu->addAction(DeleteActAction);
				popMenu->addSeparator();
			}
			if (Is_AttFra)
			{
				DeleteAttAction = new QAction(this);
				DeleteAttAction->setObjectName(QStringLiteral("mydeleteAction"));
				DeleteAttAction->setText(QStringLiteral("删除攻击关键帧"));
				QObject::connect(DeleteAttAction, SIGNAL(triggered()), this, SLOT(deleteAtt()));
				popMenu->addAction(DeleteAttAction);
				ClearAttAction = new QAction(this);
				ClearAttAction->setObjectName(QStringLiteral("mydeleteAction"));
				ClearAttAction->setText(QStringLiteral("清空攻击关键帧"));
				QObject::connect(ClearAttAction, SIGNAL(triggered()), this, SLOT(clearAtt()));
				popMenu->addAction(ClearAttAction);
				popMenu->addSeparator();
			}
			else
			{
				AddAttAction = new QAction(this);
				AddAttAction->setObjectName(QStringLiteral("mydeleteAction"));
				AddAttAction->setText(QStringLiteral("增加攻击关键帧"));
				QObject::connect(AddAttAction, SIGNAL(triggered()), this, SLOT(addAtt()));
				popMenu->addAction(AddAttAction);
				popMenu->addSeparator();
			}
			if (Is_InjFra)
			{
				DeleteInjAction = new QAction(this);
				DeleteInjAction->setObjectName(QStringLiteral("mydeleteAction"));
				DeleteInjAction->setText(QStringLiteral("删除受击关键帧"));
				QObject::connect(DeleteInjAction, SIGNAL(triggered()), this, SLOT(deleteInj()));
				popMenu->addAction(DeleteInjAction);
				ClearInjAction = new QAction(this);
				ClearInjAction->setObjectName(QStringLiteral("mydeleteAction"));
				ClearInjAction->setText(QStringLiteral("清空受击关键帧"));
				QObject::connect(ClearInjAction, SIGNAL(triggered()), this, SLOT(clearInj()));
				popMenu->addAction(ClearInjAction);
				popMenu->addSeparator();
			}
			else
			{
				AddInjAction = new QAction(this);
				AddInjAction->setObjectName(QStringLiteral("mydeleteAction"));
				AddInjAction->setText(QStringLiteral("增加受击关键帧"));
				QObject::connect(AddInjAction, SIGNAL(triggered()), this, SLOT(addInj()));
				popMenu->addAction(AddInjAction);
				popMenu->addSeparator();
			}
			if (Is_BodyFra)
			{
				DeleteBodyAction = new QAction(this);
				DeleteBodyAction->setObjectName(QStringLiteral("mydeleteAction"));
				DeleteBodyAction->setText(QStringLiteral("删除碰撞关键帧"));
				QObject::connect(DeleteBodyAction, SIGNAL(triggered()), this, SLOT(deleteBody()));
				popMenu->addAction(DeleteBodyAction);
				ClearBodyAction = new QAction(this);
				ClearBodyAction->setObjectName(QStringLiteral("mydeleteAction"));
				ClearBodyAction->setText(QStringLiteral("清空碰撞关键帧"));
				QObject::connect(ClearBodyAction, SIGNAL(triggered()), this, SLOT(clearBody()));
				popMenu->addAction(ClearBodyAction);
				popMenu->addSeparator();
			}
			else
			{
				AddBodyAction = new QAction(this);
				AddBodyAction->setObjectName(QStringLiteral("mydeleteAction"));
				AddBodyAction->setText(QStringLiteral("增加碰撞关键帧"));
				QObject::connect(AddBodyAction, SIGNAL(triggered()), this, SLOT(addBody()));
				popMenu->addAction(AddBodyAction);
				popMenu->addSeparator();
			}
			if (Is_EffFra)
			{
				DeleteEffAction = new QAction(this);
				DeleteEffAction->setObjectName(QStringLiteral("mydeleteAction"));
				DeleteEffAction->setText(QStringLiteral("删除特效关键帧"));
				QObject::connect(DeleteEffAction, SIGNAL(triggered()), this, SLOT(deleteEff()));
				popMenu->addAction(DeleteEffAction);
				ClearEffAction = new QAction(this);
				ClearEffAction->setObjectName(QStringLiteral("mydeleteAction"));
				ClearEffAction->setText(QStringLiteral("清空特效关键帧"));
				QObject::connect(ClearEffAction, SIGNAL(triggered()), this, SLOT(clearEff()));
				popMenu->addAction(ClearEffAction);
				popMenu->addSeparator();
			}
			else
			{
				AddEffAction = new QAction(this);
				AddEffAction->setObjectName(QStringLiteral("mydeleteAction"));
				AddEffAction->setText(QStringLiteral("增加特效关键帧"));
				QObject::connect(AddEffAction, SIGNAL(triggered()), this, SLOT(addEff()));
				popMenu->addAction(AddEffAction);
				popMenu->addSeparator();
			}
			if (Is_AttFra || Is_InjFra || Is_ActFra || Is_BodyFra || Is_EffFra)
			{
				DeleteAllAction = new QAction(this);
				DeleteAllAction->setObjectName(QStringLiteral("mydeleteAction"));
				DeleteAllAction->setText(QStringLiteral("删除所有关键帧"));
				QObject::connect(DeleteAllAction, SIGNAL(triggered()), this, SLOT(deleteFra()));
				popMenu->addAction(DeleteAllAction);
			}

			//else if (!(Is_AttFra && Is_InjFra && Is_ActFra && Is_BodyFra))
			//{
			//	AddAllAction = new QAction(this);
			//	AddAllAction->setObjectName(QStringLiteral("mydeleteAction"));
			//	AddAllAction->setText(QStringLiteral("增加所有关键帧"));
			//	QObject::connect(AddAllAction, SIGNAL(triggered()), this, SLOT(addFra()));
			//	popMenu->addAction(AddAllAction);
			//}
			popMenu->setStyleSheet("QMenu{background-color:rgb(255,255,255);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
				"QMenu::item:selected{background-color:#CCDAE7;}");
			popMenu->exec(QCursor::pos());
		}

	}
	else
	{
		//其他的返回父类使用
		__super::mousePressEvent(e);
	}
}
void QtButton::deleteFra()
{
	Is_AttFra = false;
	Is_InjFra = false;
	Is_ActFra = false;
	Is_BodyFra = false;
	Is_EffFra = false;
	deleteAction(true);
}
void QtButton::deleteEff()
{
	Is_EffFra = false;
	_EffFraButton->setStyleSheet("background:transparent");
	DoDelete();
}
//int i = 0;
void QtButton::deleteAct()
{
	Is_ActFra = false;
	_ActFraButton->setStyleSheet("background:transparent");
	DoDelete();
}
void QtButton::deleteAtt()
{
	Is_AttFra = false;
	_AttFraButton->setStyleSheet("background:transparent");
	DoDelete();
}
void QtButton::deleteInj()
{
	Is_InjFra = false;
	_InjFraButton->setStyleSheet("background:transparent");
	DoDelete();
}
void QtButton::deleteBody()
{
	Is_BodyFra = false;
	_BodyFraButton->setStyleSheet("background:transparent");
	DoDelete();
}
//删除当前关键帧
void QtButton::deleteAction(bool Is_Update /* = false */)
{
	//Is_AttFra = false;
	if (!Is_AttFra)
	{
		_AttFraButton->setStyleSheet("background:transparent");
	}
	if (!Is_ActFra)
	{
		_ActFraButton->setStyleSheet("background:transparent");
	}
	if (!Is_InjFra)
	{
		_InjFraButton->setStyleSheet("background:transparent");
	}
	if (!Is_BodyFra)
	{
		_BodyFraButton->setStyleSheet("background:transparent");
	}
	if (!Is_EffFra)
	{
		_EffFraButton->setStyleSheet("background:transparent");
	}
	//删除帧
	if (Is_Update)
	{
		
		_QtEdit->_DrawRectLayer->deleteFrame();
		_QtEdit->SlderAnimationAction();
	}
	//delete _QtEdit->_DrawRectLayer->spritePoints.at(_QtEdit->_DrawRectLayer->Single_ID);
}
void QtButton::clearBody()
{
	for (i = 0; i < _QtEdit->_DrawRectLayer->spritePoints.size(); i++)
	{
		MySpritePoint * _tempSpritePoint = _QtEdit->_DrawRectLayer->spritePoints.at(i);
		if (_tempSpritePoint->Single_ID == Singl_ID)
		{
			_QtEdit->_DrawRectLayer->spritePoints.at(i)->setBodyVertices(Zeor, Zeor);
			break;
		}
	}
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	_QtEdit->SlderAnimationAction();
}
void QtButton::clearAtt()
{
	for (i = 0; i < _QtEdit->_DrawRectLayer->spritePoints.size(); i++)
	{
		MySpritePoint * _tempSpritePoint = _QtEdit->_DrawRectLayer->spritePoints.at(i);
		if (_tempSpritePoint->Single_ID == Singl_ID)
		{
			_QtEdit->_DrawRectLayer->spritePoints.at(i)->setAttackVertices(Zeor, Zeor);
			break;
		}
	}
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	_QtEdit->SlderAnimationAction();
}
void QtButton::clearEff()
{
	for (i = 0; i < _QtEdit->_DrawRectLayer->spritePoints.size(); i++)
	{
		MySpritePoint * _tempSpritePoint = _QtEdit->_DrawRectLayer->spritePoints.at(i);
		if (_tempSpritePoint->Single_ID == Singl_ID)
		{
			_QtEdit->_DrawRectLayer->spritePoints.at(i)->setEffectVertices(Zeor, Zeor);
			break;
		}
	}
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	_QtEdit->SlderAnimationAction();
}

void QtButton::clearInj()
{
	for (i = 0; i < _QtEdit->_DrawRectLayer->spritePoints.size(); i++)
	{
		MySpritePoint * _tempSpritePoint = _QtEdit->_DrawRectLayer->spritePoints.at(i);
		if (_tempSpritePoint->Single_ID == Singl_ID)
		{
			_QtEdit->_DrawRectLayer->spritePoints.at(i)->setInjureVertices(Zeor, Zeor);
			break;
		}
	}
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	_QtEdit->SlderAnimationAction();
}
void QtButton::DoDelete()
{
	for (i = 0; i < _QtEdit->_DrawRectLayer->spritePoints.size(); i++)
	{
		MySpritePoint * _tempSpritePoint = _QtEdit->_DrawRectLayer->spritePoints.at(i);
		if (_tempSpritePoint->Single_ID == Singl_ID)
		{
			if (!Is_ActFra)
			{
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->Is_ActFra = false;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->_height = _IN_Height;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->_width = _IN_Width;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->_ScallX = _IN_ScallX;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->_ScallY = _IN_ScallY;
			}
			if (!Is_AttFra)
			{
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->Is_AttFra = false;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->attackVertices = nullptr;
			}
			if (!Is_InjFra)
			{
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->Is_InjFra = false;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->injureVertices = nullptr;
			}
			if (!Is_BodyFra)
			{
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->Is_BodyFra = false;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->bodyVertices = nullptr;
			}
			if (!Is_EffFra)
			{
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->Is_EffFra = false;
				_QtEdit->_DrawRectLayer->spritePoints.at(i)->effectVertices = nullptr;
			}
			if (!Is_InjFra && !Is_AttFra && !Is_ActFra && !Is_BodyFra && !Is_EffFra)
			{
				_QtEdit->_DrawRectLayer->spritePoints.erase(_QtEdit->_DrawRectLayer->spritePoints.begin() + i);
				FREE_DEL_OBJ(_tempSpritePoint);
				_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
			}
			break;
		}
	}
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	_QtEdit->SlderAnimationAction();
}


void QtButton::addAct()
{
	//Is_ActFra = true;
	//_ActFraButton->setAutoFillBackground(true);
	//_ActFraButton->setPalette(QPalette(Qt::blue));

}
void QtButton::addAtt()
{
	te_sh = _QtEdit->Shift_is_ON;
	te_ct = _QtEdit->Ctrl_Is_On;
	te_sp = _QtEdit->Space_is_ON;
	_QtEdit->Shift_is_ON = false;
	_QtEdit->Space_is_ON = false;
	_QtEdit->Ctrl_Is_On = true;
	_QtEdit->_DrawRectLayer->removeDrawNode();
	_QtEdit->_DrawRectLayer->updataOrInsertFra();
	_QtEdit->Ctrl_Is_On = false;
	_QtEdit->Shift_is_ON = te_sh;
	_QtEdit->Ctrl_Is_On = te_ct;
	_QtEdit->Space_is_ON = te_sp;
}
void QtButton::addBody()
{
	Is_BodyFra = true;
	//_BodyFraButton->setAutoFillBackground(true);
	//_BodyFraButton->setPalette(QPalette(Qt::green));
	te_sh = _QtEdit->Shift_is_ON;
	te_ct = _QtEdit->Ctrl_Is_On;
	te_sp = _QtEdit->Space_is_ON;
	_QtEdit->Ctrl_Is_On = false;
	_QtEdit->Space_is_ON = false;
	_QtEdit->Shift_is_ON = true;
	_QtEdit->_DrawRectLayer->removeDrawNode();
	_QtEdit->_DrawRectLayer->updataOrInsertFra();
	_QtEdit->Shift_is_ON = false;
	_QtEdit->Shift_is_ON = te_sh;
	_QtEdit->Ctrl_Is_On = te_ct;
	_QtEdit->Space_is_ON = te_sp;

}
void QtButton::addEff()
{
	Is_EffFra = true;
	//_InjFraButton->setAutoFillBackground(true);
	//_InjFraButton->setPalette(QPalette(Qt::yellow));
	te_sh = _QtEdit->Shift_is_ON;
	te_ct = _QtEdit->Ctrl_Is_On;
	te_sp = _QtEdit->Space_is_ON;
	_QtEdit->Ctrl_Is_On = false;
	_QtEdit->Shift_is_ON = false;
	_QtEdit->Space_is_ON = true;
	_QtEdit->_DrawRectLayer->removeDrawNode();
	_QtEdit->_DrawRectLayer->updataOrInsertFra();
	_QtEdit->Shift_is_ON = te_sh;
	_QtEdit->Ctrl_Is_On = te_ct;
	_QtEdit->Space_is_ON = te_sp;
}
void QtButton::addInj()
{
	Is_InjFra = true;
	//_InjFraButton->setAutoFillBackground(true);
	//_InjFraButton->setPalette(QPalette(Qt::yellow));
	te_sh = _QtEdit->Shift_is_ON;
	te_ct = _QtEdit->Ctrl_Is_On;
	te_sp = _QtEdit->Space_is_ON;
	_QtEdit->Ctrl_Is_On = false;
	_QtEdit->Shift_is_ON = false;
	_QtEdit->Space_is_ON = false;
	_QtEdit->_DrawRectLayer->removeDrawNode();
	_QtEdit->_DrawRectLayer->updataOrInsertFra();
	_QtEdit->Shift_is_ON = te_sh;
	_QtEdit->Ctrl_Is_On = te_ct;
	_QtEdit->Space_is_ON = te_sp;
}
void QtButton::addFra()
{

}