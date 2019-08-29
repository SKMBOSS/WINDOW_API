#include "TextBrickSpawner.h"
#include "TextBrick.h"
#include <time.h>
#include <algorithm>


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
	tbBox.push_back(new TextBrick(GetRandomPos(), 4, GetNextWord()));
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

bool TextBrickSpanwner::IsCorrectAnswer(string _inputStr)
{
	list<TextBrick*>::iterator iter = find_if(tbBox.begin(), tbBox.end(),
		[_inputStr](TextBrick* tb) -> bool
	{
		return _inputStr == tb->GetTargetText();
	});

	if (iter != tbBox.end())
	{
		delete (*iter);
		tbBox.erase(iter);
		return true;
	}

	else
		return false;
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