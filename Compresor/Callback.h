#ifndef CALLBACK_H
#define CALLBACK_H

#include <string>

#define CALLBACK_OK		1
#define CALLBACK_ERROR	0
#define THRES_MAX		1	//a modo de ejempo. verificar valores razonables

typedef struct
{
	std::string path;
	float threshold;
}CallbackData;

int Callback(char *key, char *value, void *userData);

#endif // !CALLBACK_H

