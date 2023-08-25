#include "main.h"

/**
 * conv_itoa - con inhjt to str.
 * @number: num to con.
 *
 * Return: str.
 */
char *conv_itoa(int number)
{
	unsigned int m;
	int ln = get_length(number);
	char *bufer;

	bufer = malloc(sizeof(char) * (ln + 1));
	if (bufer == 0)
		return (NULL);

	*(bufer + ln) = '\0';

	if (number < 0)
	{
		m = number * -1;
		bufer[0] = '-';
	}
	else
		m = number;

	ln--;
	do {
		*(bufer + ln) = (m % 10) + '0';
		m = m / 10;
		ln--;
	} while (m > 0);
	return (bufer);
}

/**
 * get_length - lentgh
 * @number: num
 *
 * Return: len.
 */
int get_length(int number)
{
	unsigned int m;
	int ln = 1;

	if (number < 0)
	{
		ln++;
		m = number * -1;
	}
	else
		m = number;
	while (m > 9)
	{
		ln++;
		m = m / 10;
	}

	return (ln);
}

/**
 * _atoi - wee rgg.
 * @str: wefe eee.
 *
 * Return: ewgf sgwrg.
 */
int _atoi(char *str)
{
	unsigned int cnt = 0, sz = 0, in = 0, pl = 1, n = 1, y;


	while (*(str + cnt) != '\0')
	{
		if (sz > 0 && (*(str + cnt) < '0' || *(str + cnt) > '9'))
			break;

		if (*(str + cnt) == '-')
			pl *= -1;

		if ((*(str + cnt) >= '0') && (*(str + cnt) <= '9'))
		{
			if (sz > 0)
				n *= 10;
			sz++;
		}
		cnt++;
	}

	for (y = cnt - sz; y < cnt; y++)
	{
		in = in + ((*(str + y) - 48) * n);
		n /= 10;
	}
	return (in * pl);
}
