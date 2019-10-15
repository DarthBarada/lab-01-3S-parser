#pragma once

#include <set>
#include <map>
#include <vector>
#include <any>

//            Ненужные знаки
const std::set <char> unused_chars {' ',','};

//            Знаки - границы
const std::set <char> edge_chars {',',']','}',':'};

class JsonParser
  {
    public:
     ~JsonParser() = default;
      static std::pair<std::map<std::string, std::any>,std::vector<std::any>> parser(std::string);
//      Фукнции для парсинга
      static std::pair<std::map<std::string, std::any>,std::vector<std::any>>  parse(std::string);      // Функция парсинга строки
      static std::pair<std::map<std::string, std::any>,std::vector<std::any>> parseFile(std::string);  // Функция парсинга файла
  };
