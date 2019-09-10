#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_TYPE_DEFAULT,
	RES_TYPE_BLOCK_00,//����
	RES_TYPE_BLOCK_01,//������
	RES_TYPE_BLOCK_02,//�޺���
	RES_TYPE_BLOCK_03,//�Ʒ�����
	RES_TYPE_BLOCK_04,//��������
	RES_TYPE_BLOCK_05,//ö��
	RES_TYPE_BLOCK_06,//��
	RES_TYPE_BLOCK_07,//��
	RES_TYPE_BLOCK_08,//��ü��ö����
	RES_TYPE_BLOCK_09,//����ö
	RES_TYPE_BLOCK_10,//�ް�ö
	RES_TYPE_BLOCK_11,//�Ʒ���ö
	RES_TYPE_BLOCK_12,//������ö
	RES_TYPE_BLOCK_13,//������
	RES_TYPE_BLOCK_14,//����������
	RES_TYPE_END
};

class BitMap;
class ResourceManager
{
private:
	static ResourceManager* m_sThis;
	BitMap* m_pBitMap[RES_TYPE_END];
	vector<string> resPath;
public:
	static ResourceManager* GetInstance();
	BitMap* GetBitMap(int index);
	SIZE GetBitMapSize(int index);
private:
	void InitResPath();
	void InitBitMap(HDC hdc);
public:
	void Init(HDC hdc);
	void Release();
private:
	ResourceManager();
public:
	~ResourceManager();
};

