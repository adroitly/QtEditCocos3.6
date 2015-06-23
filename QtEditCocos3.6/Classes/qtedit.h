#ifndef QTEDIT_H
#define QTEDIT_H

#include <QtWidgets/QMainWindow>
#include "ui_qtedit.h"
#include "DrawRectLayer.h"
#include "QtButton.h"
#include "QTableWidget.h"
#include "qframe.h"
#include "QScrollArea.h"
#include "MyVector.h" 
//#include "MyConfig.h"
class AppDelegate;
namespace Ui {
	class QtEdit;
}
class QtEdit : public QMainWindow
{
	Q_OBJECT

public:
	//声明友元
	friend class Export_Data;
	friend class QtButton;

	QtEdit(QWidget *parent = 0);
	~QtEdit();
	void setGLView(QWidget *glWidget);
	void ShowMsg(std::string);
	static QtEdit * getInstance();
	void MySpriteChange();
	void AddAnimationList(QString);
	void SlderChange(float Percentage);
	void AddSliderButton();
	void ChangeSliderButton();
	void SlderAnimationAction();
	void AnimationUpdate(float);
	void setSlideEndFPX(int);
	bool Is_Point_Into(QPoint, QPoint ,QPoint);
	void doSaveData(QString,bool tobase = false);
	void setMyFrame(int rol = -1,int posi = -1, bool dele = false, int last_rol = -1);
	bool CheckIsFrame();
	void SetMyUI();
	void SetFraDe(MySpritePoint * _temp_sprite_point);
	void AddCao();
	void setMyBox_ComBox(QStringList);
	void setMyBox(int);
	void setPerWiget(int);
	void MySQLite(bool is_Update = false, QString data = 0 , QString col_name = "");
public:
	int SpiteS_Model = 0;
	bool Ctrl_Is_On;
	QVector<QLabel *> sliderFameshow;
	QVector<QtButton *> sliderButton;
	QtButton * oneButton;
	QWidget * buttonWidget;
	QtButton * zhenButton;
	QFrame * line;
	QLabel * showline;
	QScrollArea *scrollArea;
	QtButton * _lastButton = NULL;
	QtButton * _endButton = NULL;
	QtButton* btn = NULL;
	int FPX = -1;
	MyVector * myVector;
	MyVector *tempVector;
	std::vector<MyVector *> spritesPoints;
	bool is_import;
	DrawRectLayer *_DrawRectLayer;
	Ui::QtEditClass ui;
	int pu = -1;
	QTextCodec *codec;
	bool Shift_is_ON;
	bool Space_is_ON;
	QStringList myBox_Comboxlist;
	QRegExp  *double_rx;//正则表达式
	QRegExpValidator * validtor;
	bool Is_ChangeInputToBox;//
	QStringList animation_list;
	QString openC3bFile_Path = "./";
	QString export_Byte_Path = "./";
	QString export_Json_Path = "./";
	QString openSpineFile_Path = "./";
private slots:
	void yestButtonClick();
	void import();
	void importSpine();
	void exportData();
	void openData();
	void ChangeInput();
	void ReChangeInput();
	void showmessageChange();
	void pausebuttonclick();
	void AnimationSlderChange();
	void AnimationSlderClick(int);
	void keyPressEvent(QKeyEvent *);
	void keyReleaseEvent(QKeyEvent *);
	void AnimationTreeWidgetClick(QTreeWidgetItem * item, int column);
	void SlderButtonClick();
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void ActionHelp();
	void deleteDrawnode();
	void saveAllData();
	void Mybox_Combox(QString str);
	void BoxChangeInput(QString str);
	void export_byteData();
	void wheelEvent(QWheelEvent *e);//鼠标滚动
protected:
	void closeEvent(QCloseEvent *);
	void setParent(HWND);
	void Init();
	
private:
	
	AppDelegate         *_appDelegate;
	QWidget             *_glWidget;

	std::string			mymsg;
	
	double				mouseX;
	double				mouseY;
	char				myshowstr[100];
	QPoint				stPoint;
	QPoint				enPoint;
	QPoint				attstPoint;
	QPoint				attenPoint;
	QPoint				injstPoint;
	QPoint				injenPoint;
	QString				saveDataName;
	QString				_filename;
	int					_mycol;
	bool				deleteAtt;
	bool				deleteInj;
	QString				re_file_path;
	QScrollBar			*scallbar;
public:
	HWND m_Parent;
};

#endif // QTEDIT_H
