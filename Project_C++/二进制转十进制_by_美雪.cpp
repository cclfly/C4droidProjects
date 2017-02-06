#include <iostream>

char lookahead = 0;
char *str;

void match (char terminal)
{
    if (terminal == lookahead)
    {
        lookahead = *(str++);
    }
    else
        throw "Syntax error.";
}

int B ();
int R (int);

int B ()
{
    int syn;
    if (lookahead == '1')
    {
        match ('1');
        syn = R (0);
    }
    else
        throw "Syntax error in B()";
    return syn;
}

int R (int inh)
{
    int syn;
    if (lookahead == '1')
    {
        match ('1');
        syn = R (2 * inh + 1);
    }
    else if (lookahead == '0')
    {
        match ('0');
        syn = R (2 * inh);
    }
    else
        syn = inh;
    return syn;
}

int calc (char *s)
{
    str = s;
    lookahead = *str;
    return B ();
}

int main ()
{
    try
    {
        std::cout << calc ("1010");
    }
    catch (const char *e)
    {
        std::cout << e;
    }
}