#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>
#include <filesystem>
#include "utils/path-parser.h"
#include "utils/is_executable.h"

std::string &ltrim(std::string &s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                  { return !std::isspace(ch); }));
  return s;
}

std::string &rtrim(std::string &s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                       { return !std::isspace(ch); })
              .base(),
          s.end());
  return s;
}

std::string &trim(std::string &s)
{
  return ltrim(rtrim(s));
}

void handleEcho(std::string &command)
{
  std::string echoCommand = command.substr(4);
  trim(echoCommand);
  std::cout << echoCommand << std::endl;
}

void handleType(std::string &command)
{
  std::string typeCommand = command.substr(5);
  trim(typeCommand);

  if (typeCommand == "echo" || typeCommand == "exit" || typeCommand == "type")
  {
    std::cout << typeCommand << " is a shell builtin" << std::endl;
    return;
  }

  const char *paths = std::getenv("PATH");
  std::vector<std::string> pathDirs = pathParser(paths);

  for (const std::string &dir : pathDirs)
  {
    // NOTE: requires C++17
    if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir))
    {
      for (const auto &entry : std::filesystem::directory_iterator(dir))
      {
        if (entry.is_regular_file())
        {
          std::string filename = entry.path().filename().string();
          if (filename == typeCommand || entry.path().string() == typeCommand)
          {
            if (is_executable(entry.path()))
            {
              std::cout << filename << " is " << entry.path().string() << std::endl;
            }

            return;
          }
        }
      }
    }
  }

  std::cout << typeCommand << ": not found" << std::endl;
}

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  bool isLoopEnabled = true;

  while (isLoopEnabled)
  {
    std::cout << "$ ";

    std::string command;
    std::getline(std::cin, command);
    trim(command);

    if (command == "exit")
    {
      return 0;
    }

    if (command.rfind("echo ", 0) == 0)
    {
      handleEcho(command);
      continue;
    }

    if (command.rfind("type ", 0) == 0)
    {
      handleType(command);
      continue;
    }

    std::cout << command << ": command not found" << std::endl;
  }
}
