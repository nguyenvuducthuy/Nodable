#include "BinaryOperation.h"
#include "Log.h"		// for LOG_DBG(...)
#include "Member.h"
#include "Variable.h"
#include "Member.h"

using namespace Nodable;

 // BinaryOperationComponent :
//////////////////////////

/* Precendence for binary operators */
bool BinaryOperationComponent::NeedsToBeEvaluatedFirst(std::string op, std::string nextOp)
{
	if (op == "=" && nextOp == "=") return false;	
	if (op == "=" && nextOp == "-") return false;	
	if (op == "=" && nextOp == "+") return false;	
	if (op == "=" && nextOp == "*") return false;	
	if (op == "=" && nextOp == "/") return false;

	if (op == "+" && nextOp == "=") return false;
	if (op == "+" && nextOp == "-") return true;	
	if (op == "+" && nextOp == "+") return true;	
	if (op == "+" && nextOp == "*") return false;	
	if (op == "+" && nextOp == "/") return false;

	if (op == "-" && nextOp == "=") return false;
	if (op == "-" && nextOp == "-") return true;	
	if (op == "-" && nextOp == "+") return true;	
	if (op == "-" && nextOp == "*") return false;	
	if (op == "-" && nextOp == "/") return false;

	if (op == "*" && nextOp == "=") return false;
	if (op == "*" && nextOp == "-") return true;	
	if (op == "*" && nextOp == "+") return true;	
	if (op == "*" && nextOp == "*") return true;	
	if (op == "*" && nextOp == "/") return true;

	if (op == "/" && nextOp == "=") return false;
	if (op == "/" && nextOp == "-") return true;	
	if (op == "/" && nextOp == "+") return true;	
	if (op == "/" && nextOp == "*") return true;	
	if (op == "/" && nextOp == "/") return true;

	return true;
}

 // Node_Add :
//////////////

void Add::update()
{
	switch(left->getType())
	{
		case Type_String:
		{
			auto sum = left->getValueAsString() + right->getValueAsString();
			result->setValue(sum);
			break;
		}

		case Type_Boolean:
		{
			auto sum = left->getValueAsBoolean() || right->getValueAsBoolean();
			result->setValue(sum);
			break;
		}	

		default:
		case Type_Number:
		{
			auto sum = left->getValueAsNumber() + right->getValueAsNumber();
			result->setValue(sum);
			break;
		}	
	}
	
	std::string expr;
	expr += left->getSourceExpression();
	expr += "+";
	expr += right->getSourceExpression();
	result->setSourceExpression(expr.c_str());

	LOG_MSG("%s + %s = %f\n", left->getValueAsString().c_str(), 
                              right->getValueAsString().c_str(),
                              result->getValueAsString().c_str());
}

 // Node_Substract :
///////////////////////

void Substract::update()
{
	double sub = left->getValueAsNumber() - right->getValueAsNumber();
	result->setValue(sub);
	
	std::string expr;
	expr += left->getSourceExpression();
	expr += "-";
	expr += right->getSourceExpression();
	result->setSourceExpression(expr.c_str());

	LOG_MSG("%s - %s = %f\n", left->getValueAsString().c_str(), 
                              right->getValueAsString().c_str(),
                              result->getValueAsString().c_str());
}

 // Node_Divide :
///////////////////////

void Divide::update()
{
	if (right->getValueAsNumber() != 0.0f)
	{
		auto div = left->getValueAsNumber() / right->getValueAsNumber();
		result->setValue(div);
		
		LOG_MSG("%s / %s = %f\n", left->getValueAsString().c_str(), 
                                  right->getValueAsString().c_str(),
                                  result->getValueAsString().c_str());
	}

	std::string expr;
	expr += left->getSourceExpression();
	expr += "/";
	expr += right->getSourceExpression();
	result->setSourceExpression(expr.c_str());
}

 // Node_Multiply :
///////////////////////

void Multiply::update()
{
	switch(left->getType())
	{
		case Type_Boolean:
		{
			auto mul = left->getValueAsBoolean() && right->getValueAsBoolean();
			result->setValue(mul);
			break;
		}	

		default:
		{
			auto mul = left->getValueAsNumber() * right->getValueAsNumber();
			result->setValue(mul);
			break;
		}
	}
	std::string expr;
	expr += left->getSourceExpression();
	expr += "*";
	expr += right->getSourceExpression();
	result->setSourceExpression(expr.c_str());

	LOG_MSG("%s * %s = %f\n", left->getValueAsString().c_str(), 
	                          right->getValueAsString().c_str(),
	                          result->getValueAsString().c_str());
}

 // Node_Assign :
///////////////////////

void Assign::update()
{
	switch (right->getType())
	{
		case Type_Number:
		{
			auto v = right->getValueAsNumber();
			result->setValue(v);
			left->setValue(v);
			break;
		}
		case Type_String:
		{
			auto v = right->getValueAsString().c_str();
			result->setValue(v);
			left->setValue(v);
			break;
		}
		default:
		{
			auto v = right->getValueAsNumber();
			result->setValue(v);
			left->setValue(v);
			break;
		}
	}
	
	std::string expr;

	expr += left->getSourceExpression();
	expr += "=";
	expr += right->getSourceExpression();

	result->setSourceExpression(expr.c_str());

	LOG_MSG("%s = %s (result %s)\n", 	left->getValueAsString().c_str(),
										right->getValueAsString().c_str(),
										result->getValueAsString().c_str());	
}