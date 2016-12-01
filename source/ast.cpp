#include "basic.h"
#include "ast.h"
#include "object.h"
#include "parser.h"
namespace ICM
{
	//=======================================
	// * Struct Element
	//=======================================
	namespace ASTBase
	{
		Element Element::Data(size_t type, size_t index) {
			EleType et;
			if (type == T_Number) { // TODO
				et = E_Int;
				Element r(et);
				r.data.ivalue = index;
				return r;
				//et = E_Number;
			}
			else if (type == T_String) {
				et = E_String;
			}
			else if (type == T_Boolean) {
				et = E_Boolean;
			}
			else if (type == T_Nil) {
				et = E_Nil;
			}
			else {
				println("Error type in Element::Data.");
			}
			Element r(et);
			r.data.index = index;
			return r;
		}
		Element Element::Refer(size_t index) {
			return Element(E_Refer).setIndex(index);
		}
		Element Element::Keyword(Keyword::KeywordID key) {
			return Element(E_Keyword).setIndex(static_cast<size_t>(key));
		}
		Element Element::Identifier(const string & name) {
			return Element(E_Identifier).setIndex(GlobalIdentifierMap[name]);
		}
		Element Element::Variable(size_t index) {
			return Element(E_Variable).setIndex(index);
		}
		Element Element::Function(size_t index) {
			return Element(E_Function).setIndex(index);
		}

		Object Element::getData() const {
			assert(isData());
			// TODO
			// (Now) Create the copy.
			switch (this->type) {
			case E_Int:
				return Object(T_Number, new int(this->data.ivalue)); // TODO
			case E_Number:
				return Object(T_Number, new TypeBase::NumberType(*(TypeBase::NumberType*)GlobalElementObjectPool.get(data.index))); // TODO
			case E_String:
				return Object(T_String, new string((char*)GlobalElementObjectPool.get(data.index))); // TODO
			case E_Boolean:
				return Object(T_Boolean, new bool(this->data.bvalue)); // TODO
			case E_Nil:
				return Object(T_Nil);
			}
			return Object();
		}
		size_t Element::getRefer() const {
			assert(isRefer() || isDispRefer());
			return data.index;
		}
		Keyword::KeywordID Element::getKeyword() const {
			assert(isKeyword());
			return data.key;
		}
		const string& Element::getIdentifier() const {
			assert(isIdentifier());
			return GlobalIdentifierMap.getKey(data.index);
		}
		VariableTableUnit& Element::getVariable() const {
			assert(isVariable());
			return GlobalVariableTable[data.index];
		}
		FuncTableUnit& Element::getFunction() const {
			assert(isFunction());
			return GlobalFunctionTable[data.index];
		}
		bool Element::getBoolean() const {
			assert(isBoolean());
			return data.bvalue;
		}
		Element & Element::setDisp() {
			assert(isRefer() || isIdentifier());
			if (type == E_Refer)
				type = E_DispRefer;
			else
				type = E_DispData;
			return *this;
		}
	}
	//=======================================
	// * Class AST
	//=======================================
	void AST::pushData(Element&& element) {
		currptr->push_back(element);
	}
	/*void AST::pushData(Object *op) {
		pushData(Element::Data(op));
	}
	void AST::pushData(Keyword::KeywordID key) {
		pushData(Element::Keyword(key));
	}
	void AST::pushData(const string & name) {
		pushData(Element::Identifier(name));
	}*/
	//void AST::pushData(const TypeBase::FunctionType & func) {
	//	currptr->push_back(Element::Function(func.getData().getID()));
	//}
	void AST::pushNode() {
		currptr->push_back(Element::Refer(currindex));
		NodePtr tmp(new Node(currindex++));
		farthptrs.push(currptr);
		currptr = tmp.get();
		Table.push_back(std::move(tmp));
	}
	bool AST::retNode() {
		if (!farthptrs.empty()) {
			currptr = farthptrs.top();
			farthptrs.pop();
			return true;
		}
		return false;
	}
}
