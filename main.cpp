#include "NotationConverter.hpp"
#include <iostream>
#include <string>
#include <functional>

std::string processConversion(const std::string& input, std::function<std::string(const std::string&)> function)
{
	return function(input);
}

int main()
{
	NotationConverter c;

	std::cout << "\nNotation Conversion Codes:\n"
			  << "1: Postfix to Infix\n"
			  << "2: Postfix to Prefix\n"
			  << "3: Infix to Postfix\n"
			  << "4: Infix to Prefix\n"
			  << "5: Prefix to Infix\n"
			  << "6: Prefix to Postfix\n"
			  << "\nSelect desired conversion: ";
	int code;
	std::cin >> code;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "\nRequirements:\n- Single-letter variables only\n- Operands and operators separated by a space\n\n"
			  << "Sample input :\nInfix --> (A + B) + C\tPostfix --> A B + C + \tPrefix --> + + A B C\n\nEnter input string : ";
	std::string input;
	std::getline(std::cin, input);

	std::string result;
	switch (code)
	{
	case 1:
		result = processConversion(input, [&](const std::string& inStr) { return c.postfixToInfix(inStr); });
		break;
	case 2:
		result = processConversion(input, [&](const std::string& inStr) { return c.postfixToPrefix(inStr); });
		break;
	case 3:
		result = processConversion(input, [&](const std::string& inStr) { return c.infixToPostfix(inStr); });
		break;
	case 4:
		result = processConversion(input, [&](const std::string& inStr) { return c.infixToPrefix(inStr); });
		break;
	case 5:
		result = processConversion(input, [&](const std::string& inStr) { return c.prefixToInfix(inStr); });
		break;
	case 6:
		result = processConversion(input, [&](const std::string& inStr) { return c.prefixToPostfix(inStr); });
		break;
	default:
		std::cout << "Error: Invalid code." << std::endl;
		return 1;
	}

	std::cout << "\nConversion result: " << result << std::endl;
	return 0;
}