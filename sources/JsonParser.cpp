#include "JsonParser.hpp"
#include "Exceptions.hpp"
#include "Addons.hpp"

#include <fstream>

std::pair<std::map<std::string, std::any>,std::vector<std::any>> JsonParser::parser(std::string string)
  {
      if (is_file(string))
        {
          if (!std::filesystem::exists(string))
            {
                std::filesystem::directory_entry(std::filesystem::current_path.parent_path());
            }
          parseFile(string);
        }
      else
        {
          parse(string);
        }
        return std::make_pair(objects,arrays);
  }

void parse(std::string string)
  {

  }

void  parseFile(std::string filename)
  {
  }
