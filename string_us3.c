#include "main.h"

/**
 * _strspn - Calculates the length of the initial segment
 * @str: Point to the string to check.
 * @acc: accepted bytes.
 * Return: The length of the prefix substring
 */
int _strspn(char *str, char *acc)
{
	int y, k, bool;

	for (y = 0; *(str + y) != '\0'; y++)
	{
		bool = 1;
		for (k = 0; *(acc + k) != '\0'; k++)
		{
			if (*(str + y) == *(acc + k))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}

	return (y);
}

/**
 * _strcat - integrate two strings.
 * @dest: Point to the dest str
 * @src: Point to the src str
 * Return: Pointer to the destination string after integration .
 */
char *_strcat(char *dest, const char *src)
{
	int y, k;

	for (y = 0; dest[y] != '\0'; y++)
		;

	for (k = 0; src[k] != '\0'; k++)
	{
		dest[y] = src[k];
		y++;
	}

	dest[y] = '\0';

	return (dest);
}

/**
 * _strcmp - Contrast two strs.
 * @str1: the first str to contrast.
 * @str2: the second str to contrast.
 * Return: hhhhh
 */
int _strcmp(char *str1, char *str2)
{
	int y;

	for (y = 0; str1[y] == str2[y] && str1[y]; y++)
		;

	if (str1[y] > str2[y])
		return (1);
	if (str1[y] < str2[y])
		return (-1);

	return (0);
}

/**
 * _strchr - search cha.
 * @str: string to search.
 * @c: Chara.
 *
 * Return: o or bigger
 */
char *_strchr(char *str, char c)
{
	unsigned int y = 0;

	for (; *(str + y) != '\0'; y++)
		if (*(str + y) == c)
			return (str + y);
	if (*(str + y) == c)
		return (str + y);
	return ('\0');
}

/**
 * _strcpy -  Copies the string pointed to dest.
 * @dest: dest str.
 * @src: src str.
 * Return: dest string.
 */
char *_strcpy(char *dest, char *src)
{

	size_t b;

	for (b = 0; src[b] != '\0'; b++)
		dest[b] = src[b];

	dest[b] = '\0';

	return (dest);
}
