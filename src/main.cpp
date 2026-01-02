#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

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
      std::string echoCommand = command.substr(4);
      trim(echoCommand);
      std::cout << echoCommand << std::endl;
      continue;
    }

    std::cout << command << ": command not found" << std::endl;
  }
}
