#ifndef __EXPORTDATA_H__
#define __EXPORTDATA_H__
#pragma once
#include "iostream"
#include <vector>
#include "MyVector.h"
//#include "MyConfig.h"
#include "qtedit.h"
//#include "MySpritePoint.h"
#include "json/json.h"
#include "ATLENC.H"
#include "atlstr.h "
#include "ByteArray.h"
#include <fstream>
using namespace std;
class Export_Data
{
public:
	Export_Data();
	~Export_Data();
	static Export_Data * getInstence();
	void DrawDataTo_Qtedit();
	void Dosave_ExportByte(const char * file_name, const vector<MyVector *> _export_data);
	void Dosave_JsonData(const char * file_name, const vector<MyVector * > _export_data , bool tobase = false);
	//void CharToFile(const char * file_name, const char * data);


public:
	int numTimeline;
	int numKeyFrames;
	float rotation;
	bool enabled;
	float time;
	float my_Scall;
	float _x, _y;
	float width;
	float height;
	int i, j;
	int k;
};
#endif

