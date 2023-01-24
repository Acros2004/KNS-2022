#include "stdafx.h"

using namespace Error;


In::IN In::getIn(wchar_t infile[], wchar_t outfile[])
{
	ifstream stream(infile);
	ofstream outputFile(outfile);

	IN in;
	in.size = 0;
	in.file_size = 0;
	in.lines = 0;
	in.ignor = 0;
	int table[] = IN_CODE_TABLE;
	in.text = new unsigned char[IN_MAX_LEN_TEXT] {};
	int col = 0;
	char c;
	string tmpString = "";
	bool flag = false;

	if (stream.is_open())
	{
		while (in.size < IN_MAX_LEN_TEXT)
		{
			stream.get(c);
			unsigned char ch = c;
			if (stream.eof())//если конец файла
			{
				break;
			}
			if ((unsigned char)ch == '|') {
				throw ERROR_THROW_IN(111, in.lines, col);
			}
			if ((unsigned char)ch == '\n')
			{
				col = 0;
				in.size++;
				in.lines++;
				in.text[in.file_size] = IN_SEPARATOR;
				in.file_size++;
				continue;
			}

			if (((unsigned char)ch == ' ' || (unsigned char)ch == '\t') && table[(unsigned char)in.text[in.file_size - 1]] == IN::A)
			{
				col++;
				in.size++;
				continue;
			}

			if ((unsigned char)ch == '\'')
			{
				if (flag == true)
					flag = false;
				else
					flag = true;
			}

			if (flag == true)
			{
				in.text[in.file_size] = ch;
				col++;
				in.size++;
				in.file_size++;
				continue;
			}

			if (table[(unsigned char)ch] == IN::A)
			{
				if (in.text[in.file_size - 1] == ' ')
				{
					in.text[in.file_size - 1] = ch;
					col++;
				}
				else
				{
					in.text[in.file_size] = ch;
					col++;
					in.size++;
					in.file_size++;
					continue;
				}
			}

			else if (table[(unsigned char)ch] == IN::T)
			{
				in.text[in.file_size] = (unsigned char)ch;
				in.size++;
				in.file_size++;
			}

			else if (table[(unsigned char)ch] == IN::F)
			{
				throw ERROR_THROW_IN(111, in.lines, col);
			}

			else if (table[(unsigned char)ch] == IN::I)
			{
				in.ignor++;
			}

			else
			{
				in.text[in.file_size] = table[(unsigned char)ch];
				in.size++;
				in.file_size++;
			}
			col++;
		}
		
		in.text[in.file_size] = IN_SEPARATOR;
		in.file_size++;
		in.text[in.file_size] = '\0';//в конец добавляем \0
	}
	else
	{
		throw ERROR_THROW(110);
	}

	stream.close();
	int i = 0;
	while (i < in.file_size)
	{
		outputFile << in.text[i];
		i++;
	}

	outputFile.close();
	return in;
}

