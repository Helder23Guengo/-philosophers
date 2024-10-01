#include "philo.h"

int ft_atoi(const char *str)
{
	int num;
	int np;
	int cont;

	num = 0;
	np = 1;
	cont = 0;
	while(str[cont] == ' ' || str[cont] == '\f' || str[cont] == '\t'
			|| str[cont] == '\r' || str[cont] == '\n' || str[cont] == '\v')
	{
			cont++;
	}
	if(str[cont] == '+' || str[cont] == '-')
	{
		if (str[cont++] == '-')
		{
			np *= -1;
		}
	}
	while(str[cont] >= '0' && str[cont] <= '9')
	{
		num = (num * 10) + (str[cont] - '0');
		cont++;
	}
	return(num * np);
}
