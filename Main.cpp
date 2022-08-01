#include "Logger.h"
#include "BitmapImporter.h"
using namespace LoggerClass;

int main()
{
	BitmapImporter bitmap;
	bitmap.CreateImage(100, 150, 260, 20, 00);
	bitmap.WriteBitmap("bitmap1.bmp");


	BitmapImporter bit;
	bit.ReadBitmap("b.bmp");
	for (int i = 10; i < 100; i++)
	{
		for (int j = 10; j < 100; j++)
		{
			bit.SetPixel(j, i, 160, 180, 155);
		}
	}
	bit.WriteBitmap("b.bmp");

	/*
	bit.ReadBitmap("siz.bmp");
	int poseX=50, poseY=50;

	for (int i = 0; i < 100; i++)
	{
	for (int j = 0; j < 100; j++)
	{
	if (sqrt((i - 50) * (i - 50) + (j - 50) * (j - 50)) < 50)
	{
	bit.SetPixel(j + poseX, i + poseY, 220, 100, 78);
	}

	}
	}*/



	system("pause");
	return 0;
}
