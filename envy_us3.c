#include "main.h"

/**
 * Get the value of an environment variable.
 * @env_name: Name of the environment variable.
 * @_env: Array of environment variables.
 *
 * Return: NULL or pointer to value.
 */
char *get_environment(const char *env_name, char **_env)
{
	char *ptr_env;
	int offset, y;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	offset = 0;
	/* Compare all environment variables */
	/* The _env array is declared in the header file */
	for (y = 0; _env[y]; y++)
	{
		/* If name and env_name are equal */
		offset = compare_envname(_env[y], env_name);
		if (offset)
		{
			ptr_env = _env[y];
			break;
		}
	}

	return (ptr_env + offset);
}

/**
 * Display environment variables.
 * @data_sh: Data structure.
 * Return: 1 or 0.
 */
int display_environment(shll_comm *data_sh)
{
	int idx, len;

	for (idx = 0; data_sh->_env[idx]; idx++)
	{
		for (len = 0; data_sh->_env[idx][len]; len++)
			;

		write(STDOUT_FILENO, data_sh->_env[idx], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_sh->stat = 0;

	return (1);
}

/**
 * Read input line from a file stream.
 * @lnptr: Pointer to the line buffer.
 * @num: Size of the buffer.
 * @file_stream: Stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lnptr, size_t *num, FILE *file_stream)
{
	int ind;
	static ssize_t input_count;
	ssize_t retval;
	char *buf;
	char temp_char = 'z';

	if (input_count == 0)
		fflush(file_stream);
	else
		return (-1);
	input_count = 0;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (buf == 0)
		return (-1);
	while (temp_char != '\n')
	{
		ind = read(STDIN_FILENO, &temp_char, 1);
		if (ind == -1 || (ind == 0 && input_count == 0))
		{
			free(buf);
			return (-1);
		}
		if (ind == 0 && input_count != 0)
		{
			input_count++;
			break;
		}
		if (input_count >= BUFSIZE)
			buf = _realloc(buf, input_count, input_count + 1);
		buf[input_count] = temp_char;
		input_count++;
	}
	buf[input_count] = '\0';
	get_line(lnptr, num, buf, input_count);
	retval = input_count;
	if (ind != 0)
		input_count = 0;
	return (retval);
}
