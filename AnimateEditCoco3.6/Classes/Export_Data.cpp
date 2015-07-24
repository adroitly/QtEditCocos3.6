#include "Export_Data.h"
#include "qtedit.h"
#include "json/json.h"
#include "json/json.h"
#include "ATLENC.H"
#include "atlstr.h "
#include <fstream>
using namespace std;
Export_Data * Export_Data::_Export_Data = NULL;
static QtEdit * _QtEdit = NULL;
Export_Data::Export_Data()
{
	_QtEdit = QtEdit::getInstance();
}


Export_Data::~Export_Data()
{
}

Export_Data * Export_Data::getinstance()
{
	if (_Export_Data == NULL)
	{
		_Export_Data = new Export_Data();
	}
	return _Export_Data;
}

void Export_Data::Export_JSONData(QVector<MyLineVector *> & _animateLineButton, std::string file_name)
{

}

void Export_Data::Export_SaveData(QVector<MyLineVector *> & _animateLineButton, std::string file_name)
{
	Json::Value root_json;
	Json::Value _anima_json;
	Json::Value _line_anima;
	Json::Value _item;
	Json::Value ObjectItem;
	Json::Value _item_item;
	Json::Value _saItem;
	QVector<QVector<ClickButton *>> _lineButton;
	ClickButton * _temp;
	DrawNodeVertices * _drawNodeVertices;
	std::string _ani_name;
	int _anima_ID;
	int _line_ID;
	int i;
	int j;
	int k;
	float _ScallX;
	float _ScallY;
	float Width;
	float Height;
	float _last_w;
	float _last_h;
	float _last_sx;
	float _last_sy;
	float st_x;
	float st_y;
	float en_x;
	float en_y;
	float _rotate;
	int _row;
	int _col;
	int frame_model;
	bool _is_frame;
	bool _is_null;
	for (k = 0; k < _animateLineButton.size(); k ++)
	{

		_saItem.clear();
		_lineButton = _animateLineButton.at(k)->_lineButton;
		_ani_name = _animateLineButton.at(k)->_anima_Name;
		_anima_ID = _animateLineButton.at(k)->_anima_ID;
		_saItem["name"] = _ani_name;
		_saItem["ID"] = _anima_ID;
		_line_anima.clear();
		for (i = 0; i < _lineButton.size(); i ++)
		{
			ObjectItem.clear();
			_line_ID = _lineButton.at(i).at(0)->getLineID();
			ObjectItem["line_id"] = _line_ID;
			_item_item.clear();
			for (j = 0; j < _lineButton.at(i).size(); j ++)
			{
				_temp = _lineButton.at(i).at(j);
				//if (!_temp->isFrame())
				//{
				//	continue;
				//}
				_ScallX = _temp->_ScallX;
				_ScallY = _temp->_ScallY;
				Width = _temp->_Width;
				Height = _temp->_Height;
				_drawNodeVertices = _temp->_DrawNodeVertices;
				_last_w = _drawNodeVertices->_last_Width;
				_last_h = _drawNodeVertices->_last_Height;
				_last_sx = _drawNodeVertices->_last_ScallX;
				_last_sy = _drawNodeVertices->_last_ScallY;
				st_x = _drawNodeVertices->Relativevertices[0].x;
				st_y = _drawNodeVertices->Relativevertices[0].y;
				en_x = _drawNodeVertices->Relativevertices[2].x;
				en_y = _drawNodeVertices->Relativevertices[2].y;
				_rotate = _drawNodeVertices->Rotate;
				_row = _temp->getRow();
				_col = _temp->getCol();
				_is_frame = _temp->isFrame();
				if (_is_frame)
				{
					log("YES");
				}
				frame_model = _temp->getFrameMode();
				_is_null = _temp->isNULL();
				_item.clear();
				_item["_ScallX"] = _ScallX;
				_item["_ScallY"] = _ScallY;
				_item["Width"] = Width;
				_item["Height"] = Height;
				_item["_last_w"] = _last_w;
				_item["_last_h"] = _last_h;
				_item["_last_sx"] = _last_sx;
				_item["_last_sy"] = _last_sy;
				_item["st_x"] = st_x;
				_item["st_y"] = st_y;
				_item["en_x"] = en_x;
				_item["en_y"] = en_y;
				_item["_rotate"] = _rotate;
				_item["_row"] = _row;
				_item["_col"] = _col;
				_item["_is_frame"] = _is_frame;
				_item["frame_model"] = frame_model;
				_item["_is_null"] = _is_null;
				_item_item[j] = _item;
			}
			ObjectItem["line_data"] = _item_item;
			_line_anima[i] = ObjectItem;
		}
		//log("%s", _line_anima.toStyledString().c_str());
		_saItem["_data"] = _line_anima;
		_anima_json[k] = _saItem;
	}
	std::string str = file_name.substr(file_name.find_last_of("/"));
	int _len = str.find_last_of(".");

	str = str.substr(1, _len - 1);
	root_json[str] = _anima_json;
	str = root_json.toStyledString();
	ofstream fout(file_name);
	fout << str;
	fout.flush();
	fout.close();
}

