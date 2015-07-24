#include "ClickButton.h"

#include "qtedit.h"
#include "qmessagebox.h"
static QtEdit * _QtEdit;

ClickButton::ClickButton(int row, int col, int frame_Model /*= 0*/, QWidget *parent /*= 0*/) :QPushButton(parent)
{
	_row = row;
	_col = col;
	_frame_Model = frame_Model;
	_QtEdit = QtEdit::getInstance();
	_parent = parent;
	_line_ID = 0;
	_DrawNodeVertices = DrawNodeVertices::create();
}

void ClickButton::setButtonColor()
{
	if (_frame_Model == 0)
	{
		//setStyleSheet("background: transparent;border:0px");
		setAutoFillBackground(true);
		setPalette(QPalette(Qt::blue));
	}
	if (_frame_Model == 1)
	{
		setAutoFillBackground(true);
		setPalette(QPalette(Qt::green));
	}
	else if (_frame_Model == 2)
	{
		setAutoFillBackground(true);
		setPalette(QPalette(Qt::yellow));
	}
	else if (_frame_Model == 3)
	{
		setAutoFillBackground(true);
		setPalette(QPalette(Qt::red));
	}
	else if (_frame_Model == 4)
	{
		setAutoFillBackground(true);
		setPalette(QPalette(Qt::white));
	}
	_is_Frame = true;
}

//void ClickButton::keyPressEvent(QKeyEvent *e)
//{
//
//}
//
//void ClickButton::keyReleaseEvent(QKeyEvent *e)
//{
//
//}

void ClickButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton)
	{
		if (_row == 0)
		{
			if (_is_Frame)
			{
				popMenu = new QMenu(this);
				one_BoxAction = new QAction(this);
				one_BoxAction->setText(QStringLiteral("删除当前人物属性"));
				QObject::connect(one_BoxAction, SIGNAL(triggered()), this, SLOT(DelAction()));
				popMenu->addAction(one_BoxAction);
				popMenu->addSeparator();

				popMenu->setStyleSheet("QMenu{background-color:rgb(255,255,255);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
					"QMenu::item:selected{background-color:#CCDAE7;}");
				popMenu->exec(QCursor::pos());
			}
			return;
		}

		if (_QtEdit->ui.PauseButton->text().toStdString() == _Pausetext)
		{
			_QtEdit->pausebuttonclick();
		}

		popMenu = new QMenu(this);

		if (_is_Frame)
		{
			one_BoxAction = new QAction(this);
			one_BoxAction->setText(QStringLiteral("删除当前盒子"));
			QObject::connect(one_BoxAction, SIGNAL(triggered()), this, SLOT(DelAction()));
			free_BoxAction = new QAction(this);
			free_BoxAction->setText(QStringLiteral("清空当前盒子"));
			QObject::connect(free_BoxAction, SIGNAL(triggered()), this, SLOT(FreeBox()));
			popMenu->addAction(free_BoxAction);
			popMenu->addSeparator();
		}
		else
		{
			one_BoxAction = new QAction(this);
			one_BoxAction->setText(QStringLiteral("增加一个盒子"));
			QObject::connect(one_BoxAction, SIGNAL(triggered()), this, SLOT(DddAction()));
		}
		delete_LineAction = new QAction(this);
		delete_LineAction->setText(QStringLiteral("删除当前时间线"));
		QObject::connect(delete_LineAction, SIGNAL(triggered()), this, SLOT(DelLine()));

		delete_AllAction = new QAction(this);
		delete_AllAction->setText(QStringLiteral("删除当前关键帧"));
		QObject::connect(delete_AllAction, SIGNAL(triggered()), this, SLOT(DelFrame()));

		popMenu->addAction(one_BoxAction);
		popMenu->addSeparator();
		popMenu->addAction(delete_LineAction);
		popMenu->addSeparator();
		popMenu->addAction(delete_AllAction);
		popMenu->addSeparator();

		popMenu->setStyleSheet("QMenu{background-color:rgb(255,255,255);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
			"QMenu::item:selected{background-color:#CCDAE7;}");
		popMenu->exec(QCursor::pos());
	}
	else if (e->button() == Qt::LeftButton)
	{
		if (_QtEdit->ui.PauseButton->text().toStdString() == _Pausetext)
		{
			_QtEdit->pausebuttonclick();
		}
		if (_row != 0)
		{
			if (_QtEdit->selectRow != -1 && _QtEdit->selectRow < _QtEdit->_allClickButton.size() && _QtEdit->selectCol < _QtEdit->_allClickButton.at(0).size())
			{
				_QtEdit->_allClickButton.at(_QtEdit->selectRow).at(_QtEdit->selectCol)->Click_ED(false);
			}
			Click_ED(true);
		}
	}
	
}

