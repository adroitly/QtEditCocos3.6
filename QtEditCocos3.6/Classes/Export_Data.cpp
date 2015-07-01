#include "Export_Data.h"


static QtEdit *_QtEdit = NULL;
static Export_Data *_Export_ByteArrry = NULL;
static MyVector * _tempVector;
static MySpritePoint * _tempSpritePoint;
static MyDrawNode * _tempDrawNode;
static ByteArray * _ByteArray;
static ByteArray * _anima;
Export_Data::Export_Data()
{
}

Export_Data * Export_Data::getInstence()
{
	if (_Export_ByteArrry == NULL)
	{
		_Export_ByteArrry = new Export_Data();
		_QtEdit = QtEdit::getInstance();
		_tempVector = new MyVector();
		_tempSpritePoint = new MySpritePoint();
		_tempDrawNode = new MyDrawNode();
		_ByteArray = new ByteArray(false);
	}
	return _Export_ByteArrry;
}


Export_Data::~Export_Data()
{
	//free(_tempVector);
	delete _tempVector;
	//free(_tempSpritePoint);
	delete _tempSpritePoint;
	//free(_tempDrawNode);
	delete _tempDrawNode;
	//free (_Export_ByteArrry);
	delete _Export_ByteArrry;
}


void Export_Data::DrawDataTo_Qtedit()
{
	
	//MyVector * _tempVector = new MyVector();
	if (_QtEdit->myVector == NULL)
	{
		_QtEdit->myVector = new MyVector();
		_QtEdit->myVector->Singl_ID = 0;
		_QtEdit->myVector->Sprites = _QtEdit->_DrawRectLayer->spritePoints;
		_QtEdit->spritesPoints.push_back(_QtEdit->myVector);
	}
	for (i = 0; i < _QtEdit->spritesPoints.size(); i++)
	{
		_QtEdit->tempVector = _QtEdit->spritesPoints.at(i);
		if (_QtEdit->tempVector->Singl_ID == _QtEdit->myVector->Singl_ID)
		{
			_QtEdit->spritesPoints.at(i)->Sprites = _QtEdit->_DrawRectLayer->spritePoints;
			break;
		}
	}
}

