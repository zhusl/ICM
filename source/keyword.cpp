#include "keyword.h"
#include "function.h"
#include "deffunc.h"
#include "objectdef.h"
#include "number.h"
#include "tabledata.h"


namespace ICM
{
	void addDefFuncs(FuncTable &DefFuncTable);
	// Create Default FuncTable
	void createDefFuncTable()
	{
		addDefFuncs(DefFuncTable);
		// TODO : Memory leak
#if USE_VARIABLE
		DefVariableTable.add("Nil", new Objects::Nil());
#else
		ObjectPtr nil(new Objects::Identifier(TypeBase::IdentifierType("Nil", ObjectPtr())));
		DefVariableTable.add("Nil", nil);
#endif
		//DefVariableTable.add("NIL", nil);
		//DefVariableTable.add("nil", nil);
		//ObjectPtr nan(new Objects::Identifier("NaN", ObjectPtr(new Objects::Number(Common::Number::Rational(0, 0)))));
		//DefVariableTable.add("NaN", nan);
	}

	BijectionKVMap<string, KeywordID> DefKeywordTable = {
		{ "p",        KeywordID::PTI      },
		{ "let",      KeywordID::LET      },
		{ "cpy",      KeywordID::CPY      },
		{ "ref",      KeywordID::REF      },
		{ "if",       KeywordID::IF       },
		{ "then",     KeywordID::THEN     },
		{ "else",     KeywordID::ELSE     },
		{ "elsif",    KeywordID::ELSIF    },
		{ "loop",     KeywordID::LOOP     },
		{ "while",    KeywordID::WHILE    },
		{ "break",    KeywordID::BREAK    },
		{ "for",      KeywordID::FOR      },
		{ "in",       KeywordID::IN       },
		{ "to",       KeywordID::TO       },
		{ "case",     KeywordID::CASE     },
		{ "when",     KeywordID::WHEN     },
		{ "function", KeywordID::FUNCTION },
	};
}