void ClickButton::DelAction()
{
	//setButtonColor();
	_QtEdit = QtEdit::getInstance();
	QString str = _QtEdit->windowTitle();
	str = str.split("*").at(0);
	str += "*";
	_QtEdit->setWindowTitle(str);
	_is_Frame = false;
	setStyleSheet("background: transparent;border:0px");
	_DrawNodeVertices->reset();
	int i;
	for (i = 0; i < _QtEdit->_allClickButton.size(); i++)
	{
		_QtEdit->_allClickButton.at(i).at(_col - 1)->_DrawNodeVertices->updateRetlativeVertices(_IN_Width , _IN_Height , _IN_ScallX , _IN_ScallY);
	}
	Click_ED(true);
}

void ClickButton::DddAction()
{
	_QtEdit = QtEdit::getInstance();
	QString str = _QtEdit->windowTitle();
	str = str.split("*").at(0);
	str += "*";
	_QtEdit->setWindowTitle(str);
	setButtonColor();
	_is_null = false;
	Click_ED(true);
}

void ClickButton::DelFrame()
{
	_QtEdit = QtEdit::getInstance();
	QString str = _QtEdit->windowTitle();
	str = str.split("*").at(0);
	str += "*";
	_QtEdit->setWindowTitle(str);
	int i;
	for (i = 0; i < _QtEdit->_allClickButton.size(); i ++)
	{
		_QtEdit->_allClickButton.at(i).at(_col - 1)->DoDelFrame();
	}
	Click_ED(true);
}

void ClickButton::DelLine()
{
	//setButtonColor();
	switch (QMessageBox::warning(_parent, "Wraning", QStringLiteral("确定删除?"), QMessageBox::Yes | QMessageBox::Cancel))
	{
	case QMessageBox::Yes:
		_QtEdit->DeleteLine(_row);
	default:
		break;
	}
	
}

//void ClickButton::focusInEvent(QFocusEvent *e)
//{
//	_QtEdit->selectCol = _col;
//	_QtEdit->selectRow = _row;
//	if (_QtEdit->SeleteLineRow == -1)
//	{
//		_QtEdit->SeleteLineRow = _row;
//	}
//	_QtEdit->isClickToChange = true;
//	_QtEdit->ui.PencentageSlider->setValue(_col);
//	QPushButton::focusInEvent(e);
//	setText(QStringLiteral("囧"));
//}

void ClickButton::DoDelFrame()
{
	_is_Frame = false;
	_ScallX = _IN_ScallX;
	_ScallY = _IN_ScallY;
	_Height = _IN_Height;
	_Width = _IN_Width;
	_DrawNodeVertices->reset();
	setStyleSheet("background: transparent;border:0px");
}

void ClickButton::FreeBox()
{
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	_is_null = true;
	_DrawNodeVertices->reset();
	Click_ED(true);
}


