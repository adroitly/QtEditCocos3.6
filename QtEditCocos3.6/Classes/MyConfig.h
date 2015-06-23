#ifndef  _MYCONFIG_H_
#define  _MYCONFIG_H_

#define  _IN_Width				500.0
#define  _IN_Height				100.0
#define  _IN_ScallX				1.0
#define  _IN_ScallY				1.0
#define  oneFPX					30.0
#define	 PI						3.1415926535898
#define  _Effecttext			"Effect"
#define  _Bodytext				"Body"
#define  _Atttext				"Attack"
#define  _Injtext				"Injure"
#define  _InComboxtext			"-\350\257\267\351\200\211\346\213\251-"
#define  _Input_EXP				"^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,6})?$|(^\\t?$)"
#define  QStringToDouble(str)	str.toDouble();
#define  QStringToFloat(str)	str.toFloat()
#define  QStringToVec2(w,h)		Vec2(w.toFloat(),h.toFloat())
#define  FREE_DEL_VEC(f) do{if(f != NULL) {delete []f;}}while (0);
#define  FREE_DEL_OBJ(f) do{if(f != NULL) {delete (f) ; f = NULL;}}while (0);
#define  MYDELETE(f) do{if(f != NULL) delete (f);}while(0);


#endif