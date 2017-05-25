#ifndef TILE_H
#define TILE_H

#define TILE_HEIGHT 152
#define TILE_WIDTH	252
#define TILE_THICK	5

#include <allegro5\allegro.h>
#include <string>

class Tile
{
public:

	Tile(std::string _fileName);
	bool validTile();
	void toggleSelection();
	bool isSelected();
	std::string getFileName();
	void draw(unsigned int x0,unsigned int y0);

private:
	std::string fileName;
	bool selected;
	ALLEGRO_BITMAP *img;
};
#endif // !TILE_H