/********************************************************************************
** Form generated from reading UI file 'qtedit.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEDIT_H
#define UI_QTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtEditClass
{
public:
    QAction *closeaction;
    QAction *openaction;
    QAction *importaction;
    QAction *actionHelp;
    QAction *exportaction;
    QAction *Action_Save;
    QAction *export_byte;
    QAction *import_Spine;
    QWidget *centralWidget;
    QDockWidget *SceneWidget;
    QWidget *dockWidgetContents_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_3;
    QTreeWidget *AnimationtreeWidget;
    QDockWidget *OutWiget;
    QWidget *dockWidgetContents_4;
    QPlainTextEdit *showmessage;
    QDockWidget *PerWiget;
    QWidget *dockWidgetContents_5;
    QSlider *PencentageSlider;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *Width;
    QLineEdit *Height;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *ScallX;
    QLineEdit *ScallY;
    QPushButton *PauseButton;
    QLineEdit *Re_Width;
    QLineEdit *Re_Height;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *St_Width;
    QLineEdit *St_Height;
    QLabel *label_10;
    QLineEdit *En_Height;
    QLineEdit *En_Width;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_22;
    QLineEdit *Rotate;
    QLineEdit *St_Width_RE;
    QLabel *label_11;
    QLineEdit *St_Height_RE;
    QLineEdit *En_Width_RE;
    QLabel *label_9;
    QLineEdit *En_Height_RE;
    QLabel *label_26;
    QLabel *label_27;
    QLineEdit *Line_ID;
    QLabel *label_12;
    QLabel *label_20;
    QLineEdit *Box_Width;
    QLineEdit *Box_Width_RE;
    QLabel *label_28;
    QLineEdit *Box_Height_RE;
    QLineEdit *Box_Height;
    QLabel *label_29;
    QLabel *label_21;
    QLabel *label_24;
    QLineEdit *Box_Y_Posi;
    QLabel *label_25;
    QLineEdit *Box_X_Posi;
    QLineEdit *Box_X_Posi_RE;
    QLineEdit *Box_Y_Posi_RE;
    QLabel *label_30;
    QLabel *label_31;
    QLineEdit *Rotate3D_X;
    QLabel *label_5;
    QLabel *label_13;
    QLineEdit *Rotate3D_Y;
    QLabel *label_14;
    QLineEdit *Rotate3D_Z;
    QLabel *label_15;
    QLineEdit *Is_show;

    void setupUi(QMainWindow *QtEditClass)
    {
        if (QtEditClass->objectName().isEmpty())
            QtEditClass->setObjectName(QStringLiteral("QtEditClass"));
        QtEditClass->setEnabled(true);
        QtEditClass->resize(1768, 960);
        QtEditClass->setMinimumSize(QSize(0, 0));
        QtEditClass->setMaximumSize(QSize(16777215, 16777215));
        closeaction = new QAction(QtEditClass);
        closeaction->setObjectName(QStringLiteral("closeaction"));
        openaction = new QAction(QtEditClass);
        openaction->setObjectName(QStringLiteral("openaction"));
        importaction = new QAction(QtEditClass);
        importaction->setObjectName(QStringLiteral("importaction"));
        actionHelp = new QAction(QtEditClass);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        exportaction = new QAction(QtEditClass);
        exportaction->setObjectName(QStringLiteral("exportaction"));
        Action_Save = new QAction(QtEditClass);
        Action_Save->setObjectName(QStringLiteral("Action_Save"));
        export_byte = new QAction(QtEditClass);
        export_byte->setObjectName(QStringLiteral("export_byte"));
        import_Spine = new QAction(QtEditClass);
        import_Spine->setObjectName(QStringLiteral("import_Spine"));
        centralWidget = new QWidget(QtEditClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SceneWidget = new QDockWidget(centralWidget);
        SceneWidget->setObjectName(QStringLiteral("SceneWidget"));
        SceneWidget->setGeometry(QRect(0, 0, 960, 680));
        SceneWidget->setMinimumSize(QSize(960, 680));
        SceneWidget->setMaximumSize(QSize(960, 680));
        QFont font;
        font.setKerning(false);
        SceneWidget->setFont(font);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        SceneWidget->setWidget(dockWidgetContents_2);
        QtEditClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtEditClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1768, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        QtEditClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(QtEditClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtEditClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(QtEditClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setMaximumSize(QSize(611, 841));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        AnimationtreeWidget = new QTreeWidget(dockWidgetContents_3);
        AnimationtreeWidget->setObjectName(QStringLiteral("AnimationtreeWidget"));
        AnimationtreeWidget->setGeometry(QRect(0, 0, 611, 841));
        AnimationtreeWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        dockWidget->setWidget(dockWidgetContents_3);
        QtEditClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
        OutWiget = new QDockWidget(QtEditClass);
        OutWiget->setObjectName(QStringLiteral("OutWiget"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        showmessage = new QPlainTextEdit(dockWidgetContents_4);
        showmessage->setObjectName(QStringLiteral("showmessage"));
        showmessage->setGeometry(QRect(0, 0, 431, 191));
        QFont font1;
        font1.setPointSize(12);
        showmessage->setFont(font1);
        OutWiget->setWidget(dockWidgetContents_4);
        QtEditClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), OutWiget);
        PerWiget = new QDockWidget(QtEditClass);
        PerWiget->setObjectName(QStringLiteral("PerWiget"));
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QStringLiteral("dockWidgetContents_5"));
        PencentageSlider = new QSlider(dockWidgetContents_5);
        PencentageSlider->setObjectName(QStringLiteral("PencentageSlider"));
        PencentageSlider->setGeometry(QRect(0, 0, 960, 51));
        PencentageSlider->setMaximumSize(QSize(16777215, 16777215));
        PencentageSlider->setFont(font1);
        PencentageSlider->setMinimum(0);
        PencentageSlider->setMaximum(99);
        PencentageSlider->setValue(0);
        PencentageSlider->setOrientation(Qt::Horizontal);
        PerWiget->setWidget(dockWidgetContents_5);
        QtEditClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), PerWiget);
        dockWidget_4 = new QDockWidget(QtEditClass);
        dockWidget_4->setObjectName(QStringLiteral("dockWidget_4"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 0, 61, 21));
        label->setFont(font1);
        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 0, 71, 21));
        label_2->setFont(font1);
        Width = new QLineEdit(dockWidgetContents);
        Width->setObjectName(QStringLiteral("Width"));
        Width->setGeometry(QRect(20, 40, 61, 20));
        Height = new QLineEdit(dockWidgetContents);
        Height->setObjectName(QStringLiteral("Height"));
        Height->setGeometry(QRect(120, 40, 71, 20));
        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(230, 0, 54, 21));
        label_3->setFont(font1);
        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(330, 0, 54, 21));
        label_4->setFont(font1);
        ScallX = new QLineEdit(dockWidgetContents);
        ScallX->setObjectName(QStringLiteral("ScallX"));
        ScallX->setGeometry(QRect(220, 40, 71, 20));
        ScallY = new QLineEdit(dockWidgetContents);
        ScallY->setObjectName(QStringLiteral("ScallY"));
        ScallY->setGeometry(QRect(320, 40, 71, 20));
        PauseButton = new QPushButton(dockWidgetContents);
        PauseButton->setObjectName(QStringLiteral("PauseButton"));
        PauseButton->setGeometry(QRect(86, 245, 75, 23));
        PauseButton->setFont(font1);
        Re_Width = new QLineEdit(dockWidgetContents);
        Re_Width->setObjectName(QStringLiteral("Re_Width"));
        Re_Width->setGeometry(QRect(20, 96, 61, 20));
        Re_Height = new QLineEdit(dockWidgetContents);
        Re_Height->setObjectName(QStringLiteral("Re_Height"));
        Re_Height->setGeometry(QRect(120, 96, 71, 20));
        label_6 = new QLabel(dockWidgetContents);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(23, 66, 71, 21));
        label_6->setFont(font1);
        label_7 = new QLabel(dockWidgetContents);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(123, 66, 81, 21));
        label_7->setFont(font1);
        label_8 = new QLabel(dockWidgetContents);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(278, 175, 54, 21));
        label_8->setFont(font1);
        St_Width = new QLineEdit(dockWidgetContents);
        St_Width->setObjectName(QStringLiteral("St_Width"));
        St_Width->setGeometry(QRect(266, 195, 71, 20));
        St_Height = new QLineEdit(dockWidgetContents);
        St_Height->setObjectName(QStringLiteral("St_Height"));
        St_Height->setGeometry(QRect(266, 245, 71, 20));
        label_10 = new QLabel(dockWidgetContents);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(278, 220, 54, 21));
        label_10->setFont(font1);
        En_Height = new QLineEdit(dockWidgetContents);
        En_Height->setObjectName(QStringLiteral("En_Height"));
        En_Height->setGeometry(QRect(368, 245, 71, 20));
        En_Width = new QLineEdit(dockWidgetContents);
        En_Width->setObjectName(QStringLiteral("En_Width"));
        En_Width->setGeometry(QRect(368, 195, 71, 20));
        label_18 = new QLabel(dockWidgetContents);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(380, 220, 54, 21));
        label_18->setFont(font1);
        label_19 = new QLabel(dockWidgetContents);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(380, 173, 54, 21));
        label_19->setFont(font1);
        label_22 = new QLabel(dockWidgetContents);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(99, 176, 54, 21));
        label_22->setFont(font1);
        Rotate = new QLineEdit(dockWidgetContents);
        Rotate->setObjectName(QStringLiteral("Rotate"));
        Rotate->setGeometry(QRect(87, 198, 71, 20));
        St_Width_RE = new QLineEdit(dockWidgetContents);
        St_Width_RE->setObjectName(QStringLiteral("St_Width_RE"));
        St_Width_RE->setEnabled(false);
        St_Width_RE->setGeometry(QRect(268, 300, 71, 20));
        label_11 = new QLabel(dockWidgetContents);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(280, 331, 54, 21));
        label_11->setFont(font1);
        St_Height_RE = new QLineEdit(dockWidgetContents);
        St_Height_RE->setObjectName(QStringLiteral("St_Height_RE"));
        St_Height_RE->setEnabled(false);
        St_Height_RE->setGeometry(QRect(268, 356, 71, 20));
        En_Width_RE = new QLineEdit(dockWidgetContents);
        En_Width_RE->setObjectName(QStringLiteral("En_Width_RE"));
        En_Width_RE->setEnabled(false);
        En_Width_RE->setGeometry(QRect(370, 301, 71, 20));
        label_9 = new QLabel(dockWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(280, 280, 54, 21));
        label_9->setFont(font1);
        En_Height_RE = new QLineEdit(dockWidgetContents);
        En_Height_RE->setObjectName(QStringLiteral("En_Height_RE"));
        En_Height_RE->setEnabled(false);
        En_Height_RE->setGeometry(QRect(370, 351, 71, 20));
        label_26 = new QLabel(dockWidgetContents);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(382, 326, 54, 21));
        label_26->setFont(font1);
        label_27 = new QLabel(dockWidgetContents);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(382, 279, 54, 21));
        label_27->setFont(font1);
        Line_ID = new QLineEdit(dockWidgetContents);
        Line_ID->setObjectName(QStringLiteral("Line_ID"));
        Line_ID->setGeometry(QRect(220, 96, 71, 20));
        label_12 = new QLabel(dockWidgetContents);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(220, 66, 81, 21));
        label_12->setFont(font1);
        label_20 = new QLabel(dockWidgetContents);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(21, 176, 54, 21));
        label_20->setFont(font1);
        Box_Width = new QLineEdit(dockWidgetContents);
        Box_Width->setObjectName(QStringLiteral("Box_Width"));
        Box_Width->setGeometry(QRect(8, 198, 71, 20));
        Box_Width_RE = new QLineEdit(dockWidgetContents);
        Box_Width_RE->setObjectName(QStringLiteral("Box_Width_RE"));
        Box_Width_RE->setEnabled(false);
        Box_Width_RE->setGeometry(QRect(8, 304, 71, 20));
        label_28 = new QLabel(dockWidgetContents);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(22, 329, 54, 21));
        label_28->setFont(font1);
        Box_Height_RE = new QLineEdit(dockWidgetContents);
        Box_Height_RE->setObjectName(QStringLiteral("Box_Height_RE"));
        Box_Height_RE->setEnabled(false);
        Box_Height_RE->setGeometry(QRect(7, 354, 71, 20));
        Box_Height = new QLineEdit(dockWidgetContents);
        Box_Height->setObjectName(QStringLiteral("Box_Height"));
        Box_Height->setGeometry(QRect(8, 248, 71, 20));
        label_29 = new QLabel(dockWidgetContents);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(22, 282, 54, 21));
        label_29->setFont(font1);
        label_21 = new QLabel(dockWidgetContents);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(20, 223, 54, 21));
        label_21->setFont(font1);
        label_24 = new QLabel(dockWidgetContents);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(177, 222, 54, 21));
        label_24->setFont(font1);
        Box_Y_Posi = new QLineEdit(dockWidgetContents);
        Box_Y_Posi->setObjectName(QStringLiteral("Box_Y_Posi"));
        Box_Y_Posi->setGeometry(QRect(166, 247, 71, 20));
        label_25 = new QLabel(dockWidgetContents);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(179, 175, 54, 21));
        label_25->setFont(font1);
        Box_X_Posi = new QLineEdit(dockWidgetContents);
        Box_X_Posi->setObjectName(QStringLiteral("Box_X_Posi"));
        Box_X_Posi->setGeometry(QRect(166, 197, 71, 20));
        Box_X_Posi_RE = new QLineEdit(dockWidgetContents);
        Box_X_Posi_RE->setObjectName(QStringLiteral("Box_X_Posi_RE"));
        Box_X_Posi_RE->setEnabled(false);
        Box_X_Posi_RE->setGeometry(QRect(166, 303, 71, 20));
        Box_Y_Posi_RE = new QLineEdit(dockWidgetContents);
        Box_Y_Posi_RE->setObjectName(QStringLiteral("Box_Y_Posi_RE"));
        Box_Y_Posi_RE->setEnabled(false);
        Box_Y_Posi_RE->setGeometry(QRect(167, 353, 71, 20));
        label_30 = new QLabel(dockWidgetContents);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(180, 281, 54, 21));
        label_30->setFont(font1);
        label_31 = new QLabel(dockWidgetContents);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(180, 328, 54, 21));
        label_31->setFont(font1);
        Rotate3D_X = new QLineEdit(dockWidgetContents);
        Rotate3D_X->setObjectName(QStringLiteral("Rotate3D_X"));
        Rotate3D_X->setGeometry(QRect(19, 151, 71, 20));
        label_5 = new QLabel(dockWidgetContents);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 123, 54, 21));
        label_5->setFont(font1);
        label_13 = new QLabel(dockWidgetContents);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(125, 122, 54, 21));
        label_13->setFont(font1);
        Rotate3D_Y = new QLineEdit(dockWidgetContents);
        Rotate3D_Y->setObjectName(QStringLiteral("Rotate3D_Y"));
        Rotate3D_Y->setGeometry(QRect(124, 150, 71, 20));
        label_14 = new QLabel(dockWidgetContents);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(225, 122, 54, 21));
        label_14->setFont(font1);
        Rotate3D_Z = new QLineEdit(dockWidgetContents);
        Rotate3D_Z->setObjectName(QStringLiteral("Rotate3D_Z"));
        Rotate3D_Z->setGeometry(QRect(224, 150, 71, 20));
        label_15 = new QLabel(dockWidgetContents);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(319, 123, 71, 21));
        label_15->setFont(font1);
        Is_show = new QLineEdit(dockWidgetContents);
        Is_show->setObjectName(QStringLiteral("Is_show"));
        Is_show->setEnabled(false);
        Is_show->setGeometry(QRect(318, 151, 71, 20));
        Is_show->setReadOnly(false);
        Is_show->setClearButtonEnabled(false);
        dockWidget_4->setWidget(dockWidgetContents);
        QtEditClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_4);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(openaction);
        menu->addAction(Action_Save);
        menu->addAction(closeaction);
        menu_2->addAction(importaction);
        menu_2->addAction(import_Spine);
        menu_2->addAction(export_byte);
        menu_2->addAction(exportaction);
        menu_3->addAction(actionHelp);

        retranslateUi(QtEditClass);

        QMetaObject::connectSlotsByName(QtEditClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtEditClass)
    {
        QtEditClass->setWindowTitle(QApplication::translate("QtEditClass", "QtEdit", 0));
        closeaction->setText(QApplication::translate("QtEditClass", "\345\205\263\351\227\255", 0));
        openaction->setText(QApplication::translate("QtEditClass", "FBX\346\226\207\344\273\266\350\275\254\346\215\242", 0));
        importaction->setText(QApplication::translate("QtEditClass", "\345\257\274\345\205\245c3b,c3t", 0));
        actionHelp->setText(QApplication::translate("QtEditClass", "Help", 0));
        exportaction->setText(QApplication::translate("QtEditClass", "\345\257\274\345\207\272JSON", 0));
        Action_Save->setText(QApplication::translate("QtEditClass", "\344\277\235\345\255\230Ctrl+S", 0));
        export_byte->setText(QApplication::translate("QtEditClass", "\345\257\274\345\207\272\344\272\214\350\277\233\345\210\266", 0));
        import_Spine->setText(QApplication::translate("QtEditClass", "\345\257\274\345\205\245Spine", 0));
        menu->setTitle(QApplication::translate("QtEditClass", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("QtEditClass", "\347\274\226\350\276\221", 0));
        menu_3->setTitle(QApplication::translate("QtEditClass", "\345\270\256\345\212\251", 0));
        QTreeWidgetItem *___qtreewidgetitem = AnimationtreeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("QtEditClass", "Animations", 0));
        label->setText(QApplication::translate("QtEditClass", "P_Width", 0));
        label_2->setText(QApplication::translate("QtEditClass", "P_Height", 0));
        Width->setText(QApplication::translate("QtEditClass", "500", 0));
        Height->setText(QApplication::translate("QtEditClass", "100", 0));
        label_3->setText(QApplication::translate("QtEditClass", "ScallX", 0));
        label_4->setText(QApplication::translate("QtEditClass", "ScallY", 0));
        ScallX->setText(QApplication::translate("QtEditClass", "1", 0));
        ScallY->setText(QApplication::translate("QtEditClass", "1", 0));
        PauseButton->setText(QApplication::translate("QtEditClass", "Start", 0));
        Re_Width->setText(QApplication::translate("QtEditClass", "0", 0));
        Re_Height->setText(QApplication::translate("QtEditClass", "0", 0));
        label_6->setText(QApplication::translate("QtEditClass", "\347\233\270\345\257\271Width", 0));
        label_7->setText(QApplication::translate("QtEditClass", "\347\233\270\345\257\271Height", 0));
        label_8->setText(QApplication::translate("QtEditClass", "\350\265\267\347\202\271X", 0));
        St_Width->setText(QString());
        St_Height->setText(QString());
        label_10->setText(QApplication::translate("QtEditClass", "\350\265\267\347\202\271Y", 0));
        En_Height->setText(QString());
        En_Width->setText(QString());
        label_18->setText(QApplication::translate("QtEditClass", "\347\273\210\347\202\271Y", 0));
        label_19->setText(QApplication::translate("QtEditClass", "\347\273\210\347\202\271X", 0));
        label_22->setText(QApplication::translate("QtEditClass", "Rotate", 0));
        Rotate->setText(QString());
        St_Width_RE->setText(QString());
        label_11->setText(QApplication::translate("QtEditClass", "\350\265\267\347\202\271Y", 0));
        St_Height_RE->setText(QString());
        En_Width_RE->setText(QString());
        label_9->setText(QApplication::translate("QtEditClass", "\350\265\267\347\202\271X", 0));
        En_Height_RE->setText(QString());
        label_26->setText(QApplication::translate("QtEditClass", "\347\273\210\347\202\271Y", 0));
        label_27->setText(QApplication::translate("QtEditClass", "\347\273\210\347\202\271X", 0));
        Line_ID->setText(QApplication::translate("QtEditClass", "0", 0));
        label_12->setText(QApplication::translate("QtEditClass", "Line_ID", 0));
        label_20->setText(QApplication::translate("QtEditClass", "\345\256\275\345\272\246", 0));
        Box_Width->setText(QString());
        Box_Width_RE->setText(QString());
        label_28->setText(QApplication::translate("QtEditClass", "\351\253\230\345\272\246", 0));
        Box_Height_RE->setText(QString());
        Box_Height->setText(QString());
        label_29->setText(QApplication::translate("QtEditClass", "\345\256\275\345\272\246", 0));
        label_21->setText(QApplication::translate("QtEditClass", "\351\253\230\345\272\246", 0));
        label_24->setText(QApplication::translate("QtEditClass", "\344\270\255\345\277\203Y", 0));
        Box_Y_Posi->setText(QString());
        label_25->setText(QApplication::translate("QtEditClass", "\344\270\255\345\277\203X", 0));
        Box_X_Posi->setText(QString());
        Box_X_Posi_RE->setText(QString());
        Box_Y_Posi_RE->setText(QString());
        label_30->setText(QApplication::translate("QtEditClass", "\344\270\255\345\277\203X", 0));
        label_31->setText(QApplication::translate("QtEditClass", "\344\270\255\345\277\203Y", 0));
        Rotate3D_X->setText(QApplication::translate("QtEditClass", "1", 0));
        label_5->setText(QApplication::translate("QtEditClass", "X\350\275\264\346\227\213\350\275\254", 0));
        label_13->setText(QApplication::translate("QtEditClass", "Y\350\275\264\346\227\213\350\275\254", 0));
        Rotate3D_Y->setText(QApplication::translate("QtEditClass", "1", 0));
        label_14->setText(QApplication::translate("QtEditClass", "Z\350\275\264\346\227\213\350\275\254", 0));
        Rotate3D_Z->setText(QApplication::translate("QtEditClass", "1", 0));
        label_15->setText(QApplication::translate("QtEditClass", "\346\230\257\345\220\246\346\230\276\347\244\272", 0));
        Is_show->setText(QApplication::translate("QtEditClass", "true", 0));
    } // retranslateUi

};

namespace Ui {
    class QtEditClass: public Ui_QtEditClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEDIT_H
