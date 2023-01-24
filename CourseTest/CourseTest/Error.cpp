#include "Error.h"
#include "IT.h"
#include "LT.h"

namespace Error
{
	ERROR error[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"),
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY(101,"Превышен максимально допустимый размер файла"),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,"Ошибка при создании файла генерации (asm)"),
		ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY(119, "Lex analysis: тип возвращаемого значения не соответствует с прототипом"),//+
		ERROR_ENTRY(120, "Lex analysis: нераспознанная лексема"),//+
		ERROR_ENTRY(121, "Lex analysis: превышена максимальная длина строкового литерала"),
		ERROR_ENTRY(122, "LT: Превышен максимальный размер таблицы лексем"),
		ERROR_ENTRY(123, "Lex analysis: переопределение функции"),//+
		ERROR_ENTRY(124, "Lex analysis: параметры нельзя указывать функции без объявления"),
		ERROR_ENTRY(125, "IT: Переполнение таблицы идентификаторов"),//+
		ERROR_ENTRY(126, "Lex analysis: превышен размер имени индетификатора"),//+
		ERROR_ENTRY(127, "IT: Ошибка в создании файла с таблицей идентификаторов"),//+
		ERROR_ENTRY(128, "IT: превышен максимальный размер таблицы идентификаторов"),//+
		ERROR_ENTRY(129, "Lex analysis: неизвестная переменная"),//+
		ERROR_ENTRY(130, "Lex analysis: превышено максимальное значение целочисленного литерала"),//+
		ERROR_ENTRY(131, "LT: ошибка при создании файла для таблицы лексем"),//+
		ERROR_ENTRY(132, "Lex analysis: название параметра функции повторяется"),//+
		ERROR_ENTRY(133, "Lex analysis: токен слишком большой"),//+
		ERROR_ENTRY(134, "Lex analysis: массив должен иметь тип unshort и его элементы"),//+
		ERROR_ENTRY(135, "Lex analysis: переопределение существующего идентификатора"),//+
		ERROR_ENTRY(136, "Lex analysis: неправельно использован строковый литерал"),//+
		ERROR_ENTRY(137, "Lex analysis: указаны параметры у прототипа"),//+
		ERROR_ENTRY(138, "Lex analysis: не объявлен прототип функции"),//+
		ERROR_ENTRY(139, "Lex analysis: нет реализации функции"),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "Sint analysis: ошибка оформления структры блоков"),
		ERROR_ENTRY(201, "Sint analysis: ошибка в оператарах программы"),
		ERROR_ENTRY(202, "Sint analysis: ошибка в выражении"),
		ERROR_ENTRY(203, "Sint analysis: ошибка в значениях массива"),
		ERROR_ENTRY(204, "Sint analysis: ошибка в операнде выражения"),
		ERROR_ENTRY(205, "Sint analysis: ошибка в выражении"),
		ERROR_ENTRY(206, "Sint analysis: ошибка в структуре условии"),
		ERROR_ENTRY(207, "Sint analysis: ошибка в операторе условия"),
		ERROR_ENTRY(208, "Sint analysis: ошибка в параметрах функции"),
		ERROR_ENTRY(209, "Sint analysis: ошибка в аргументах функции"),
		ERROR_ENTRY_NODEF10(210),ERROR_ENTRY_NODEF10(220),ERROR_ENTRY_NODEF10(230),
		ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF10(250),ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "Sem analysis: отсутствует блок DATA"),
		ERROR_ENTRY(301, "Sem analysis: повторение блока SOURSE"),
		ERROR_ENTRY(302, "Sem analysis: отсутствует блок SOURSE"),
		ERROR_ENTRY(303, "Sem analysis: выход за пределы массива"),
		ERROR_ENTRY(304, "Sem analysis: параметру нельзя присваивать значения"),
		ERROR_ENTRY(305, "Sem analysis: присвоение переменной другого типа"),
		ERROR_ENTRY(306, "Sem analysis: неверный тип возвпащаемого значения"),
		ERROR_ENTRY(307, "Sem analysis: количество передаваемых аргументов не совпадает"),
		ERROR_ENTRY(308, "Sem analysis: обнаружено деление на ноль"),
		ERROR_ENTRY(309, "Sem analysis: тип данных массива должен быть unint"),
		ERROR_ENTRY(310, "Sem analysis: при сложении строк может быть только два операнда"),
		ERROR_ENTRY_NODEF(300),ERROR_ENTRY_NODEF(400),ERROR_ENTRY_NODEF(500),
		ERROR_ENTRY_NODEF(600),ERROR_ENTRY_NODEF(700),ERROR_ENTRY_NODEF(800),ERROR_ENTRY_NODEF(900),
	};
	ERROR geterror(int id)
	{
		ERROR e;//объявляем переменную е структуры ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)//Проверяем диапазон
			e = error[0];//если ошибка выходит за диапазон
		else
			e = error[id];//Если входит в диапазон
		return e;

	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;//объявляем переменную е структуры ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)//снова проверяем диапазон
			e = error[0];//не входит
		else//входит
		{
			e = error[id];//записываем ошибку
			e.inext.line = line;//определяем строку
			e.inext.col = col;//определяем позицию
		}
		return e;
	}

};