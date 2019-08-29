#include "TextBrickSpawner.h"
#include "TextBrick.h"
#include <time.h>


using namespace std;

TextBrickSpanwner::TextBrickSpanwner()
{
}

TextBrickSpanwner::~TextBrickSpanwner()
{
}

TextBrickSpanwner::TextBrickSpanwner(string _fileName)
{
	fileName = _fileName;
}

int TextBrickSpanwner::GetRandomPos()
{
	return rand() % 1000 + 100;
}

string TextBrickSpanwner::GetNextWord()
{
	string tempStr = "clear";
	if (!inFile.eof())
	{
		inFile >> tempStr;
	}

	return tempStr;
}

void TextBrickSpanwner::CreateBricks()
{
	tbBox.push_back(new TextBrick(GetRandomPos(), 6, GetNextWord()));
}

void TextBrickSpanwner::DownBricks()
{
	for (auto iter = tbBox.begin(); iter != tbBox.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void TextBrickSpanwner::CrashBrickDelete(RECT _floor)
{
	RECT temp;
	list<TextBrick*>::iterator crashIter = tbBox.begin();
	for (crashIter; crashIter != tbBox.end();)
	{
		if (IntersectRect(&temp, &(*crashIter)->GetRtCollider(), &_floor))
		{
			delete (*crashIter);
			crashIter = tbBox.erase(crashIter);
		}
		else
			crashIter++;
	}
}

void TextBrickSpanwner::Init()
{
	srand(time(nullptr));
	inFile.open(fileName);
}

void TextBrickSpanwner::Update()
{
	if (ResetCycleCount())
	{
		CreateBricks();
	}
	DownBricks();
	ReduceCycleCount();
}
void TextBrickSpanwner::Render(HDC hdc)
{
	for (auto iter = tbBox.begin(); iter != tbBox.end(); ++iter)
	{
		(*iter)->Render(hdc);
	}
}
void TextBrickSpanwner::Release()
{
	inFile.close();
}