#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
char stack[20];
int top = -1;
void push(char x)
{
	stack[++top] = x;
}

char pop()
{
	if (top == -1)
		return -1;
	else
		return stack[top--];
}

int priority(char x)
{
	if (x == '(')
		return 0;
	if (x == '+' || x == '-')
		return 1;
	if (x == '*' || x == '/' || x == '%')
		return 2;
	if (x == '^')
		return 3;
}

main()
{
	char exp[20];
	char* e, x;
	printf("Enter the expression :");
	scanf("%s", exp);
	e = exp;
	while (*e != '\0')
	{
		if (isalnum(*e) || e == '.')
		{
			printf("%c", *e);
			//printf("\n");
		}
		else if (*e == '(')
			push(*e);
		else if (*e == ')')
		{
			while ((x = pop()) != '(')
				printf("%c", x);
				printf("\n");
		}
		else
		{
			while (priority(stack[top]) >= priority(*e))
				//printf("\n");
				printf("%c", pop());
				printf("\n");
			push(*e);
		}
		e++;
	}
	while (top != -1)
	{
		//printf("\n");
		printf("\n%c", pop());
	}
	// printf("\n");
}
