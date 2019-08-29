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
	return rand() % 1050 + 60;
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

void TextBrickSpanwner::Init()
{
	srand(time(nullptr));
	inFile.open(fileName);
}

void TextBrickSpanwner::Update()
{
	if (ResetCycleCount())
	{
		tbBox.push_back(new TextBrick(GetRandomPos(),6, GetNextWord()));
	}
		
	for (auto iter = tbBox.begin(); iter != tbBox.end(); ++iter)
	{
		(*iter)->DownBrick();
	}

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