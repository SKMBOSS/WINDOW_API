#include "CircusObject.h"

int CircusObject::m_sScreenPosX = 0;
int CircusObject::m_sScreenSpeed = 2;
int CircusObject::m_bMove = true;

CircusObject::CircusObject()
{
}


CircusObject::~CircusObject()
{
}

void CircusObject::MoveScreenRight()
{
	if(m_bMove)
	m_sScreenPosX += m_sScreenSpeed;
}
void CircusObject::MoveScreenLeft()
{
	if (m_bMove)
	m_sScreenPosX -= m_sScreenSpeed;
}