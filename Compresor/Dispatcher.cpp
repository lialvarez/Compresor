#include "Dispatcher.h"

void dispatcher(ALLEGRO_EVENT *ev, Board& tileBoard)
{
	if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev->keyboard.keycode)
		{
		case ALLEGRO_KEY_1:
			tileBoard.selectItem(1);
			break;
		case ALLEGRO_KEY_2:
			tileBoard.selectItem(2);
			break;
		case ALLEGRO_KEY_3:
			tileBoard.selectItem(3);
			break;
		case ALLEGRO_KEY_4:
			tileBoard.selectItem(4);
			break;
		case ALLEGRO_KEY_5:
			tileBoard.selectItem(5);
			break;
		case ALLEGRO_KEY_6:
			tileBoard.selectItem(6);
			break;
		case ALLEGRO_KEY_7:
			tileBoard.selectItem(7);
			break;
		case ALLEGRO_KEY_8:
			tileBoard.selectItem(8);
			break;
		case ALLEGRO_KEY_9:
			tileBoard.selectItem(9);
			break;
		case ALLEGRO_KEY_LEFT:
			tileBoard.previousPage();
			break;
		case ALLEGRO_KEY_RIGHT:
			tileBoard.nextPage();
			break;
		case ALLEGRO_KEY_A:
			tileBoard.selectAll();
			break;
		case ALLEGRO_KEY_N:
			tileBoard.unSelectAll();
			break;
		default:
			break;
		}
	}
}

