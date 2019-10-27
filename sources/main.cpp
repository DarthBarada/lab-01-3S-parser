#include <iostream>

#include "Json.hpp"
int main()
	{
		//Json json("{\"menu\": \"Файл\",\"commands\":[{\"title\":\"Новый\",\"action\":\"CreateDoc\"},{\"title\":\"Открыть\",\"action\":\"OpenDoc\"},{\"title\":\"Закрыть\",\"action\": \"CloseDoc\"}]}");
		Json json("Json.json");
		//Json json(R"({"lastname": "Ivanov","firstname": "Ivan","age": 25,"islegal": false,"marks":[4,5,5,5,2,3],"address":{"city":"Moscow","street": "Vozdvijenka"}})");
		json.print();
		//std::cout << "//---------------------------------\n";
		//b.print();
		return 0;
	}
