#include "qtedit.h"
#include "AppDelegate.h"
#include <QtWidgets/QApplication>
USING_NS_CC;
int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	//QtEdit w;
	//w.show();
	//return a.exec();
	AppDelegate app(argc, argv);
	return cocos2d::CCQApplication::getInstance()->run();
}
