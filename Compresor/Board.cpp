#include "Board.h"

Board::Board() : currentPage(1), pageNum(0) 
{
	tileFont = al_load_ttf_font(FONT_PATH, FONT_SIZE, 0);
}

Board::~Board()
{
	tiles.clear();
}

void Board::addTile(std::string fileName)
{
	Tile * newTile = new Tile(fileName, tileFont);
	if (newTile->validTile())
	{
		tiles.push_back(*newTile);
	}
	pageNum = 1 + tiles.size() / 9;
}

void Board::nextPage()
{
	if (currentPage < pageNum)
	{
		currentPage++;
	}
	else if (currentPage == pageNum)
	{
		currentPage = 1;
	}
}

void Board::previousPage()
{
	if (currentPage > 1)
	{
		currentPage--;
	}
	else if (currentPage == 1)
	{
		currentPage = pageNum;
	}
}

void Board::draw()
{
	unsigned int x0, y0;
	for (unsigned int i = 0; i < 9; i++)
	{
		y0 = (i / 3 + 1) * VERT_MARGIN + (i/3)*TILE_HEIGHT;
		x0 = (i - 3 * (i / 3) + 1)*HORIZ_MARGIN + (i - 3 * (i / 3))*TILE_WIDTH;
		if (tiles.size() > (currentPage - 1) * 9 + i)
		{
			tiles[(currentPage - 1) * 9 + i].draw(x0, y0);
			//Hay que agregarle el nombre del tile
		}
	}
}

void Board::selectItem(unsigned int tileNum)
{
	if (tiles.size() > (currentPage - 1) * 9 + tileNum - 1)
	{
		tiles[(currentPage - 1) * 9 + tileNum - 1].toggleSelection();
	}
}

void Board::selectAll()
{
	for (unsigned int i = 0; i < 9; i++)
	{
		if (tiles.size() > (currentPage - 1) * 9 + i)
		{
			if (!tiles[(currentPage - 1) * 9 + i].isSelected())
			{
				tiles[(currentPage - 1) * 9 + i].toggleSelection();
			}
		}
	}
}

void Board::unSelectAll()
{
	for (unsigned int i = 0; i < 9; i++)
	{
		if (tiles.size() >(currentPage - 1) * 9 + i)
		{
			if (tiles[(currentPage - 1) * 9 + i].isSelected())
			{
				tiles[(currentPage - 1) * 9 + i].toggleSelection();
			}
		}
	}
}

std::vector<std::string> Board::selectedTilesFiles()
{
	std::vector<std::string> ret;
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].isSelected())
		{
			ret.push_back(tiles[i].getFileName());
		}
	}
	return ret;
}