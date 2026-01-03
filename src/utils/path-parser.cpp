#include "path-parser.h"
#include <sstream>

#ifdef _WIN32
const char PATH_DELIMITER = ';';
#else
const char PATH_DELIMITER = ':';
#endif

std::vector<std::string> pathParser(const char *paths)
{
    std::vector<std::string> pathDirs;

    if (paths == nullptr)
    {
        return pathDirs;
    }

    std::stringstream ss(paths);
    std::string dir;
    while (std::getline(ss, dir, PATH_DELIMITER))
    {
        if (!dir.empty())
        {

            pathDirs.push_back(dir);
        }
    }

    return pathDirs;
}
