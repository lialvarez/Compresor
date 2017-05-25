#include "FileSystem.h"

std::vector<std::string> getExtensionFiles(std::string directory, std::string extension)
{
	std::string aux;
	std::vector<std::string> ret;
	boost::filesystem::path path(directory);
	if (boost::filesystem::exists(path))
	{
		for (boost::filesystem::directory_iterator itr(path); itr != boost::filesystem::directory_iterator(); ++itr)
		{
			if (itr->path().string().find('.' + extension) != std::string::npos)	//Si encuentra un archivo con la extension indicada
			{
				ret.push_back(itr->path().string());
			}
		}
	}
	return ret;
}
