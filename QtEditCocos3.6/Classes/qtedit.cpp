#include "qtedit.h"
//#include <QtDebug>
#include "Export_Data.h"
#include "Classes/AppDelegate.h"
#include "Classes/CocosQtPort/CCQGLView.h"
#include <QTimer>
#include <QDockWidget>
#include "QTextEdit"
#include "QTextBlock"
#include <QEvent>
#include <qfiledialog.h>
#include "QMessageBox.h"
#include "DrawRectLayer.h"
#include "cocos2d.h"
#include "QTableWidget.h"
#include "QTextStream.h"
#include "string.h"
#include "QTextCodec.h"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonValue"
#include "QJsonParseError"
#include <QProcess>
#include "QJSONobject"
#include "json/json.h"
#include "SQLite/DBUtil.h"
//#include "spine/spine-cocos2dx.h"
//#pragma comment(lib, "Qt5Sql.lib")  
USING_NS_CC;
static QtEdit		* _QtEdit;
static Export_Data *_Export_Data;

QtEdit::QtEdit(QWidget *parent)
	: QMainWindow(parent),
	_appDelegate(NULL),
	_glWidget(NULL),
	is_import(false),
	Ctrl_Is_On(false),
	_lastButton(NULL),
	FPX(-1),
	myVector(NULL),
	Shift_is_ON(false),
	Is_ChangeInputToBox(false),
	Space_is_ON(false)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	_QtEdit = this;
	ui.setupUi(this);
	ui.SceneWidget->setWindowTitle("Cocos2dx Scene");
	ui.SceneWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.OutWiget->setWindowTitle("Out Put");
	//ui.OutWiget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.PerWiget->setWindowTitle("Frame Control");
	ui.PerWiget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.dockWidget->setWindowTitle("");
	ui.dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.AnimationtreeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.AnimationtreeWidget->header()->setStretchLastSection(true);
	ui.dockWidgetContents_5->setUpdatesEnabled(TRUE);
	//ui.PencentageSlider->setGeometry(0, 0, this->width(), 40);
	codec = QTextCodec::codecForName("GB18030");
	AddCao();
	MySQLite();
	AddSliderButton();
}

