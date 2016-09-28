#include "match.h"
#include "keyword.h"

namespace ICM
{
	MatchResult Match::matchNext()
	{
		MatchResult mr;
		MatchType type = MT_Null;
		const char *begin = currptr;
		int mode = 0;
		vector<char> findchars;
		vector<char> ignorechars;
		bool firstfind = false;
		static const char breakfindchars[] = " \n\t()[];"; // include '\0'

		while (true) {
			char c = *currptr;
			if (c == '\n')
				this->linenum++;
			switch (mode)
			{
			case 0:  // No Match
				switch (c)
				{
				case '(':  /* Left Bracket */
					++currptr;
					mr = MatchResult(MT_LBracket, currptr - 1, currptr);
					goto EndMatch;
				case ')':  /* Right Bracket */
					++currptr;
					mr = MatchResult(MT_RBracket, currptr - 1, currptr);
					goto EndMatch;
				case '[':  /* Left Square Bracket */
					++currptr;
					mr = MatchResult(MT_LSBracket, currptr - 1, currptr);
					goto EndMatch;
				case ']':  /* Right Square Bracket */
					++currptr;
					mr = MatchResult(MT_RSBracket, currptr - 1, currptr);
					goto EndMatch;
				case ';':  /* Comment */
					findchars = { '\n', '\0' };
					//ignorechars = { '\\' };
					type = MT_Comment;
					begin = currptr;
					mode = 1;
					break;
				case '"':  /* String */
					findchars = { '"', '\0' };
					//ignorechars = { '\\' };
					type = MT_String;
					begin = currptr + 1;
					mode = 1;
					break;
				case '\'':  /* Symbol */ 
					findchars = { '\'', '\0' };
					type = MT_Symbol;
					begin = currptr + 1;
					mode = 1;
					break;
				case '-': /* (Maybe) Number */
					type = MT_Number;
					begin = currptr;
					mode = 3;
					firstfind = false;
					break;
				default:
					if (isdigit(c)) /* Number */ {
						type = MT_Number;
						begin = currptr;
						mode = 2;
					}
					else if (isalpha(c) || ispunct(c)) /* Idenit */ {
						type = MT_Identifier;
						begin = currptr;
						mode = 2;
					}
				}
				break;
			case 1:  // Match Long with findchar
				if (std::find(findchars.begin(), findchars.end(), c) != findchars.end()) {
					mr = MatchResult(type, begin, currptr);
					if (c != '\0')
						++currptr;
					goto EndMatch;
				}
				break;
			case 2:  // Match Long without findchar
				if (std::find(std::begin(breakfindchars), std::end(breakfindchars), c) != std::end(breakfindchars)) {
					mr = MatchResult(type, begin, currptr);
					goto EndMatch;
				}
				break;
			case 3:  // Match Long with function find
				if (isdigit(c)) {
					firstfind = true;
				}
				else {
					if (firstfind) {
						mr = MatchResult(type, begin, currptr);
						goto EndMatch;
					}
					else {
						currptr -= 2;
						type = MT_Identifier;
						mode = 2;
					}
				}
				break;
			default:
				break;
			}
			if (c == '\0')
				break;
			++currptr;
		}
		EndMatch:
		if (mr.getType() == MT_Identifier) {
			if (mr.getString() == "Nil")
				;//mr.setType(MT_Nil);
			else if (mr.getString() == "T" || mr.getString() == "F")
				mr.setType(MT_Boolean);
			else if (DefKeywordTable.findKey(mr.getString()) != DefKeywordTable.size())
				mr.setType(MT_Keyword);
		}

		return mr;
	}

	string to_string(MatchType type)
	{
		switch (type) {
		case MT_Null:       return "Null";
		case MT_LBracket:   return "LBracket";
		case MT_RBracket:   return "RBracket";
		case MT_LSBracket:  return "LSBracket";
		case MT_RSBracket:  return "RSBracket";
		case MT_Comment:    return "Comment";
		case MT_Identifier: return "Identifier";
		case MT_Keyword:    return "Keyword";
		case MT_Number:     return "Number";
		case MT_Boolean:    return "Boolean";
		case MT_String:     return "String";
		case MT_Symbol:     return "Symbol";
		default:            return "UnfoundType";
		}
	}
}
