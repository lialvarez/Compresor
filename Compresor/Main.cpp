/////////////////////////////////////////////////////////////////////////////////////////////	
//
// Instituto Tecnologico de Buenos Aires						29/05/2017
//
// Algoritmos y Estructuras de Datos - Trabajo Práctico 8
//
//
// Alvarez, Lisandro						 ////////////////////////////////////////////////
// Bualo, Santiago							//	  Compresor de imágenes - Metodo Quad Tree
// Navarro, Paulo						   //////////////////////////////////////////////////
//
// Compresor:
//
// El programa recibe por linea de comando un path como parametro y un threshold como 
// una opcion con valores en el rango (0 ; 1]. El usuario, a traves de un Board en el
// cual se listaran los archivos ".png" cotenidos en el directorio ingresado, sleccionara
// las imagenes que desea comprimir. Las imagenes comprimidas se amacenaran en un archivo
// del mismo nombre al inicial pero de extension ".eda". Al finalizar la compresion el
// programa se cerrara automaticamente.
/////////////////////////////////////////////////////////////////////////////////////////////


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
#include "QuadTree.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>


#define PARSER_OK		2
#define PARSER_ERROR	-1
#define EXTENSION		"png"

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

	if (!al_init_font_addon()) {
		fprintf(stderr, "Error al incializar Font Addon!\n");
		return -1;
	}

	if (!al_init_ttf_addon()) {
		fprintf(stderr, "Error al incializar TTF Addon!\n");
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

	std::vector<std::string> dirExtContent = getExtensionFiles(userData.path, EXTENSION);
	Board tileBoard;

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
			return 0;
		}
	} while (ev.keyboard.keycode != ALLEGRO_KEY_ENTER);
	//Si llego aca es pq aprete enter
	selectedImgs = tileBoard.selectedTilesFiles();	//Todos los nombres de los archivos seleccionados
	QuadTree compress;
	ALLEGRO_FONT *font, *font2;
	ALLEGRO_BITMAP *icon = NULL;
	font = al_load_ttf_font(FONT_PATH, 50, 0);
	font2 = al_load_ttf_font(FONT_PATH, 20, 0);
	for (unsigned int i = 0; i < selectedImgs.size(); i++)
	{
		icon = al_load_bitmap(selectedImgs[i].c_str());
		std::string aux = selectedImgs[i].substr(selectedImgs[i].find_last_of("\\") + 1);
		aux = "Comprimiendo archivo " + std::to_string(i + 1) + " de " + std::to_string(selectedImgs.size());
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_text(font, al_map_rgb(0, 0, 0), 500, 50, ALLEGRO_ALIGN_CENTRE, aux.c_str());
		al_draw_scaled_bitmap(icon, 0, 0, al_get_bitmap_width(icon), al_get_bitmap_height(icon), 350, 200, 300, 200, 0);
		al_draw_rectangle(350, 400, 650, 200, al_map_rgb(0, 0, 0), 1);
		aux = selectedImgs[i].substr(selectedImgs[i].find_last_of("\\") + 1);
		al_draw_text(font2, al_map_rgb(0, 0, 0), 500, 400, ALLEGRO_ALIGN_CENTRE, aux.c_str());
		al_flip_display();
		compress.QTCompress(selectedImgs[i], userData.threshold);
	}
}

