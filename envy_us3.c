#include "main.h"

/**
 * get_environ - upw Get the val of an env var.
 * @envname: khggu.
 * @_env: Array.
 *
 * Return: null or pointer
 */
char *get_environ(const char *envname, char **_env)
{
	char *ptr_env;
	int y, m;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	m = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (y = 0; _env[y]; y++)
	{
		/* If name and env are equal */
		m = compare_envname(_env[y], envname);
		if (m)
		{
			ptr_env = _env[y];
			break;
		}
	}

	return (ptr_env + m);
}

/**
 * display_env - display env .
 * @data_sh: data struct
 * Return: 1 or 0.
 */
int display_env(shll_comm *data_sh)
{
	int k, s;

	for (k = 0; data_sh->_env[k]; k++)
	{

		for (s = 0; data_sh->_env[k][s]; s++)
			;

		write(STDOUT_FILENO, data_sh->_env[k], s);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_sh->stat = 0;

	return (1);
}

/**
 * _getline - Read inp
 * @lnptr: pointer
 * @num: size
 * @filestream: Stream to read
 *
 * Return: The num of byt
 */
ssize_t _getline(char **lnptr, size_t *num, FILE *filestream)
{
	int ind;
	static ssize_t inp;
	ssize_t retval;
	char *buf;
	char t = 'z';

	if (inp == 0)
		fflush(filestream);
	else
		return (-1);
	inp = 0;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (buf == 0)
		return (-1);
	while (t != '\n')
	{
		ind = read(STDIN_FILENO, &t, 1);
		if (ind == -1 || (ind == 0 && inp == 0))
		{
			free(buf);
			return (-1);
		}
		if (ind == 0 && inp != 0)
		{
			inp++;
			break;
		}
		if (inp >= BUFSIZE)
			buf = _realloc(buf, inp, inp + 1);
		buf[inp] = t;
		inp++;
	}
	buf[inp] = '\0';
	get_ln(lnptr, num, buf, inp);
	retval = inp;
	if (ind != 0)
		inp = 0;
	return (retval);
}
