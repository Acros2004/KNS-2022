#include "Error.h"
#include "IT.h"
#include "LT.h"

namespace Error
{
	ERROR error[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,"������������ ��� ������"),
		ERROR_ENTRY(1,"��������� ����"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"�������� -in ������ ���� �����"),
		ERROR_ENTRY(101,"�������� ����������� ���������� ������ �����"),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111,"������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112,"������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113,"������ ��� �������� ����� ��������� (asm)"),
		ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY(119, "Lex analysis: ��� ������������� �������� �� ������������� � ����������"),//+
		ERROR_ENTRY(120, "Lex analysis: �������������� �������"),//+
		ERROR_ENTRY(121, "Lex analysis: ��������� ������������ ����� ���������� ��������"),
		ERROR_ENTRY(122, "LT: �������� ������������ ������ ������� ������"),
		ERROR_ENTRY(123, "Lex analysis: ��������������� �������"),//+
		ERROR_ENTRY(124, "Lex analysis: ��������� ������ ��������� ������� ��� ����������"),
		ERROR_ENTRY(125, "IT: ������������ ������� ���������������"),//+
		ERROR_ENTRY(126, "Lex analysis: �������� ������ ����� ��������������"),//+
		ERROR_ENTRY(127, "IT: ������ � �������� ����� � �������� ���������������"),//+
		ERROR_ENTRY(128, "IT: �������� ������������ ������ ������� ���������������"),//+
		ERROR_ENTRY(129, "Lex analysis: ����������� ����������"),//+
		ERROR_ENTRY(130, "Lex analysis: ��������� ������������ �������� �������������� ��������"),//+
		ERROR_ENTRY(131, "LT: ������ ��� �������� ����� ��� ������� ������"),//+
		ERROR_ENTRY(132, "Lex analysis: �������� ��������� ������� �����������"),//+
		ERROR_ENTRY(133, "Lex analysis: ����� ������� �������"),//+
		ERROR_ENTRY(134, "Lex analysis: ������ ������ ����� ��� unshort � ��� ��������"),//+
		ERROR_ENTRY(135, "Lex analysis: ��������������� ������������� ��������������"),//+
		ERROR_ENTRY(136, "Lex analysis: ����������� ����������� ��������� �������"),//+
		ERROR_ENTRY(137, "Lex analysis: ������� ��������� � ���������"),//+
		ERROR_ENTRY(138, "Lex analysis: �� �������� �������� �������"),//+
		ERROR_ENTRY(139, "Lex analysis: ��� ���������� �������"),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "Sint analysis: ������ ���������� �������� ������"),
		ERROR_ENTRY(201, "Sint analysis: ������ � ���������� ���������"),
		ERROR_ENTRY(202, "Sint analysis: ������ � ���������"),
		ERROR_ENTRY(203, "Sint analysis: ������ � ��������� �������"),
		ERROR_ENTRY(204, "Sint analysis: ������ � �������� ���������"),
		ERROR_ENTRY(205, "Sint analysis: ������ � ���������"),
		ERROR_ENTRY(206, "Sint analysis: ������ � ��������� �������"),
		ERROR_ENTRY(207, "Sint analysis: ������ � ��������� �������"),
		ERROR_ENTRY(208, "Sint analysis: ������ � ���������� �������"),
		ERROR_ENTRY(209, "Sint analysis: ������ � ���������� �������"),
		ERROR_ENTRY_NODEF10(210),ERROR_ENTRY_NODEF10(220),ERROR_ENTRY_NODEF10(230),
		ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF10(250),ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "Sem analysis: ����������� ���� DATA"),
		ERROR_ENTRY(301, "Sem analysis: ���������� ����� SOURSE"),
		ERROR_ENTRY(302, "Sem analysis: ����������� ���� SOURSE"),
		ERROR_ENTRY(303, "Sem analysis: ����� �� ������� �������"),
		ERROR_ENTRY(304, "Sem analysis: ��������� ������ ����������� ��������"),
		ERROR_ENTRY(305, "Sem analysis: ���������� ���������� ������� ����"),
		ERROR_ENTRY(306, "Sem analysis: �������� ��� ������������� ��������"),
		ERROR_ENTRY(307, "Sem analysis: ���������� ������������ ���������� �� ���������"),
		ERROR_ENTRY(308, "Sem analysis: ���������� ������� �� ����"),
		ERROR_ENTRY(309, "Sem analysis: ��� ������ ������� ������ ���� unint"),
		ERROR_ENTRY(310, "Sem analysis: ��� �������� ����� ����� ���� ������ ��� ��������"),
		ERROR_ENTRY_NODEF(300),ERROR_ENTRY_NODEF(400),ERROR_ENTRY_NODEF(500),
		ERROR_ENTRY_NODEF(600),ERROR_ENTRY_NODEF(700),ERROR_ENTRY_NODEF(800),ERROR_ENTRY_NODEF(900),
	};
	ERROR geterror(int id)
	{
		ERROR e;//��������� ���������� � ��������� ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)//��������� ��������
			e = error[0];//���� ������ ������� �� ��������
		else
			e = error[id];//���� ������ � ��������
		return e;

	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;//��������� ���������� � ��������� ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)//����� ��������� ��������
			e = error[0];//�� ������
		else//������
		{
			e = error[id];//���������� ������
			e.inext.line = line;//���������� ������
			e.inext.col = col;//���������� �������
		}
		return e;
	}

};