#include "JsonParser.hpp"
#include "Exceptions.hpp"
#include "Addons.hpp"

#include <iterator>

Json* JsonParser::parse(std::string input) // Tested
  {
		std::vector <std::string> big_string_vector;

    first_step_of_cleaning(input);
		///
		///---------------- � ���� ����� �� ������ json ������ � ������ ----------------
		///

		if (is_json_object(input) == 1)
			{
				big_string_vector = object_parser(input);
			}
		else
			{
				big_string_vector = array_parser(input);
			}
      
    second_step_of_cleaning(input);

		///
		///------------------------------- ����� ����� -------------------------------
		///

		return vector_to_object(big_string_vector);
  }


Json* JsonParser::vector_to_object(std::vector <std::string>& input) // Tested
	{
		Json *json = new Json;

		if (input.empty())
			{
				throw JsonWarning("Something going worng! Please, check your json string!");
			}
		if (input.front().compare("{") == 0)
			{
				JsonParser::object_gatherer(input, json);
			}
		if (!input.empty() && input.front().compare("[") == 0)
			{
				JsonParser::array_gatherer(input, json);
			}
		return json;
	}

std::pair <size_t, size_t> find_segment_borders(std::string input, size_t index) // Tested
	{
		char my_char = input.at(index);
		char reverse_char;

		if (my_char == '{')
			{
				reverse_char = '}';
			}
		else if (my_char == '[')
			{
				reverse_char = ']';
			}

		size_t temp = index;
		size_t last = input.find_first_of(reverse_char, index);

		// ����� ����� �����: �� ������� ����� ������� ������� ('}' ��� ']'), ���� ������� ������ ����� ������ ������� ('{' ��� '[')
		// C ++ ����� ����������� ������������� temp, ������� ����� ������������ + 1
		while ((input.find_first_of(my_char, temp) < input.find_first_of(my_char, temp + 1)) && (input.find_first_of(my_char,temp + 1) < input.find_first_of(reverse_char, last)))
			{
				temp = input.find_first_of(my_char, temp + 1);			// <- ��� �� ������� ������� ���������
				last = input.find_first_of(reverse_char, last + 1);		// <- ��� �� ������� �������� ����������� ������
			}
		return std::make_pair(index,++last);
	}

///			��������������� ������� ��� �������� ��������
void objfound_quote(std::string& input, std::vector <std::string>& plurality, std::pair <std::string, std::string>& key_value, size_t index) // Tested
	{
		if (key_value.second.empty() && !key_value.first.empty())
			{
				key_value.second = input.substr(index, std::find_first_of(input.begin() + index, input.end(), edge_chars.begin(), edge_chars.end()) - input.begin());

				second_step_of_cleaning(key_value.first);
				second_step_of_cleaning(key_value.second);
				clear_quotes(key_value.first);
				clear_quotes(key_value.second);

				plurality.insert(plurality.end(), key_value.first);
				plurality.insert(plurality.end(), ":");
				plurality.insert(plurality.end(), key_value.second);

				input.erase(input.begin(), std::find_first_of(input.begin() + index, input.end(), edge_chars.begin(), edge_chars.end()));
				reset(key_value);
			}
		else if (key_value.first.empty())
			{
				key_value.first = input.substr(index, std::find_first_of(input.begin() + index, input.end(), edge_chars.begin(), edge_chars.end()) - input.begin()); // �������� ���� � �������
				second_step_of_cleaning(key_value.first);																												 // ������ ������ � ����� �����
				clear_quotes(key_value.first);																															 // ������ ���� �� �������
				input.erase(index, std::find_first_of(input.begin() + index, input.end(), edge_chars.begin(), edge_chars.end()) - input.begin());					 // ������� ��� �����, ��������� ������
			}
	}

void objfound_comma(std::string& input, std::vector <std::string>& plurality, std::pair <std::string, std::string>& key_value, size_t index) // Tested
	{
		if (key_value.first.empty())
			{
				throw JsonWarning("Something wrong in json string!");
			}
		if (key_value.second.empty() && !key_value.first.empty())
			{
				key_value.second = input.substr(0, index);

				second_step_of_cleaning(key_value.first);
				second_step_of_cleaning(key_value.second);
				clear_quotes(key_value.first);
				clear_quotes(key_value.second);

				plurality.insert(plurality.end(), key_value.first);
				plurality.insert(plurality.end(), ":");
				plurality.insert(plurality.end(), key_value.second);

				reset(key_value);

				input.erase(input.begin(), std::next(std::find_first_of(input.begin() + index, input.end(), edge_chars.begin(), edge_chars.end())));
			}
	}

