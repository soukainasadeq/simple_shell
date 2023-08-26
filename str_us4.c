#include "main.h"

/**
 * _strlen - Returnshhj to length of a str.
 * @str: string.
 * Return: The leng of the str.
 */
int _strlen(const char *str)
{
	int ln;

	for (ln = 0; str[ln] != 0; ln++)
	{
	}
	return (ln);
}

/**
 * _isdigit - Determines if a string contient only numeric dig.
 * @str: The inp str to be check.
 * Return: 1 or 0
 */
int _isdigit(const char *str)
{
	unsigned int y;

	for (y = 0; str[y]; y++)
		if (str[y] < 48 || str[y] > 57)
			return (0);
	return (1);
}

/**
 * _strdup - rrDupl a str.
 * @str: str to dupl.
 * Return: dupl string.
 */
char *_strdup(const char *str)
{
	char *newstr;
	size_t len;

	len = _strlen(str);
	newstr = malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	_memcpy(newstr, str, len + 1);

	return (newstr);
}

/**
 * compare_chars - study the characters of str.
 * @str: Input str to study.
 * @delimiter: Delimiter str to compare.
 * Return: 1 or 0.
 */
int compare_chars(char str[], const char *delimiter)
{
	unsigned int y, k, n;

	for (y = 0, n = 0; str[y]; y++)
	{
		for (k = 0; delimiter[k]; k++)
		{
			if (str[y] == delimiter[k])
			{
				n++;
				break;
			}
		}
	}
	if (y == n)
		return (1);
	return (0);
}

/**
 * _strtok -  Splits a string.
 * @str: Inp string.
 * @delimiter: Delimiter str.
 * Return: pointer.
 */
char *_strtok(char str[], const char *delimiter)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int y, bol;

	if (str != NULL)
	{
		if (compare_chars(str, delimiter))
			return (NULL);
		splitted = str; /*Store first address*/
		y = _strlen(str);
		str_end = &str[y]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bol = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (y = 0; delimiter[y]; y++)
		{
			if (*splitted == delimiter[y])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bol == 0 && *splitted) /*Str != Delim*/
			bol = 1;
	}
	if (bol == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}