void Export_Data::Export_ByteData(QVector<MyLineVector *> & _animateLineButton, std::string file_name)
{
	int k, i, j;
	ByteArray *_anima;
	_ByteArray = new ByteArray(false);
	_ByteArray->writeUnsignedShort(1);//°æ±¾ºÅ
	MyLineVector * _MyLineVector;
	QVector<QVector<ClickButton *>> _lineButton;
	ClickButton * _temp;
	DrawNodeVertices * _drawNodeVertices;
	std::string _ani_name;
	int _anima_ID;
	int _line_ID;
	float _ScallX;
	float _ScallY;
	float Width;
	float Height;
	float _last_w;
	float _last_h;
	float _last_sx;
	float _last_sy;
	float st_x;
	float st_y;
	float en_x;
	float en_y;
	float _rotate;
	int _row;
	int _col;
	int frame_model;
	bool _is_frame;
	bool _is_null;
	float _tempScall;
	int _count;
	for (k = 0; k < _animateLineButton.size(); k ++ )
	{
		_MyLineVector = _animateLineButton.at(k);
		_lineButton = _MyLineVector->_lineButton;
		_ani_name = _MyLineVector->_anima_Name;
		_anima_ID = _MyLineVector->_anima_ID;
		_anima = new ByteArray(false);
		//name (string)
		_anima->writeString(_ani_name);
		//numTimeline (unsigned char)
		_anima->writeUnsignedChar(_lineButton.size());
		for (i = 0; i < _lineButton.size(); i ++)
		{
			//_anima->writeUnsignedChar(_lineButton.at(i).at(0)->getFrameMode());
			frame_model = _lineButton.at(i).at(0)->getFrameMode();
			//timelineType (unsigned char) //0=character, 1=body, 2=suffer, 3=attacker, 4=label;
			_anima->writeUnsignedChar(frame_model);
			//partID (unsigned char);
			_anima->writeUnsignedChar(_lineButton.at(i).at(0)->getLineID());
			_count = 0;
			_tempScall = 1;
			for (j = 0; j < _lineButton.at(i).size(); j++)
			{
				if (_lineButton.at(i).at(j)->isFrame())
				{
					_count++;
					if (_count == 1)
					{
						_tempScall = _lineButton.at(0).at(j)->_ScallX;
						_drawNodeVertices = _lineButton.at(i).at(j)->_DrawNodeVertices;
						Width = abs(_drawNodeVertices->Relativevertices[0].x - _drawNodeVertices->Relativevertices[2].x);
						Height = abs(_drawNodeVertices->Relativevertices[0].y - _drawNodeVertices->Relativevertices[2].y);
					}
				}
			}
			_count = 0;
			for (j = 0; j < _lineButton.at(i).size(); j++)
			{
				if (_lineButton.at(i).at(j)->isFrame())
				{
					_count++;
				}
			}
			//shapeType (unsigned char) //0=none, 1=box, 2=circle;
			//if (shapeType == 0) {
			//	//none
			//}
			//else if (shapeType == 1) {
			//	width(float);
			//	height(float);
			//}
			//else if (shapeType == 2) {
			//	radius(float);
			//}
			if (i == 0)
			{
				_anima->writeUnsignedChar(0);
			}
			else
			{
				_anima->writeUnsignedChar(1);
				_anima->writeFloat(Width / _tempScall);
				_anima->writeFloat(Height / _tempScall);
			}

			_anima->writeUnsignedShort(_count);
			for (j = 0; j < _lineButton.at(i).size(); j ++)
			{
				if (_lineButton.at(i).at(j)->isFrame())
				{
					_temp = _lineButton.at(i).at(j);
					_drawNodeVertices = _lineButton.at(i).at(j)->_DrawNodeVertices;
					float time = j / oneFPX;
					float _x = (_drawNodeVertices->Relativevertices[0].x + _drawNodeVertices->Relativevertices[2].x) / 2.0 - _temp->_Width;
					float _y = (_drawNodeVertices->Relativevertices[0].y + _drawNodeVertices->Relativevertices[2].y) / 2.0 - _temp->_Height;
					float _my_Scall = _lineButton.at(0).at(j)->_ScallX;
					_x = _x / _my_Scall;
					_y = _y / _my_Scall;
					if (i == 0)
					{
						_x = _temp->_Width - _IN_Width;
						_y = _temp->_Height - _IN_Height;
					}
					else
					{
						_my_Scall = _my_Scall / _tempScall;
					}
					float rotation = _drawNodeVertices->Rotate;
					bool is_null = _lineButton.at(i).at(j)->isNULL();
					if (!is_null)
					{
						is_null = true;
					}
					else
					{
						is_null = false;
					}
					_anima->writeFloat(time);
					_anima->writeFloat(_x);
					_anima->writeFloat(_y);
					_anima->writeFloat(_my_Scall);
					_anima->writeFloat(rotation);
					_anima->writeBool(is_null);
				}
			}
		}
		_ByteArray->writeUnsignedInt(_anima->getLength());
		_ByteArray->writeBytes(_anima);
	}
	FILE *fp;
	fp = fopen(file_name.c_str(), "wb");
	if (fp == NULL)
	{
		log("Open %s Error", file_name.c_str());;
	}
	fwrite(_ByteArray->getBytes(), _ByteArray->getLength(), 1, fp);
	std::fclose(fp);
	delete _ByteArray;
}

