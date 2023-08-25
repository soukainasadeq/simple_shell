#include "main.h"

/**
 * _memcpy - vophy
 * @new_pointer: yyydestinahhtion pointer.
 * @pointer: yyysource pointer.
 * @s: trtsize of the new pointer.
 *
 * Return: No.
 */
void _memcpy(void *new_pointer, const void *pointer, unsigned int s)
{
	char *char_pr = (char *)pointer;
	char *char_nptr = (char *)new_pointer;
	unsigned int y;

	for (y = 0; y < s; y++)
		char_nptr[y] = char_pr[y];
}

/**
 * _realloc - rtdrt Reallocates a memory
 * @pointer: yuy Pointer
 * @old_s:  old Size
 * @new_s: New size
 *
 * Return: Point.
 */
void *_realloc(void *pointer, unsigned int old_s, unsigned int new_s)
{
	void *nptr;

	if (pointer == NULL)
		return (malloc(new_s));

	if (new_s == 0)
	{
		free(pointer);
		return (NULL);
	}

	if (new_s == old_s)
		return (pointer);

	nptr = malloc(new_s);
	if (nptr == NULL)
		return (NULL);

	if (new_s < old_s)
		_memcpy(nptr, pointer, new_s);
	else
		_memcpy(nptr, pointer, old_s);

	free(pointer);
	return (nptr);
}

/**
 * _reallocdp - sfav saaa
 * @pointer: fioioh oihijl.
i * @old_s: oldSize
 * @new_s: New size.
 *
 * Return: Point.
 */
char **_reallocdp(char **pointer, unsigned int old_s, unsigned int new_s)
{
	char **nptr;
	unsigned int y;

	if (pointer == NULL)
		return (malloc(sizeof(char *) * new_s));

	if (new_s == old_s)
		return (pointer);

	nptr = malloc(sizeof(char *) * new_s);
	if (nptr == NULL)
		return (NULL);

	for (y = 0; y < old_s; y++)
		nptr[y] = pointer[y];

	free(pointer);

	return (nptr);
}
