#include "stdafx.h"	

#include <time.h>


#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;//определяем переменную
		log.stream = new ofstream;//открываем поток
		log.stream->open(logfile);//открываем файл
		if (log.stream->fail())//если не открылся то ошибка
			throw ERROR_THROW(112);
		wcscpy_s(log.logfile, logfile);//копируем инфу в log
		return log;
	}
	void WriteLine(LOG log, const char* c, ...)//функция пишущая ТЕСТ БЕЗ ОШИБОК
	{
		const char** ptr = &c;//ставим указатель на начало масива
		int i = 0;
		while (ptr[i] != "")//делаем проходку,и передаём символы до ""
			*log.stream << ptr[i++];
		*log.stream << endl;
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << endl;
	}
	void WriteLog(LOG log)
	{
		tm* timeinf;
		time_t timet;
		time(&timet);
		timeinf = localtime(&timet);
		char temp[100];
		strftime(temp, sizeof(temp), "\n------------ПРОТОКОЛ------------\n ----%d.%m.%y %T----\n ", timeinf);
		*log.stream << temp;
	}
	void WriteIn(LOG log, In::IN in)//пишем исходные данные
	{
		*log.stream << "\n---- Исходные данные ----\n" << in.text
			<< "\n\nВсего символов: " << in.size
			<< "\n\nВсего строк: " << in.lines
			<< "\n\nПропущено: " << in.ignor << endl;
	}
	void WriteParm(LOG log, Parm::PARM parm)//выводим параметры переданные в log
	{
		char in_text[PARM_MAX_SIZE];
		char out_text[PARM_MAX_SIZE];
		char log_text[PARM_MAX_SIZE];
		wcstombs(in_text, parm.in, PARM_MAX_SIZE);//копируем данные в массив char
		wcstombs(out_text, parm.out, PARM_MAX_SIZE);
		wcstombs(log_text, parm.log, PARM_MAX_SIZE);
		*log.stream << "\n ---- Параметры ---- \n\n-in: " << in_text
			<< "\n-out: " << out_text
			<< "\n-log: " << log_text << endl;
	}
	void WriteError(LOG log, Error::ERROR error)//печатаем в поток ошибки
	{
		if (log.stream)
		{
			*log.stream << "\nОшибка " << error.id
				<< ": " << error.message
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << endl;
			Close(log);
		}
		else
		{
			cout << "\nОшибка " << error.id
				<< ": " << error.message
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << endl;
		}
	}
	void Close(LOG log)//закрываем поток
	{
		log.stream->close();
		delete log.stream;
	}

}