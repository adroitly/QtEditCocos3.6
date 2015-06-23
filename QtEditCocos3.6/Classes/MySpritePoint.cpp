#include "MySpritePoint.h"


MySpritePoint::MySpritePoint()
{
	Single_ID = -1;
	RotateAtt = 0.0;
	RotateInj = 0.0;
	_height = _IN_Height;
	_width = _IN_Width;
	_ScallX = _IN_ScallX;
	_ScallY = _IN_ScallY;
	Is_InjFra = false;
	Is_AttFra = false;
	Is_ActFra = false;
	Is_BodyFra = false;
	Is_EffFra = false;
	injureVertices = new Vec2[5];
	bodyVertices = new Vec2[5];
	attackVertices = new Vec2[5];
	effectVertices = new Vec2[5];
}


MySpritePoint::~MySpritePoint()
{
	FREE_DEL_VEC(bodyVertices);
	FREE_DEL_VEC(attackVertices);
	FREE_DEL_VEC(injureVertices);
	FREE_DEL_VEC(effectVertices);
}
void MySpritePoint::setAttackVertices(Vec2 st, Vec2 en)
{
	if (attackVertices == nullptr)
	{
		attackVertices = new Vec2[5];
	}
	attackVertices[0].set(st);
	attackVertices[1].set(Vec2(st.x, en.y));
	attackVertices[2].set(en);
	attackVertices[3].set(Vec2(st.x, en.y));
	attackVertices[4].set(st);
}
void MySpritePoint::setInjureVertices(Vec2 st, Vec2 en)
{
	if (injureVertices == nullptr)
	{
		injureVertices = new Vec2[5];
	}
	injureVertices[0].set(st);
	injureVertices[1].set(Vec2(st.x, en.y));
	injureVertices[2].set(en);
	injureVertices[3].set(Vec2(st.x, en.y));
	injureVertices[4].set(st);
}

void MySpritePoint::setBodyVertices(Vec2 st, Vec2 en)
{
	if (bodyVertices == nullptr)
	{
		bodyVertices = new Vec2[5];
	}
	bodyVertices[0].set(st);
	bodyVertices[1].set(Vec2(st.x, en.y));
	bodyVertices[2].set(en);
	bodyVertices[3].set(Vec2(st.x, en.y));
	bodyVertices[4].set(st);
}
void MySpritePoint::setEffectVertices(Vec2 st, Vec2 en)
{
	if (effectVertices == nullptr)
	{
		effectVertices = new Vec2[5];
	}
	effectVertices[0].set(st);
	effectVertices[1].set(Vec2(st.x, en.y));
	effectVertices[2].set(en);
	effectVertices[3].set(Vec2(st.x, en.y));
	effectVertices[4].set(st);
}