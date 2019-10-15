#include <iostream>

#include "Addons.hpp"
int main()
	{
		//Json json("{\"menu\": \"Файл\",\"commands\":[{\"title\":\"Новый\",\"action\":\"CreateDoc\"},{\"title\":\"Открыть\",\"action\":\"OpenDoc\"},{\"title\":\"Закрыть\",\"action\": \"CloseDoc\"}]}");
		//Json a("Json.json");
		//a.print();
		//std::cout << "//---------------------------------\n";
		//b.print();
		std::cout<<"\n"<<is_file("Json.json")<<"\n";
		setlocale(LC_ALL, "ru-RU");
		return 0;
	}
