#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "NotationConverterDeque.hpp"
#include <string>

class NotationConverter : public NotationConverterInterface
{
public:
	std::string postfixToInfix(std::string inStr) override;		// converts postfix to infix
	std::string postfixToPrefix(std::string inStr) override;	// converts postfix to prefix

	std::string infixToPostfix(std::string inStr) override;		// converts infix to postfix
	std::string infixToPrefix(std::string inStr) override;		// converts infix to prefix

	std::string prefixToInfix(std::string inStr) override;		// converts prefix to infix
	std::string prefixToPostfix(std::string inStr) override;	// converts prefix to postfix

	int precedence(const std::string op);		// checks precedence of operators (used in infixToPostfix and infixToPrefix)
	bool isOperator(const std::string op);		// checks if string is an operator (+, -, /, *)
};

#endif /* NOTAIONCONVERTER_H */