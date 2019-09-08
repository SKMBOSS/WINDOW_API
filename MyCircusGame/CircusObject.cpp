#include "CircusObject.h"

int CircusObject::m_sScreenPosX = 0;
int	CircusObject::m_sSavedPosX = 0;
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

int	 CircusObject::GetDirection()
{
	if ((m_sScreenPosX - m_sSavedPosX) > 0)
		return 1;
	else if ((m_sScreenPosX - m_sSavedPosX) < 0)
		return -1;

	else return 0;
}