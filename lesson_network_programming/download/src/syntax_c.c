#if defined(WIN32)
	#include <windows.h>
#endif
	#include <stdio.h>
	#include <wchar.h>
	#include <locale.h>

void hello() { printf("Hello, World"); }

void data_def()
{
	printf("---Base Data Type---\n");

	printf("sizeof(char): %lu\n", (unsigned long)sizeof(char));
	printf("sizeof(short): %lu\n", (unsigned long)sizeof(short));
	printf("sizeof(int): %lu\n", (unsigned long)sizeof(int));
	printf("sizeof(long): %lu\n", (unsigned long)sizeof(long));
	printf("sizeof(long long): %lu\n", (unsigned long)sizeof(long long));
	printf("sizeof(float): %lu\n", (unsigned long)sizeof(float));
	printf("sizeof(double): %lu\n", (unsigned long)sizeof(double));
	printf("sizeof(long double): %lu\n", (unsigned long)sizeof(long double));
	printf("sizeof(wchar_t): %lu\n", (unsigned long)sizeof(wchar_t));

	char b1 = -1;
	printf("b1=%d, b1=%#x, b1=%u\n", b1, b1, (unsigned char)b1);

	short int b2 = 0x0102;
	printf("b2=%#x\n", b2);

	int b4 = 0x01020304;
	printf("b4=%#x\n", b4);

	long int l4 = 0x04000001;
	printf("l4=%#lx\n", l4);

	long long int b8 = 0x0100000002;
#if defined(WIN32)
	printf("b8=%I64d\n", b8);
#else
	printf("b8=%lld\n", b8);
#endif
	
	float f = 3.1;
	printf("f=%f\n", f);

	double lf = 3e8;
	printf("lf=%f\n", lf);

	char ch = '1';
	printf("ch=%#x\n", ch);

	wchar_t wch1 = 0x4e00; 
	wchar_t wch2 = 0x9fa5; 
	printf("wch1=%#lx, wch2=%#lx\n", 
		(unsigned long)wch1, 
		(unsigned long)wch2
	); 
	printf("wch1=%lc, wch2=%lc\n", 
		(wint_t)wch1, 
		(wint_t)wch2
	); 

	printf("---Array Data Type---\n");

	printf("sizeof(char[4]): %lu\n", (unsigned long)sizeof(char[4]));
	printf("sizeof(int[4]): %lu\n", (unsigned long)sizeof(int[4]));
	printf("sizeof(char[2][4]): %lu\n", (unsigned long)sizeof(char[2][4]));
	printf("sizeof(int[2][4]): %lu\n", (unsigned long)sizeof(int[2][4]));

	int arr1[4];
	printf("arr1[0]=%d, arr1[1]=%d, arr1[2]=%d, arr1[3]=%d\n", arr1[0], arr1[1], arr1[2], arr1[3]);

	char arr2[4] = {0x31, 0x32};
	printf("arr2[0]=%d, arr2[1]=%d, arr2[2]=%d, arr2[3]=%d\n", arr2[0], arr2[1], arr2[2], arr2[3]);

	char arr3[2][4]={{1,2,3,4},{5,6,7,8}};
	printf("arr3[0][0]=%d, arr3[0][1]=%d, arr3[0][2]=%d, arr3[0][3]=%d\n", arr3[0][0], arr3[0][1], arr3[0][2], arr3[0][3]);
	printf("arr3[1][0]=%d, arr3[1][1]=%d, arr3[1][2]=%d, arr3[1][3]=%d\n", arr3[1][0], arr3[1][1], arr3[1][2], arr3[1][3]);

	printf("---Struct Data Type---\n");

	struct acnt {
		unsigned int id;
		char name[8];
		char pass[8];
	};
	struct acnt acnt1 = { 0, "Zhang", "123" };
	acnt1.id = 1;
	printf("sizeof(struct acnt): %lu\n", (unsigned long)sizeof(acnt1));

	struct auth {
		unsigned long long token;
		unsigned char is_expired;
	};
	printf("sizeof(struct auth): %lu\n", (unsigned long)sizeof(struct auth));

	printf("---Union Data Type---\n");

	union ip {
		unsigned long b32;
		char b8[4];
	};
	printf("sizeof(union ip): %lu\n", (unsigned long)sizeof(union ip));

	printf("---Pointer Data Type---\n");
	printf("sizeof(char*): %lu\n", (unsigned long)sizeof(char *));
	printf("sizeof(void*): %lu\n", (unsigned long)sizeof(void *));

	int *pb4 = &b4;
	printf("pb4=%p, *pb4=%#x\n", pb4, *pb4);

	int *parr1 = arr1;
	*parr1 = 1; parr1[1] = 2; *(parr1+2) = 3;
	printf("arr1[0]=%d, arr1[1]=%d, arr1[2]=%d, arr1[3]=%d\n", arr1[0], arr1[1], arr1[2], arr1[3]);

	char *s = "123";
	printf("s=%p, *s=%c, s:%s\n", s, *s, s);

	struct acnt *pacnt = &acnt1;
	pacnt->id = 2; (*pacnt).name[0] = 0;

	void (*phello)(void);
	phello = hello; phello();

	printf("---Size Data Type---\n");
	printf("sizeof(size_t): %lu\n", (unsigned long)sizeof(size_t));
	printf("sizeof(ssize_t): %lu\n", (unsigned long)sizeof(ssize_t));

#if defined(WIN32)
	printf("---Windows Data Type---\n");
	printf("sizeof(HANDLE): %lu\n", (unsigned long)sizeof(DWORD));
	printf("sizeof(DWORD): %lu\n", (unsigned long)sizeof(DWORD));
#endif
}

void func()
{
	char line[]="012345678901234";
	printf("Input string by scanf(ex: Hello,World):");
	scanf("%s", line); 
	printf("Output string by printf:\n");
	printf("%s\n", line);

	//printf("Input by gets:");
	//gets(line);
	//puts(line);

	//fgets(line, sizeof(line), stdin);

	printf("Input string by fgets(ex: Hello World):");
	fgets(line, sizeof(line), stdin);
	printf("Output string by fputs:\n");
	fputs(line, stdout);

	printf("Input string by fgets(ex: hello world):");
	fgets(line, sizeof(line), stdin);
	fputs(line, stdout);
	printf("Input string by sscanf:\n");
	char a[8]="", b[8]="";
	sscanf(line, "%s%s", a, b);
	printf("Output string by sprintf:\n");
	sprintf(line, "key=%s, val=%s\n", a, b);
	fputs(line, stdout);
}

int main(void)
{
	setlocale(LC_ALL, "");
	data_def();
	//func();
	return 0;
}
