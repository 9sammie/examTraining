#include "ctype.h"
#include "stdio.h"

char *s;
int sum(void);

//fourni par le suj
void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int parsing(char *str)
{
    int i=0;
    int par = 0;

    if (str[i] == 0)
        return(unexpected(str[i]), 1);

    while (str[i])
    {
        if (str[i] == '(')
        {
            if (str[i + 1] == ')' || str[i + 1] == '+' || str[i + 1] == '*')
                return(unexpected(str[i + 1]), 1);
            par++;
        }

        else if (str[i] == ')')
        {
            par--;
            if (str[i + 1] == '(')
                return(unexpected(str[i + 1]), 1);
            if (par < 0)
                return(unexpected(str[i]), 1);
        }

        else if (isdigit(str[i]))
        {
            if (isdigit(str[i + 1]))
                return(unexpected(str[i + 1]), 1);
            if (str[i + 1] != '*' && str[i + 1] != '+' && str[i + 1] != ')' && str[i + 1])
                return(unexpected(str[i + 1]), 1);
        }

        else if (str[i] == '*' || str[i] == '+')
        {
            if (str[i + 1] == '*' || str[i + 1] == '+' || !str[i + 1])
                return(unexpected(str[i + 1]), 1);
        }
        else
            return(unexpected(str[i]), 1);
        i++;
    }
    if (par != 0)
        return(unexpected('('), 1);
    return (0);
}


int factor(void)
{
    int n = 0;

    if (isdigit(*s))
        return (*s++ - 48);
    if (*s == '(')
    {
        s++;
        n = sum();
        s++;
    }
    return (n);
}

int mult(void)
{
    int a = factor();
    int b = 0;

    while (*s == '*')
    {
        s++;
        b = factor();
        a *= b;
    }
    return (a);
}

int sum(void)
{
    int a = mult();
    int b = 0;
    while (*s == '+')
    {
        s++;
        b = mult();
        a += b;
    }
    return (a);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    if (parsing(av[1]) == 1)
        return (1);
    s = av[1];
    printf("%d\n", sum());
}