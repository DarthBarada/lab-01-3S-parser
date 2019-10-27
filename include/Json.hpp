#pragma once

#include <iostream>
#include <fstream>

#include <string>

#include <set>
#include <map>
#include <vector>

#include <any>
#include <typeinfo>
#include <algorithm>


class Json
	{
	public:
		// Контейнеры для хранения объектов
		std::map<std::string, std::any> Objects; // Для хранения объектов
		std::vector<std::any> Arrays;			 			 // Для хранения массивов

		bool contains_object = false;
		bool contains_array = false;

		// Конструктор из строки, содержащей Json-данные.
		Json(const std::string& s);
		// Конструктор из Json-объекта, содержащей Json-данные.
		Json(Json& s);
		// Пустой конструктор
		Json() = default;

		~Json() = default;

		// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
		bool is_array() const;
		// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
		bool is_object() const;
		// Метод возвращает true, еслиесли данный экземпляр не содержит в себе JSON-объект и JSON-массив. Иначе false.
		bool is_empty() const;

		//
		void copy_json(const Json a)
			{
				contains_object = a.contains_object;
				contains_array = a.contains_array;
				Arrays = a.give_arrays();
				Objects = a.give_objects();
			}
		// Добавить в словарь ключ, значение
		void AddObject(const std::string &key, const std::any &value);

		// Добавить значение в массив
		void AddArray(const std::any &value);

		std::vector<std::any> give_arrays() const
			{
				return Arrays;
			}

		std::map<std::string, std::any> give_objects() const
			{
				return Objects;
			}

		// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
		// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
		// Если экземпляр является JSON-массивом, генерируется исключение.
		std::any& operator[](const std::string& key);

		// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
		// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
		// Если экземпляр является JSON-объектом, генерируется исключение.
		std::any& operator[](int index);

		// Метод возвращает объект класса Json из строки, содержащей Json-данные.
		static Json parse(const std::string& string)
			{
				return Json(string);
			}

		// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
		static Json parseFile(const std::string& path_to_file);

		void print();
	};