void Export_Data::Dosave_ExportByte(const char * file_name, const vector<MyVector *> _export_data)
{
	_ByteArray = new ByteArray(false);
	_ByteArray->writeUnsignedShort(1);//版本号
	for (i = 0; i < _export_data.size(); i ++)
	{
		_tempVector = _export_data.at(i);
		_anima = new ByteArray(false);
		numTimeline = 0;
		width = 0.0; 
		height = 0.0;
		int num[5] = { 0 };
		for (j = 0; j < _tempVector->Sprites.size(); j ++)
		{
			_tempSpritePoint = _tempVector->Sprites.at(j);
			
			if (_tempSpritePoint->Is_ActFra && num[0] == 0)
			{
				num[0] = 1;
				numTimeline++;
			}
			else if (_tempSpritePoint->Is_ActFra)
			{
				num[0] ++;
			}
			if (_tempSpritePoint->Is_BodyFra && num[1] == 0)
			{
				num[1] = 1;
				numTimeline++;
			}
			else if (_tempSpritePoint->Is_BodyFra)
			{
				num[1] ++;
			}

			if (_tempSpritePoint->Is_InjFra && num[2] == 0)
			{
				num[2] = 1;
				numTimeline++;
			}
			else if (_tempSpritePoint->Is_InjFra)
			{
				num[2] ++;
			}

			if (_tempSpritePoint->Is_AttFra && num[3] == 0)
			{
				num[3] = 1;
				numTimeline++;
			}
			else if (_tempSpritePoint->Is_AttFra)
			{
				num[3] ++;
			}

			if (_tempSpritePoint->Is_EffFra && num[4] == 0)
			{
				num[4] = 1;
				numTimeline++;
			}
			else if (_tempSpritePoint->Is_EffFra)
			{
				num[4] ++;
			}
			
		}
		std::string name = _QtEdit->animation_list.at(_export_data.at(i)->Singl_ID).mid(_QtEdit->animation_list.at(_export_data.at(i)->Singl_ID).lastIndexOf("/") + 1).split(".").at(0).toStdString();
		//cocos2d::log("Name = %s", name.c_str());
		//cocos2d::log("LINE = %d", numTimeline);
		//写入名字和时间线
		_anima->writeString(name);
		_anima->writeUnsignedChar(numTimeline);
		for (k = 0; k < 5; k ++)
		{
			if (num[k] == 0)
			{
				continue;
			}
			width = -0.0;
			height = -0.0;
			//0=character, 1=body, 2=suffer, 3=attacker;4=label;
			//timelineType
			_anima->writeUnsignedChar(k);
			if (k == 4)
			{
				_anima->writeString("defult");
			}
			float _tempScall = 1;
			for (j = 0; j < _tempVector->Sprites.size(); j++)
			{
				_tempSpritePoint = _tempVector->Sprites.at(j);
				if (k == 0)
				{
				}
				else if (k == 1)
				{
					if (_tempSpritePoint->bodyVertices != NULL && (_tempSpritePoint->bodyVertices[0].x > 0.0 || _tempSpritePoint->bodyVertices[2].x > 0.0))
					{
						width = abs(_tempSpritePoint->bodyVertices[0].x - _tempSpritePoint->bodyVertices[2].x);
						height = abs(_tempSpritePoint->bodyVertices[0].y - _tempSpritePoint->bodyVertices[2].y);
						_tempScall = _tempSpritePoint->_ScallX;
						break;
					}
				}
				else if (k == 2)
				{
					if (_tempSpritePoint->injureVertices != NULL && (_tempSpritePoint->injureVertices[0].x > 0.0 || _tempSpritePoint->injureVertices[2].x > 0.0))
					{
						width = abs(_tempSpritePoint->injureVertices[0].x - _tempSpritePoint->injureVertices[2].x);
						height = abs(_tempSpritePoint->injureVertices[0].y - _tempSpritePoint->injureVertices[2].y);
						_tempScall = _tempSpritePoint->_ScallX;
						break;
					}
				}
				else if (k == 3)
				{
					if (_tempSpritePoint->attackVertices != NULL && (_tempSpritePoint->attackVertices[0].x > 0.0 || _tempSpritePoint->attackVertices[2].x > 0.0))
					{
						width = abs(_tempSpritePoint->attackVertices[0].x - _tempSpritePoint->attackVertices[2].x);
						height = abs(_tempSpritePoint->attackVertices[0].y - _tempSpritePoint->attackVertices[2].y);
						_tempScall = _tempSpritePoint->_ScallX;
						break;
					}
				}
				else if (k == 4)
				{
					if (_tempSpritePoint->effectVertices != NULL && (_tempSpritePoint->effectVertices[0].x > 0.0 || _tempSpritePoint->effectVertices[2].x > 0.0))
					{
						width = abs(_tempSpritePoint->effectVertices[0].x - _tempSpritePoint->effectVertices[2].x);
						height = abs(_tempSpritePoint->effectVertices[0].y - _tempSpritePoint->effectVertices[2].y);
						_tempScall = _tempSpritePoint->_ScallX;
						break;
					}
				}
			}
			//shapeType
			if (k == 0)
			{
				_anima->writeUnsignedChar(0);
			}
			else
			{
				_anima->writeUnsignedChar(1);
				//with,height
				_anima->writeFloat(width);
				_anima->writeFloat(height);
			}
			//num[k] 
			_anima->writeUnsignedShort(num[k]);
			//cocos2d::log("NUM = %d", num[k]);
			for (j = 0; j < _tempVector->Sprites.size(); j ++)
			{
				_tempSpritePoint = _tempVector->Sprites.at(j);
				if (k == 0 && !_tempSpritePoint->Is_ActFra)
				{
					continue;
				}
				if (k == 1 && !_tempSpritePoint->Is_BodyFra)
				{
					continue;
				}
				if (k == 2 && !_tempSpritePoint->Is_InjFra)
				{
					continue;
				}
				if (k == 3 && !_tempSpritePoint->Is_AttFra)
				{
					continue;
				}
				if (k == 4 && !_tempSpritePoint->Is_EffFra)
				{
					continue;
				}
				rotation = 0;
				my_Scall = _IN_ScallX;
				time = _tempSpritePoint->Single_ID / oneFPX;
				Vec2 myposi(_tempSpritePoint->_width, _tempSpritePoint->_height);
				if (k == 1 && _tempSpritePoint->Is_BodyFra)
				{
					_tempDrawNode->Vertices = _tempSpritePoint->bodyVertices;
					_tempDrawNode->setRelativeVertices(_tempDrawNode->Vertices, myposi);
				}
				else if (k == 2 && _tempSpritePoint->Is_InjFra)
				{
					_tempDrawNode->Vertices = _tempSpritePoint->injureVertices;
					_tempDrawNode->setRelativeVertices(_tempDrawNode->Vertices, myposi);
					rotation = 180.0 / PI * _tempSpritePoint->RotateInj;
				}
				else if (k == 3 && _tempSpritePoint->Is_AttFra)
				{
					_tempDrawNode->Vertices = _tempSpritePoint->attackVertices;
					_tempDrawNode->setRelativeVertices(_tempDrawNode->Vertices, myposi);
					rotation = 180.0 / PI * _tempSpritePoint->RotateAtt;
				}
				else if (k == 4 && _tempSpritePoint->Is_EffFra)
				{
					_tempDrawNode->Vertices = _tempSpritePoint->effectVertices;
					_tempDrawNode->setRelativeVertices(_tempDrawNode->Vertices, myposi);
					rotation = 180.0 / PI * _tempSpritePoint->RotateAtt;
				}
				if (k == 0)
				{
					_x = _tempSpritePoint->_width - _IN_Width;
					_y = _tempSpritePoint->_height - _IN_Height;
					my_Scall = _tempSpritePoint->_ScallX;
					enabled = true;
				}
				else
				{
					
					my_Scall = _tempSpritePoint->_ScallX;
					if (_tempDrawNode->Vertices[0].x > 0.0 || _tempDrawNode->Vertices[2].x > 0.0)
					{
						_x = (_tempDrawNode->Relativevertices[0].x + _tempDrawNode->Relativevertices[2].x) / 2.0 - _tempSpritePoint->_width;
						_y = (_tempDrawNode->Relativevertices[0].y + _tempDrawNode->Relativevertices[2].y) / 2.0 - _tempSpritePoint->_height;
						enabled = true;
					}
					else
					{
						_x = 0;
						_y = 0;
						enabled = false;
					}
					
				}
				//cocos2d::log("%f , %f ", _tempDrawNode->Relativevertices[0].x, _tempDrawNode->Relativevertices[2].x);
				//time , x , y , scale , enable
				//log("%f , %f , %f ,%f  , %f , %s", time, x, y, my_Scall ,rotation , enabled == true ? "true" : "false");
				_anima->writeFloat(time);
				_anima->writeFloat(_x);
				_anima->writeFloat(_y);
				_anima->writeFloat(my_Scall / _tempScall);
				_anima->writeFloat(rotation);
				_anima->writeBool(enabled);
			}
		}
		_ByteArray->writeUnsignedInt(_anima->getLength());
		_ByteArray->writeBytes(_anima);
		//delete _anima;
	}
	//ofstream fout(file_name, ios::binary);
	//ofstream f();
	//fout << _ByteArray->getBytes();
	//fout.flush();
	//fout.close();
	FILE *fp;
	fp = fopen(file_name, "wb");
	if (fp == NULL)
	{
		log("Open %s Error", file_name);;
	}
	fwrite(_ByteArray->getBytes(), _ByteArray->getLength(), 1, fp);
	fclose(fp);
	delete _ByteArray;
}


