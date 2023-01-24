#include "stdafx.h"


namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM parm;//создаём переменную структуры
		bool in = 0, o = 0, l = 0;//определяем какие параметры переданы
		for (int i = 1; i < argc; i++)//считываем столько раз,сколько параметров указано
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)//проверка на превышение длины
				throw ERROR_THROW(104);//генерируем ошибку
			if (wcsstr(argv[i], PARM_IN))//если мы НАШЛИ -in
			{
				wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));//копируем параметры -in
				in = 1;//отмечаем,что -in параметр указан
			}
			if (wcsstr(argv[i], PARM_OUT))//если встретили -out
			{
				wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT));//копируем параметры
				o = 1;//отмечаем,что -out параметр указан
			}
			if (wcsstr(argv[i], PARM_LOG))//если встретили -log
			{
				wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG));//копируем параметры
				l = 1;//отмечаем,что -log параметр указан
			}
		}
		if (!in) throw ERROR_THROW(100);//если параметр -in не указан,то генерируем ошибку
		if (!o)
		{
			wcscpy_s(parm.out, parm.in);//копируем название и расширение in
			wcscat_s(parm.out, PARM_OUT_DEFAULT_EXIT);//добавляем расширение .out
		}
		if (!l)
		{
			wcscpy_s(parm.log, parm.in);//копируем название и расширение in
			wcscat_s(parm.log, PARM_LOG_DEFAULT_EXIT);//добавляем расширение .log
		}
		return parm;
	}
}