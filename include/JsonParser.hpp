#pragma once

#include <set>
#include <map>
#include <vector>
#include <any>

//            Знаки - границы
const std::set <char> edge_chars {',',']','}',':'};

class JsonParser
  {
    struct json
      {
          bool is_object = false;
          std::map<std::string, std::any> objects;
          std::vector<std::any> arrays;
      };
    public:
     ~JsonParser() = default;
      static std::pair<std::map<std::string, std::any>,std::vector<std::any>> parser(std::string);
//      Фукнции для парсинга
      static void parse(std::string);      // Функция парсинга строки
      static void parseFile(std::string);  // Функция парсинга файла
  };
