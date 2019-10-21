#include <gtest/gtest.h>

#include "Json.hpp"
#include "Exceptions.hpp"

TEST(JsonArray, SimpleArray)
	{
		Json json{ "[ 1 ]" };
		EXPECT_EQ(json.is_object(), false);
		EXPECT_EQ(json.is_array(), true);
		EXPECT_EQ(json.is_empty(), false);

		EXPECT_EQ(std::any_cast<double>(json[0]), 1.);
	}

TEST(JsonArray, MultitypeArray)
	{
		Json json{ "[1.5, \"String\", \"AnotherString\", false]" };
		EXPECT_EQ(json.is_object(), false);
		EXPECT_EQ(json.is_array(), true);
		EXPECT_EQ(json.is_empty(), false);

		EXPECT_EQ(std::any_cast<double>(json[0]), 1.5);
		EXPECT_EQ(std::any_cast<std::string>(json[1]), "String");
		EXPECT_EQ(std::any_cast<std::string>(json[2]), "AnotherString");
		EXPECT_EQ(std::any_cast<bool>(json[3]), false);
	}

TEST(JsonArray, NoSpaceBeforeAndAfter)
	{
		Json json{ "[1]" };

		EXPECT_EQ(json.is_object(), false);
		EXPECT_EQ(json.is_array(), true);
		EXPECT_EQ(json.is_empty(), false);

		EXPECT_EQ(std::any_cast<double>(json[0]), 1.);
	}

TEST(JsonArray, ArrayWithObjects)
{
	Json json{ "[{\"a\": \"b\"}, {\"b\": true}, {\"test\": 123}]" };

	EXPECT_EQ(json.is_object(), false);
	EXPECT_EQ(json.is_array(), true);
	EXPECT_EQ(json.is_empty(), false);

	{
		Json &nested = *std::any_cast<Json *>(json[0]);
		EXPECT_EQ(nested.is_object(), true);
		EXPECT_EQ(nested.is_array(), false);
		EXPECT_EQ(nested.is_empty(), false);

		EXPECT_EQ(std::any_cast<std::string>(nested["a"]), "b");
	}

	{
		Json &nested = *std::any_cast<Json *>(json[1]);
		EXPECT_EQ(nested.is_object(), true);
		EXPECT_EQ(nested.is_array(), false);
		EXPECT_EQ(nested.is_empty(), false);

		EXPECT_EQ(std::any_cast<bool>(nested["b"]), true);
	}

	{
		Json &nested = *std::any_cast<Json *>(json[2]);
		EXPECT_EQ(nested.is_object(), true);
		EXPECT_EQ(nested.is_array(), false);
		EXPECT_EQ(nested.is_empty(), false);

		EXPECT_EQ(std::any_cast<double>(nested["test"]), 123);
	}
}

TEST(JsonArray, ArrayWithNull)
{
	Json json{ "[ null ]" };
	EXPECT_EQ(json.is_object(), false);
	EXPECT_EQ(json.is_array(), true);
	EXPECT_EQ(json.is_empty(), false);

	EXPECT_EQ(json[0].has_value(), true);
}

TEST(JsonArray, ArrayWithAnything)
	{
		Json json{ "[null, 654,false,[ 1, 2, 3 ],100,{ \"a\" : \"b\" },\"String\" ]" };

		EXPECT_EQ(json.is_object(), false);
		EXPECT_EQ(json.is_array(), true);
		EXPECT_EQ(json.is_empty(), false);

		// null
		EXPECT_EQ(json[0].has_value(), true);

		// 654
		EXPECT_EQ(std::any_cast<double>(json[1]), 654);

		// false
		EXPECT_EQ(std::any_cast<bool>(json[2]), false);

		{       // [ 1, 2, 3 ]
			Json &nested = *std::any_cast<Json *>(json[3]);

			EXPECT_EQ(nested.is_object(), false);
			EXPECT_EQ(nested.is_array(), true);
			EXPECT_EQ(nested.is_empty(), false);

			// 1
			EXPECT_EQ(std::any_cast<double>(nested[0]), 1);

			// 2
			EXPECT_EQ(std::any_cast<double>(nested[1]), 2);

			// 3
			EXPECT_EQ(std::any_cast<double>(nested[2]), 3);
		}

		// 100
		EXPECT_EQ(std::any_cast<double>(json[4]), 100);

		{       // { "a" : "b" }
			Json &nested = *std::any_cast<Json *>(json[5]);
			EXPECT_EQ(nested.is_object(), true);
			EXPECT_EQ(nested.is_array(), false);
			EXPECT_EQ(nested.is_empty(), false);

			EXPECT_EQ(std::any_cast<std::string>(nested["a"]), "b");
		}

		// "String"
		EXPECT_EQ(std::any_cast<std::string>(json[6]), "String");
	}
