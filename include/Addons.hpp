#pragma once
#include "Exceptions.hpp"

#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>

void log_exit(const std::string& input)
  {
    std::ofstream fout;
    fout.open("log.txt",std::ios::app);
    fout<<input;
    fout.close();
  }

//            Ненужные знаки
static const std::set <char> unused_chars {' ',',',':'};
static const std::set <char> unused_chars2{'\n','\t','\b','\v'};

// Функция сбрасывает пару строк
void reset(std::pair<std::string,std::string>& pair) // Tested
  {
    pair.first.clear();pair.second.clear();
  }

// Функция проверяет существование файла
bool is_file(const std::string& filename) // Tested
	{
    std::ifstream file(filename);
    if (!file.is_open())
      {
        return false;
      }
      file.close();
    return true;
	}

std::string second_step_of_cleaning(std::string& temp_string); // Tested

std::string& first_step_of_cleaning(std::string& temp_string)   // Tested
  {
    //std::string temp;
    if (temp_string.empty())
      {
        return temp_string;
      }
    auto temp_iterator = std::find_first_of(temp_string.begin(),temp_string.end(),unused_chars2.begin(),unused_chars2.end());
     while (temp_iterator != temp_string.end())
       {
         temp_string.erase(std::prev(temp_iterator),std::next(temp_iterator));
         temp_iterator =std::find_first_of(temp_string.begin(),temp_string.end(),unused_chars2.begin(),unused_chars2.end());
       }
    //log_exit(temp_string);
    //second_step_of_cleaning(temp_string);
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

void clear_quotes(std::string & string)
	{
		if (string.front() == '\"' || string.front() == '\'')
			{
				string.erase(string.begin());
			}
		if (string.back() == '\"' || string.back() == '\'')
			{
				string.pop_back();
			}
	}

bool is_json(const std::string& string)
{
  if ((string.front() == '{' && string.back() == '}') || (string.front() == '[' && string.back() == ']'))
    {
      return true;
    }
    return false;
}

int is_json_object(const std::string& string) // 0 - не объект, 1 - объект, 2 - массив
	{
		if (string.front() == '{' && string.back() == '}')
			{
				return 1;
			}
		else if (string.front() == '[' && string.back() == ']')
			{
				return 2;
			}
		else
			{
				throw WrongJson("You have errors in your .json file");
			}
		return 0;
	}
