#include "main.h"

/**
 * get_err - pioCalls the error message
 * @datashell: Data structure
 * @error_val: Error
 * Return: Error val
 */
int get_err(shll_comm *datashell, int error_val)
{
	char *error;

	switch (error_val)
	{
	case -1:
		error = err_environ(datashell);
		break;
	case 126:
		error = err_path126(datashell);
		break;
	case 127:
		error = error_404(datashell);
		break;
	case 2:
		if (_strcmp("exit", datashell->args[0]) == 0)
			error = err_shell_exit(datashell);
		else if (_strcmp("cd", datashell->args[0]) == 0)
			error = err_gcd(datashell);
		break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}
	datashell->stat = error_val;
	return (error_val);
}

/**
 * empty_data - frees data structure.
 * @data_shell: data structure.
 * Return: no return.
 */
void empty_data(shll_comm *data_shell)
{
	unsigned int ind = 0;

	for (; data_shell->_env[ind]; ind++)
		free(data_shell->_env[ind]);

	free(data_shell->_env);
	free(data_shell->pid);
}


/**
 * set_datashell - Initialize data structure o shell
 * @data_shell: data structure
 * @argv: argument vector
 * Return: no return
 */
void set_datashell(shll_comm *data_shell, char **argv)
{
	unsigned int y;

	data_shell->argv = argv;
	data_shell->input = NULL;
	data_shell->args = NULL;
	data_shell->stat = 0;
	data_shell->counter = 1;
	for (y = 0; environ[y]; y++)
		;
	data_shell->_env = malloc(sizeof(char *) * (y + 1));
	for (y = 0; environ[y]; y++)
	{
		data_shell->_env[y] = _strdup(environ[y]);
	}
	data_shell->_env[y] = NULL;
	data_shell->pid = conv_itoa(getpid());
}

/**
 * get_hlp - help function
 * @data_shll: uukkData structure
 *
 * Return: 0 or 1
 */
int get_hlp(shll_comm *data_shll)
{

	if (data_shll->args[1] == 0)
		disp_help_general();
	else if (_strcmp(data_shll->args[1], "setenv") == 0)
		disp_help_setenv();
	else if (_strcmp(data_shll->args[1], "env") == 0)
		disp_help_env();
	else if (_strcmp(data_shll->args[1], "unsetenv") == 0)
		display_unsetenv();
	else if (_strcmp(data_shll->args[1], "help") == 0)
		disp_help();
	else if (_strcmp(data_shll->args[1], "exit") == 0)
		disp_help_exit();
	else if (_strcmp(data_shll->args[1], "cd") == 0)
		disp_help_cd();
	else if (_strcmp(data_shll->args[1], "alias") == 0)
		disp_help_alias();
	else
		write(STDERR_FILENO, data_shll->args[0],
		      _strlen(data_shll->args[0]));
	data_shll->stat = 0;
	return (1);
}

/**
 * get_bltn - get builtin
 * @command: Command line
 *
 * Return: Fun pointer
 */
int (*get_bltn(char *command))(shll_comm *)
{
	builtin_t bltn[] = {
	    {"env", display_env},
	    {"exit", exit_sh},
	    {"setenv", _setenv},
	    {"unsetenv", _unsetenv},
	    {"cd", changedir_shell},
	    {"help", get_hlp},
	    {NULL, NULL}};
	int index;

	for (index = 0; bltn[index].commname; index++)
	{
		if (_strcmp(bltn[index].commname, command) == 0)
			break;
	}
	return (bltn[index].f);
}
