#pragma once

bool IsOutOfRangeIndex(int index, int vecSize)
{
	if (index < 0)
		return true;
	if (index >= vecSize)
		return true;

	return false;
}