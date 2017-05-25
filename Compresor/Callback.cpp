#include <stdio.h>
#include <boost\filesystem.hpp>
#include <algorithm>
#include "Callback.h"

int Callback(char *key, char *value, void *userData)
{
	int ret = CALLBACK_ERROR;
	std::string sKey;
	std::string sValue;
	float threshold;
	CallbackData * data = (CallbackData *)userData;
	if (key == NULL)	//Path
	{
		sValue = std::string(value);
		boost::filesystem::path path(sValue);
		if (boost::filesystem::exists(path)) //Si el path ingresado es valido
		{
			if (boost::filesystem::is_directory(path))	//Si el path ingresado es un directorio
			{
				data->path = sValue;
				ret = CALLBACK_OK;
			}
		}
	}
	else	//Threshold
	{
		sKey = std::string(key);
		std::transform(sKey.begin(), sKey.end(), sKey.begin(), ::tolower);
		if (sKey.compare("threshold") == 0)
		{
			sValue = std::string(value);
			threshold = std::stof(sValue);
			if (threshold > 0 && threshold <= THRES_MAX)	//Si el path esta entre los valores permitidos
			{
				data->threshold = threshold;
				ret = CALLBACK_OK;
			}
		}
	}
	return ret;
}