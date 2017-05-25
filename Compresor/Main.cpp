extern "C"
{
#include "parseCmdLine.h"
}
#include <list>
#include <stdio.h>
#include "Callback.h"
#include <iostream>
#include "Board.h"
#include "FileSystem.h"
#include "Dispatcher.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>

#define PARSER_OK		2
#define PARSER_ERROR	-1

int main(int argc, char *argv[])
{
	CallbackData userData;
	int parsedArgs = parseCmdLine(argc, argv, Callback, &userData);
	if (parsedArgs == PARSER_ERROR)
	{
		std::cout << "Error de forma. Verifique los argumentos ingresados" << std::endl;
		std::cout << "Presione una tecla para salir..." << std::endl;
		getchar();
		return 0;
	}
	else if (parsedArgs != PARSER_OK)
	{
		std::cout << "Argumentos invalidos. Verifique los argumentos ingresados" << std::endl;
		std::cout << "Presione una tecla para salir..." << std::endl;
		getchar();
		return 0;
	}

	Board tileBoard;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *evQueue = NULL;

	if (!al_init()) {
		fprintf(stderr, "Error al inicializar Allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "Error al incializar teclado!\n");
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "Error al incializar Primitives Addon!\n");
		return -1;
	}

	if (!al_init_image_addon())
	{
		fprintf(stderr, "Error al incializar Image Addon!\n");
		return -1;
	}

	display = al_create_display(1000, 600);
	if (!display) {
		fprintf(stderr, "Error al crear display!\n");
		return -1;
	}

	evQueue = al_create_event_queue();
	if (!evQueue) {
		fprintf(stderr, "Error al crear la cola de eventos!\n");
		al_destroy_display(display);
		return -1;
	}
	std::vector<std::string> dirExtContent = getExtensionFiles(userData.path, "png");
	for (unsigned int i = 0; i < dirExtContent.size(); i++)
	{

		tileBoard.addTile(dirExtContent[i]);
	}
	std::vector<std::string> selectedImgs;
	ALLEGRO_EVENT ev;

	al_register_event_source(evQueue, al_get_display_event_source(display));
	al_register_event_source(evQueue, al_get_keyboard_event_source());

	do
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));
		tileBoard.draw();
		al_flip_display();

		al_wait_for_event(evQueue, &ev);

		dispatcher(&ev, tileBoard);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			al_destroy_event_queue(evQueue);
			al_destroy_display(display);
		}
	} while (ev.keyboard.keycode != ALLEGRO_KEY_ENTER);
	//Si llego aca es pq aprete enter
	selectedImgs = tileBoard.selectedTilesFiles();	//Todos los nombres de los archivos seleccionados
}