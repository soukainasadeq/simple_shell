#include "main.h"

/**
 * rev_string - converses the char in a given str.
 * @s: The input string to be conversed.
 * Return: nothing
 */
void rev_string(char *s)
{
	int cnt = 0, y, k;
	char *str, tmp;

	while (cnt >= 0)
	{
		if (s[cnt] == '\0')
			break;
		cnt++;
	}
	str = s;

	for (y = 0; y < (cnt - 1); y++)
	{
		for (k = y + 1; k > 0; k--)
		{
			tmp = *(str + k);
			*(str + k) = *(str + (k - 1));
			*(str + (k - 1)) = tmp;
		}
	}
}
