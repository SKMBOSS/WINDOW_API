#include "MyBenechia.h"

MyBenechia* MyBenechia::MyBenechiaInstance = nullptr;

MyBenechia::MyBenechia()
{
}

MyBenechia::~MyBenechia()
{
}

MyBenechia* MyBenechia::GetInstance()
{
	if (MyBenechiaInstance == nullptr)
	{
		MyBenechiaInstance = new MyBenechia;
	}
	return MyBenechiaInstance;
}

void MyBenechia::Render(HDC _hdc)
{
	//Rectangle(_hdc, rt.left, rt.top, rt.right, rt.bottom);
	tb->Render(_hdc);
}

void MyBenechia::Init()
{ 
	tb = new TextBrick();
	tb->Init();
}

void MyBenechia::Update()
{
	tb->Update();
}