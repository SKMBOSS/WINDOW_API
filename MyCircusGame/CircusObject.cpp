#include "CircusObject.h"

int CircusObject::m_sScreenPosX = 0;
int CircusObject::m_sScreenSpeed = 2;

CircusObject::CircusObject()
{
}


CircusObject::~CircusObject()
{
}

void CircusObject::MoveScreenRight()
{
	m_sScreenPosX += m_sScreenSpeed;
}
void CircusObject::MoveScreenLeft()
{
	m_sScreenPosX -= m_sScreenSpeed;
}