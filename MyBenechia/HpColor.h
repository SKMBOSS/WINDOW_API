#pragma once

struct MyRGB
{
	int R;
	int G;
	int B;
};

class HpColor
{
public:
	MyRGB _RGB[8];
public:
	void SetRGB()
	{
		//�ٴ�
		_RGB[7].R = 051;
		_RGB[7].G = 051;
		_RGB[7].B = 204;
		//��
		_RGB[6].R = 255;
		_RGB[6].G = 051;
		_RGB[6].B = 051;
		//��
		_RGB[5].R = 255;
		_RGB[5].G = 153;
		_RGB[5].B = 000;
		//��
		_RGB[4].R = 255;
		_RGB[4].G = 255;
		_RGB[4].B = 051;
		//��
		_RGB[3].R = 000;
		_RGB[3].G = 255;
		_RGB[3].B = 000;
		//��
		_RGB[2].R = 000;
		_RGB[2].G = 051;
		_RGB[2].B = 255;
		//��
		_RGB[1].R = 000;
		_RGB[1].G = 051;
		_RGB[1].B = 051;
		//��
		_RGB[0].R = 153;
		_RGB[0].G = 051;
		_RGB[0].B = 204;
	}
	
public:
	HpColor();
	~HpColor();
};

