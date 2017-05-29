#ifndef QUADTREE_H
#define QUADTREE_H

#include <fstream>
#include <lodepng.h>

class QuadTree
{
public:
	void QTCompress(std::string fileName, float threshold);

private:
	std::ofstream compressedFile;
	std::vector<unsigned char> rawData;
	unsigned int error, width, height, totSide;
	float  threshold;
	void quadTree(unsigned int x0, unsigned int y0, unsigned int side);

};
#endif // !QUADTREE_H

