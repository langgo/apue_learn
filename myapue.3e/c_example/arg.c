#include "apue.h"
#include <stdarg.h>

int sum(int e1, ...);
double average(double v1, double v2, ...);
int test_copy(int v1, ...);

int
main(void)
{
	printf("%d\n", sum(1, 0));
	printf("%d\n", sum(1, 2, 0));
	printf("%d\n", sum(1, 2, 3, 0));

	/* 可变参数的实参类型必须与va_arg一致 */
	printf("%f\n", average(1, 2, 0));
	printf("%f\n", average(1, 2, 3.0, 0.0));
	printf("%f\n", average(1, 2, 3.0, 4.0, 0.0));

	test_copy(1, 2);

	return 0;
}

int sum(int e1, ...)
{
	int ele_sum = e1;
	int value = 0;
	va_list parg;

	va_start(parg, e1);
	while ((value = va_arg(parg, int)) != 0) {
		printf("value : %d\n", value);
		ele_sum += value;
	}
	va_end(parg);

	return ele_sum;
}

double average(double v1, double v2, ...)
{
	va_list parg;
	double sum = v1 + v2;
	double value = 0.0;
	int count = 2;

	va_start(parg, v2);
	while ((value = va_arg(parg, double)) != 0.0) {
		sum += value;
		++count;
	}
	va_end(parg);

	printf("%d\n", count);
	return sum / count;
}

int test_copy(int v1, ...)
{
	va_list parg;
	va_list parg_copy;
	va_list parg_copy_copy;

	va_start(parg, v1);
	va_start(parg_copy, v1);

	va_copy(parg_copy, parg);
	va_copy(parg_copy, parg);
	va_copy(parg_copy_copy, parg_copy);

	printf("parg 1 : %d\n", va_arg(parg, int));
	printf("parg_copy 1 : %d\n", va_arg(parg_copy, int));
	printf("parg_copy_copy 1 : %d\n", va_arg(parg_copy_copy, int));

	va_end(parg);
	va_end(parg_copy);
	va_end(parg_copy_copy);

	/* 
	在《C语言入门经典》上如是说：
	在对parg_copy执行va_end()之前，不能将va_list对象parg_copy用作另一个复制过程的目标。 
	
	但是，事实并不一定完全是这样。和具体的事项相关。
	上面，parg_copy 被当作目标两次，而没有出现错误。
	*/

	/*
	gcc -ansi -I../include -Wall -DLINUX -D_GNU_SOURCE  arg.c -o arg  -L../lib -lapue

	在加上ansi时，会提示找不到va_copy宏
	gcc  -I../include -Wall -DLINUX -D_GNU_SOURCE  arg.c -o arg  -L../lib -lapue
	*/

	return 0;
}