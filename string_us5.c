#include "main.h"

/**
 * rev_string - converts the zzzz in a zzzzzz szz.
 * @s: zzz zzzz zzzzz to be zzzzzzz.
 * Return: zzzzzz
 */
void rev_string(char *s)
{
	int i = 0, y, k;
	char *str, tmp;

	while (i >= 0)
	{
		if (s[i] == '\0')
			break;
		i++;
	}
	str = s;

	for (y = 0; y < (i - 1); y++)
	{
		for (k = y + 1; k > 0; k--)
		{
			tmp = *(str + k);
			*(str + k) = *(str + (k - 1));
			*(str + (k - 1)) = tmp;
		}
	}
}
