#pragma once
#include <filesystem>
#include <set>
#include <iostream>
#include <algorithm>

//            Поиск пути
namespace fs = std::filesystem;
const fs::path l_path(fs::current_path().parent_path()); // Указывает на папку, которая ниже

//            Ненужные знаки
const std::set <char> unused_chars {' ',','};
const std::set <char> unused_chars2{'\n','\t','\b','\v'};

// Функция сбрасывает пару строк
void reset(std::pair<std::string,std::string> pair) // Tested
  {
    pair.first.clear();pair.second.clear();
  }

// Функция проверяет существование файла
// Замечание: файл проверяется не в _build, а в папке, где хранится _build(source/_build/<filename>)
bool is_file(const std::string& filename) // Tested
	{
    /*std::cout<<"\n"<<fs::current_path()<<" "<<l_path<<"\n";*/
    if (!fs::exists(filename))  // Если в текущей папке нет файла, то переходим в папку ниже
      {                         // Сделано для _build
        return fs::exists(l_path.string()+'/'+ filename);
      }
		return fs::exists(filename);
	}

std::string second_step_of_cleaning(std::string& temp_string); // Tested

std::string first_step_of_cleaning(std::string& temp_string)   // Tested
  {
    if (temp_string.empty())
      return temp_string;

    auto temp_iterator = std::find_first_of(temp_string.begin(),temp_string.end(),unused_chars2.begin(),unused_chars2.end());
     while (temp_iterator != temp_string.end())
       {
         temp_string.erase(temp_iterator);
         temp_iterator =std::find_first_of(temp_string.begin(),temp_string.end(),unused_chars2.begin(),unused_chars2.end());
       }
    second_step_of_cleaning(temp_string);
    return temp_string;
  }

std::string second_step_of_cleaning(std::string& temp_string) // Tested
  {
    if (temp_string.empty())
      return temp_string;

    auto front_iterator = unused_chars.find(temp_string.front());
    auto back_iterator = unused_chars.find(temp_string.back());

     while (front_iterator != unused_chars.end())
       {
         temp_string.erase(temp_string.begin());
         front_iterator = unused_chars.find(temp_string.front());
       }
     while (back_iterator != unused_chars.end())
       {
         temp_string.pop_back();
         back_iterator = unused_chars.find(temp_string.back());
       }

    return temp_string;
  }

  std::string read_file(std::string path)
    {
        
    }
