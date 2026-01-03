#include "is_executable.h"

bool is_executable(const std::filesystem::__cxx11::path &path)
{
    // NOTE: on windows, you don't need to check for file being executable I think.
    // AI suggests using file extension but this could actually break it I think
    // as if file is executable but without ext, it won't be found. If all it takes
    // is extension in Windows, then no special check is necessary. Just string comparison
    // on file name.

#ifdef _WIN32
    // on windows there are no executable permissions to check so all files are executable... I think
    return true;
#else
    auto perms = std::filesystem::status(path).permissions();
    return (perms & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ||
           (perms & std::filesystem::perms::group_exec) != std::filesystem::perms::none ||
           (perms & std::filesystem::perms::others_exec) != std::filesystem::perms::none;
#endif
}