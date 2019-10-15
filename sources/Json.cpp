#include  "Json.hpp"
#include "JsonParser.hpp"

bool Json::is_empty() const
	{
		return Objects.empty() && Arrays.empty();
	}

bool Json::is_array() const
	{
		return contains_array;
	}
bool Json::is_object() const
	{
		return contains_object;
	}

Json::Json(const std::string& string)
	{
		std::pair<std::map<std::string, std::any>,std::vector<std::any>> temp;
		temp = std::pair<std::map<std::string, std::any>,std::vector<std::any>>(JsonParser::parser(string));
	}

Json::Json(Json& s)
	{
		Arrays = s.give_arrays();
		Objects = s.give_objects();
		contains_array = s.contains_array;
		contains_object = s.contains_object;
	}

std::any& Json::operator[](const std::string& key)
	{
		if (Objects.empty())
			{
				throw JsonNoContainer("Objects don't exists!");
			}
		if (Objects.find(key) == Objects.end())
			{
				throw JsonWrongKey("No objects with this key!");
			}
		return Objects[key];
	}

std::any& Json::operator[](int index)
	{
		if (Arrays.empty())
			{
				throw JsonNoContainer("Arrays don't exists!");
			}
		if (int(Arrays.size()) <= index)
			{
				throw JsonWrongKey("No arrays with this key!");
			}
		return Arrays[index];
	}
/*std::pair <std::vector<std::string>::iterator, std::vector<std::string>::iterator> find_for_gatherer_borders(std::vector <std::string>& s, size_t index)
	{
		std::string my_char = s.at(index);
		std::string  reverse_char;

		if (my_char == "{" - '\0')
			{
				reverse_char = "}"-'\0';
			}
		else if (my_char == "[" - '\0')
			{
				reverse_char = "]" - '\0';
			}
		else
			{
				throw JsonWarning("Что-то пошло не так!");
			}

		auto temp = s.begin() + index;
		auto last = std::find(std::begin(s)+index, std::end(s), reverse_char);

		// Смысл этого цикла: мы находим новую дальнюю границу ('}' или ']'), пока находим внутри новую нижнюю границу ('{' или '[')
		while (std::find(temp, std::end(s), my_char) < std::find(temp + 1, std::end(s), my_char) && std::find(temp + 1, std::end(s), my_char) < std::find(last, std::end(s), reverse_char))
			{
				temp = std::find(temp + 1, std::end(s), my_char);			// <- Это мы находим сколько вложенных
				last = std::find(last+1, std::end(s), reverse_char);		// <- Это мы находим следущую закрывающую скобку
			}
		return std::make_pair(s.begin() + index,last+1);
	}*/

 /*Json Json::parse(const std::string& s)
	{

	}

 Json Json::parseFile(const std::string& path_to_file)
	{

	}*/

void Json::AddObject(const std::string &key, const std::any &value)
	{
	 	Objects.insert(std::pair<std::string, std::any>(key, value));
	}

void Json::AddArray(const std::any &value)
	{
		Arrays.push_back(value);
	}

std::string any_to_normal(std::any s)
	{
		if (s.type() == typeid(std::nullptr_t))
			{
				return "null";
			}
		if (s.type() == typeid(double))
			{
				return std::to_string(std::any_cast<double>(s));
			}
		if (s.type() == typeid(bool))
			{
				if (std::any_cast<bool>(s) == true)
					return "true";
				else
					return "false";
			}
		if (s.type() == typeid(std::string))
			{
				return std::any_cast<std::string>(s);
			}
		else
			{
				throw JsonWarning("Unexpected type!");
			}
	}

void Json::print()
	{
		setlocale(LC_ALL, "ru-RU");
		if (is_object())
			{
				std::cout << "{\n";
				for (auto i = Objects.begin(); i != Objects.end(); i++)
					{
						std::cout << i->first << " : ";
						if (i->second.type() == typeid(Json *))
							{
								std::any_cast<Json *>(i->second)->print();
							}
						else
							{
								std::cout << any_to_normal(i->second) << std::endl;
							}
					}
				std::cout << "}\n";
			}
		else   // Если не объект, то массив
			{
				std::cout << "  [\n";
				for (auto i = Arrays.begin(); i != Arrays.end(); i++)
					{
						if (i->type() == typeid(Json *))
							{
								(std::any_cast<Json *>(*i))->print();
							}
						else
							{
								std::cout << any_to_normal(*i) << std::endl;
							}
					}
				std::cout << "  ]\n";
			}
	}
