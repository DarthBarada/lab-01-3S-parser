#include "JsonParser.hpp"
#include "Exceptions.hpp"
#include "Addons.hpp"

std::pair<std::map<std::string, std::any>,std::vector<std::any>> JsonParser::parser(std::string string)
  {
      if (is_file(string))
        {
          std::filesystem::directory_entry(std::filesystem::current_path().parent_path());
          return parseFile(string);
        }
      else
        {
          return parse(string);
        }
  }

std::pair<std::map<std::string, std::any>,std::vector<std::any>>  parse(std::string string )
  {
    std::pair<std::map<std::string, std::any>,std::vector<std::any>> temp;
    std::cout<<"\n"<<std::filesystem::current_path()<<"\n";
    return temp;
  }

std::pair<std::map<std::string, std::any>,std::vector<std::any>>  parseFile(std::string filename)
  {
    std::pair<std::map<std::string, std::any>,std::vector<std::any>> temp;
    std::cout<<"\n"<<std::filesystem::current_path()<<"\n";
    return temp;
  }
