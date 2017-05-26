#include "QuadTree.h"
#include <math.h>
#include <boost/algorithm/string/replace.hpp>

typedef enum{R,G,B,A}pixel;
#define PIXEL_SIZE	4
#define ALPHA		0xFF
#define PESO_MAX	765.0

void QuadTree::QTCompress(std::string fileName, float threshold)
{
	if (threshold < 0 || threshold > 1)
	{
		return;
	}
	this->threshold = threshold*PESO_MAX;
	rawData.clear();
	error = lodepng::decode(rawData, width, height, fileName.c_str());
	if (error)
	{
		return;
	}
	if (width != height)
	{
		return;
	}
	side = height;
	unsigned char pot = log2(side);
	if (side % 2 != 0)	//si el lado de la imagen no es potencia de 2
	{
		return;
	}
	//verificar que side sea potencia de 2
	boost::replace_all(fileName, ".png", ".eda");
	compressedFile.open(fileName, std::ios_base::binary);
	if (compressedFile.fail())
	{
		return;
	}
	compressedFile.put(pot);	//potencia del lado de la imagen comprimida
	quadTree(0, 0, side);
	compressedFile.close();
	rawData.clear();
}

void QuadTree::quadTree(unsigned int x0, unsigned int y0, unsigned int side)
{
	unsigned int peso;
	double Rmed = 0.0, Gmed = 0.0, Bmed = 0.0;
	int maxR = 0, minr = 255, maxG = 0, ming = 255, maxB = 0, minb = 255;
	for (unsigned int i = 0; i < side; i++)
	{
		for (unsigned int j = 0; j < side; j++)
		{
			maxR = rawData[(i*side + j) * PIXEL_SIZE + R] > maxR ? rawData[(i*side + j) * PIXEL_SIZE + R] : maxR;
			maxG = rawData[(i*side + j) * PIXEL_SIZE + G] > maxG ? rawData[(i*side + j) * PIXEL_SIZE + G] : maxG;
			maxB = rawData[(i*side + j) * PIXEL_SIZE + B] > maxB ? rawData[(i*side + j) * PIXEL_SIZE + B] : maxB;

			minr = rawData[(i*side + j) * PIXEL_SIZE + R] < minr ? rawData[(i*side + j) * PIXEL_SIZE + R] : minr;
			ming = rawData[(i*side + j) * PIXEL_SIZE + G] < ming ? rawData[(i*side + j) * PIXEL_SIZE + G] : ming;
			minb = rawData[(i*side + j) * PIXEL_SIZE + B] < minb ? rawData[(i*side + j) * PIXEL_SIZE + B] : minb;

			Rmed += rawData[(i*side + j) * PIXEL_SIZE + R];
			Gmed += rawData[(i*side + j) * PIXEL_SIZE + G];
			Bmed += rawData[(i*side + j) * PIXEL_SIZE + B];
		}
	}
	Rmed /= side*side;
	Gmed /= side*side;
	Bmed /= side*side;
	peso = maxR - minr + maxG - ming + maxB - minb;
	if (peso > threshold && side > 1)
	{
		compressedFile.put('1');
		quadTree(x0, y0, side / 2);
		quadTree(side / 2, 0, side / 2);
		quadTree(x0, side / 2, side / 2);
		quadTree(side / 2, side / 2, side / 2);
	}
	else
	{
		compressedFile.put('0');
		compressedFile.put((char)Rmed);
		compressedFile.put((char)Gmed);
		compressedFile.put((char)Bmed);
		compressedFile.put(ALPHA);
		return;
	}
}