void objfound_begin_of_anobj(std::string& input, std::vector <std::string>& plurality, std::pair <std::string, std::string>& key_value, size_t index) // Tested
	{
		std::vector<std::string> nested;
		std::pair <size_t, size_t> borders = find_segment_borders(input, index);;
		std::string sub_string = input.substr(borders.first, borders.second - borders.first);
		input.erase(borders.first, borders.second - borders.first);
		second_step_of_cleaning(input);

		if (sub_string.front() == '{')
			{
				nested = JsonParser::object_parser(sub_string);
			}
		else if (sub_string.front() == '[')
			{
				nested = JsonParser::array_parser(sub_string);
			}

		plurality.insert(plurality.end(), key_value.first);
		plurality.insert(plurality.end(), ":");

		for (auto position = nested.begin(); position != nested.end(); ++position)
			{
				plurality.insert(plurality.end(), *position);
			}

		reset(key_value);
		nested.clear();
		sub_string.clear();
	}

///							-----------
std::vector <std::string> JsonParser::object_parser(std::string& input) // Tested
	{
		std::vector <std::string> string_objects;
		std::pair <std::string, std::string> keyval;

		const size_t start_point = -1;

		input.erase(input.begin()); input.pop_back();

		for (size_t index = 0; index < input.size(); ++index)
			{
				second_step_of_cleaning(input);
				/*if (input.at(index) == ':')
					{
						objfound_colon(input,string_objects, keyval, index);
						index = start_point;
						continue;
					}*/
				if (input.at(index) == '\"' || input.at(index) == '\'')
					{
						objfound_quote(input, string_objects, keyval, index);
						index = start_point;
						continue;
					}
				if (input.at(index) == ',')
					{
						objfound_comma(input, string_objects, keyval, index);
						index = start_point;
						continue;
					}
				if (input.at(index) == '{')
					{
						objfound_begin_of_anobj(input, string_objects, keyval, index);
						index = start_point;
						continue;
					}
				if (input.at(index) == '[')
					{

						objfound_begin_of_anobj(input, string_objects, keyval, index);
						index = start_point;
						continue;
					}
			}
		if (!input.empty())
			{
				if (keyval.second.empty() && !keyval.first.empty())
					{
						keyval.second = input;

						second_step_of_cleaning(keyval.first);
						second_step_of_cleaning(keyval.second);

						string_objects.insert(string_objects.end(), keyval.first);
						string_objects.insert(string_objects.end(), ":");
						string_objects.insert(string_objects.end(), keyval.second);

						reset(keyval);
						input.clear();
					}
			}

		string_objects.insert(string_objects.begin(), "{");
		string_objects.push_back("}");

		return string_objects;
	}

///			��������������� ������� ��� �������� ��������
void arrfound_quote(std::string& input, std::vector <std::string>& plurality, size_t index) // Tested
	{
		std::string value;

		value = input.substr(index, std::find_first_of(input.begin() + index, input.end(), edge_chars.begin(), edge_chars.end()) - input.begin());
		second_step_of_cleaning(value);
		clear_quotes(value);
		plurality.insert(plurality.end(), value);
		value.clear();

		input.erase(index, std::find_first_of(input.begin() + index, input.end(), edge_chars.begin(), edge_chars.end()) - input.begin());
	}

void arrfound_comma(std::string& input, std::vector <std::string>& plurality, size_t index)
	{
		std::string value;
		value = input.substr(0, index);

		second_step_of_cleaning(value);
		clear_quotes(value);

		plurality.insert(plurality.end(), value);
		value.clear();

		input.erase(0, ++index);
		second_step_of_cleaning(input);
	}

void arrfound_begin_of_anobj(std::string& input, std::vector <std::string>& plurality, size_t index)// Tested
	{
		std::vector <std::string> nested;
		std::pair <size_t, size_t> borders = find_segment_borders(input, index);
		std::string sub_string = input.substr(borders.first, borders.second);

		input.erase(borders.first, borders.second);
		second_step_of_cleaning(input);

		if (sub_string.front() == '{')
			{
				nested = JsonParser::object_parser(sub_string);
			}
		else if (sub_string.front() == '[')
			{
				nested = JsonParser::array_parser(sub_string);
			}

		for (auto position = nested.begin(); position != nested.end(); ++position)
			{
				plurality.insert(plurality.end(), *position);
			}

		nested.clear();
		sub_string.clear();
	}

///							-----------