void ClickButton::Click_ED(bool is_click /*= false*/)
{
	int i = 0;
	if (is_click)
	{
		_QtEdit->selectCol = _col - 1;
		_QtEdit->selectRow = _row;
		if (_QtEdit->SeleteLineRow == -1)
		{
			_QtEdit->SeleteLineRow = _row;
		}
		_QtEdit->isClickToChange = true;
		_QtEdit->ui.PencentageSlider->setValue(_col);
		setText(QStringLiteral("囧"));
		for (i = 0; i < _QtEdit->_allClickButton.size(); i ++)
		{
			_QtEdit->_allClickButton.at(i).at(_col - 1)->UpdateVertices();
		}
		_QtEdit->ClickToRepaintBar();
	}
	else
	{
		setText("");
	}
}

ClickButton * ClickButton::copy()
{
	ClickButton * _copy = new ClickButton(_row, _col, _frame_Model, _parent);
	_copy->_is_Frame = _is_Frame;
	_copy->_is_null = _is_null;
	_copy->_col = _col;
	_copy->_row = _row;
	_copy->_frame_Model = _frame_Model;
	_copy->_Height = _Height;
	_copy->_Width = _Width;
	_copy->_line_ID = _line_ID;
	_copy->_parent = _parent;
	_copy->_ScallX = _ScallX;
	_copy->_ScallY = _ScallY;
	DEL_FREE_OBJ(_copy->_DrawNodeVertices);
	_copy->_DrawNodeVertices = _DrawNodeVertices->copy();
	return _copy;
}

