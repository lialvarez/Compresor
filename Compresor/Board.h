#ifndef BOARD_H
#define BOARD_H

#define HORIZ_MARGIN	61
#define VERT_MARGIN		36

#include <string>
#include <vector>
#include "Tile.h"

class Board
{
private:
	std::vector<Tile> tiles;
	unsigned int currentPage;
	unsigned int pageNum;

public:
	Board();
	~Board();
	void addTile(std::string fileName);
	void nextPage();
	void previousPage();
	void draw();	//llama a los draw de cada Tile.
	void selectItem(unsigned int tileNum);
	void selectAll();
	void unSelectAll();
	std::vector<std::string> selectedTilesFiles();
};

#endif // !BOARD_H
