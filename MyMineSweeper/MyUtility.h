#pragma once

bool IsOutOfRangeIndex(int x, int y, int maxX, int maxY)
{
	if (x < 0)
		return true;
	if (y < 0)
		return true;
	if (x >= maxX)
		return true;
	if (y >= maxY)
		return true;

	return false;
}