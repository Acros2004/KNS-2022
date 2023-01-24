.586							; система команд (процессор Pentium)
.model flat, stdcall			; модель памяти, соглашение о вызовах
includelib kernel32.lib			; компановщику: компоновать с kernel32
includelib libucrt.lib			; для UCRT - universal C Run-Time library

ExitProcess PROTO: DWORD		; прототип функции для завершения процесса Windows

;-----------Standart functions-----------
includelib C:\Users\noname\Desktop\123\KPO2course\course_project\CourseTest\Debug\StandartLibrary.lib
cat1 PROTO : DWORD, : DWORD
cat2 PROTO : DWORD, : DWORD, : DWORD
print PROTO : DWORD
printint PROTO : DWORD
printcurrenttime PROTO
printcurrentdate PROTO
printerror PROTO
;----------------------------------------

.stack 4096

;---------------Literals---------------
.const

L6	sdword	8	 ; int literal
L8	sdword	12	 ; int literal
L9	sdword	3	 ; int literal
L10	sdword	10	 ; int literal
L11	sdword	14	 ; int literal
L12	sdword	4	 ; int literal
L13	sdword	9	 ; int literal
L14	sdword	15	 ; int literal
L15	sdword	20	 ; int literal
L29	sdword	1	 ; int literal
L32	byte	"boo,", 0
L35	sdword	1	 ; bool literal
L36	sdword	0	 ; bool literal
L37	sdword	16	 ; int literal
L38	sdword	13	 ; int literal
L39	byte	"testtext1", 0
L40	byte	"testtext2", 0
L41	byte	"concat", 0
L42	byte	"bool op", 0
L43	byte	"firstofarray", 0
L44	sdword	0	 ; int literal
L45	sdword	7	 ; int literal
L46	byte	"maxofarray", 0
L49	byte	"date", 0
;--------------------------------------------


;----------------Variables-------------------
.data

x	sdword	0	 ; int variable
y	sdword	0	 ; int variable
z	sdword	0	 ; int variable
k	sdword	0	 ; int variable
m	sdword	0	 ; int variable
l	sdword	0	 ; int variable
sa	byte	255 dup(0)	 ; string variable
sb	byte	255 dup(0)	 ; string variable
sc	byte	255 dup(0)	 ; string variable
bfs	sdword	0	 ; bool variable
bte	sdword	0	 ; bool variable
saySomethingboo	byte	255 dup(0)	 ; string variable
sumsadc	sdword	0	 ; int variable
myArray sdword 12, 3, 10, 14, 4, 9, 15, 20
tmp1 byte 255 dup(0)
;--------------------------------------------

;----------------Functions-------------------

.code

f_sum PROC suma : sdword, sumb : sdword

push suma
push sumb
pop eax
pop ebx
add eax, ebx
push eax
pop sumsadc
mov eax, L29
	ret
f_sum endp


f_saySomething PROC saySomethingmyname : sdword

push offset L32
mov edi, saySomethingmyname
push edi
push offset tmp1
call cat2
push offset tmp1
push offset saySomethingboo
call cat1
push offset saySomethingboo
call print
mov eax, L29
	ret
f_saySomething endp


f_Reverse PROC Reversev : sdword

mov eax, L35
cmp eax, Reversev
jne condition_end
mov eax, L36
	ret
condition_end: 
mov eax, L35
	ret
f_Reverse endp


main PROC

push L37
pop x
push x
call printint
push z
call printint
push L38
pop y
push y
call printint
push x
push y
call f_sum
push eax
pop l
push l
call printint
push x
push y
pop eax
pop ebx
mul ebx
push eax
push x
push y
call f_sum
push eax
push l
push L29
pop ebx
pop eax
sub eax, ebx
cmp eax,0
jl inend
push eax
pop ebx
pop eax
sub eax, ebx
cmp eax,0
jl inend
push eax
push L29
pop eax
pop ebx
div ebx
push eax
pop ebx
pop eax
sub eax, ebx
cmp eax,0
jl inend
push eax
pop z
push z
call printint
push offset L39
push offset sa
call cat1
push offset L40
push offset sb
call cat1
push offset L41
call print
push offset sa
push offset sb
push offset tmp1
call cat2
push offset tmp1
push offset sc
call cat1
push offset sc
call print
push offset sa
call f_saySomething
push eax
pop x
push L36
pop bfs
push bfs
call f_Reverse
push eax
pop bte
push offset L42
call print
push bte
call printint
push offset L43
call print
push myArray[4*0]
call printint
push L44
pop k
push myArray[4*0]
pop m
while_start: 
mov eax, L45
cmp eax, k
jb while_end
mov esi, k
mov eax, myArray[4*esi]
cmp eax, m
jbe condition_end
mov esi, k
push myArray[4*esi]
pop m
condition_end: 
push k
push L29
pop eax
pop ebx
add eax, ebx
push eax
pop k
jmp while_start
while_end: 
push offset L46
call print
push m
call printint
call printcurrenttime
push eax
pop x
call printcurrenttime
push eax
pop x
push offset L49
call print
call printcurrentdate
push eax
pop x
mov eax, L44
	ret
invoke ExitProcess, 0
inend:
call printerror
invoke ExitProcess, 1
main ENDP
end main
;----------------------------------------------
