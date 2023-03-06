#include <iostream>
#include <ctime>

using namespace std;

bool IsEvenDivide(int a)
{
	int result;
	__asm
	{
		mov eax, a
		mov ebx, 2
		cdq
		idiv ebx
		mov ebx, 0 
		cmp edx, ebx
		je if1
		mov edx, 0
		jmp finish
if1 :
		mov edx, 1
finish :
		mov result, edx
	}
	return result;
}

bool IsEvenBinary(int a)
{
	int result;
	__asm
	{
		mov eax, a
		mov ebx, 0
		and eax, 1
		cmp eax, ebx
		je if1
		mov edx, 0
		jmp finish
if1 :
		mov edx, 1
finish :
		mov result, edx
	}
	return result;
}

int SumFrom1ToN(int n)
{
	int result;
	__asm
	{
		mov eax, n
		mov edx, 0
for_label:
		add edx, eax
		sub eax, 1
		cmp eax, 0
		jne for_label
		mov result, edx
	}
	return result;
}

int SumArray(int* a, int n)
{
	int result;
	__asm
	{
		mov edi, a
		mov eax, n
		mov edx, 0
for_label:
		add edx, [edi+4*eax-4]
		sub eax, 1
		cmp eax, 0
		jne for_label
		mov result, edx
	}
	return result;
}

int SumArrayWithLoop(int* a, int n)
{
	int result;
	__asm
	{
		mov edi, a
		mov ecx, n
		mov edx, 0
for_label:
		add edx, [edi + 4 * ecx - 4]
		sub eax, 1
		cmp eax, 0
		loop for_label
		mov result, edx
	}
	return result;
}

bool IsSimple(int n)
{
	int result, sqrt;
	__asm
	{
		mov eax, n
		mov ebx, 2
		cdq
		idiv ebx
		cmp edx, 0
		je not_simple
		add ebx, 1
		fild n
		fsqrt
		fistp sqrt
		cmp ebx, sqrt
		jg simple

for_label:
		mov eax, n
		cdq
		idiv ebx
		cmp edx, 0
		je not_simple
		add ebx, 2
		cmp ebx, sqrt
		jle for_label

simple:
		mov result, 1
		jmp finish

not_simple:
		mov result, 0
finish:
	}
	return result;
}

int SumArrayWithUpperBound(int* a, int n, int bound)
{
	int result;
	__asm
	{
		mov edi, a
		mov eax, n
		mov ecx, bound
		mov edx, 0
for_label:
		cmp [edi + 4 * eax - 4], ecx
		jg unsuitable
		add edx, [edi + 4 * eax - 4]
unsuitable:
		sub eax, 1
		cmp eax, 0
		jne for_label
		mov result, edx
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	/*int n;
	cin >> n;
	bool result = IsEvenDivide(n);
	cout << (result ? "even" : "odd") << '\n';
	int result2 = SumFrom1ToN(n);
	cout << result2 << '\n';
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = (rand() % 300 + rand() / 56611 % 45) % 21;
		cout << a[i] << ' ';
	}
	cout << '\n';
	int result3 = SumArray(a, n);
	cout << result3 << '\n';
	int result4 = SumArrayWithLoop(a, n);
	cout << result4 << '\n';*/
	int num;
	cin >> num;
	cout << "Число = " << num << (IsSimple(num) ? " - простое\n" : " - составное\n");
	int n = rand() % 11 + 5;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = (rand() % 300 + rand() / 56611 % 45) % 21;
		cout << a[i] << ' ';
	}
	cout << "\nСумма элементов <= 10: " << SumArrayWithUpperBound(a, n, 10) << '\n';
	return 0;
}