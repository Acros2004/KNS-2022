#include "stdafx.h"

using namespace In;
using namespace LT;
using namespace IT;

static bool flag_for_declaration = false;

namespace LA
{
	void LexAnalysis(const IN& source, LexTable& lexTable, IdTable& idTable)
	{
		bool flagOFsourse = false;
		int NumOfString = 0;
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT] {};
		text = source.text;
		int ColInString = 0;
		int table[] = IN_CODE_TABLE;
		int tmpSize = 0;
		char tmp[254];
		bool FlagForStringLiteral = false;

		for (int i = 0; i < source.file_size; i++)
		{
			if(tmpSize == IDENT_STR_MAXSIZE)
				throw ERROR_THROW_IN(121, NumOfString, ColInString);
			if (table[(unsigned char)(source.text[i])] != IN::A)
			{
				tmp[tmpSize] = source.text[i];
				tmpSize++;
				ColInString++;
				continue;
			}
			else
			{
				if (tmpSize != 0)
				{
					if ((text[i - 1] == '>' && text[i] == '=') || (text[i - 1] == '<' && text[i] == '='))
					{
						tmp[tmpSize] = source.text[i];
						tmpSize++;
						ColInString++;
						tmp[tmpSize] = '\0';
						if (TokenAnalysis(tmp, NumOfString, lexTable, idTable, ColInString - 1,flagOFsourse))
						{
							tmp[0] = '\0';
							tmpSize = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(120, NumOfString, ColInString - 1);
					}

					tmp[tmpSize] = '\0';
					if (TokenAnalysis(tmp, NumOfString, lexTable, idTable, ColInString - 1,flagOFsourse))
					{
						tmp[0] = '\0';
						i--;
						tmpSize = 0;
						continue;
					}
					else
						throw ERROR_THROW_IN(120, NumOfString, ColInString - 1);
				}
				else
				{
					if (source.text[i] == '\'')
					{
						tmp[tmpSize++] = source.text[i++];
						for (int SizeOfStringLiteral = 0; source.text[i] != '\''; SizeOfStringLiteral++, i++, tmpSize++)
						{
							if (source.text[i] == '|') {
								throw ERROR_THROW_IN(136, NumOfString, ColInString - 1);
							}
							if (SizeOfStringLiteral <= IDENT_STR_MAXSIZE)
							{
								tmp[tmpSize] = source.text[i];
								ColInString++;
							}
							else
								throw ERROR_THROW_IN(121, NumOfString, ColInString - 1);
						}
						tmp[tmpSize++] = source.text[i];
						tmp[tmpSize] = '\0';
						if (TokenAnalysis(tmp, NumOfString, lexTable, idTable, ColInString - 1,flagOFsourse))
						{
							tmp[0] = '\0';
							tmpSize = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(120, NumOfString, ColInString - 1);
					}
					else if (source.text[i] == '{' && lexTable.table[lexTable.current_size - 1].lexema == LEX_DATAELEMENTS)
					{
						flag_for_declaration = true;
						tmp[tmpSize] = source.text[i];
						tmpSize++;
						ColInString++;
						continue;
					}
					else if (source.text[i] == '{' && lexTable.table[lexTable.current_size - 1].lexema == LEX_SOURSE)
					{
						flagOFsourse = true;
						flag_for_declaration = true;
						tmp[tmpSize] = source.text[i];
						tmpSize++;
						ColInString++;
						continue;
					}
					else if (source.text[i] == '}' && flag_for_declaration)
					{
						flag_for_declaration = false;
						tmp[tmpSize] = source.text[i];
						tmpSize++;
						ColInString++;
						continue;
					}
					else if (source.text[i] == '|')
					{
						NumOfString++;
						ColInString = 0;
						continue;
					}
					else if (source.text[i] == ' ')
					{
						ColInString++;
						continue;
					}
					else if ((text[i] == '>' && text[i + 1] == '=') || (text[i] == '<' && text[i + 1] == '=')) {
						tmp[tmpSize] = source.text[i];
						tmpSize++;
						ColInString++;
						continue;
					}
					else
					{
						tmp[tmpSize++] = source.text[i];
						tmp[tmpSize] = '\0';
						if (TokenAnalysis(tmp, NumOfString, lexTable, idTable, ColInString - 1,flagOFsourse))
						{
							tmp[0] = '\0';
							ColInString++;
							tmpSize = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(120, NumOfString, ColInString - 1);
					}
				}
			}
		}
	}

	bool TokenAnalysis(char* token, int strNumber, LexTable& lexTable, IdTable& idTable, int colinstring,bool& flagOFsourse)
	{
		//bool flagOFsourse = false;
		static TypeOfVariable tov;

		switch (token[0])
		{
		case LEX_SEMICOLON:
		{
			LT::Add(lexTable, { LEX_SEMICOLON, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_COMMA:
		{
			LT::Add(lexTable, { LEX_COMMA, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_LEFTBRACE:
		{
			LT::Add(lexTable, { LEX_LEFTBRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_RIGHTBRACE:
		{
			LT::Add(lexTable, { LEX_RIGHTBRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_LEFTHESIS:
		{
			LT::Add(lexTable, { LEX_LEFTHESIS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}
		case LEX_EQUAL_IF:
		{
			LT::Add(lexTable, { LEX_EQUAL_IF, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}
		case LEX_NOT_EQUAL_IF:
		{
			LT::Add(lexTable, { LEX_NOT_EQUAL_IF, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}
		case LEX_EQUALS:
		{
			LT::Add(lexTable, { LEX_EQUALS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_REFERENSE:
		{
			LT::Add(lexTable, { LEX_REFERENSE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_RIGHTHESIS:
		{
			LT::Add(lexTable, { LEX_RIGHTHESIS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_PLUS:
		{
			LT::Add(lexTable, { LEX_PLUS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_MINUS:
		{
			LT::Add(lexTable, { LEX_MINUS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_STAR:
		{
			LT::Add(lexTable, { LEX_STAR, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_DIRSLASH:
		{
			LT::Add(lexTable, { LEX_DIRSLASH, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}
		case LEX_MORE:
		{
			FST::FST* auto_value = new FST::FST(MORE_OR_EQUAL(token));
			if (FST::execute(*auto_value)) {
				LT::Add(lexTable, { LEX_MORE_OR_EQUAL, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
				break;
			}
			else {
				LT::Add(lexTable, { LEX_MORE, strNumber, (int)LT_TI_NULLXDX });
				return true;
				break;
			}

		}

		case LEX_LESS:
		{
			FST::FST* auto_value = new FST::FST(LESS_OR_EQUAL(token));
			if (FST::execute(*auto_value)) {
				LT::Add(lexTable, { LEX_LESS_OR_EQUAL, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
				break;
			}
			else {
				LT::Add(lexTable, { LEX_LESS, strNumber, (int)LT_TI_NULLXDX });
				return true;
				break;
			}
		}

		case LEX_LEFT_SQ_BRACE:
		{
			LT::Add(lexTable, { LEX_LEFT_SQ_BRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_RIGHT_SQ_BRACE:
		{
			LT::Add(lexTable, { LEX_RIGHT_SQ_BRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}
		case 'e': {
			FST::FST* auto_value = new FST::FST(IF(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_CONDITION, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring, flagOFsourse);
			}
		}
		case 'u':
		{
			FST::FST* auto_value = new FST::FST(UNSHORT(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_INT, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				tov.LT_position = lexTable.current_size - 1;
				tov.type_of_variable = TypeOfVariable::INT;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
		}

		case 's':
		{
			FST::FST* auto_value = new FST::FST(SOURCE_FUNCTION(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_SOURSE, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				FST::FST* auto_value = new FST::FST(STRING(token));
				if (FST::execute(*auto_value))
				{
					LT::Add(lexTable, { LEX_STRING, strNumber, (int)LT_TI_NULLXDX });
					delete auto_value;
					auto_value = NULL;
					tov.LT_position = lexTable.current_size - 1;
					tov.type_of_variable = TypeOfVariable::STRING;
					return true;
				}
				else
				{
					delete auto_value;
					auto_value = NULL;
					return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
				}
				break;
			}
			break;
		}
		case 'w':
		{
			FST::FST* auto_value = new FST::FST(WHILE(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_WHILE, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case 't':
		{
			FST::FST* auto_value = new FST::FST(TRUE(token));
			if (FST::execute(*auto_value))
			{
				int i = IT::GetProvVlogic(idTable, 1);
				if (i != (int)LT_TI_NULLXDX) {
					LT::Add(lexTable, { LEX_LITERAL, strNumber, i });
					delete auto_value;
					auto_value = NULL;
					return true;
				}
				else {
					char* name = IT::GetLexemaName(idTable);
					IT::Entry entry;
					entry.iddatatype = BOO;
					entry.idtype = L;
					entry.idxLT = lexTable.current_size;
					strcpy_s(entry.id, name);
					strcpy_s(entry.parrent_block_name, "");

					Add(idTable, entry);
					idTable.table[idTable.current_size - 1].value.vlogic = true;
					Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

					delete auto_value;
					auto_value = NULL;
					return true;
				}
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case 'f':
		{
			FST::FST* auto_value = new FST::FST(FALSE(token));
			if (FST::execute(*auto_value))
			{
				int i = IT::GetProvVlogic(idTable, 0);
				if (i != (int)LT_TI_NULLXDX) {
					LT::Add(lexTable, { LEX_LITERAL, strNumber, i });
					delete auto_value;
					auto_value = NULL;
					return true;
				}
				else {
					char* name = IT::GetLexemaName(idTable);
					IT::Entry entry;
					entry.iddatatype = BOO;
					entry.idtype = L;
					entry.idxLT = lexTable.current_size;
					strcpy_s(entry.id, name);
					strcpy_s(entry.parrent_block_name, "");

					Add(idTable, entry);
					idTable.table[idTable.current_size - 1].value.vlogic = false;
					Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

					delete auto_value;
					auto_value = NULL;
					return true;
				}
			}
			auto_value = new FST::FST(FUNCTION(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_FUNCTION, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case 'd':
		{
			FST::FST* data_main = new FST::FST(DATA(token));
			if (FST::execute(*data_main))
			{
				LT::Add(lexTable, { LEX_DATAELEMENTS, strNumber, (int)LT_TI_NULLXDX });
				delete data_main;
				data_main = NULL;
				return true;
			}
			else
			{
				delete data_main;
				data_main = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case 'r':
		{
			FST::FST* auto_value = new FST::FST(RETURN(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_RETURN, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case 'b':
		{
			FST::FST* auto_value = new FST::FST(BOOL(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_BOOL, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				tov.LT_position = lexTable.current_size - 1;
				tov.type_of_variable = TypeOfVariable::BOOL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case 'p':
		{
			FST::FST* auto_value = new FST::FST(PRINT(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_PRINT, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case '\'':
		{
			FST::FST* auto_value = new FST::FST(STRING_LITERAL(token));
			if (FST::execute(*auto_value))
			{
				if (strlen(token) >= IDENT_STR_MAXSIZE)
					throw ERROR_THROW_IN(121, strNumber, colinstring);
				int i = IT::GetProvVStr(idTable, token);
				if (i != (int)LT_TI_NULLXDX) {
					LT::Add(lexTable, { LEX_LITERAL, strNumber, i });
					delete auto_value;
					auto_value = NULL;
					return true;
				}
				else {
					char* name = IT::GetLexemaName(idTable);
					IT::Entry entry;
					entry.idxLT = lexTable.current_size;
					entry.iddatatype = STR;
					entry.idtype = L;
					strcpy_s(entry.id, name);
					strcpy_s(entry.parrent_block_name, "");

					Add(idTable, entry);
					idTable.table[idTable.current_size - 1].value.vstr->len = 0;
					int i = 0, j = 0;
					for (; token[i] != '\0'; i++)
					{
						if (token[i] != '\'')
						{
							idTable.table[idTable.current_size - 1].value.vstr->str[j] = token[i];
							idTable.table[idTable.current_size - 1].value.vstr->len++;
							j++;
						}
					}
					idTable.table[idTable.current_size - 1].value.vstr->str[j] = '\0';
					Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

					delete auto_value;
					auto_value = NULL;
					return true;
				}

			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
			break;
		}

		case '0':
		{
			FST::FST* auto_value = new FST::FST(OCT_LITERAL(token));
			if (FST::execute(*auto_value))
			{
				int vint = (int)strtol(token, &token, 8);
				int i = IT::GetProvVInt(idTable, vint);
				if (i != (int)LT_TI_NULLXDX) {
					LT::Add(lexTable, { LEX_LITERAL, strNumber, i });
					delete auto_value;
					auto_value = NULL;
					return true;
				}
				else {
					char* name = IT::GetLexemaName(idTable);
					IT::Entry entry;
					entry.idxLT = lexTable.current_size;
					entry.iddatatype = INT;
					entry.idtype = L;
					strcpy_s(entry.id, name);
					strcpy_s(entry.parrent_block_name, "");

					Add(idTable, entry);
					idTable.table[idTable.current_size - 1].value.vint.value = vint;
					Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

					delete auto_value;
					auto_value = NULL;
					return true;
				}
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return false;
			}
		}

		default:
		{
			FST::FST* auto_value = new FST::FST(INTEGER_LITERAL(token));
			if (FST::execute(*auto_value))
			{
				int vint = atoi(token);
				if (atoi(token) >= INT_MAX)
					throw ERROR_THROW_IN(130, strNumber, colinstring);
				int i = IT::GetProvVInt(idTable, vint);
				if (i != (int)LT_TI_NULLXDX) {
					LT::Add(lexTable, { LEX_LITERAL, strNumber, i });
					delete auto_value;
					auto_value = NULL;
					return true;
				}
				else {
					char* name = IT::GetLexemaName(idTable);
					IT::Entry entry;
					entry.iddatatype = INT;
					entry.idtype = L;
					entry.idxLT = lexTable.current_size;
					strcpy_s(entry.id, name);
					strcpy_s(entry.parrent_block_name, "");
					Add(idTable, entry);
					idTable.table[idTable.current_size - 1].value.vint.value = vint;
					Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

					delete auto_value;
					auto_value = NULL;
					return true;
				}

			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring,flagOFsourse);
			}
		}
		}
	}

	bool IdentificatorAnalysis(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVariable& type, int colinstring,bool sourseFlag)
	{

		FST::FST* identificator = new FST::FST(IDENTIFICATOR(token));
		if (FST::execute(*identificator))
		{
			if (strlen(token) >= 32)
				throw ERROR_THROW_IN(126, strNumber, colinstring);
			bool is_already_checked = false;
			char ready_id[5] = {};
			char source[] = { 's','o','u','r','s','e','\0' };
			int i = 0;

			if (flag_for_declaration)
			{
				//массив sourse
				if (!is_already_checked && (lexTable.table[lexTable.current_size - 1].lexema == LEX_RIGHT_SQ_BRACE && lexTable.table[lexTable.current_size - 2].lexema == LEX_LITERAL && lexTable.table[lexTable.current_size - 3].lexema == LEX_LEFT_SQ_BRACE && type.LT_position == lexTable.current_size - 4))
				{
					if (IsId(idTable, token) == IDENT_NULLIDX)
					{
						IT::Entry entry;
						strcpy_s(entry.parrent_block_name, "sourse");
						strcpy_s(entry.id, token);
						entry.idxLT = lexTable.current_size;
						entry.iddatatype = INT;
						entry.idtype = A;

						if (type.type_of_variable == TypeOfVariable::INT)
						{
							entry.value.vint.array_size = idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].value.vint.value;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							throw ERROR_THROW_IN(134, strNumber, colinstring);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							throw ERROR_THROW_IN(134, strNumber, colinstring);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(135, strNumber, colinstring);
				}
				//массив с указание область видимости
				if (!is_already_checked && (lexTable.table[lexTable.current_size - 1].lexema == LEX_RIGHT_SQ_BRACE && lexTable.table[lexTable.current_size - 2].lexema == LEX_LITERAL && lexTable.table[lexTable.current_size - 3].lexema == LEX_LEFT_SQ_BRACE && lexTable.table[lexTable.current_size - 4].lexema == LEX_REFERENSE && lexTable.table[lexTable.current_size - 5].lexema == LEX_ID && type.LT_position == lexTable.current_size - 7))
				{
					char* test = GetLexemaNameFunc(token, idTable.table[lexTable.table[lexTable.current_size - 5].idxTI].id);
					if (IsId(idTable, test, idTable.table[lexTable.table[lexTable.current_size - 5].idxTI].id) == IDENT_NULLIDX)
					{

						IT::Entry entry;
						strcpy_s(entry.parrent_block_name, idTable.table[lexTable.table[lexTable.current_size - 5].idxTI].id);
						strcpy_s(entry.id, test);
						entry.idxLT = lexTable.current_size;
						entry.iddatatype = INT;
						entry.idtype = A;

						if (type.type_of_variable == TypeOfVariable::INT)
						{
							entry.value.vint.array_size = idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].value.vint.value;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							throw ERROR_THROW_IN(134, strNumber, colinstring);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							throw ERROR_THROW_IN(134, strNumber, colinstring);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(135, strNumber, colinstring);

				}

				//параметр прототипа
				if (!is_already_checked && lexTable.table[lexTable.current_size - 1].lexema == 't' && type.LT_position == lexTable.current_size - 1)
				{
					for (int i = lexTable.current_size - 1; i > 0; i--)
					{
						if (lexTable.table[i].lexema == ')') break;
						if (lexTable.table[i].lexema == '|') break;
						if (lexTable.table[i].lexema == LEX_ID && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::PF)
						{
							if (lexTable.table[i - 1].lexema == LEX_FUNCTION && lexTable.table[i - 2].lexema == 't')
							{
								throw ERROR_THROW_IN(137, strNumber, colinstring);
							}

						}
					}
				}
				//объ€вление переменной
				if (!is_already_checked && lexTable.table[lexTable.current_size - 1].lexema == 't' && type.LT_position == lexTable.current_size - 1) {
					if (IsId(idTable, token) == IDENT_NULLIDX)
					{
						
						IT::Entry entry;
						entry.idxLT = lexTable.current_size;
						strcpy_s(entry.parrent_block_name, "sourse");
						strcpy_s(entry.id, token);
						entry.iddatatype = INT;
						entry.idtype = V;

						if (type.type_of_variable == TypeOfVariable::INT)
						{
							entry.value.vint.value = 0;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							entry.iddatatype = STR;
							entry.value.vstr->len = 0;
							strcpy_s(entry.value.vstr->str, "");
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							entry.iddatatype = BOO;
							entry.value.vlogic = false;
							IT::Add(idTable, entry);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(135, strNumber, colinstring);
				}


				//объ€вление переменной с областью видимости
				if (!is_already_checked && (lexTable.table[lexTable.current_size - 1].lexema == LEX_REFERENSE && lexTable.table[lexTable.current_size - 2].lexema == LEX_ID && lexTable.table[lexTable.current_size - 3].lexema == LEX_REFERENSE && type.LT_position == lexTable.current_size - 4))
				{
					char* test = GetLexemaNameFunc(token, idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].id);
					if (IsId(idTable, test, idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].id) == IDENT_NULLIDX)
					{
						IT::Entry entry;
						strcpy_s(entry.parrent_block_name, idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].id);
						strcpy_s(entry.id, test);
						entry.idxLT = lexTable.current_size;
						entry.iddatatype = INT;
						entry.idtype = V;

						if (type.type_of_variable == TypeOfVariable::INT)
							IT::Add(idTable, entry);

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							entry.iddatatype = STR;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							entry.iddatatype = BOO;
							IT::Add(idTable, entry);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(135, strNumber, colinstring);
				}
				//прототпи функции
				if (strcmp(token, "sourse") == 0 || (!is_already_checked && ((GetEntry(lexTable, lexTable.current_size - 1).lexema == LEX_FUNCTION && GetEntry(lexTable, lexTable.current_size - 2).lexema == 't') && type.LT_position == lexTable.current_size - 2)))
				{
					IT::Entry entry;
					entry.idxLT = lexTable.current_size;
					strcpy_s(entry.parrent_block_name, "");
					strcpy_s(entry.id, token);
					entry.iddatatype = IT::IDDATATYPE::INT;
					entry.idtype = PF;
					entry.value.vint.parm_count = 0;

					if (IsId(idTable, token) == -1 || idTable.table[IsId(idTable, token)].idtype != PF)
					{
						if (strcmp(token, "sourse") == 0)
						{
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_SOURSE, strNumber, idTable.current_size - 1 });
						}
						else
						{
							if (type.type_of_variable == TypeOfVariable::INT)
								IT::Add(idTable, entry);

							if (type.type_of_variable == TypeOfVariable::STRING)
							{
								entry.iddatatype = STR;
								IT::Add(idTable, entry);
							}

							if (type.type_of_variable == TypeOfVariable::BOOL)
							{
								entry.iddatatype = BOO;
								IT::Add(idTable, entry);
							}

							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;


						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(123, strNumber, colinstring);


				}
				if (!is_already_checked)
				{

					int tempIndex = IsId(idTable, token);
					if (tempIndex != -1)
					{
						LT::Add(lexTable, { LEX_ID, strNumber, tempIndex });
					}
					else
					{
						throw ERROR_THROW_IN(129, strNumber, colinstring);
					}
					is_already_checked = true;

				}
			}
			else
			{  
				if(lexTable.current_size == 0)
					throw ERROR_THROW_IN(129, strNumber, colinstring);
			//реализаци€ функции
				if ((strcmp(token, "sourse") == 0 || strcmp(token, "printcurrentdate") == 0 || strcmp(token, "printcurrenttime") == 0) || (!is_already_checked && ((GetEntry(lexTable, lexTable.current_size - 1).lexema == LEX_FUNCTION && GetEntry(lexTable, lexTable.current_size - 2).lexema == 't') && type.LT_position == lexTable.current_size - 2)))
				{
					IT::Entry entry;
					strcpy_s(entry.parrent_block_name, "");
					strcpy_s(entry.id, token);
					entry.idxLT = lexTable.current_size;
					entry.iddatatype = INT;
					entry.idtype = F;
					entry.value.vint.parm_count = 0;

					if (IsId(idTable,token) == -1||idTable.table[IsId(idTable, token)].idtype == PF)
					{
						if(IsIdF(idTable,token) != -1)
							throw ERROR_THROW_IN(123, strNumber, colinstring);
						if (strcmp(token, "sourse") == 0)
						{
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_SOURSE, strNumber, idTable.current_size - 1 });
						}
						else if (strcmp(token, "printcurrentdate") == 0)
						{
							entry.idtype = PF;
							entry.value.vint.parm_count = 0;
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}
						else if (strcmp(token, "printcurrenttime") == 0)
						{
							entry.idtype = PF;
							entry.value.vint.parm_count = 0;
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}
						else
						{
							
							if (sourseFlag) {
								throw ERROR_THROW_IN(123, strNumber, colinstring);
							}
							if (IsId(idTable, token) == -1) {
								throw ERROR_THROW_IN(138, strNumber, colinstring);
							}
							int pos_back_proto = IsId(idTable, token);
							if(idTable.table[pos_back_proto].iddatatype != type.type_of_variable)
								throw ERROR_THROW_IN(119, strNumber, colinstring);
							if (type.type_of_variable == TypeOfVariable::INT)
								IT::Add(idTable, entry);

							if (type.type_of_variable == TypeOfVariable::STRING)
							{
								entry.iddatatype = STR;
								IT::Add(idTable, entry);
							}

							if (type.type_of_variable == TypeOfVariable::BOOL)
							{
								entry.iddatatype = BOO;
								IT::Add(idTable, entry);
							}

							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;


						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(123, strNumber, colinstring);
				}
				//параметры функции
				if (!is_already_checked && lexTable.table[lexTable.current_size - 1].lexema == 't' && type.LT_position == lexTable.current_size - 1)
				{
					for (int i = lexTable.current_size - 1; i > 0; i--)
					{
						if (lexTable.table[i].lexema == ')') break;
						if (lexTable.table[i].lexema == LEX_ID && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::F)
						{
							if (lexTable.table[i - 1].lexema == LEX_FUNCTION && lexTable.table[i - 2].lexema == 't')
							{
								char* test = GetLexemaNameFunc(token, idTable.table[lexTable.table[i].idxTI].id);
								IT::Entry entry;
								strcpy_s(entry.parrent_block_name, idTable.table[lexTable.table[i].idxTI].id);
								strcpy_s(entry.id, test);
								entry.idxLT = lexTable.current_size;
								entry.iddatatype = INT;
								entry.idtype = P;
								idTable.table[lexTable.table[i].idxTI].value.vint.parm_count++;
								if (IsId(idTable, test) != -1) {
									throw ERROR_THROW_IN(132, strNumber, colinstring);
								}
								int pos_func_block = IsId(idTable, idTable.table[lexTable.table[i].idxTI].id);
								idTable.table[pos_func_block].value.vint.parm_count++;
								if (type.type_of_variable == TypeOfVariable::INT)
									IT::Add(idTable, entry);

								if (type.type_of_variable == TypeOfVariable::STRING)
								{
									entry.iddatatype = STR;
									IT::Add(idTable, entry);
								}

								if (type.type_of_variable == TypeOfVariable::BOOL)
								{
									entry.iddatatype = BOO;
									IT::Add(idTable, entry);
								}

								type.LT_position = -1;
								type.type_of_variable = TypeOfVariable::UNDEF;

								LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
								is_already_checked = true;
								break;
							}
						}
					}
				}
				//переменна€ без объ€влени€
				if (!is_already_checked)
				{
					if (lexTable.table[lexTable.current_size - 1].lexema != LEX_INT)
					{
						int temp = 0;
						int temp2 = 0;
						bool isLeftBraceWas = false;
						for (int i = lexTable.current_size - 1; i > 0; i--)
						{
							if (GetEntry(lexTable, i).lexema == LEX_LEFTBRACE)
							{
								isLeftBraceWas = true;
							}

							if (isLeftBraceWas && ((lexTable.table[i].lexema == LEX_ID && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::F) || lexTable.table[i].lexema == LEX_SOURSE))
							{
								if (lexTable.table[i].lexema == LEX_SOURSE)
								{
									temp = IsId(idTable, token);
									if (temp != -1) {
										if (idTable.table[temp].idtype == IT::IDTYPE::PF)
										{
											if(IsIdF(idTable,token) == -1)
												throw ERROR_THROW_IN(139, strNumber, colinstring);
											LT::Add(lexTable, { LEX_ID, strNumber, temp });
											is_already_checked = true;
											break;
										}
										else {
											LT::Add(lexTable, { LEX_ID, strNumber, temp });
											is_already_checked = true;
											break;
										}
									}
									else {
										throw ERROR_THROW_IN(129, strNumber, colinstring);
									}
								}
								else
								{
									char* test = GetLexemaNameFunc(token, idTable.table[lexTable.table[i].idxTI].id);
									temp = IsId(idTable, test);
									if (temp != -1) {
										LT::Add(lexTable, { LEX_ID, strNumber, temp });
										is_already_checked = true;
										break;
									}
									else {
										throw ERROR_THROW_IN(129, strNumber, colinstring);
									}

								}

							}
						}
					}
					else
						return false;
				}
			}
			if (is_already_checked) {
				return true;
			}
			else
				return false;

		}
		else
		{
			delete identificator;
			identificator = NULL;
			return false;
		}
	}
}