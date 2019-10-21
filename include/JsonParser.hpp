#pragma once

#include "Json.hpp"

#include <set>
#include <map>
#include <vector>
#include <any>

//            Знаки - границы
const std::set <char> edge_chars {',',']','}',':'};

class JsonParser
  {

    public:
	  static Json* parser(const std::string&);
//      Фукнции для парсинга
      static Json* parse(std::string);      // Функция парсинга строки
      static Json* parseFile(std::string);  // Функция парсинга файла

	  static std::vector <std::string> array_parser(std::string&);
	  static std::vector <std::string> object_parser(std::string&);
	  static Json* vector_to_object(std::vector <std::string>&);
	  static void object_gatherer(std::vector <std::string>&, Json*);
	  static void array_gatherer(std::vector <std::string>&, Json *);
  };
