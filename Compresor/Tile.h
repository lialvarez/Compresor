#ifndef TILE_H
#define TILE_H

#define TILE_HEIGHT 152
#define TILE_WIDTH	252
#define TILE_THICK	5

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <string>

class Tile
{
public:

	Tile(std::string _fileName, ALLEGRO_FONT *tileFont);
	bool validTile();
	void toggleSelection();
	bool isSelected();
	std::string getFileName();
	void draw(unsigned int x0,unsigned int y0);

private:
	std::string fileName;
	bool selected;
	ALLEGRO_BITMAP *img;
	ALLEGRO_FONT *font;
};
#endif // !TILE_H