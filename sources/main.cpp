#include <iostream>

#include "Json.hpp"
int main()
	{
		Json json("{\"menu\": \"Файл\",\"commands\":[{\"title\":\"Новый\",\"action\":\"CreateDoc\"},{\"title\":\"Открыть\",\"action\":\"OpenDoc\"},{\"title\":\"Закрыть\",\"action\": \"CloseDoc\"}]}");
		//Json json = Json::parseFile("../tests/TestJson.json");
		//Json json = Json::parse(R"({"lastname": "Ivanov","firstname": "Ivan","age": 25,"islegal": false,"marks":[4,5,5,5,2,3],"address":{"city":"Moscow","street": "Vozdvijenka"}})");
		//Json json{ "{}" };
		json.print();
		//std::cout << "//---------------------------------\n";
		//b.print();
		return 0;
	}
