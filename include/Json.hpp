#pragma once
#include <string>
#include <map>
#include <vector>
#include <any>
#include <typeinfo>

class Json 
	{
		// ���������� ��� �������� ��������
		std::map<std::string, std::any> Objects; // ��� �������� ��������
		std::vector<std::any> Arrays;			 // ��� �������� ��������
		
	public:
		// ����������� �� ������, ���������� Json-������.
		Json(const std::string& s);
		// ����������� �� Json-�������, ���������� Json-������.
		Json(Json& s);
		// ������ �����������
		Json() = default;
		
		virtual ~Json();

		// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
		bool is_array() const;
		// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
		bool is_object() const;
		// ����� ���������� true, �������� ������ ��������� �� �������� � ���� JSON-������ � JSON-������. ����� false.
		bool is_empty() const;

		//
		void copy_json(const Json a)
			{
				Arrays = a.give_arrays();
				Objects = a.give_objects();
			}
		// �������� � ������� ����, ��������
		void AddObject(const std::string &key, const std::any &value);

		// �������� �������� � ������
		void AddArray(const std::any &value);

		std::vector<std::any> give_arrays() const
			{
				return Arrays;
			}

		std::map<std::string, std::any> give_objects() const
			{
				return Objects;
			}

		// ����� ���������� �������� �� ����� key, ���� ��������� �������� JSON-��������.
		// �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
		// ���� ��������� �������� JSON-��������, ������������ ����������.
		std::any& operator[](const std::string& key);

		// ����� ���������� �������� �� ������� index, ���� ��������� �������� JSON-��������.
		// �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
		// ���� ��������� �������� JSON-��������, ������������ ����������.
		std::any& operator[](int index);

		// ����� ���������� ������ ������ Json �� ������, ���������� Json-������.
		static Json parse(const std::string& s);

		// ����� ���������� ������� ������ Json �� �����, ����������� Json-������ � ��������� �������.
		static Json parseFile(const std::string& path_to_file);
		
		void print();
	};