void Export_Data::Dosave_JsonData(const char * file_name, const vector<MyVector * > _export_data, bool tobase /* = false */)
{
	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;
	Json::Value OnjectItem;
	Json::Value SItem;
	Json::Value _data;
	int i, j, k;
	double attsx, attsy, attex, attey;
	double attrotate;
	double injsx, injsy, injex, injey;
	double injrotate;
	double bodsx, bodsy, bodex, bodey;
	double effsx, effsy, effex, effey;
	//QFile file(name);
	//if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	//{
	//	QMessageBox::about(this, tr("information"), tr("Save Error"));
	//	return;
	//}
	MySpritePoint * _tempSp;
	//QTextStream out(&file);
	arrayObj.clear();
	_tempVector = nullptr;
	for (i = 0; i < _export_data.size(); i++)
	{
		_tempVector = _export_data.at(i);
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
		}
		//_data["data"] = OnjectItem;
		//_data["scx"] = _tempVector->_ScallX;
		//_data["scy"] = _tempVector->_ScallY;
		//_data["he"] = _tempVector->_height;
		//_data["wi"] = _tempVector->_width;
		//arrayObj[animation_list.at(i).split("/").at(1).split(".").at(0).toStdString()] = OnjectItem;
		arrayObj[_QtEdit->animation_list.at(_export_data.at(i)->Singl_ID).mid(_QtEdit->animation_list.at(_export_data.at(i)->Singl_ID).lastIndexOf("/") + 1).split(".").at(0).toStdString()] = OnjectItem;
	}
	root[_QtEdit->_filename.toStdString()] = arrayObj;
	std::string outfile;
	outfile = root.toStyledString();
	CStringA outfiledata;
	if (tobase)
	{
		CString strSSL = outfile.c_str();
		CStringA strTemp = CT2A(strSSL);
		unsigned char* pBuf = (unsigned char*)strTemp.GetBuffer(strTemp.GetLength());
		CStringA strA;
		int bufLen = strTemp.GetLength();
		int outlen = bufLen * 2;
		if (Base64Encode(pBuf, bufLen, strA.GetBuffer(outlen), &outlen, ATL_BASE64_FLAG_NONE))
		{
			strA.ReleaseBuffer(outlen);
			outfiledata = CA2T(strA);
		}
	}
	else
	{
		outfiledata = outfile.c_str();
	}
	ofstream fout(file_name);
	fout << outfiledata;
	fout.flush();
	fout.close();
}