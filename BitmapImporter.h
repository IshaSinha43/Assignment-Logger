
#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <cmath>
#include "Logger.h"
using namespace std;

class BitmapImporter
{
public:
	struct BGR
	{
		BYTE B;
		BYTE G;
		BYTE R;
	};

#pragma pack(push,2)
	struct BITMAPFILEHEADER
	{
		WORD  bfType;
		DWORD bfSize;
		WORD  bfReserved1;
		WORD  bfReserved2;
		DWORD bfOffBits;
	};

	struct BITMAPINFOHEADER
	{
		DWORD biSize;
		LONG  biWidth;
		LONG  biHeight;
		WORD  biPlanes;
		WORD  biBitCount;
		DWORD biCompression;
		DWORD biSizeImage;
		LONG  biXPelsPerMeter;
		LONG  biYPelsPerMeter;
		DWORD biClrUsed;
		DWORD biClrImportant;
	};

#pragma pack(pop)
	bool CreateImage(int width, int height, BYTE R, BYTE G, BYTE B);
	bool ReadBitmap(const char* filePath);
	bool WriteBitmap(const char* filePath);
	BGR	 GetPixel(int x, int y);
	void SetPixel(int x, int y, BYTE B, BYTE G, BYTE R);
	void Release();


private:
	BITMAPFILEHEADER m_fileheader;
	BITMAPINFOHEADER m_infoheader;
	BGR** m_data = nullptr;
};
