#include "Exceptions.hpp"
#include "Json.hpp"
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
		copy_json(*JsonParser::parser(string));
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