void QtEdit::AddCao()
{
	//QObject::connect(importaction, SIGNAL(triggered()), QtEditClass, SLOT(import()));
	//QObject::connect(Width, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(Height, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(ScallX, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(ScallY, SIGNAL(textEdited(QString)), QtEditClass, SLOT(ChangeInput()));
	//QObject::connect(PauseButton, SIGNAL(clicked()), QtEditClass, SLOT(pausebuttonclick()));
	//QObject::connect(showmessage, SIGNAL(textChanged()), QtEditClass, SLOT(showmessageChange()));
	//QObject::connect(PencentageSlider, SIGNAL(valueChanged(int)), QtEditClass, SLOT(AnimationSlderChange()));
	//QObject::connect(AnimationtreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), QtEditClass, SLOT(AnimationTreeWidgetClick(QTreeWidgetItem*, int)));
	//QObject::connect(PencentageSlider, SIGNAL(actionTriggered(int)), QtEditClass, SLOT(AnimationSlderClick(int)));
	//QObject::connect(actionHelp, SIGNAL(triggered()), QtEditClass, SLOT(ActionHelp()));
	//QObject::connect(exportaction, SIGNAL(triggered()), QtEditClass, SLOT(exportData()));
	//QObject::connect(openaction, SIGNAL(triggered()), QtEditClass, SLOT(openData()));
	//QObject::connect(closeaction, SIGNAL(triggered()), QtEditClass, SLOT(close()));
	QObject::connect(ui.importaction, SIGNAL(triggered()), this, SLOT(import()));
	QObject::connect(ui.import_Spine, SIGNAL(triggered()), this, SLOT(importSpine()));
	QObject::connect(ui.Width, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.Height, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.ScallX, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.ScallY, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.ScallY, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	//QObject::connect(ui.Width, SIGNAL(wheelEvent(QWheelEvent *)), this, SLOT(wheelEvent(QWheelEvent*)));
	QObject::connect(ui.Re_Width, SIGNAL(textEdited(QString)), this, SLOT(ReChangeInput()));
	QObject::connect(ui.Re_Height, SIGNAL(textEdited(QString)), this, SLOT(ReChangeInput()));
	QObject::connect(ui.PauseButton, SIGNAL(clicked()), this, SLOT(pausebuttonclick()));
	QObject::connect(ui.showmessage, SIGNAL(textChanged()), this, SLOT(showmessageChange()));
	QObject::connect(ui.PencentageSlider, SIGNAL(valueChanged(int)), this, SLOT(AnimationSlderChange()));
	QObject::connect(ui.AnimationtreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(AnimationTreeWidgetClick(QTreeWidgetItem*, int)));
	QObject::connect(ui.PencentageSlider, SIGNAL(actionTriggered(int)), this, SLOT(AnimationSlderClick(int)));
	QObject::connect(ui.actionHelp, SIGNAL(triggered()), this, SLOT(ActionHelp()));
	QObject::connect(ui.exportaction, SIGNAL(triggered()), this, SLOT(exportData()));
	QObject::connect(ui.openaction, SIGNAL(triggered()), this, SLOT(openData()));
	QObject::connect(ui.closeaction, SIGNAL(triggered()), this, SLOT(close()));
	QObject::connect(ui.Action_Save, SIGNAL(triggered()), this, SLOT(saveAllData()));
	QObject::connect(ui.export_byte, SIGNAL(triggered()), this, SLOT(export_byteData()));
	QObject::connect(ui.MyBox_comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(Mybox_Combox(QString)));
	QObject::connect(ui.St_Width, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.St_Height, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.En_Width, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.En_Height, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.Rotate, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	double_rx = new QRegExp(_Input_EXP);
	validtor = new QRegExpValidator(*double_rx);
	ui.St_Width->setValidator(validtor);
	ui.St_Height->setValidator(validtor);
	ui.En_Width->setValidator(validtor);
	ui.En_Height->setValidator(validtor);
	ui.Rotate->setValidator(validtor);
	ui.Width->setValidator(validtor);
	ui.Height->setValidator(validtor);
	ui.ScallX->setValidator(validtor);
	ui.ScallY->setValidator(validtor);
	QDir dir;
	//ui.Re_Width->setValidator(validtor);
	//ui.Re_Height->setValidator(validtor);
}

QtEdit::~QtEdit()
{
	Director::getInstance()->release();
	delete _Export_Data;
	delete _DrawRectLayer;
	delete _QtEdit;
}

QtEdit * QtEdit::getInstance()
{
	if (_QtEdit == NULL)
	{
		new QtEdit();
	}
	return _QtEdit;
}
void QtEdit::ShowMsg(std::string str)
{
	mymsg = mymsg + str + "\n";
	ui.showmessage->setPlainText((codec->toUnicode(mymsg.c_str())));
	QTextCursor cursor = ui.showmessage->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui.showmessage->setTextCursor(cursor);
	
}
void QtEdit::BoxChangeInput(QString str)
{
	QString comboxstring = ui.MyBox_comboBox->currentText();
	if (!is_import || comboxstring == _InComboxtext)
	{
		return;
	}
	this->setWindowTitle(this->windowTitle().split("*").at(0) + "*");
	_DrawRectLayer->Startpoint = Vec2(ui.Width->text().toFloat() + ui.St_Width->text().toFloat(), ui.St_Height->text().toFloat() + ui.Height->text().toFloat());
	_DrawRectLayer->Endpoint = Vec2(ui.Width->text().toFloat() + ui.En_Width->text().toFloat(), ui.En_Height->text().toFloat() + ui.Height->text().toFloat());
	bool ctrl_temp, shift_temp , space_temp;
	ctrl_temp = Ctrl_Is_On;
	space_temp = Space_is_ON;
	shift_temp = Shift_is_ON;
	Is_ChangeInputToBox = true;
	if (comboxstring == _Injtext)
	{
		Ctrl_Is_On = false;
		Shift_is_ON = false;
		Space_is_ON = false;
	}
	else if (comboxstring == _Atttext)
	{
		Shift_is_ON = false;
		Space_is_ON = false;
		Ctrl_Is_On = true;
	}
	else if (comboxstring == _Bodytext)
	{
		Shift_is_ON = true;
		Ctrl_Is_On = false;
		Space_is_ON = false;
	}
	else if (comboxstring == _Effecttext)
	{
		Shift_is_ON = false;
		Ctrl_Is_On = false;
		Space_is_ON = true;
	}
	if (comboxstring == _Bodytext || comboxstring == _Effecttext)
	{
		ui.Rotate->setText("0");
	}
	_DrawRectLayer->Input_Change_Update_Box(QStringToFloat(ui.Rotate->text()) * (PI / 180));
	//_DrawRectLayer->myupdate();
	Ctrl_Is_On = ctrl_temp;
	Shift_is_ON = shift_temp;
	Space_is_ON = space_temp;
	ui.MyBox_comboBox->setCurrentText(comboxstring);
	setRePosition(getCurrIndex(comboxstring));
	Is_ChangeInputToBox = false;
}
void QtEdit::Mybox_Combox(QString str)
{
	if (!is_import)
	{
		return;
	}
	if (str == _InComboxtext)
	{
		setMyBox(0);
	}
	else if (str == _Injtext)
	{
		//log("%s", str.toStdString().c_str());
		setMyBox(1);
	}
	else if (str == _Atttext)
	{
		//log("%s", str.toStdString().c_str());
		setMyBox(2);
	}
	else if (str == _Bodytext)
	{
		//log("%s", str.toStdString().c_str());
		setMyBox(3);
	}
	else if (str == _Effecttext)
	{
		setMyBox(4);
	}
}
void QtEdit::wheelEvent(QWheelEvent *e)
{
	//int numDegrees = e->delta() / 8;//滚动的角度，*8就是鼠标滚动的距离
	//int numSteps = numDegrees / 15;//滚动的步数，*15就是鼠标滚动的角度
	/*bool has = ui.Width->hasFocus();*/
	//if (!is_import)
	//{
	//	return;
	//}
	float _ScallX = ui.ScallX->text().toFloat();
	float _ScallY = ui.ScallY->text().toFloat();
	int num = e->delta();
	int down_up = 1;
	if (num < 0)//向下滚动
	{
		down_up = -1;
	}
	else
	{
		down_up = 1;
	}
	if (ui.Width->hasFocus())
	{
		ui.Width->setText(QString::number(ui.Width->text().toFloat() + down_up));
		ui.Re_Width->setText(QString::number(ui.Re_Width->text().toFloat() + down_up));
		ChangeInput();
	}
	else if (ui.Height->hasFocus())
	{
		ui.Height->setText(QString::number(ui.Height->text().toFloat() + down_up));
		ui.Re_Height->setText(QString::number(ui.Re_Height->text().toFloat() + down_up));
		ChangeInput();
	}
	else if (ui.Re_Width->hasFocus())
	{
		ui.Width->setText(QString::number(ui.Width->text().toFloat() + down_up));
		ui.Re_Width->setText(QString::number(ui.Re_Width->text().toFloat() + down_up));
		ChangeInput();
	}
	else if (ui.Re_Height->hasFocus())
	{
		ui.Height->setText(QString::number(ui.Height->text().toFloat() + down_up));
		ui.Re_Height->setText(QString::number(ui.Re_Height->text().toFloat() + down_up));
		ChangeInput();
	}
	//else if (ui.Rotate->hasFocus())
	//{
	//	ui.Rotate->setText(QString::number(ui.Rotate->text().toFloat() + down_up));
	//	ChangeInput();
	//}
	else if (ui.ScallX->hasFocus())
	{
		ui.ScallX->setText(QString::number(ui.ScallX->text().toFloat() + (down_up * 0.1)));
		ChangeInput();
	}
	else if (ui.ScallY->hasFocus())
	{
		ui.ScallY->setText(QString::number(ui.ScallY->text().toFloat() + (down_up * 0.1)));
		//ReChangeInput();
		ChangeInput();
	}
	else if (ui.St_Width->text() != "")
	{
		if (ui.St_Width->hasFocus())
		{
			ui.St_Width->setText(QString::number(ui.St_Width->text().toFloat() + down_up));
		}
		else if (ui.St_Height->hasFocus())
		{
			ui.St_Height->setText(QString::number(ui.St_Height->text().toFloat() + down_up));
		}
		else if (ui.En_Width->hasFocus())
		{
			ui.En_Width->setText(QString::number(ui.En_Width->text().toFloat() + down_up));
		}
		else if (ui.En_Height->hasFocus())
		{
			ui.En_Height->setText(QString::number(ui.En_Height->text().toFloat() + down_up));
		}
		else if (ui.Rotate->hasFocus())
		{
			ui.Rotate->setText(QString::number(ui.Rotate->text().toFloat() + down_up));
		}
		BoxChangeInput("");
		pu = 1;
		pausebuttonclick();
		QString str = ui.MyBox_comboBox->currentText();
		int a = getCurrIndex(str);

		setRePosition(a);
	}
}
int QtEdit::getCurrIndex(QString &str)
{
	int a;
	if (str == _InComboxtext)
	{
		a = 0;
	}
	else if (str == _Injtext)
	{
		a = 1;
	}
	else if (str == _Atttext)
	{
		a = 2;
	}
	else if (str == _Bodytext)
	{
		a = 3;
	}
	else if (str == _Effecttext)
	{
		a = 4;
	}
	return a;
}
void QtEdit::setRePosition(int a)
{
	double _PoScallX = ui.ScallX->text().toDouble();
	double _PoScallY = ui.ScallY->text().toDouble();
	if (a == 0)
	{
		ui.St_Width->setText("");
		ui.St_Height->setText("");
		ui.En_Width->setText("");
		ui.En_Height->setText("");
		ui.Rotate->setText("");
	}
	else if (a == 1)
	{
		ui.St_Width_RE->setText(QString("%1").arg((_DrawRectLayer->injuredNode->Relativevertices[0].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.St_Height_RE->setText(QString("%1").arg((_DrawRectLayer->injuredNode->Relativevertices[0].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.En_Width_RE->setText(QString("%1").arg((_DrawRectLayer->injuredNode->Relativevertices[2].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.En_Height_RE->setText(QString("%1").arg((_DrawRectLayer->injuredNode->Relativevertices[2].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.Rotate->setText(QString("%1").arg(180.0 / PI * (_DrawRectLayer->injuredNode->Rotate)));
	}
	else if (a == 2)
	{
		ui.St_Width_RE->setText(QString("%1").arg((_DrawRectLayer->attackNode->Relativevertices[0].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.St_Height_RE->setText(QString("%1").arg((_DrawRectLayer->attackNode->Relativevertices[0].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.En_Width_RE->setText(QString("%1").arg((_DrawRectLayer->attackNode->Relativevertices[2].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.En_Height_RE->setText(QString("%1").arg((_DrawRectLayer->attackNode->Relativevertices[2].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.Rotate->setText(QString("%1").arg(180.0 / PI * (_DrawRectLayer->attackNode->Rotate)));
	}
	else if (a == 3)
	{
		ui.St_Width_RE->setText(QString("%1").arg((_DrawRectLayer->bodyNode->Relativevertices[0].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.St_Height_RE->setText(QString("%1").arg((_DrawRectLayer->bodyNode->Relativevertices[0].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.En_Width_RE->setText(QString("%1").arg((_DrawRectLayer->bodyNode->Relativevertices[2].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.En_Height_RE->setText(QString("%1").arg((_DrawRectLayer->bodyNode->Relativevertices[2].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.Rotate->setText("0");
	}
	else if (a == 4)
	{
		ui.St_Width_RE->setText(QString("%1").arg((_DrawRectLayer->effefcNode->Relativevertices[0].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.St_Height_RE->setText(QString("%1").arg((_DrawRectLayer->effefcNode->Relativevertices[0].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.En_Width_RE->setText(QString("%1").arg((_DrawRectLayer->effefcNode->Relativevertices[2].x - ui.Width->text().toFloat()) / _PoScallX));
		ui.En_Height_RE->setText(QString("%1").arg((_DrawRectLayer->effefcNode->Relativevertices[2].y - ui.Height->text().toFloat()) / _PoScallY));
		ui.Rotate->setText("0");
	}
}
void QtEdit::setMyBox(int a)
{
	if (a == 0)
	{
		ui.St_Width->setText("");
		ui.St_Height->setText("");
		ui.En_Width->setText("");
		ui.En_Height->setText("");
		ui.Rotate->setText("");
	}
	if (a == 1)
	{
		//ui.St_Width->setText(QString("%1").arg(_DrawRectLayer->OneSpritePoint->injureVertices[0].x));
		//ui.St_Height->setText(QString("%1").arg(_DrawRectLayer->OneSpritePoint->injureVertices[0].y));
		//ui.En_Width->setText(QString("%1").arg(_DrawRectLayer->OneSpritePoint->injureVertices[2].x));
		//ui.En_Height->setText(QString("%1").arg(_DrawRectLayer->OneSpritePoint->injureVertices[2].y));
		//ui.Rotate->setText(QString("%1").arg(_DrawRectLayer->OneSpritePoint->RotateInj));
		//if (_DrawRectLayer->injuredNode->Relativevertices[0].x == -3500 && _DrawRectLayer->injuredNode->Relativevertices[0].y == -700)
		//{
		//	Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
		//	_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices,posi );
		//	_DrawRectLayer->injuredNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, ui.ScallX->text().toFloat());
		//	_DrawRectLayer->injuredNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, ui.ScallY->text().toFloat());
		//}
		Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
		_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, posi);
		_DrawRectLayer->injuredNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, ui.ScallX->text().toFloat());
		_DrawRectLayer->injuredNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, ui.ScallY->text().toFloat());
		//else if (_DrawRectLayer->injuredNode->Rotate != 0.0)
		//{
		//	Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
		//	_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, posi);
		//}
		ui.St_Width->setText(QString("%1").arg(int(_DrawRectLayer->injuredNode->Relativevertices[0].x - ui.Width->text().toFloat())));
		ui.St_Height->setText(QString("%1").arg(int(_DrawRectLayer->injuredNode->Relativevertices[0].y - ui.Height->text().toFloat())));
		ui.En_Width->setText(QString("%1").arg(int(_DrawRectLayer->injuredNode->Relativevertices[2].x - ui.Width->text().toFloat())));
		ui.En_Height->setText(QString("%1").arg(int(_DrawRectLayer->injuredNode->Relativevertices[2].y - ui.Height->text().toFloat())));
		ui.Rotate->setText(QString("%1").arg(180.0 / PI * (_DrawRectLayer->injuredNode->Rotate)));

	}
	else if (a == 2)
	{
		//if (_DrawRectLayer->attackNode->Relativevertices[0].x == -3500 && _DrawRectLayer->attackNode->Relativevertices[0].y == -700)
		//{
		//	Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
		//	_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, posi);
		//	_DrawRectLayer->attackNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, ui.ScallX->text().toFloat());
		//	_DrawRectLayer->attackNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, ui.ScallY->text().toFloat());
		//}
		//if (_DrawRectLayer->attackNode->Relativevertices[0].x == -500 && _DrawRectLayer->attackNode->Relativevertices[0].y == -100)
		{
			Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, posi);
			_DrawRectLayer->attackNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, ui.ScallX->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, ui.ScallY->text().toFloat());
		}
		//else if (_DrawRectLayer->attackNode->Rotate != 0.0)
		//{
		//	Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
		//	_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, posi);
		//}
		ui.St_Width->setText(QString("%1").arg(int(_DrawRectLayer->attackNode->Relativevertices[0].x - ui.Width->text().toFloat())));
		ui.St_Height->setText(QString("%1").arg(int(_DrawRectLayer->attackNode->Relativevertices[0].y - ui.Height->text().toFloat())));
		ui.En_Width->setText(QString("%1").arg(int(_DrawRectLayer->attackNode->Relativevertices[2].x - ui.Width->text().toFloat())));
		ui.En_Height->setText(QString("%1").arg(int(_DrawRectLayer->attackNode->Relativevertices[2].y - ui.Height->text().toFloat())));
		ui.Rotate->setText(QString("%1").arg(180.0 / PI * (_DrawRectLayer->attackNode->Rotate)));

		
	}
	else if (a == 3 )
	{
		//if (_DrawRectLayer->bodyNode->Relativevertices[0].x == -3500 && _DrawRectLayer->bodyNode->Relativevertices[0].y == -700)
		{
			Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
			_DrawRectLayer->bodyNode->setRelativeVertices(_DrawRectLayer->bodyNode->Vertices, posi);
			_DrawRectLayer->bodyNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, ui.ScallX->text().toFloat());
			_DrawRectLayer->bodyNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, ui.ScallY->text().toFloat());
		}
		ui.St_Width->setText(QString("%1").arg(int(_DrawRectLayer->bodyNode->Relativevertices[0].x - ui.Width->text().toFloat())));
		ui.St_Height->setText(QString("%1").arg(int(_DrawRectLayer->bodyNode->Relativevertices[0].y - ui.Height->text().toFloat())));
		ui.En_Width->setText(QString("%1").arg(int(_DrawRectLayer->bodyNode->Relativevertices[2].x - ui.Width->text().toFloat())));
		ui.En_Height->setText(QString("%1").arg(int(_DrawRectLayer->bodyNode->Relativevertices[2].y - ui.Height->text().toFloat())));
		ui.Rotate->setText(QString("%1").arg(_DrawRectLayer->bodyNode->Rotate));
	}
	else if (a == 4)
	{
		//if (_DrawRectLayer->effefcNode->Relativevertices[0].x == -3500 && _DrawRectLayer->effefcNode->Relativevertices[0].y == -700)
		{
			Vec2 posi(ui.Width->text().toFloat(), ui.Height->text().toFloat());
			_DrawRectLayer->effefcNode->setRelativeVertices(_DrawRectLayer->effefcNode->Vertices, posi);
			_DrawRectLayer->effefcNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, ui.ScallX->text().toFloat());
			_DrawRectLayer->effefcNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, ui.ScallY->text().toFloat());
		}
		ui.St_Width->setText(QString("%1").arg(int(_DrawRectLayer->effefcNode->Relativevertices[0].x - ui.Width->text().toFloat())));
		ui.St_Height->setText(QString("%1").arg(int(_DrawRectLayer->effefcNode->Relativevertices[0].y - ui.Height->text().toFloat())));
		ui.En_Width->setText(QString("%1").arg(int(_DrawRectLayer->effefcNode->Relativevertices[2].x - ui.Width->text().toFloat())));
		ui.En_Height->setText(QString("%1").arg(int(_DrawRectLayer->effefcNode->Relativevertices[2].y - ui.Height->text().toFloat())));
		ui.Rotate->setText(QString("%1").arg(_DrawRectLayer->effefcNode->Rotate));
	}
	setRePosition(a);
}
void QtEdit::saveAllData()
{
	if (is_import && saveDataName != NULL && !saveDataName.isNull())
	{
		this->setWindowTitle(this->windowTitle().split("*").at(0));
		_Export_Data = Export_Data::getInstence();
		_Export_Data->DrawDataTo_Qtedit();
		_Export_Data->Dosave_JsonData(saveDataName.toStdString().c_str(), spritesPoints, true);
		//doSaveData(saveDataName, true);

	}
	
}
void QtEdit::importSpine()
{
	QString file_name;
	QString filter = openSpineFile_Path;;
	if (openSpineFile_Path.lastIndexOf(".") != -1)
	{
		filter = "atlas files (*.atlas);;all files (*)";
	}
	if (this->windowTitle().indexOf("*") != -1)
	{
		QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有操作保存，是否先保存再导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::Yes)
		{
			//import();
			_Export_Data = Export_Data::getInstence();
			_Export_Data->DrawDataTo_Qtedit();
			_Export_Data->Dosave_JsonData(saveDataName.toStdString().c_str(), spritesPoints, true);
		}
	}
	file_name = QFileDialog::getOpenFileName(this,
		codec->toUnicode("导入atlas文件"), openSpineFile_Path, filter);
	if (!file_name.isNull())
	{
		//fileName是文件名
		is_import = true;
		MySQLite(true, file_name, "open_spine_path");
		_DrawRectLayer = DrawRectLayer::getInstence();
		//log("%d", file_name.lastIndexOf("/"));
		//QStringList strlist = file_name.split("Resources/");
		QString Re_File_name = file_name.mid(file_name.lastIndexOf("/") + 1);
		this->setWindowTitle(Re_File_name);
		QFileInfo fi;
		fi = QFileInfo(file_name);
		saveDataName = fi.path() + "/" + fi.fileName().split(".").at(0) + tr(".data");
		_filename = fi.fileName().split(".").at(0);
		if (is_import)
		{
			animation_list.clear();
			_DrawRectLayer->removeAllChildrenWithCleanup(true);
			_DrawRectLayer->spritePoints.clear();
			_DrawRectLayer->DrawInitPosi();
			pu = 1;
			pausebuttonclick();
		}

		_DrawRectLayer->updateMySpine(file_name.toStdString(), (fi.path() + "/" + fi.fileName().split(".").at(0)  +".json").toStdString());
		SpiteS_Model = 2;
		AddAnimationList(file_name);

		if (animation_list.size() != 0)
		{
			float _end_dt = -1;
			if (is_import&& _DrawRectLayer->animation)
			{
				_end_dt = _DrawRectLayer->_MySpineDuration * oneFPX;
			}
			_end_dt = _end_dt > FPX ? _end_dt : FPX;
			is_import = true;
			_DrawRectLayer->setMySpineAnimation(animation_list.at(0).toStdString().c_str(), true);
			ui.dockWidget->setWindowTitle(animation_list.at(0));
			setSlideEndFPX(_DrawRectLayer->_MySpineDuration * oneFPX * 1);
			setPerWiget(_DrawRectLayer->_MySpineDuration * oneFPX);
			//从.data文件中导入数据
			Init();

			btn = sliderButton.at(0);
			btn->Is_Click = true;
			btn->setPalette(QPalette(Qt::green));
			btn->setAutoFillBackground(true);
			showline = sliderFameshow.at((btn->Singl_ID));
			showline->setVisible(true);
			_lastButton = btn;


			setMyFrame(-1, -1, false, _DrawRectLayer->_MySpineDuration * oneFPX > _end_dt ? _DrawRectLayer->_MySpineDuration * oneFPX : _end_dt);
			SlderAnimationAction();

		}
		else
		{
			//QMessageBox::about(this, tr("information"), tr("No animations"));
			QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有animations"));
		}

	}
	else{
		//点的是取消
	}
}
void QtEdit::export_byteData()
{
	//ShowMsg("Export");
	if (!is_import)
	{
		QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有导入资源,请先导入资源"));
		//QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有导入资源，是否先导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		//if (rb == QMessageBox::Yes)
		//{
		//	import();

		//}

	}
	else
	{
		QString fileName = QFileDialog::getSaveFileName(this,
			codec->toUnicode("导出二进制数据"),
			export_Byte_Path,
			tr("byte Files (*.byte);; all files (*)"));

		if (!fileName.isNull())
		{
			int i;
			//fileName是文件名
			MySQLite(true, fileName, "byte_path");
			_Export_Data = Export_Data::getInstence();
			_Export_Data->DrawDataTo_Qtedit();
			_Export_Data->Dosave_ExportByte(fileName.toStdString().c_str(), spritesPoints );
		}
		else
		{
			//点的是取消
		}
	}
}
void QtEdit::closeEvent(QCloseEvent *event)
{
	if (this->windowTitle().indexOf("*") != -1)
	{
		std::string showabout = "当前未保存是否退出?";
		switch (QMessageBox::warning(this, codec->toUnicode("警告"), codec->toUnicode(showabout.c_str()),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
		case QMessageBox::Save:
			//label->setText(" Warning button / Save ");
			_Export_Data = Export_Data::getInstence();
			_Export_Data->DrawDataTo_Qtedit();
			_Export_Data->Dosave_JsonData(saveDataName.toStdString().c_str(), spritesPoints, true);
			cocos2d::Director::getInstance()->end();
			exit(0);
			qApp->quit();
			event->accept();  //接受退出信号，程序退出
			break;
		case QMessageBox::Discard:
			//label->setText(" Warning button / Discard ");
			cocos2d::Director::getInstance()->end();
			exit(0);
			qApp->quit();
			event->accept();  //接受退出信号，程序退出
			break;
		case QMessageBox::Cancel:
			//label->setText(" Warning button / Cancel ");
			event->ignore();  //忽略退出信号，程序继续运行
			break;
		default:
			break;
		}
		
	}
	else
	{
		cocos2d::Director::getInstance()->end();
		exit(0);
		qApp->quit();
		event->accept();  //接受退出信号，程序退出
	}
}
void QtEdit::setGLView(QWidget *glWidget)
{
	_glWidget = glWidget;

	if (_glWidget)
	{
		this->setParent((HWND)glWidget->winId());
 		ui.SceneWidget->setWidget(_glWidget);
		_glWidget->setFixedHeight(639);
		//ui.SceneWidget->setTitleBarWidget(_glWidget);
 		setCentralWidget(ui.SceneWidget);
	}
}
void QtEdit::MySQLite(bool is_Update /* = false */, QString data /* = 0  */, QString col_name /* = "" */)
{
	int i;
	if (!is_Update)
	{
		DBUtil *db = DBUtil::getInstance();
		db->openDBWithName("QtEditSQLite");
		//db->deleteTable("DROP TABLE IF EXISTS tb_FilePath;", "tb_FilePath");
		db->createTable("create table if not exists tb_FilePath(open_c3b_path VARCHAR(50) NOT NULL ,open_spine_path VARCHAR(50) NOT NULL, byte_path VARCHAR(50) NOT NULL , json_path VARCHAR(50) NOT NULL)", "tb_FilePath");
		std::vector<std::map<std::string, std::string> > SQL_data = db->searchData("select * from tb_FilePath");
		if (SQL_data.size() == 0)
		{
			db->insertData("insert into tb_FilePath values('./' , './', './' , './')");
		}
		for (i = 0; i < SQL_data.size(); i++)
		{
			map<string, string> temp = SQL_data.at(i);
			//temp.at(0).at(1);
			for (map<string, string>::iterator iter = temp.begin(); iter != temp.end(); ++iter)
			{
				log("%s:%s", iter->first.c_str(), iter->second.c_str());
				if (iter->first == "byte_path")
				{
					export_Byte_Path = iter->second.c_str();
				}
				else if (iter->first == "json_path")
				{
					export_Json_Path = iter->second.c_str();
				}
				else if (iter->first == "open_spine_path")
				{
					openSpineFile_Path = iter->second.c_str();
				}
				else
				{
					openC3bFile_Path = iter->second.c_str();
				}
				//openFile_Path = iter->second.c_str();
			}
		}
		db->closeDB();
	}
	else
	{
		DBUtil *db = DBUtil::getInstance();
		db->openDBWithName("QtEditSQLite");
		std::sprintf(myshowstr, "update tb_FilePath set %s = '%s'", col_name.toStdString().c_str() , data.toStdString().c_str());
		db->updateData(myshowstr);
		db->closeDB();
		if (col_name.toStdString() == "open_c3b_path")
		{
			openC3bFile_Path = data;
		}
		else if (col_name.toStdString() == "json_path")
		{
			export_Json_Path = data;
		}
		else if (col_name.toStdString() == "open_spine_path")
		{
			openSpineFile_Path = data;
		}
		else
		{
			export_Byte_Path = data;
		}
	}
}
void QtEdit::exportData()
{
	//ShowMsg("Export");
	if (!is_import)
	{
		//QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有导入资源，是否先导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		//if (rb == QMessageBox::Yes)
		//{
		//	import();
		//	
		//}
		QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有导入资源，请先导入资源"));
	}
	else
	{
		QString fileName = QFileDialog::getSaveFileName(this,
			codec->toUnicode("导出JSON文件"),
			export_Json_Path,
			tr("json Files (*.json);; all files (*)"));

		if (!fileName.isNull())
		{
			//fileName是文件名
			//doSaveData(fileName);
			MySQLite(true, fileName, "json_path");
			_Export_Data = Export_Data::getInstence();
			_Export_Data->DrawDataTo_Qtedit();
			_Export_Data->Dosave_JsonData(fileName.toStdString().c_str(), spritesPoints);
		}
		else
		{
			//点的是取消
		}
	}
}
void QtEdit::ReChangeInput()
{
	ui.Height->setText(QString("%1").arg(ui.Re_Height->text().toFloat() + _IN_Height));
	ui.Width->setText(QString("%1").arg(ui.Re_Width->text().toFloat() + _IN_Width));
	ChangeInput();
}
void QtEdit::ActionHelp()
{
	//QMessageBox::aboutQt(NULL, "About Qt");
	std::string showabout = "";
	showabout = "cocos Action Edit是FBX用cocos2dx自带的转换器转换到c3b或c3t中，支持一个model多个Animation的动作编辑器\n";
	showabout += "贴图的名字必须和model的一样，并且贴图文件是.png格式，动作的c3b和c3t必须放在animations文件夹下\n";
	showabout += "本编辑器还支持Spine的操作，Spine的文件要求是json文件和atlas文件名必须一致，否则出错,\n";
	showabout += "这个编辑器支持保存操作、导出二进制文件和导出json格式操作。二进制文件格式为自己的格式";
	showabout += "\n本编辑器存在很多问题。如发现问题发邮件到：liweicg@gmail.com";
	showabout += "\nCopyRight(©) killer & TimeNew Studios";
	QMessageBox::about(NULL, "About Edit", codec->toUnicode(showabout.c_str()));
}

void QtEdit::openData()
{
	QDir dir;
	std::sprintf(myshowstr, "cmd   /c   %s/RunScore/StartFBXToCocos.bat", dir.currentPath().toStdString().c_str());
	WinExec(myshowstr, SW_HIDE);
}
void QtEdit::import()
{
	QString file_name;
	QString filter = openC3bFile_Path;;
	if (openC3bFile_Path.lastIndexOf(".") != -1)
	{
		if (openC3bFile_Path.mid(openC3bFile_Path.lastIndexOf(".") + 1) != "c3t")
		{
			filter = tr("c3b Files (*.c3b);; c3t Files (*.c3t);; all Files (*)");
		}
		else
		{
			filter = tr("c3t Files (*.c3t);; c3b Files (*.c3b);; all Files (*)");
		}
	}
	if (this->windowTitle().indexOf("*") != -1)
	{
		QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有操作保存，是否先保存再导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::Yes)
		{
			_Export_Data = Export_Data::getInstence();
			_Export_Data->DrawDataTo_Qtedit();
			_Export_Data->Dosave_JsonData(saveDataName.toStdString().c_str(), spritesPoints, true);
		}
	}
	file_name = QFileDialog::getOpenFileName(this,
		codec->toUnicode("导入文件"), openC3bFile_Path, filter);
	if (!file_name.isNull())
	{
		//fileName是文件名
		SpiteS_Model = 1;
		MySQLite(true , file_name , "open_c3b_path");
		_DrawRectLayer = DrawRectLayer::getInstence();
		//log("%d", file_name.lastIndexOf("/"));
		//QStringList strlist = file_name.split("Resources/");
		QString Re_File_name = file_name.mid(file_name.lastIndexOf("/") + 1);
		this->setWindowTitle(Re_File_name);
		
		if (is_import && _DrawRectLayer->sp)
		{
			_DrawRectLayer->removeChild(_DrawRectLayer->sp, true);
		}

		QFileInfo fi; 
		fi = QFileInfo(file_name);
		saveDataName = fi.path() + "/" +  fi.fileName().split(".").at(0) + tr(".data");
		_filename = fi.fileName().split(".").at(0);
		if (is_import)
		{
			animation_list.clear();
			_DrawRectLayer->removeAllChildrenWithCleanup(true);
			_DrawRectLayer->spritePoints.clear();
			_DrawRectLayer->DrawInitPosi();
			_DrawRectLayer->EndUpdate();
			pu = 1;
			pausebuttonclick();
		}
		
		AddAnimationList(file_name);
		
		if (animation_list.size() != 0)
		{
			float _end_dt = -1;
			if (is_import&& _DrawRectLayer->animation)
			{
				_end_dt = _DrawRectLayer->animation->getDuration() * oneFPX;
			}
			_end_dt = _end_dt > FPX ? _end_dt : FPX;
			is_import = true;
			_DrawRectLayer->updateMySprite3D(file_name.toStdString(), file_name.split(".").at(0).toStdString() + ".png", animation_list.at(0).toStdString());
			ui.dockWidget->setWindowTitle(animation_list.at(0));
			setSlideEndFPX(_DrawRectLayer->animation->getDuration() * oneFPX * 1);
			setPerWiget(_DrawRectLayer->animation->getDuration() * oneFPX);
			//从.data文件中导入数据
			Init();
			
			btn = sliderButton.at(0);
			btn->Is_Click = true;
			btn->setPalette(QPalette(Qt::green));
			btn->setAutoFillBackground(true);
			showline = sliderFameshow.at((btn->Singl_ID));
			showline->setVisible(true);
			_lastButton = btn;
			
			
			//MySpriteChange();
			setMyFrame(-1, -1, false, _DrawRectLayer->animation->getDuration() * oneFPX > _end_dt ? _DrawRectLayer->animation->getDuration() * oneFPX : _end_dt);
			SlderAnimationAction();
			SetMyUI();
			//btn = sliderButton.at(0);
			//btn->Is_Click = true;
			//btn->setPalette(QPalette(Qt::green));
			//btn->setAutoFillBackground(true);
			//showline = sliderFameshow.at((btn->Singl_ID));
			//showline->setVisible(true);
			//_lastButton = btn;
			//SlderAnimationAction();
			//AddSliderButton();
		}
		else
		{
			//QMessageBox::about(this, tr("information"), tr("No animations"));
			QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有animations"));
		}
		
	}
	else{
		//点的是取消
	}
}

void QtEdit::Init()
{
	MyVector * tempVector;
	MySpritePoint * tempSprite;
	spritesPoints.clear();
	_DrawRectLayer->spritePoints.clear();
	QFile file(saveDataName);
	if (!file.exists())
	{
		file.open(QIODevice::ReadWrite);
		file.close();
		return;
	}
	QString _MyData = NULL;
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::about(this, tr("information"), tr("Read ERROR"));
		return;
	}
	_MyData = QByteArray::fromBase64(file.readAll());
	file.close();
	int i, j;
	double ex, ey, sx, sy;
	double _wi, _he, _sclx, _scly;
	float rotate;
	QString oneJieDian;
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(_MyData.toLatin1(), &json_error);
	if (json_error.error == QJsonParseError::NoError)
	{
		if (parse_doucment.isObject())
		{
			QJsonObject readObj = parse_doucment.object();
			if (readObj.contains(_filename))
			{
				QJsonObject root_Obj = readObj.value(_filename).toObject();
				for (i = 0; i < animation_list.size(); i ++ )
				{
					oneJieDian = animation_list.at(i).mid(animation_list.at(i).lastIndexOf("/") + 1).split(".").at(0);
					tempVector = new MyVector();
					if (root_Obj.contains(oneJieDian))
					{
						//FREE_DEL(tempVector);
						QJsonArray per_Root = root_Obj[oneJieDian].toArray();
						for (j = 0; j < per_Root.size(); j++)
						{
							//FREE_DEL(tempSprite);
							tempSprite = new MySpritePoint();
							QJsonValue per_Value = per_Root[j];
							QJsonObject per_Obj = per_Value.toObject();
							if (per_Obj.contains("fre"))
							{
								int fre = per_Obj.value("fre").toInt();
								tempSprite->Single_ID = fre;
							}
							if (per_Obj.contains("act"))
							{
								QJsonObject act_Obj = per_Obj.value("act").toObject();
								_he = act_Obj.value("he").toDouble();
								_wi = act_Obj.value("wi").toDouble();
								_sclx = act_Obj.value("scalx").toDouble();
								_scly = act_Obj.value("scaly").toDouble();
								tempSprite->_ScallX = _sclx;
								tempSprite->_ScallY = _scly;
								tempSprite->_width = _wi;
								tempSprite->_height = _he;
								tempSprite->Is_ActFra = true;

							}
							if (per_Obj.contains("att"))
							{
								QJsonObject att_Obj = per_Obj.value("att").toObject();
								sx = att_Obj.value("sx").toDouble();
								sy = att_Obj.value("sy").toDouble();
								ex = att_Obj.value("ex").toDouble();
								ey = att_Obj.value("ey").toDouble();
								rotate = att_Obj.value("ro").toDouble();
								Vec2 spoint(sx , sy);
								Vec2 epoint(ex, ey);
								tempSprite->setAttackVertices(spoint, epoint);
								tempSprite->RotateAtt = rotate;
								tempSprite->Is_AttFra = true;
							}
							if (per_Obj.contains("inj"))
							{
								QJsonObject inj_Obj = per_Obj.value("inj").toObject();
								sx = inj_Obj.value("sx").toDouble();
								sy = inj_Obj.value("sy").toDouble();
								ex = inj_Obj.value("ex").toDouble();
								ey = inj_Obj.value("ey").toDouble();
								rotate = inj_Obj.value("ro").toDouble();
								Vec2 spoint(sx, sy);
								Vec2 epoint(ex, ey);
								tempSprite->setInjureVertices(spoint, epoint);
								tempSprite->RotateInj = rotate;
								tempSprite->Is_InjFra = true;
							}
							if (per_Obj.contains("body"))
							{
								QJsonObject body_Obj = per_Obj.value("body").toObject();
								sx = body_Obj.value("sx").toDouble();
								sy = body_Obj.value("sy").toDouble();
								ex = body_Obj.value("ex").toDouble();
								ey = body_Obj.value("ey").toDouble();
								rotate = body_Obj.value("ro").toDouble();
								Vec2 spoint(sx, sy);
								Vec2 epoint(ex, ey);
								tempSprite->setBodyVertices(spoint, epoint);
								tempSprite->Is_BodyFra = true;
							}
							if (per_Obj.contains("eff"))
							{
								QJsonObject eff_Obj = per_Obj.value("eff").toObject();
								sx = eff_Obj.value("sx").toDouble();
								sy = eff_Obj.value("sy").toDouble();
								ex = eff_Obj.value("ex").toDouble();
								ey = eff_Obj.value("ey").toDouble();
								rotate = eff_Obj.value("ro").toDouble();
								Vec2 spoint(sx, sy);
								Vec2 epoint(ex, ey);
								tempSprite->setEffectVertices(spoint, epoint);
								tempSprite->Is_EffFra = true;
							}
							tempVector->Sprites.push_back(tempSprite);
						}
						
					}
					tempVector->Singl_ID = i;
					spritesPoints.push_back(tempVector);
					
				}
			}
		}
	}
	for (i = 0; i < spritesPoints.size(); i ++ )
	{
		if (spritesPoints.at(i)->Singl_ID == 0)
		{
			myVector = new MyVector();
			myVector->Singl_ID = 0;
			myVector->Sprites = spritesPoints.at(i)->Sprites;
			//if (spritesPoints.at(i)->Sprites.at(0)->Single_ID == 0)
			//{
			//	myVector->initFromSprite(spritesPoints.at(i)->Sprites.at(i));
			//}
			for (i = 0; i < spritesPoints.at(i)->Sprites.size(); i++)
			{
				if (spritesPoints.at(i)->Sprites.at(i)->Single_ID == 0)
				{
					myVector->initFromSprite(spritesPoints.at(i)->Sprites.at(i));
					break;
				}
			}
			_DrawRectLayer->spritePoints = myVector->Sprites;
			//SetMyUI();
			break;;
		}
	}
}

void QtEdit::SetMyUI()
{
	if (myVector != nullptr)
	{
		ui.Height->setText(QString::number(myVector->_height, 'f', 0));
		ui.Width->setText(QString::number(myVector->_width, 'f', 0));
		ui.ScallX->setText(QString::number(myVector->_ScallX, 'f', 0));
		ui.ScallY->setText(QString::number(myVector->_ScallY, 'f', 0));
		ui.Re_Height->setText(QString("%1").arg(ui.Height->text().toFloat() - _IN_Height));
		ui.Re_Width->setText(QString("%1").arg(ui.Width->text().toFloat() - _IN_Width));
		//ChangeInput();
		MySpriteChange();
	}
}
//Slider下的Button响应
void QtEdit::SlderButtonClick()
{
	btn = dynamic_cast<QtButton*>(sender());
	if (!is_import)
	{
		FPX = btn->Singl_ID;
	}
	if (is_import && btn->Singl_ID <= FPX)
	{
		//_DrawRectLayer->unscheduleUpdate();
		_DrawRectLayer->EndUpdate();
		ui.PauseButton->setText("Start");
		pu = -1;
		//_DrawRectLayer->drawPositionEdit(btn->Singl_ID);
	}
	ui.PencentageSlider->setValue(btn->Singl_ID);
	//SlderAnimationAction();

	
}
void  QtEdit::SlderAnimationAction()
{
	if (is_import)
	{
		if (btn->Singl_ID > FPX)
		{
			return;
		}
		//if (btn->Singl_ID == FPX)
		//{
		//	if (is_import)
		//	{
		//		//std::sprintf(myshowstr, "%d", 100);
		//		_DrawRectLayer->animate->updateOnPercentage(0.01 * btn->Singl_ID * (100.0 / FPX));
		//		return;
		//	}
		//}
	}
	if (_lastButton != nullptr)
	{
		if (_lastButton->Singl_ID % 5 != 0)
		{
			showline = sliderFameshow.at((_lastButton->Singl_ID ));
			showline->setVisible(false);
		}
		try
		{
			_lastButton->Is_Click = false;
			//_lastButton->setAutoFillBackground(true);
			_lastButton->setStyleSheet("background: transparent;border:0px");
		}
		catch (...)
		{
			
		}
		
		//_endButton->setPalette(QPalette(Qt::red));
	}
	if (btn->Singl_ID < FPX || FPX == -1)
	{
		_lastButton = btn;
	}
	else if (!is_import)
	{
		_lastButton = btn;
	}
	btn->Is_Click = true;
	btn->setPalette(QPalette(Qt::green));
	btn->setAutoFillBackground(true);
	showline = sliderFameshow.at((btn->Singl_ID));
	showline->setVisible(true);
	if (is_import)
	{
		_DrawRectLayer->drawPositionEdit(btn->Singl_ID);
		if (1 == SpiteS_Model)
		{
			_DrawRectLayer->animate->updateOnPercentage(0.01 * btn->Singl_ID * 100.0 / (FPX - 1));
		}
		else
		{
			//Spine
			_DrawRectLayer->updateMySpinePercentage(btn->Singl_ID / oneFPX);
		}
		_endButton->setPalette(QPalette(Qt::red));
	}
	myBox_Comboxlist.clear();
	myBox_Comboxlist.push_back(_InComboxtext);
	if (btn->Is_BodyFra)
	{
		myBox_Comboxlist.push_back(_Bodytext);
	}
	if (btn->Is_InjFra)
	{
		myBox_Comboxlist.push_back(_Injtext);
	}
	if (btn->Is_AttFra)
	{
		myBox_Comboxlist.push_back(_Atttext);
	}
	if (btn->Is_EffFra)
	{
		myBox_Comboxlist.push_back(_Effecttext);
	}
	setMyBox_ComBox(myBox_Comboxlist);
}

void QtEdit::setMyBox_ComBox(QStringList myBox_Comboxlist)
{
	ui.MyBox_comboBox->clear();
	ui.MyBox_comboBox->insertItems(0, myBox_Comboxlist);
}
//
void QtEdit::ChangeSliderButton()
{

}

//添加按钮
void QtEdit::AddSliderButton()
{
	int  i;
	int size = 400;
	int wi;
	_lastButton = NULL;
	buttonWidget = new QWidget(ui.PerWiget);
	buttonWidget->setPalette(QPalette(Qt::gray));
	buttonWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea = new QScrollArea(ui.PerWiget);
	scrollArea->setAlignment(Qt::AlignCenter);
	//scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(buttonWidget);
	scrollArea->setGeometry(QRect(0, 20, 1780, 210));
	scallbar = scrollArea->horizontalScrollBar();
	buttonWidget->setGeometry(QRect(0, 0, 8000, 190));
	ui.PencentageSlider->setParent(buttonWidget);
	ui.PencentageSlider->setGeometry(QRect(0, 0, size * 20, 50));
	ui.PencentageSlider->setMinimum(0);
	ui.PencentageSlider->setMaximum(size);
	sliderFameshow.clear();
	sliderButton.clear();
	//float duratime = _DrawRectLayer->animation->getDuration();
	QFont font;
	font.setPointSize(9);
	for (i = 0; i < size; i ++ )
	{
		std::sprintf(myshowstr, "%d", i);
		line = new QFrame(buttonWidget);
		oneButton = new QtButton(i , buttonWidget);
		//oneButton->setAutoFillBackground(true);
		
		oneButton->Singl_ID = i;
		oneButton->Is_Click = false;
		wi = i * 20;
		oneButton->setGeometry(QRect(wi, 60, 20, 105));
		oneButton->setStyleSheet("background: transparent;border:0px");
		oneButton->_EffFraButton->setGeometry(QRect(wi, 165, 20, 5));
		//oneButton->_AttFraButton->setAutoFillBackground(true);
		oneButton->_EffFraButton->setStyleSheet("background: transparent;border:0px");
		oneButton->_AttFraButton->setGeometry(QRect(wi, 170, 20, 5));
		//oneButton->_AttFraButton->setAutoFillBackground(true);
		oneButton->_AttFraButton->setStyleSheet("background: transparent;border:0px");
		oneButton->_ActFraButton->setGeometry(QRect(wi, 175, 20, 5));
		//oneButton->_AttFraButton->setAutoFillBackground(true);
		oneButton->_ActFraButton->setStyleSheet("background: transparent;border:0px");
		oneButton->_InjFraButton->setGeometry(QRect(wi, 180, 20, 5));
		//oneButton->_AttFraButton->setAutoFillBackground(true);
		oneButton->_InjFraButton->setStyleSheet("background: transparent;border:0px");
		oneButton->_BodyFraButton->setGeometry(QRect(wi, 185, 20, 5));
		//oneButton->_BodyFraButton->setAutoFillBackground(true);
		oneButton->_BodyFraButton->setStyleSheet("background: transparent;border:0px");
		line->setGeometry(QRect(wi, 60, 3, 105));
		line->setFrameShape(QFrame::VLine);
		line->setFrameShadow(QFrame::Sunken);
		QObject::connect(oneButton, SIGNAL(clicked()), this, SLOT(SlderButtonClick()));
		showline = new QLabel(buttonWidget);
		showline->setGeometry(QRect(wi, 47, 20, 15));
		showline->setFont(font);
		showline->setText(myshowstr);
		showline->setAlignment(Qt::AlignCenter);
		showline->setVisible(false);
		if (i % 5 == 0)
		{
			showline->setVisible(true);
		}
		sliderFameshow.push_back(showline);
		sliderButton.push_back(oneButton);
		//sliderButtonList.push_back(oneButton);
	}

}

void QtEdit::AnimationUpdate(float dt)
{
	//_lastButton = btn;
	int sing_id = dt * 100.0 / (100.0 / oneFPX);
	
	//btn = sliderButton.at(sing_id);
	ui.PencentageSlider->setValue(sing_id);
	//SlderAnimationAction();
}

void QtEdit::showmessageChange()
{
	
	mymsg = ui.showmessage->toPlainText().toStdString();
}
void QtEdit::ChangeInput()
{
	QString combox_text = ui.MyBox_comboBox->currentText();
	ui.Re_Height->setText(QString("%1").arg(ui.Height->text().toFloat() - _IN_Height));
	ui.Re_Width->setText(QString("%1").arg(ui.Width->text().toFloat() - _IN_Width));
	_DrawRectLayer = DrawRectLayer::getInstence();
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	if (btn != nullptr && is_import)
	{
		int i = btn->Singl_ID;
		_DrawRectLayer->EndUpdate();
		//for (i = 0; i < FPX; i ++)
		{
			//if (sliderButton.at(i)->Singl_ID == btn->Singl_ID)
			{
				//sliderButton.at(i)->Is_ActFra = true;
				sliderButton.at(i)->_ActFraButton->setPalette(QPalette(Qt::blue));
				sliderButton.at(i)->_ActFraButton->setAutoFillBackground(true);
				sliderButton.at(i)->Is_ActFra = true;
				MySpritePoint * OneSpritePoint = new MySpritePoint();
				OneSpritePoint->Single_ID = _DrawRectLayer->Single_ID;
				OneSpritePoint->attackVertices = _DrawRectLayer->attackNode->Vertices;
				OneSpritePoint->RotateAtt = _DrawRectLayer->attackNode->Rotate;
				OneSpritePoint->injureVertices = _DrawRectLayer->injuredNode->Vertices;
				OneSpritePoint->RotateInj = _DrawRectLayer->injuredNode->Rotate;
				//if (ui.Width->text().toDouble() != _IN_Width || ui.Height->text().toDouble() != _IN_Height || ui.ScallX->text().toDouble() != _IN_SacllX || ui.ScallY->text().toDouble() != _IN_ScallY)
				//{
				//	OneSpritePoint->Is_ActFra = true;
				//}
				//else
				//{
				//	OneSpritePoint->Is_ActFra = false;
				//}
				OneSpritePoint->Is_ActFra = true;
				//新的
				bool Is_Has = false;
				MySpritePoint * _tempSpritePoint;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					_tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					//showMsg("SIngle_ID", NULL, _tempSpritePoint->Single_ID);
					//showMsg("Size", NULL, spritePoints.size());
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->attackVertices = OneSpritePoint->attackVertices;
						_DrawRectLayer->spritePoints.at(i)->injureVertices = OneSpritePoint->injureVertices;
						//if (ui.Width->text().toDouble() != _IN_Width || ui.Height->text().toDouble() != _IN_Height || ui.ScallX->text().toDouble() != _IN_SacllX || ui.ScallY->text().toDouble() != _IN_ScallY)
						//{
						//	_DrawRectLayer->spritePoints.at(i)->Is_ActFra = true;
						//}
						//else
						//{
						//	_DrawRectLayer->spritePoints.at(i)->Is_ActFra = false;
						//	sliderButton.at(btn->Singl_ID)->deleteAct();
						//}
						_DrawRectLayer->spritePoints.at(i)->Is_ActFra = true;
						Is_Has = true;
						break;
					}
				}
				if (!Is_Has)
				{
					MySpritePoint * ss = new MySpritePoint();
					ss->Single_ID = OneSpritePoint->Single_ID;
					ss->Is_ActFra = OneSpritePoint->Is_ActFra;
					ss->attackVertices = OneSpritePoint->attackVertices;
					ss->injureVertices = OneSpritePoint->injureVertices;
					_DrawRectLayer->spritePoints.push_back(ss);
				}
				//break;
			}
		}
	}
	if (is_import)
	{
		
		MySpriteChange();
		SlderAnimationAction();
	}
	else
	{
		//QMessageBox::about(this, tr("information"), tr("NULL Import"));
	}
	ui.MyBox_comboBox->setCurrentText(combox_text);
}

void QtEdit::pausebuttonclick()
{
	//QPushButton* btn = dynamic_cast<QPushButton*>(sender());
	//ShowMsg(btn->text().toStdString());
	pu *= -1;
	if (is_import)
	{
		if (-1 == pu)
		{
			ui.PauseButton->setText(tr("Start"));
			_DrawRectLayer->EndUpdate();
			//_DrawRectLayer->unscheduleUpdate();
		}
		else
		{
			ui.PauseButton->setText(tr("Pause") );
			_DrawRectLayer->StartUpdate();
			//_DrawRectLayer->scheduleUpdate();
			
		}
	}
}


void QtEdit::SlderChange(float Percentage)
{
	ui.PencentageSlider->setValue((int)(Percentage * 100));
}

void QtEdit::MySpriteChange()
{
	//由于窗口植入QT中有所变化，所以需要进行一个数值的等宽高缩放，
	Point point(ui.Width->text().toFloat(), ui.Height->text().toFloat());
	//_DrawRectLayer->sp->setPosition(point);
	if (myVector != NULL)
	{
		myVector->_width = ui.Width->text().toFloat();
		myVector->_height = ui.Height->text().toFloat();
	}
	//if (ui.ScallX->text().toDouble() > 0.0)
	{
		//_DrawRectLayer->sp->setScaleX(ui.ScallX->text().toDouble() );
		if (myVector != NULL)
		{
			myVector->_ScallX = ui.ScallX->text().toFloat();
		}
	}
	//if (ui.ScallY->text().toDouble() > 0.0)
	{
		//_DrawRectLayer->sp->setScaleY(ui.ScallY->text().toDouble());
		if (myVector != NULL)
		{
			myVector->_ScallY = ui.ScallY->text().toFloat();
		}
	}
	_DrawRectLayer->setSpritePosition(point.x, point.y, ui.ScallX->text().toFloat(), ui.ScallY->text().toFloat());
	if (btn != nullptr)
	{
		int i;
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i ++)
		{
			if (_DrawRectLayer->spritePoints.at(i)->Single_ID == btn->Singl_ID)
			{
				_DrawRectLayer->spritePoints.at(i)->_height = ui.Height->text().toDouble();
				_DrawRectLayer->spritePoints.at(i)->_width = ui.Width->text().toDouble();
				_DrawRectLayer->spritePoints.at(i)->_ScallX = ui.ScallX->text().toDouble();
				_DrawRectLayer->spritePoints.at(i)->_ScallY = ui.ScallY->text().toDouble();
				break;
			}
		}
	}
	//SlderAnimationAction();
	//AnimationSlderChange();
}

//进度条有点击
void QtEdit::AnimationSlderClick(int per)
{
	btn = sliderButton.at(per);
	if (is_import)
	{
		//_DrawRectLayer->unscheduleUpdate();
		_DrawRectLayer->EndUpdate();
		ui.PauseButton->setText("Start");
		pu = -1;
	}
	SlderAnimationAction();
		
}

void QtEdit::setPerWiget(int max)
{
	ui.PencentageSlider->setGeometry(QRect(0, 0, FPX * 20, 50));
	ui.PencentageSlider->setMaximum(max);
	ui.PencentageSlider->setMinimum(0);
	ui.PencentageSlider->setValue(0);
	;
}

//进度条值变换了
void QtEdit::AnimationSlderChange()
{
	double a = ui.PencentageSlider->value();
	if (a >= sliderButton.size())
	{
		return;
	}
	btn = sliderButton.at(a * 1);
	SlderAnimationAction();
	a *= 0.01;
	//ui.PerWiget->setWindowTitle("PerCentage  " + QString::number((int) (a * 100)) + "%");
	//if (is_import)
	//{
	//	_DrawRectLayer->animate->updateOnPercentage(a);
	//}
}
void QtEdit::yestButtonClick()
{
	auto _DrawRectLayer = DrawRectLayer::getInstence();
	//_DrawRectLayer->updatemydata(ui.lineEdit->text().toStdString());
}



//键盘操作
//Ctrl是否有按下
void QtEdit::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Control)
	{
		Ctrl_Is_On = true;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Shift_is_ON = true;
	}
	if (e->key() == Qt::Key_Space)
	{
		Space_is_ON = true;
	}
	//if (Ctrl_Is_On == true && e->key() == Qt::Key_Z)
	//{
	//	if (is_import)
	//	{
	//		_DrawRectLayer->CtrlZ();
	//	}

	//}
	//if (Ctrl_Is_On == true && e->key() == Qt::Key_Y)
	//{
	//	if (is_import)
	//	{
	//		_DrawRectLayer->CtrlY();
	//	}

	//}
	//if (Ctrl_Is_On == true && e->key() == Qt::Key_D)
	//{
	//	if (is_import)
	//	{
	//		_DrawRectLayer->CtrlD();
	//	}
	//}
	if (Ctrl_Is_On == true && e->key() == Qt::Key_S)
	{
		if (is_import)
		{
			this->setWindowTitle(this->windowTitle().split("*").at(0));
			//doSaveData(saveDataName , true);
			_Export_Data = Export_Data::getInstence();
			_Export_Data->DrawDataTo_Qtedit();
			_Export_Data->Dosave_JsonData(saveDataName.toStdString().c_str(), spritesPoints, true);
		}
	}

}

void QtEdit::doSaveData(QString name , bool istobase)
{

	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;
	Json::Value OnjectItem;
	Json::Value SItem;
	Json::Value _data;
	int i, j, k;
	int attsx, attsy, attex, attey;
	float attrotate;
	int injsx, injsy, injex, injey;
	float injrotate;
	int bodsx, bodsy, bodex, bodey;
	int effsx, effsy, effex, effey;
	MyVector * _tempVector = new MyVector();
	if (myVector == NULL)
	{
		myVector = new MyVector();
		myVector->Singl_ID = 0;
		myVector->Sprites = _DrawRectLayer->spritePoints;
		spritesPoints.push_back(myVector);
	}
	for (i = 0; i < spritesPoints.size(); i++)
	{
		tempVector = spritesPoints.at(i);
		if (tempVector->Singl_ID == myVector->Singl_ID)
		{
			spritesPoints.at(i)->Sprites = _DrawRectLayer->spritePoints;
			break;
		}
	}
	QFile file(name);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::about(this, tr("information"), tr("Save Error"));
		return;
	}
	MySpritePoint * _tempSp;
	QTextStream out(&file);
	arrayObj.clear();
	FREE_DEL_VEC(_tempVector);
	_tempVector = nullptr;
	for (i = 0; i < spritesPoints.size(); i++)
	{
		_tempVector = spritesPoints.at(i);
		OnjectItem.clear();
		for (j = 0; j < _tempVector->Sprites.size(); j++)
		{
			attsx = -100.0;
			injex = -100.0;
			bodsx = -100.0;
			effsx = -100.0;
			item.clear();
			_tempSp = _tempVector->Sprites.at(j);
			if (_tempSp->attackVertices != nullptr && _tempSp->Is_AttFra)
			{
				attsx = _tempSp->attackVertices[0].x;
				attsy = _tempSp->attackVertices[0].y;
				attex = _tempSp->attackVertices[2].x;
				attey = _tempSp->attackVertices[2].y;
			}
			attrotate = _tempSp->RotateAtt;

			if (_tempSp->injureVertices != nullptr && _tempSp->Is_InjFra)
			{
				injsx = _tempSp->injureVertices[0].x;
				injsy = _tempSp->injureVertices[0].y;
				injex = _tempSp->injureVertices[2].x;
				injey = _tempSp->injureVertices[2].y;
			}
			injrotate = _tempSp->RotateInj;

			if (_tempSp->bodyVertices != nullptr && _tempSp->Is_BodyFra)
			{
				bodsx = _tempSp->bodyVertices[0].x;
				bodsy = _tempSp->bodyVertices[0].y;
				bodex = _tempSp->bodyVertices[2].x;
				bodey = _tempSp->bodyVertices[2].y;
			}
			if (_tempSp->effectVertices != nullptr && _tempSp->Is_EffFra)
			{
				effsx = _tempSp->effectVertices[0].x;
				effsy = _tempSp->effectVertices[0].y;
				effex = _tempSp->effectVertices[2].x;
				effey = _tempSp->effectVertices[2].y;
			}
			if (_tempSp->Is_ActFra)
			{
				SItem.clear();
				SItem["he"] = _tempSp->_height;
				SItem["wi"] = _tempSp->_width;
				SItem["scalx"] = _tempSp->_ScallX;
				SItem["scaly"] = _tempSp->_ScallY;
				item["act"] = SItem;
			}
			if (attsx >= 0.0)
			{
				SItem.clear();
				SItem["sx"] = attsx;
				SItem["sy"] = attsy;
				SItem["ex"] = attex;
				SItem["ey"] = attey;
				SItem["ro"] = attrotate;
				item["att"] = SItem;
			}
			if (injex >= 0.0)
			{
				SItem.clear();
				SItem["sx"] = injsx;
				SItem["sy"] = injsy;
				SItem["ex"] = injex;
				SItem["ey"] = injey;
				SItem["ro"] = injrotate;
				item["inj"] = SItem;
			}
			if (bodsx >= 0.0)
			{
				SItem.clear();
				SItem["sx"] = bodsx;
				SItem["sy"] = bodsy;
				SItem["ex"] = bodex;
				SItem["ey"] = bodey;
				item["body"] = SItem;
			}
			if (effsx >= 0.0)
			{
				SItem.clear();
				SItem["sx"] = effsx;
				SItem["sy"] = effsy;
				SItem["ex"] = effex;
				SItem["ey"] = effey;
				item["eff"] = SItem;
			}
			item["fre"] = _tempSp->Single_ID;
			OnjectItem[j] = item;
			item["fre"] = _tempSp->Single_ID;
			OnjectItem[j] = item;
		}
		//_data["data"] = OnjectItem;
		//_data["scx"] = _tempVector->_ScallX;
		//_data["scy"] = _tempVector->_ScallY;
		//_data["he"] = _tempVector->_height;
		//_data["wi"] = _tempVector->_width;
		//arrayObj[animation_list.at(i).split("/").at(1).split(".").at(0).toStdString()] = OnjectItem;
		arrayObj[animation_list.at(i).mid(animation_list.at(i).lastIndexOf("/") + 1).split(".").at(0).toStdString()] = OnjectItem;
	}
	root[_filename.toStdString()] = arrayObj;
	std::string outfile;
	outfile = root.toStyledString();
	file.resize(0);
	const char * str = outfile.c_str();
	if (istobase)
	{
		out << (QByteArray(str).toBase64());
	}
	else
	{
		out << str;
	}
	file.close();
}
void QtEdit::keyReleaseEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Control)
	{
		Ctrl_Is_On = false;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Shift_is_ON = false;
	}
	if (e->key() == Qt::Key_Space)
	{
		Space_is_ON = false;
	}
}

void QtEdit::AddAnimationList(QString full_path_name)
{
	
	QFileInfo fi;
	QString file_name, file_path;
	fi = QFileInfo(full_path_name);
	file_name = fi.fileName();
	file_path = fi.absolutePath(); 
	file_path = file_path + "/animations/";
	re_file_path = file_path;
	int dir_count;
	QDir dir(file_path);
	if (1 == SpiteS_Model)
	{
		//SpiteS_Model = 1;
		//判断路径是否存在
		if (!dir.exists(file_path))
		{
			QMessageBox::about(this, tr("information"), tr("No animations Fold"));
			return;
		}
		//获取所选文件类型过滤器
		QStringList filters;
		filters << QString("*.c3t") << QString("*.c3b");
		//定义迭代器并设置过滤器
		dir.setNameFilters(filters);//设置文件名称过滤器，只为filters格式（后缀为.c3B，c3t等格式）
		dir_count = dir.count();
		if (dir_count <= 0)
		{
			return;
		}
	}
	else if (full_path_name.indexOf("atlas"))
	{
		//SpiteS_Model = 2;
	}
	animation_list.clear();
	//获取分隔符
	//只写结点的实现
	QList<QTreeWidgetItem *> rootList;
	//先把之前的清除了
	ui.AnimationtreeWidget->clear();
	QTreeWidgetItem *imageItem1 = new QTreeWidgetItem;   //添加第一个父节点
	imageItem1->setText(0, file_name.split(".").at(0));
	rootList.append(imageItem1);

	QTreeWidgetItem *imageItem1_1;
	int i, j;
	QString name, path;
	QString temp;
	int list_size = 0;
	bool is_in_list;
	if (1 == SpiteS_Model)
	{
		for (i = 0; i < dir_count; i++)
		{
			name = dir[i];  //文件名称
			path = re_file_path + name;   //文件路径

			list_size = animation_list.size();
			//查找是否有同名文件
			is_in_list = false;
			for (j = 0; j < list_size; j++)
			{
				temp = animation_list.at(j).split(".").at(0);//获取到文件名称，无后缀
				//存在同名
				if (path.split(".").at(0) == temp)
				{
					is_in_list = true;
				}
			}
			if (!is_in_list)
			{
				animation_list.append(path);
				ShowMsg("Import animations/" + name.toStdString());
				imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QString(path))); //添加子节点
				imageItem1->addChild(imageItem1_1);
			}
		}
	}
	else
	{
		//spine::SkeletonAnimation * MySpine = const_cast<SkeletonAnimation *>(_DrawRectLayer->MySpine);
		//spSkeletonData * self = MySpine->getSkeleton()->data;
		//for (i = 0; i < self->animationsCount; ++i)
		//{
		//	animation_list.append(self->animations[i]->name);
		//	imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QString(self->animations[i]->name))); //添加子节点
		//	imageItem1->addChild(imageItem1_1);
		//}
		vector<string> ani;
		ani = _DrawRectLayer->getSpineAnimation();
		for (i = 0; i < ani.size(); i ++)
		{
			animation_list.push_back(ani.at(i).c_str());
			imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QString(ani.at(i).c_str()))); //添加子节点
			imageItem1->addChild(imageItem1_1);
		}
			
	}
	_mycol = 0;
	ui.AnimationtreeWidget->insertTopLevelItems(0, rootList);  //将结点插入部件中

	ui.AnimationtreeWidget->expandAll(); //全部展开
}



//Tree点击事件
void QtEdit::AnimationTreeWidgetClick(QTreeWidgetItem * item, int column)
{
	int last_rol = -1;
	if (1 == SpiteS_Model)
	{
		last_rol = _DrawRectLayer->animation->getDuration() * oneFPX;
	}
	else
	{
		last_rol = _DrawRectLayer->_MySpineDuration * oneFPX;
	}
	last_rol++;
	QTreeWidgetItem *parent = item->parent();
	if (NULL == parent || !is_import) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
		return;
	int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)
	_mycol = col;
	char s[100];
	int i;
	bool Is_Has = false;
	if (myVector == NULL)
	{
		myVector = new MyVector();
		myVector->Singl_ID = 0;
		myVector->Sprites = _DrawRectLayer->spritePoints;
		spritesPoints.push_back(myVector);
	}
	for (i = 0; i < spritesPoints.size(); i ++)
	{
		tempVector = spritesPoints.at(i);
		if (tempVector->Singl_ID == myVector->Singl_ID)
		{
			spritesPoints.at(i)->Sprites = _DrawRectLayer->spritePoints;
			break;
		}
	}
	for (i = 0; i < spritesPoints.size(); i ++)
	{
		myVector = spritesPoints.at(i);
		if (myVector->Singl_ID == col)
		{
			Is_Has = true;
			_DrawRectLayer->spritePoints.clear();
			//if (myVector->Sprites.size() != 0 && myVector->Sprites.at(0)->Single_ID == 0)
			//{
			//	myVector->initFromSprite(myVector->Sprites.at(0));
			//}
			for (i = 0; i < myVector->Sprites.size();i++ )
			{
				if (myVector->Sprites.at(i)->Single_ID == 0)
				{
					myVector->initFromSprite(myVector->Sprites.at(i));
					break;
				}
			}
			_DrawRectLayer->spritePoints = myVector->Sprites;
			break;
		}
	}
	if (!Is_Has)
	{
		_DrawRectLayer->spritePoints.clear();
		myVector = new MyVector();
		myVector->Singl_ID = col;
		spritesPoints.push_back(myVector);
	}

	std::sprintf(s, "%s %d", "CL_", col);
	//
	if (1 == SpiteS_Model)
	{
		ShowMsg("animations/" + animation_list.at(col).split("animations/").at(1).toStdString());
		_DrawRectLayer->sp->stopAllActions();
		//CC_SAFE_RELEASE(_DrawRectLayer->animation);
		//CC_SAFE_RELEASE(_DrawRectLayer->animate);
		_DrawRectLayer->animation = Animation3D::getOrCreate(animation_list.at(col).toStdString());
		if (_DrawRectLayer->animation != NULL)
		{
			_DrawRectLayer->animate = Animate3D::create(_DrawRectLayer->animation);
			_DrawRectLayer->animate->is_auto_update = false;
			_DrawRectLayer->_RepeatForever = RepeatForever::create(_DrawRectLayer->animate);
			_DrawRectLayer->sp->runAction(_DrawRectLayer->_RepeatForever);
		}
		ui.dockWidget->setWindowTitle(animation_list.at(col));
		setSlideEndFPX(_DrawRectLayer->animation->getDuration() * oneFPX * 1);
		setPerWiget(_DrawRectLayer->animation->getDuration() * oneFPX);
		SetMyUI();
	}
	else
	{
		ShowMsg(animation_list.at(col).toStdString());
		//_DrawRectLayer->MySpineUnUpdate();
		_DrawRectLayer->setMySpineAnimation(animation_list.at(col).toStdString().c_str());
		ui.dockWidget->setWindowTitle(animation_list.at(col));
		setSlideEndFPX(_DrawRectLayer->_MySpineDuration * oneFPX * 1);
		setPerWiget(_DrawRectLayer->_MySpineDuration * oneFPX);
	}
	
	////AddSliderButton();
	btn = sliderButton.at(0);
	btn->Is_Click = true;
	btn->setPalette(QPalette(Qt::green));
	//btn->setAutoFillBackground(true);
	showline = sliderFameshow.at((btn->Singl_ID));
	showline->setVisible(true);
	_lastButton = btn;

	setMyFrame(-1, -1, false, last_rol);
	SlderAnimationAction();
}


void QtEdit::setSlideEndFPX(int end)
{
	int i;
	if (FPX >= 0)
	{
		sliderButton.at(FPX)->setAutoFillBackground(true);
		sliderButton.at(FPX)->setStyleSheet("background: transparent;border:0px");
		sliderButton.at(FPX)->Is_Click = false;
	}
	if (-1 != FPX && _endButton != nullptr)
	{
		showline = sliderFameshow.at((_endButton->Singl_ID));
		if (FPX % 5 != 0)
		{
			showline->setVisible(false);
		}
	}
	
	FPX = end + 1;
	_endButton = sliderButton.at(FPX);
	_endButton->setPalette(QPalette(Qt::red));
	_endButton->setAutoFillBackground(true);
	//showline = sliderFameshow.at((_endButton->Singl_ID));
	//showline->setVisible(true);
}

void QtEdit::mousePressEvent(QMouseEvent *e)
{
	//stPoint = e->pos();
	if (is_import)
	{
		if (e->button() == Qt::RightButton)
		{
			stPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			stPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			bool Att_Is_In, Inj_is_In;
			Vec2 posi(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, posi);
			_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, posi);
			_DrawRectLayer->attackNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			_DrawRectLayer->injuredNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			_DrawRectLayer->injuredNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			QPoint str(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y);
			QPoint end(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y);
			Att_Is_In = Is_Point_Into(stPoint, str, end);
			QPoint strin(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y);
			QPoint endin(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y);
			Inj_is_In = Is_Point_Into(stPoint, strin, endin);
			if (Att_Is_In)
			{
				attstPoint = stPoint;
			}
			else
			{
				attstPoint.setX(0);
				attstPoint.setY(0);
			}
			if (Inj_is_In)
			{
				injstPoint = stPoint;
			}
			else
			{
				injstPoint.setX(0);
				injstPoint.setY(0);
			}
		}
	}
}

void QtEdit::deleteDrawnode()
{
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	int i;
	if (deleteAtt)
	{
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
		{
			MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
			if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
			{
				FREE_DEL_VEC(_DrawRectLayer->spritePoints.at(i)->attackVertices);
				_DrawRectLayer->spritePoints.at(i)->attackVertices = nullptr;
				_DrawRectLayer->spritePoints.at(i)->RotateAtt = 0;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				sliderButton.at(btn->Singl_ID)->Is_AttFra = false;
				sliderButton.at(btn->Singl_ID)->deleteAction(false);
				_DrawRectLayer->attackNode = new MyDrawNode();
				if (_DrawRectLayer->spritePoints.at(i)->injureVertices == nullptr && !sliderButton.at(btn->Singl_ID)->Is_ActFra)
				{
					_DrawRectLayer->spritePoints.erase(_DrawRectLayer->spritePoints.begin() + i);
					sliderButton.at(btn->Singl_ID)->Is_AttFra = false;
					sliderButton.at(btn->Singl_ID)->deleteAction(true);
				}
				break;
			}
		}
	}
	else
	{
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
		{
			MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
			if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
			{
				FREE_DEL_VEC(_DrawRectLayer->spritePoints.at(i)->injureVertices);
				_DrawRectLayer->spritePoints.at(i)->injureVertices = nullptr;
				_DrawRectLayer->spritePoints.at(i)->RotateInj = 0;
				sliderButton.at(btn->Singl_ID)->Is_InjFra = false;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				sliderButton.at(btn->Singl_ID)->Is_InjFra = false;
				sliderButton.at(btn->Singl_ID)->deleteAction(false);
				_DrawRectLayer->injuredNode = new MyDrawNode();
				if (_DrawRectLayer->spritePoints.at(i)->attackVertices == nullptr && !sliderButton.at(btn->Singl_ID)->Is_ActFra)
				{
					_DrawRectLayer->spritePoints.erase(_DrawRectLayer->spritePoints.begin() + i);
					sliderButton.at(btn->Singl_ID)->Is_InjFra = false;
					sliderButton.at(btn->Singl_ID)->deleteAction(true);
				}
				break;
			}
		}
	}
}

void QtEdit::mouseReleaseEvent(QMouseEvent *e)
{
	if (is_import)
	{

		if (e->button() == Qt::RightButton && CheckIsFrame())
		{
			enPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			enPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			bool Att_Is_In, Inj_is_In;
			Vec2 posi(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, posi);
			_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, posi);
			_DrawRectLayer->attackNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			_DrawRectLayer->injuredNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			_DrawRectLayer->injuredNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			QPoint str(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y);
			QPoint end(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y);
			Att_Is_In = Is_Point_Into(enPoint, str, end);
			QPoint strin(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y);
			QPoint endin(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y);
			Inj_is_In = Is_Point_Into(enPoint, strin, endin);
			//Att_Is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y), QPoint(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y));
			//Inj_is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y), QPoint(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y));
			MyDrawNode *_tempDraw;
			bool Is_Update = false;
			float rotate, i;
			if (Ctrl_Is_On && Att_Is_In && attstPoint.x() != 0 && attstPoint.y() != 0 && sliderButton.at(btn->Singl_ID)->Is_AttFra)
			{
				Vec2 str(attstPoint.x(), attstPoint.y());
				Vec2 end(enPoint.x(), enPoint.y());
				Vec2 midpoint((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2);
				rotate = _DrawRectLayer->attackNode->getRotate(str, end, midpoint);
				if (attstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				else
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				_DrawRectLayer->attackNode->setRotateVertices(_DrawRectLayer->attackNode->Vertices[0], _DrawRectLayer->attackNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->bodyNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->effefcNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->effefcNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->effefcNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->effefcNode = _tempDraw;

				Is_Update = true;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateAtt = _DrawRectLayer->attackNode->Rotate;
						break;
					}
				}
			}
			else if (Inj_is_In && injstPoint.x() != 0 && injstPoint.y() != 0 && !Ctrl_Is_On && sliderButton.at(btn->Singl_ID)->Is_InjFra)
			{
				Vec2 str(injstPoint.x(), injstPoint.y());
				Vec2 end(enPoint.x(), enPoint.y());
				Vec2 midpoint((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2);

				rotate = _DrawRectLayer->injuredNode->getRotate(str, end, midpoint);
				//log("B = %f", sin(rotate));
				if (injstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}
				else
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}	
				_DrawRectLayer->injuredNode->setRotateVertices(_DrawRectLayer->injuredNode->Vertices[0], _DrawRectLayer->injuredNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->effefcNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->effefcNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->effefcNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->effefcNode = _tempDraw;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateInj = _DrawRectLayer->injuredNode->Rotate;
						break;
					}
				}
				Is_Update = true;
			}
			if (Is_Update)
			{
				_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
				_DrawRectLayer->doDraw();
			}
		}
	}
}
bool QtEdit::CheckIsFrame()
{
	return sliderButton.at(btn->Singl_ID)->Is_AttFra || sliderButton.at(btn->Singl_ID)->Is_InjFra;
}

void QtEdit::mouseMoveEvent(QMouseEvent *e)
{
	if (is_import)
	{
		if ((e->buttons() & Qt::RightButton) && CheckIsFrame())
		{
			enPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			enPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			bool Att_Is_In, Inj_is_In;
			Vec2 posi(_QtEdit->ui.Width->text().toFloat(), _QtEdit->ui.Height->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeVertices(_DrawRectLayer->attackNode->Vertices, posi);
			_DrawRectLayer->injuredNode->setRelativeVertices(_DrawRectLayer->injuredNode->Vertices, posi);
			_DrawRectLayer->attackNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			_DrawRectLayer->attackNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			_DrawRectLayer->injuredNode->setRelativeScallX(ui.Width->text().toFloat(), _IN_ScallX, _QtEdit->ui.ScallX->text().toFloat());
			_DrawRectLayer->injuredNode->setRelativeScallY(ui.Height->text().toFloat(), _IN_ScallY, _QtEdit->ui.ScallY->text().toFloat());
			QPoint str(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y);
			QPoint end(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y);
			Att_Is_In = Is_Point_Into(enPoint, str, end);
			QPoint strin(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y);
			QPoint endin(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y);
			Inj_is_In = Is_Point_Into(enPoint, strin, endin);
			//Att_Is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->attackNode->Relativevertices[0].x, _DrawRectLayer->attackNode->Relativevertices[0].y), QPoint(_DrawRectLayer->attackNode->Relativevertices[2].x, _DrawRectLayer->attackNode->Relativevertices[2].y));
			//Inj_is_In = Is_Point_Into(enPoint, QPoint(_DrawRectLayer->injuredNode->Relativevertices[0].x, _DrawRectLayer->injuredNode->Relativevertices[0].y), QPoint(_DrawRectLayer->injuredNode->Relativevertices[2].x, _DrawRectLayer->injuredNode->Relativevertices[2].y));
			MyDrawNode *_tempDraw;
			bool Is_Update = false;
			float rotate, i;
			if (Ctrl_Is_On && Att_Is_In && attstPoint.x() != 0 && attstPoint.y() != 0 && sliderButton.at(btn->Singl_ID)->Is_AttFra)
			{
				Vec2 str(attstPoint.x(), attstPoint.y());
				Vec2 end(enPoint.x(), enPoint.y());
				Vec2 midpoint((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2);
				rotate = _DrawRectLayer->attackNode->getRotate(str, end, midpoint);
				//rotate = rotate / (180 / M_PI);
				if (attstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				else
				{
					_DrawRectLayer->attackNode->Rotate = rotate;

				}
				_DrawRectLayer->attackNode->setRotateVertices(_DrawRectLayer->attackNode->Vertices[0], _DrawRectLayer->attackNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;


				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->effefcNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->effefcNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->effefcNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->effefcNode = _tempDraw;

				Is_Update = true;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateAtt = _DrawRectLayer->attackNode->Rotate;
						break;
					}
				}
			}
			else if (Inj_is_In && injstPoint.x() != 0 && injstPoint.y() != 0 && !Ctrl_Is_On && sliderButton.at(btn->Singl_ID)->Is_InjFra)
			{
				Vec2 str(injstPoint.x(), injstPoint.y());
				Vec2 end(enPoint.x(), enPoint.y());
				Vec2 midpoint((_DrawRectLayer->injuredNode->Relativevertices[0].x + _DrawRectLayer->injuredNode->Relativevertices[2].x) / 2, (_DrawRectLayer->injuredNode->Relativevertices[0].y + _DrawRectLayer->injuredNode->Relativevertices[2].y) / 2);
				rotate = _DrawRectLayer->injuredNode->getRotate(str, end, midpoint);
				//_DrawRectLayer->showMsg("QT", injstPoint.x(), enPoint.x());
				//log("B = %f", sin(rotate));
				//rotate = rotate / (180 / M_PI);
				if (injstPoint.y() > enPoint.y())
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}
				else
				{
					_DrawRectLayer->injuredNode->Rotate = rotate;
					
				}	
				_DrawRectLayer->injuredNode->setRotateVertices(_DrawRectLayer->injuredNode->Vertices[0], _DrawRectLayer->injuredNode->Vertices[2], rotate);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->attackNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->attackNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->attackNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->attackNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->attackNode->is_visible;
				_DrawRectLayer->removeChild(_DrawRectLayer->attackNode->drawnode);
				_DrawRectLayer->attackNode = _tempDraw;
				_DrawRectLayer->removeChild(_DrawRectLayer->injuredNode->drawnode);
				_tempDraw = new MyDrawNode();
				_tempDraw->Rotate = _DrawRectLayer->injuredNode->Rotate;
				_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->injuredNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->injuredNode->Vertices;
				_tempDraw->is_visible = _DrawRectLayer->injuredNode->is_visible;
				_DrawRectLayer->injuredNode = _tempDraw;


				_DrawRectLayer->removeChild(_DrawRectLayer->bodyNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->bodyNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->bodyNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->bodyNode = _tempDraw;

				_DrawRectLayer->removeChild(_DrawRectLayer->effefcNode->drawnode);
				_tempDraw = new MyDrawNode();
				//_tempDraw->Rotate = _DrawRectLayer->bodyNode->Rotate;
				//_tempDraw->RotateVertices = _DrawRectLayer->injuredNode->RotateVertices;
				_tempDraw->Singl_ID = _DrawRectLayer->effefcNode->Singl_ID;
				_tempDraw->Vertices = _DrawRectLayer->effefcNode->Vertices;
				//_tempDraw->is_visible = _DrawRectLayer->bodyNode->is_visible;
				_DrawRectLayer->effefcNode = _tempDraw;
				for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
				{
					MySpritePoint * _tempSpritePoint = _DrawRectLayer->spritePoints.at(i);
					if (_tempSpritePoint->Single_ID == _DrawRectLayer->Single_ID)
					{
						_DrawRectLayer->spritePoints.at(i)->RotateInj = _DrawRectLayer->injuredNode->Rotate;
						break;
					}
				}
				Is_Update = true;
			}
			if (Is_Update)
			{
				_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
				_DrawRectLayer->doDraw();
			}
		}
	}
}
bool  QtEdit::Is_Point_Into(QPoint po, QPoint st , QPoint en)
{
	if (po.x() < st.x() && po.x() < en.x())
	{
		return false;
	}
	if (po.x() > st.x() && po.x() > en.x())
	{
		return false;
	}
	if (po.y() < st.y() && po.y() < en.y())
	{
		return false;
	}
	if (po.y() > st.y() && po.y() > en.y())
	{
		return false;
	}
	return true;
}

//关键帧的标识
void QtEdit::setMyFrame(int rol,int posi, bool dele , int last_rol)
{
	int i;
	if (rol == -1)
	{
		int r = last_rol == -1 ? sliderButton.size() : last_rol;
		for (i = 0; i < r; i++)
		{
			try
			{
				//sliderButton.at(i)->_AttFraButton->setAutoFillBackground(true);
				if (sliderButton.at(i)->Is_AttFra)
				{
					sliderButton.at(i)->_AttFraButton->setStyleSheet("background: transparent;border:0px");
					sliderButton.at(i)->Is_AttFra = false;
				}
				if (sliderButton.at(i)->Is_InjFra)
				{
					//sliderButton.at(i)->_InjFraButton->setAutoFillBackground(true;)
					sliderButton.at(i)->_InjFraButton->setStyleSheet("background: transparent;border:0px");
					sliderButton.at(i)->Is_InjFra = false;
				}

				if (sliderButton.at(i)->Is_ActFra)
				{
					//sliderButton.at(i)->_ActFraButton->setAutoFillBackground(true);
					sliderButton.at(i)->_ActFraButton->setStyleSheet("background: transparent;border:0px");
					sliderButton.at(i)->Is_ActFra = false;
				}

				if (sliderButton.at(i)->Is_BodyFra)
				{
					sliderButton.at(i)->_BodyFraButton->setStyleSheet("background: transparent;border:0px");
					sliderButton.at(i)->Is_BodyFra = false;
				}
				if (sliderButton.at(i)->Is_EffFra)
				{
					sliderButton.at(i)->_EffFraButton->setStyleSheet("background: transparent;border:0px");
					sliderButton.at(i)->Is_EffFra = false;
				}
				
				if (i  % 5 != 0)
				{
					sliderFameshow.at(i)->setVisible(false);
				}
			}
			catch (...)
			{
				
			}
		}
		for (i = 0; i < _DrawRectLayer->spritePoints.size(); i++)
		{
			if (_DrawRectLayer->spritePoints.at(i)->Is_ActFra)
			{
				try{
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_ActFraButton->setAutoFillBackground(true);
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_ActFraButton->setPalette(QPalette(Qt::blue));
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_ActFra = true;
				}
				catch (...){}
			}
			if (_DrawRectLayer->spritePoints.at(i)->Is_AttFra)
			{
				try{
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_AttFraButton->setAutoFillBackground(true);
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_AttFraButton->setPalette(QPalette(Qt::red));
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_AttFra = true;
				}
				catch (...){}
			}
			if (_DrawRectLayer->spritePoints.at(i)->Is_InjFra)
			{
				try{
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_InjFraButton->setAutoFillBackground(true);
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_InjFraButton->setPalette(QPalette(Qt::yellow));
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_InjFra = true;
				}
				catch (...){}
			}
			if (_DrawRectLayer->spritePoints.at(i)->Is_BodyFra)
			{
				try{
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_BodyFraButton->setAutoFillBackground(true);
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_BodyFraButton->setPalette(QPalette(Qt::green));
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_BodyFra = true;
				}
				catch (...){}
			}
			if (_DrawRectLayer->spritePoints.at(i)->Is_EffFra)
			{
				try{
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_EffFraButton->setAutoFillBackground(true);
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->_EffFraButton->setPalette(QPalette(Qt::white));
					sliderButton.at(_DrawRectLayer->spritePoints.at(i)->Single_ID)->Is_EffFra = true;
				}
				catch (...){}
			}
			
		}
		return;
	}
	if (!dele)
	{
		if (posi == 1)
		{
			sliderButton.at(rol)->_AttFraButton->setPalette(QPalette(Qt::red));
			sliderButton.at(rol)->_AttFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_AttFra = true;
		}
		else if (posi == 2)
		{
			sliderButton.at(rol)->_InjFraButton->setPalette(QPalette(Qt::yellow));
			sliderButton.at(rol)->_InjFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_InjFra = true;
		}
		else if (posi == 3)
		{
			sliderButton.at(rol)->_ActFraButton->setPalette(QPalette(Qt::blue));
			sliderButton.at(rol)->_ActFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_ActFra = true;
		}
		else if (posi == 4)
		{
			sliderButton.at(rol)->_BodyFraButton->setPalette(QPalette(Qt::green));
			sliderButton.at(rol)->_BodyFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_BodyFra = true;
		}
		else if (posi == 5)
		{
			sliderButton.at(rol)->_EffFraButton->setPalette(QPalette(Qt::white));
			sliderButton.at(rol)->_EffFraButton->setAutoFillBackground(true);
			sliderButton.at(rol)->Is_EffFra = true;
		}
		return;
	}
	//if (dele)
	//{
	//	sliderButton.at(rol)->_AttFraButton->setStyleSheet("background:transparent");
	//	sliderButton.at(rol)->Is_AttFra = false;
	//}
	
}

void QtEdit::setParent(HWND parent)
{
	m_Parent = parent;
}
void QtEdit::SetFraDe(MySpritePoint * _temp_sprite_point)
{
	ui.Height->setText(QString("%1").arg(_temp_sprite_point->_height));
	ui.Width->setText(QString("%1").arg(_temp_sprite_point->_width));
	ui.ScallX->setText(QString("%1").arg(_temp_sprite_point->_ScallX));
	ui.ScallY->setText(QString("%1").arg(_temp_sprite_point->_ScallY));
	ui.Re_Height->setText(QString("%1").arg(ui.Height->text().toFloat() - _IN_Height));
	ui.Re_Width->setText(QString("%1").arg(ui.Width->text().toFloat() - _IN_Width));
	ui.St_Width->setText("");
	ui.St_Height->setText("");
	ui.En_Width->setText("");
	ui.En_Height->setText("");
	ui.Rotate->setText("");
	ui.St_Width_RE->setText("");
	ui.St_Height_RE->setText("");
	ui.En_Width_RE->setText("");
	ui.En_Height_RE->setText("");
	ui.Rotate_RE->setText("");
	//ChangeInput();
	MySpriteChange();
}