#include "Tile.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\bitmap.h>
#include <allegro5\allegro_primitives.h>

Tile::Tile(std::string _fileName, ALLEGRO_FONT *tileFont): selected(false), img(NULL), fileName(_fileName), font(tileFont)
{
	img = al_load_bitmap(fileName.c_str());
}

bool Tile::validTile()
{
	if (img != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Tile::toggleSelection()
{
	if (selected)
	{
		selected = false;
	}
	else
	{
		selected = true;
	}
}

bool Tile::isSelected()
{
	return selected;
}

std::string Tile::getFileName()
{
	return fileName;
}

void Tile::draw(unsigned int x0, unsigned int y0)
{
	std::string aux = fileName.substr(fileName.find_last_of("\\") + 1);
	al_draw_scaled_bitmap(img, 0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img), x0, y0, TILE_WIDTH, TILE_HEIGHT, 0);
	al_draw_rectangle(x0, y0, x0 + TILE_WIDTH, y0 + TILE_HEIGHT, al_map_rgb(0, 0, 0), 1);
	al_draw_text(font, al_map_rgb(0, 0, 0), x0 + TILE_WIDTH / 2, y0 + TILE_HEIGHT, ALLEGRO_ALIGN_CENTRE, aux.c_str());
	if (selected)
	{
		al_draw_rectangle(x0, y0, x0 + TILE_WIDTH, y0 + TILE_HEIGHT, al_map_rgb(255, 0, 0), 5);
	}
}