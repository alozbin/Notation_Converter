#include "NotationConverter.hpp"
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <algorithm>

// converts expressions from postfix to infix
std::string NotationConverter::postfixToInfix(std::string inStr)
{
	NotationConverterDeque deque;
	std::istringstream iss(inStr);
	std::string s;

	while (iss >> s)	// stream inputs each operand/operator to temporary string
	{
		if (isalpha(s[0]))		// if string is an operand (denoted by letter variable), inserted to back to deque
		{
			deque.insertBack(s);
		}
		else if (isOperator(s))		// if string is an operator, expression inside parenthesis formed
		{
			if (deque.getSize() < 2)	// cannot form expression if less than two operands in deque
			{
				throw std::logic_error("Error: Less operands than required.");
			}

			std::string operand2 = deque.getBack();
			deque.removeBack();
			std::string operand1 = deque.getBack();
			deque.removeBack();

			std::string final = "(" + operand1 + " " + s + " " + operand2 + ")";		// expression formed from last two operands and current operation
			deque.insertBack(final);
		}
		else
		{
			throw std::logic_error("Error: Invalid character.");	// error thrown when string contains character besides operand or operator
		}
	}

	if (deque.getSize() != 1)	// error thrown if final deque has more than one node (meaning expression not fully converted)
	{
		throw std::logic_error("Error: Conversion produced invalid expression.");
	}

	return deque.getBack();
}

// converts expressions from postfix to prefix
std::string NotationConverter::postfixToPrefix(std::string inStr)
{
	std::string conversion1 = postfixToInfix(inStr);		// original postfix string temporarily converted to infix
	std::string conversion2 = infixToPrefix(conversion1);	// temporary infix string finally converted to prefix
	return conversion2;
}

// converts expressions from infix to postfix
std::string NotationConverter::infixToPostfix(std::string inStr)
{
	NotationConverterDeque deque;
	std::string result;

	for (int i = 0; i < inStr.length(); i++)	// iterating across original infix string
	{
		char c = inStr[i];

		if (isspace(c))		// ignoring whitespace
		{
			continue;
		}

		if (!isalpha(c) && c != '(' && c != ')' && !isOperator(std::string(1, c)))		// throws error if invalid character in expression
		{
			throw std::logic_error("Error: At least one invalid character.");
		}

		if (isalpha(c))		// if input is an operand (denoted by letter variable), it is appended to result string
		{
			result += c;
			result += ' ';
		}
		else if (c == '(')		// if input is '(', it is added to front of deque
		{
			deque.insertFront(std::string(1, c));
		}
		else if (c == ')')		// if input is ')' and deque is not empty...
		{
			while (!deque.isEmpty() && deque.getFront() != "(")		// while iterator does not reach "(", front of deque is appended to result
			{
				result += deque.getFront();
				result += ' ';
				deque.removeFront();
			}
			if (deque.getFront() == "(")	// open parenthesis removed once reached
			{
				deque.removeFront();
			}
		}
		else if (isOperator(std::string(1,c)))		// if input is an operator... 
		{
			while (!deque.isEmpty() && (precedence(std::string(1, c)) <= precedence(deque.getFront())))		// front of deque appended to result while deque is not empty and front of deque is no less than precedence of input
			{
				result += deque.getFront();
				result += ' ';
				deque.removeFront();
			}
			deque.insertFront(std::string(1, c));		// then insert input as new front of deque
		}
	}

	while (!deque.isEmpty())	// while deque is not empty, append front of deque to result and remove from deque
	{
		result += deque.getFront();
		result += ' ';
		deque.removeFront();
	}


	if (!result.empty() && result.back() == ' ')	// removes extra whitespace from back of result if necessary
	{
		result.pop_back();
	}

	return result;
}

// converts expressions from infix to prefix
std::string NotationConverter::infixToPrefix(std::string inStr)
{
	std::reverse(inStr.begin(), inStr.end());	// infix string reversed to read from right to left

	for (int i = 0; i < inStr.length(); i++)	// iterating across reversed infix string
	{
		if (isalpha(inStr[i]) || inStr[i] == '(' || inStr[i] == ')' || isOperator(std::string(1, inStr[i])) || isspace(inStr[i]))		// checks for valid characters
		{
			if (inStr[i] == '(')		// reversing parenthesis to comply with reversed infix string
			{
				inStr[i] = ')';
			}
			else if (inStr[i] == ')')
			{
				inStr[i] = '(';
			}
		}
		else    // throws error if infix string contains invalid character
		{
			throw std::logic_error("Error: At least one invalid character.");
		}
	}

	std::string conversion1 = infixToPostfix(inStr);	// infix string converted using implemented function

	std::reverse(conversion1.begin(), conversion1.end());		// reversing converted string to obtain result
	return conversion1;
}

// converts expressions from prefix to infix
std::string NotationConverter::prefixToInfix(std::string inStr)
{
	NotationConverterDeque deque;

	std::reverse(inStr.begin(), inStr.end());	// original prefix string reversed to read from right to left

	std::istringstream iss(inStr);
	std::string s;

	while (iss >> s)	// stream inputs each operand/operator to temporary string
	{
		if (isalpha(s[0]))		// if string is an operand (denoted by letter variable), inserted to back to deque
		{
			deque.insertBack(s);
		}
		else if (isOperator(s))		// if string is an operator, expression inside parenthesis formed
		{
			if (deque.getSize() < 2)	// cannot form expression if less than two operands in deque
			{
				throw std::logic_error("Error: Less operands than required.");
			}

			std::string operand1 = deque.getBack();
			deque.removeBack();
			std::string operand2 = deque.getBack();
			deque.removeBack();

			std::string final = "(" + operand1 + " " + s + " " + operand2 + ")";		// expression formed from last two operands and current operation
			deque.insertBack(final);
		}
		else
		{
			throw std::logic_error("Error: Invalid character.");	// error thrown when string contains character besides operand or operator
		}
	}

	if (deque.getSize() != 1)		// error thrown if final deque has more than one node (meaning expression not fully converted)
	{
		throw std::logic_error("Error: Conversion produced invalid expression.");
	}

	return deque.getBack();
}

// converts expressions from prefix to postfix
std::string NotationConverter::prefixToPostfix(std::string inStr)
{
	std::string conversion1 = prefixToInfix(inStr);				// original prefix string temporarily converted to infix
	std::string conversion2 = infixToPostfix(conversion1);		// temporary infix string finally converted to postfix
	return conversion2;
}

// used to check if a string is an operator
bool NotationConverter::isOperator(const std::string op) {
	if (op == "+" || op == "-" || op == "/" || op == "*")
	{
		return true;
	}
	else
	{
		return false;
	}
}

// used to check the precedence of operator
int NotationConverter::precedence(const std::string op)
{
	if (op == "+" || op == "-")		// addition and subtraction have lesser precedence
	{
		return 1;
	}
	else if (op == "/" || op == "*")		// division and multiplication have greater precedence
	{
		return 2;
	}

	return 0;
}