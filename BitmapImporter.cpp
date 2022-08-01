#include "BitmapImporter.h"
#include"logger.h"
bool BitmapImporter::CreateImage(int width, int height, BYTE R, BYTE G, BYTE B)
{
	LoggerClass::LOG() << "BEGIN: " << "Create a Bitmap Image" << endl;
	const int fileheadersize = 14;
	LoggerClass::LOG() << "File Header Size: " << fileheadersize << endl;
	
	const int infoheadersize = 40;
	LoggerClass::LOG() << "Info Header Size: " << fileheadersize << endl;

	BYTE PadingData[] = { 0, 0, 0 };
	int Padding = (4 - (width * sizeof(BGR)) % 4) % 4;
	LoggerClass::LOG() << "RowSize: " << width * sizeof(BGR) + Padding << endl;
	int RowSize = width * sizeof(BGR) + Padding;
	LoggerClass::LOG() << "DataSize: " << RowSize * height + Padding << endl;
	int DataSize = RowSize * height;

	if (m_data) {
		Release();
	}

	m_fileheader.bfSize = DataSize + fileheadersize + infoheadersize;
	m_fileheader.bfOffBits = fileheadersize + infoheadersize;
	m_fileheader.bfType = 19778;
	m_fileheader.bfReserved1 = 0;
	m_fileheader.bfReserved2 = 0;

	m_infoheader.biBitCount = 24;
	m_infoheader.biClrImportant = 0;
	m_infoheader.biClrUsed = 0;
	m_infoheader.biCompression = BI_RGB;
	m_infoheader.biHeight = height;
	m_infoheader.biPlanes = 1;
	m_infoheader.biSize = 40;
	m_infoheader.biSizeImage = DataSize + fileheadersize + infoheadersize;
	m_infoheader.biWidth = width;
	m_infoheader.biYPelsPerMeter = 0;
	m_infoheader.biXPelsPerMeter = 0;

	m_data = new BGR * [height];
	for (int i = 0; i < height; i++)
	{
		m_data[i] = new BGR[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_data[i][j].B = B;
			m_data[i][j].G = G;
			m_data[i][j].R = R;
		}
	}
	return true;
}

bool BitmapImporter::ReadBitmap(const char* filePath)
{
	LoggerClass::LOG() << "BEGIN: " << "Start Loading Bitmap file for read: " << filePath << endl;
	ifstream f;
	f.open(filePath, ios::in | ios::binary);
	LoggerClass::LOG() << "file is open" << endl;
	if (!f.is_open())
	{
		LoggerClass::LOG() << "ERROR: " << "file could not open" << endl;
		return false;
	}

	const int fileheadersize = 14;
	const int infoheadersize = 40;

	f.read(reinterpret_cast<char*> (&m_fileheader), fileheadersize);
	f.read(reinterpret_cast<char*> (&m_infoheader), infoheadersize);

	LoggerClass::LOG() << "read file" << endl;
	LoggerClass::LOG() << "Width "<< m_infoheader.biBitCount << endl;
	LoggerClass::LOG() << "Width " << m_infoheader.biWidth << endl;
	LoggerClass::LOG() << "Width " << m_infoheader.biHeight << endl;

	int _Width = m_infoheader.biWidth;
	int _Height = m_infoheader.biHeight;

	BYTE PadingData[] = { 0, 0, 0 };
	int Padding = (4 - (_Width * sizeof(BGR)) % 4) % 4;
	int RowSize = _Width * sizeof(BGR) + Padding;
	int DataSize = RowSize * _Height;

	BYTE* tmpData = new BYTE[DataSize];
	m_data = new BGR * [_Height];
	f.seekg(m_fileheader.bfOffBits, ios::beg);
	LoggerClass::LOG() << "File read" << endl;
	f.read(reinterpret_cast<char*>(tmpData), DataSize);
	LoggerClass::LOG() << "File close" << endl;
	f.close();
	
	//2D array
	for (int i = 0; i < _Height; i++)
	{
		m_data[i] = new BGR[_Width];
	}
	//for counting pixel;
	int pixelctr = 0;

	for (int i = 0; i < _Height; i++)
	{
		for (int j = 0; j < _Width; j++)
		{
			m_data[i][j].B = tmpData[pixelctr + 0];
			m_data[i][j].G = tmpData[pixelctr + 1];
			m_data[i][j].R = tmpData[pixelctr + 2];
			pixelctr += 3;
		}
		pixelctr += Padding;
	}
	delete[] tmpData;
	return true;
}

bool BitmapImporter::WriteBitmap(const char* filePath)
{
	LoggerClass::LOG() << "BEGIN: " << "Start Loading Bitmap file for write: " << filePath << endl;
	ofstream of;
	LoggerClass::LOG() << "INFO: " << "File opened :" << filePath << endl;
	of.open(filePath, ios::out | ios::binary); 

	int _Width = m_infoheader.biWidth;
	int _Height = m_infoheader.biHeight;

	LoggerClass::LOG() << "_Width = " << m_infoheader.biWidth << endl;
	LoggerClass::LOG() << "_Height = " << m_infoheader.biHeight << endl;

	BYTE PadingData[] = { 0, 0, 0 };
	int Padding = (4 - (_Width * sizeof(BGR)) % 4) % 4;

	LoggerClass::LOG() << "RowSize is = " << _Width * sizeof(BGR) + Padding << endl;
	int RowSize = _Width * sizeof(BGR) + Padding;

	LoggerClass::LOG() << "DataSize is = " << RowSize * _Height << endl;
	int DataSize = RowSize * _Height;

	
	LoggerClass::LOG() << "File is opened: " << endl;
	of.open(filePath, ios::out | ios::binary);
	const int fileheadersize = 14;
	const int infoheadersize = 40;
	LoggerClass::LOG() << "Start Write into the file  "<< endl;
	of.write(reinterpret_cast<char*>(&m_fileheader), fileheadersize);

	of.write(reinterpret_cast<char*>(&m_infoheader), infoheadersize);

	for (int i = 0; i < _Height; i++)
	{
		for (int j = 0; j < _Width; j++)
		{
			of.write(reinterpret_cast<char*>(&m_data[i][j]), sizeof(BGR));
		}
		of.write(reinterpret_cast<char*>(PadingData), Padding);
	}
	LoggerClass::LOG() << "File is Closed :" << filePath << endl;
	of.close();
	return false;
}

BitmapImporter::BGR BitmapImporter::GetPixel(int x, int y)
{
	return  m_data[y][x];
}

void BitmapImporter::SetPixel(int x, int y, BYTE R, BYTE G, BYTE B)
{
	m_data[y][x].B = B;
	m_data[y][x].G = G;
	m_data[y][x].R = R;

}
void BitmapImporter::Release()
{
	int height = m_infoheader.biHeight;
	for (int i = 0; i < height; i++)
	{
		delete[] m_data[i];
	}
	delete[] m_data;

}