std::vector <std::string> JsonParser::array_parser(std::string& input) // Tested
	{
		std::vector <std::string> string_array;
		std::string value;

		const size_t start_point = -1;

		input.erase(input.begin()); input.pop_back();

		for (size_t index = 0; index < input.size(); ++index)
			{
			second_step_of_cleaning(input);
				if (input.at(index) == '\"')
					{
						arrfound_quote(input, string_array, index);
						index = start_point;
						continue;
					}
				if (input.at(index) == ',')
					{
						arrfound_comma(input, string_array, index);
						index = start_point;
						continue;
					}
				if (input.at(index) == '{')
					{
						arrfound_begin_of_anobj(input, string_array, index);
						index = start_point;
						continue;
					}
				if (input.at(index) == '[')
					{
						arrfound_begin_of_anobj(input, string_array, index);
						index = start_point;
						continue;
					}
			}
		if (!input.empty())
			{
				second_step_of_cleaning(input);
				string_array.insert(string_array.end(), input);
			}

		string_array.insert(string_array.begin(), "[");
		string_array.push_back("]");

		return string_array;
	}

///			��������������� ������� ��� ������ ��������

std::any return_data(const std::string input) // Tested
	{
		if (input.size() == 4 && input.front() == 'n')
			{
				return nullptr;
			}
		if (input.front() == 'f' && input.size() == 5)
			{
				return false;
			}
		if (input.front() == 't' && input.size() == 4)
			{
				return true;
			}
		if (int(input.front()) > 47 && int(input.front()) < 58)
			{
				return std::stod(input);
			}
		return input;
	}

std::pair <std::vector<std::string>::iterator, std::vector<std::string>::iterator> find_for_gatherer_borders(std::vector <std::string>& input, size_t index) // Tested
	{
		std::string my_char = input.at(index);
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
				throw JsonWarning("Something going wrong!");
			}

		auto temp = input.begin() + index;
		auto last = std::find(std::begin(input)+index, std::end(input), reverse_char);

		// ����� ����� �����: �� ������� ����� ������� ������� ('}' ��� ']'), ���� ������� ������ ����� ������ ������� ('{' ��� '[')
		while (std::find(temp, std::end(input), my_char) < std::find(temp + 1, std::end(input), my_char) && std::find(temp + 1, std::end(input), my_char) < std::find(last, std::end(input), reverse_char))
			{
				temp = std::find(temp + 1, std::end(input), my_char);			// <- ��� �� ������� ������� ���������
				last = std::find(last + 1, std::end(input), reverse_char);		// <- ��� �� ������� �������� ����������� ������
			}
		return std::make_pair(input.begin() + index,++last);
	}

void JsonParser::object_gatherer(std::vector <std::string>& input, Json *json)
	{
		std::pair <std::string, std::any> temp_object;
		std::pair <std::vector<std::string>::iterator, std::vector<std::string>::iterator> borders;
		const size_t start_point = -1;

		json->contains_object = true;
		input.erase(input.begin()); input.pop_back();

		for (size_t index = 0; index < input.size(); ++index)
			{
				if (input.at(index) == ":")
					{
						temp_object.first = input.at(index - 1);
						if (input.at(index + 1) == "{" || input.at(index + 1) == "[")
							{
								borders = find_for_gatherer_borders(input, index + 1);
								std::vector <std::string> temp(borders.first,borders.second);

								temp_object.second = JsonParser::vector_to_object(temp);

								json->AddObject(temp_object.first, temp_object.second);

								input.erase(input.begin(), borders.second);

								index = start_point;
								continue;
							}
						else
							{
								temp_object.second = return_data(input.at(index + 1));

								json->AddObject(temp_object.first, temp_object.second);

								input.erase(input.begin(), input.begin() + index + 2);
								index = start_point;
								continue;
							}
					}
			}
	}

void JsonParser::array_gatherer(std::vector <std::string>& input, Json *json)
	{
		std::any temp_array;
		std::pair <std::vector<std::string>::iterator, std::vector<std::string>::iterator> borders;
		const size_t start_point = -1;

		json->contains_array = true;
		input.erase(input.begin()); input.pop_back();
		for (size_t index = 0; index < input.size(); ++index)
			{
				if (input.at(index) == "{" || input.at(index) == "[")
					{
						borders = find_for_gatherer_borders(input, index);

						std::vector <std::string> temp(borders.first, borders.second);
						temp_array = JsonParser::vector_to_object(temp);
						json->AddArray(temp_array);

						input.erase(input.begin(), borders.second);

						index = start_point;
						continue;
					}
				else
					{
						temp_array = return_data(input.at(index));
						json->AddArray(temp_array);

						input.erase(input.begin(), input.begin() + index + 1);
						index = start_point;
						continue;
					}
			}
	}
///							-----------