void ClickButton::UpdateVertices()
{
	int i = 0;
	double _x = _IN_Width;
	double _y = _IN_Height;
	double _sx = _IN_ScallX;
	double _sy = _IN_ScallY;
	ClickButton * _tempbtn;
	ClickButton * _lastbtn = NULL;
	ClickButton * _nextbtn = NULL;
	int _lcha = 100000;
	int _ncha = 100000;


	_lastbtn = NULL;
	_nextbtn = NULL;
	_ncha = 10000;
	_lcha = 10000;
	//点差算法
	if (!_is_Frame)
	{
		for (i = 0; i < _QtEdit->_allClickButton.at(_row).size(); i++)
		{
			_tempbtn = _QtEdit->_allClickButton.at(_row).at(i);
			if (_tempbtn->_is_Frame)
			{
				if (_tempbtn->_col < _col && (_col - _tempbtn->_col < _lcha))
				{
					_lcha = _col - _tempbtn->_col;
					_lastbtn = _tempbtn;
				}
				else if (_tempbtn->_col > _col && (_tempbtn->_col - _col < _ncha))
				{
					_ncha = _tempbtn->_col - _col;
					_nextbtn = _tempbtn;
				}
			}
		}
		//如果有上一个
		if (_lastbtn && !_lastbtn->isNULL())
		{
			_lastbtn = _lastbtn->copy();
			_lastbtn->_DrawNodeVertices->updateRetlativeVertices(_IN_Width, _IN_Height, _IN_ScallX, _IN_ScallY);
			for (i = 0; i < 5; i++)
			{
				_DrawNodeVertices->Vertices[i].set(_lastbtn->_DrawNodeVertices->Vertices[i]);
				_DrawNodeVertices->Relativevertices[i].set(_lastbtn->_DrawNodeVertices->Relativevertices[i]);
				_DrawNodeVertices->RelativeRotateVertices[i].set(_lastbtn->_DrawNodeVertices->RelativeRotateVertices[i]);;
				_DrawNodeVertices->RotateVertices[i].set(_lastbtn->_DrawNodeVertices->RotateVertices[i]);
			}
			if (_nextbtn && !_nextbtn->isNULL())
			{
				_nextbtn = _nextbtn->copy();
				_nextbtn->_DrawNodeVertices->updateRetlativeVertices(_IN_Width, _IN_Height, _IN_ScallX, _IN_ScallY);
				Vec2 _tempPosi(0, 0);
				double _x;
				double _y;
				for (i = 0; i < 5; i++)
				{
					_x = _lastbtn->_DrawNodeVertices->Vertices[i].x + (_nextbtn->_DrawNodeVertices->Vertices[i].x - _lastbtn->_DrawNodeVertices->Vertices[i].x) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_y = _lastbtn->_DrawNodeVertices->Vertices[i].y + (_nextbtn->_DrawNodeVertices->Vertices[i].y - _lastbtn->_DrawNodeVertices->Vertices[i].y) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_tempPosi.set(_x, _y);
					_DrawNodeVertices->Vertices[i].set(_tempPosi);

					_x = _lastbtn->_DrawNodeVertices->Relativevertices[i].x + (_nextbtn->_DrawNodeVertices->Relativevertices[i].x - _lastbtn->_DrawNodeVertices->Relativevertices[i].x) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_y = _lastbtn->_DrawNodeVertices->Relativevertices[i].y + (_nextbtn->_DrawNodeVertices->Relativevertices[i].y - _lastbtn->_DrawNodeVertices->Relativevertices[i].y) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_tempPosi.set(_x, _y);
					_DrawNodeVertices->Relativevertices[i].set(_tempPosi);

					_x = _lastbtn->_DrawNodeVertices->RelativeRotateVertices[i].x + (_nextbtn->_DrawNodeVertices->RelativeRotateVertices[i].x - _lastbtn->_DrawNodeVertices->RelativeRotateVertices[i].x) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_y = _lastbtn->_DrawNodeVertices->RelativeRotateVertices[i].y + (_nextbtn->_DrawNodeVertices->RelativeRotateVertices[i].y - _lastbtn->_DrawNodeVertices->RelativeRotateVertices[i].y) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_tempPosi.set(_x, _y);
					_DrawNodeVertices->RelativeRotateVertices[i].set(_tempPosi);

					_x = _lastbtn->_DrawNodeVertices->RotateVertices[i].x + (_nextbtn->_DrawNodeVertices->RotateVertices[i].x - _lastbtn->_DrawNodeVertices->RotateVertices[i].x) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_y = _lastbtn->_DrawNodeVertices->RotateVertices[i].y + (_nextbtn->_DrawNodeVertices->RotateVertices[i].y - _lastbtn->_DrawNodeVertices->RotateVertices[i].y) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
					_tempPosi.set(_x, _y);
					_DrawNodeVertices->RotateVertices[i].set(_tempPosi);

				}
				DEL_FREE_OBJ(_nextbtn);
			}
			DEL_FREE_OBJ(_lastbtn);
			//_tempbtn = _QtEdit->_allClickButton.at(0).at(_col - 1);
			//_x = _tempbtn->_Width;
			//_y = _tempbtn->_Height;
			//_sx = _tempbtn->_ScallX;
			//_sy = _tempbtn->_ScallY;
			//_DrawNodeVertices->_last_Height = _lastbtn->_DrawNodeVertices->_last_Height;
			//_DrawNodeVertices->_last_Width = _lastbtn->_DrawNodeVertices->_last_Width;
			//_DrawNodeVertices->_last_ScallX = _lastbtn->_DrawNodeVertices->_last_ScallX;
			//_DrawNodeVertices->_last_ScallY = _lastbtn->_DrawNodeVertices->_last_ScallY;
			_DrawNodeVertices->_last_Height = _IN_Height;
			_DrawNodeVertices->_last_Width = _IN_Width;
			_DrawNodeVertices->_last_ScallX = _IN_ScallX;
			_DrawNodeVertices->_last_ScallY = _IN_ScallY;
			//_DrawNodeVertices->updateRetlativeVertices(_x, _y, _sx, _sy); 
		}
		//没有就归零
		else
		{
			_DrawNodeVertices->reset();
		}
	}
	else
	{
		_tempbtn = _QtEdit->_allClickButton.at(_row).at(_col - 1);
		double ssssx = _tempbtn->_DrawNodeVertices->_last_ScallX;
		double ssssy = _tempbtn->_DrawNodeVertices->_last_ScallY;
		_tempbtn->_DrawNodeVertices->updateRetlativeVertices(_IN_Width, _IN_Height, ssssx, ssssy);
		//_x = _tempbtn->_Width;
		//_y = _tempbtn->_Height;
		//_sx = _tempbtn->_ScallX;
		//_sy = _tempbtn->_ScallY;
	}


	_lastbtn = NULL;
	_nextbtn = NULL;
	_ncha = 10000;
	_lcha = 10000;
	//位移的差值算法
	if (!_QtEdit->_allClickButton.at(0).at(_col - 1)->_is_Frame)
	{
		for (i = 0; i < _QtEdit->_allClickButton.at(0).size(); i++)
		{
			_tempbtn = _QtEdit->_allClickButton.at(0).at(i);
			if (_tempbtn->_is_Frame)
			{
				if (_tempbtn->_col < _col && (_col - _tempbtn->_col < _lcha))
				{
					_lcha = _col - _tempbtn->_col;
					_lastbtn = _tempbtn;
				}
				else if (_tempbtn->_col > _col && (_tempbtn->_col - _col < _ncha))
				{
					_ncha = _tempbtn->_col - _col;
					_nextbtn = _tempbtn;
				}
			}
		}
		if (_lastbtn)
		{
			_ScallX = _lastbtn->_ScallX;
			_ScallY = _lastbtn->_ScallY;
			_Width = _lastbtn->_Width;
			_Height = _lastbtn->_Height;
			if (_nextbtn)
			{
				_ScallX =_lastbtn->_ScallX + (_nextbtn->_ScallX - _lastbtn->_ScallX) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
				_ScallY = _lastbtn->_ScallY + (_nextbtn->_ScallY - _lastbtn->_ScallY) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
				_Width = _lastbtn->_Width + (_nextbtn->_Width - _lastbtn->_Width) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
				_Height = _lastbtn->_Height + (_nextbtn->_Height - _lastbtn->_Height) / (_nextbtn->_col - _lastbtn->_col) * (_col - _lastbtn->_col);
			}
			_tempbtn = _QtEdit->_allClickButton.at(0).at(_col - 1);
			_tempbtn->_ScallX = _ScallX;
			_tempbtn->_ScallY = _ScallY;
			_tempbtn->_Height = _Height;
			_tempbtn->_Width = _Width;
			_tempbtn = _QtEdit->_allClickButton.at(_row).at(_col - 1);
			_tempbtn->_DrawNodeVertices->updateRetlativeVertices(_Width, _Height, _ScallX, _ScallY);
			//_tempbtn->_DrawNodeVertices->_last_ScallX = _ScallX;
			//_tempbtn->_DrawNodeVertices->_last_ScallY = _ScallY;
			//_tempbtn->_DrawNodeVertices->_last_Width = _Width;
			//_tempbtn->_DrawNodeVertices->_last_Height = _Height;
		}
		else
		{
			_ScallX = _IN_ScallX;
			_ScallY = _IN_ScallY;
			_Width = _IN_Width;
			_Height = _IN_Height;
			_tempbtn = _QtEdit->_allClickButton.at(0).at(_col - 1);
			_tempbtn->_ScallX = _ScallX;
			_tempbtn->_ScallY = _ScallY;
			_tempbtn->_Height = _Height;
			_tempbtn->_Width = _Width;
			//_tempbtn = _QtEdit->_allClickButton.at(_row).at(_col - 1);
			//_tempbtn->_DrawNodeVertices->updateRetlativeVertices(_Width, _Height, _ScallX, _ScallY);
		}
	}
	else
	{
		_tempbtn = _QtEdit->_allClickButton.at(0).at(_col - 1);
		_ScallX = _tempbtn->_ScallX;
		_ScallY = _tempbtn->_ScallY;
		_Width = _tempbtn->_Width;
		_Height = _tempbtn->_Height;
		_tempbtn = _QtEdit->_allClickButton.at(_row).at(_col - 1);
		_tempbtn->_DrawNodeVertices->updateRetlativeVertices(_Width, _Height, _ScallX, _ScallY);
	}

	
}