void Export_Data::Data_TO_Relatite(QVector<QVector<ClickButton *>> & _allButton, QVector<MyLineVector *> & _animateLineButton)
{
	std::string aniname = _QtEdit->ui.dockWidget->windowTitle().toStdString();
	QtEdit * _QtEdit = QtEdit::getInstance();
	int i = 0;
	int j = 0;
	int _ani_ID;
	for (i = 0; i < _QtEdit->animation_list.size(); i++)
	{
		if (aniname == _QtEdit->animation_list.at(i).toStdString())
		{
			_ani_ID = i;
			break;
		}
	}
	QVector<QVector<ClickButton *>> _retaliteAllClickButton;
	QVector<ClickButton*>_templine;
	ClickButton *_temp;
	_retaliteAllClickButton.clear();
	for (i = 0; i < _allButton.size(); i++)
	{
		_templine.clear();
		for (j = 0; j < _allButton.at(i).size(); j++)
		{
			_temp = _allButton.at(i).at(j)->copy();
			_templine.push_back(_temp);
		}
		_retaliteAllClickButton.push_back(_templine);
	}
	for (i = 0; i < _animateLineButton.size(); i ++)
	{
		if (_ani_ID == _animateLineButton.at(i)->_anima_ID)
		{
			_animateLineButton.at(i)->_lineButton = _retaliteAllClickButton;
			break;
		}
	}
}


