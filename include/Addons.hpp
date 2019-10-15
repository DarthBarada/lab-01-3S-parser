#pragma once
#include <filesystem>
#include <set>
#include <iostream>

namespace fs = std::filesystem;
const fs::path l_path(fs::current_path().parent_path()); // Указывает на папку, которая ниже

const std::set <char> unused_chars2{'\n','\t'};

void reset(std::pair<std::string,std::string> pair)
  {
    pair.first.clear();pair.second.clear();
  }

// Функция проверяет существование файла
// Замечание: файл проверяется не в _build, а в папке, где хранится _build(source/_build/<filename>)
bool is_file(const std::string& filename)
	{
    /*std::cout<<"\n"<<fs::current_path()<<" "<<main_path<<"\n";*/
		return fs::exists(l_path.string()+'/'+ filename);
	}
