#ifndef __QTBUTTON_H__
#define __QTBUTTON_H__
#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_qtedit.h"
//#include "DrawRectLayer.h"
#include "qpushbutton.h"
#include "QTableWidget.h"
#include "qframe.h"
#include "QScrollArea.h"
#include "MyConfig.h"

class QtButton : public QPushButton
{
	Q_OBJECT
public:
	QtButton(QWidget *parent = 0) :QPushButton(parent){
		_AttFraButton = new QPushButton(parent);
		Is_AttFra = false;
		_InjFraButton = new QPushButton(parent);
		Is_InjFra = false;
		_ActFraButton = new QPushButton(parent);
		Is_ActFra = false;
		_BodyFraButton = new QPushButton(parent);
		Is_BodyFra = false;
		_EffFraButton = new QPushButton(parent);
		Is_EffFra = false;
	};
	QtButton(int _ID, QWidget *parent = 0) : QtButton(parent){
		this_button_id = _ID;
	};
	QtButton(const QString &text, QWidget *parent = 0) :QPushButton(text, parent){};
	QtButton(const QIcon& icon, const QString &text, QWidget *parent = 0) :QPushButton(icon, text, parent){};
	~QtButton()
	{
		FREE_DEL_OBJ(_AttFraButton);
		FREE_DEL_OBJ(_InjFraButton);
		FREE_DEL_OBJ(_ActFraButton);
		FREE_DEL_OBJ(_BodyFraButton);
		FREE_DEL_OBJ(_EffFraButton);

	};
	void deleteAction(bool Is_Update = false);

	private slots:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void DoDelete();

public:

	QPushButton * _AttFraButton;
	QPushButton * _InjFraButton;
	QPushButton * _ActFraButton;
	QPushButton * _BodyFraButton;
	QPushButton * _EffFraButton;
	bool Is_AttFra;
	bool Is_InjFra;
	bool Is_ActFra;
	bool Is_BodyFra;
	bool Is_EffFra;
	QMenu* popMenu;
	QAction * DeleteActAction;
	QAction * DeleteInjAction;
	QAction * DeleteAttAction;
	QAction * DeleteBodyAction;
	QAction * DeleteAllAction;
	QAction * DeleteEffAction;

	QAction * ClearInjAction;
	QAction * ClearAttAction;
	QAction * ClearBodyAction;
	QAction * ClearEffAction;

	QAction * AddActAction;
	QAction * AddInjAction;
	QAction * AddAttAction;
	QAction * AddBodyAction;
	QAction * AddEffAction;
	QAction * AddAllAction;

	int this_button_id;

private:
	void CheckButton(int);
	int size ;
	int i;
	QtButton *_QtButton;

Q_SIGNALS :
public slots :
	void deleteFra();
	void deleteAct();
	void deleteInj();
	void deleteAtt();
	void deleteEff();
	void deleteBody();
	void clearInj();
	void clearAtt();
	void clearBody();
	void clearEff();
	void addAct();
	void addInj();
	void addAtt();
	void addBody();
	void addEff();
	void addFra();
public:
	int Singl_ID;
	bool Is_Click;
	bool te_sh;
	bool te_ct;
	bool te_sp;
};

#endif