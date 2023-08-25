#include "main.h"

/**
 * error_404 - hjgenerates an error message
 * @data_sh: data relevant
 * Return: error message.
 */
char *error_404(shll_comm *data_sh)
{
	char *err, *vstr;
	int ln;

	vstr = conv_itoa(data_sh->counter);
	ln = _strlen(data_sh->argv[0]) + _strlen(vstr);
	ln += _strlen(data_sh->args[0]) + 16;
	err = malloc(sizeof(char) * (ln + 1));
	if (err == 0)
	{
		free(err);
		free(vstr);
		return (NULL);
	}
	_strcpy(err, data_sh->argv[0]);
	_strcat(err, ": ");
	_strcat(err, vstr);
	_strcat(err, ": ");
	_strcat(err, data_sh->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(vstr);

	return (err);
}

/**
 * err_shell_exit - hso[generates a generic error message
 * @data_sh: data shell.
 *
 * Return: error message.
 */
char *err_shell_exit(shll_comm *data_sh)
{
	char *err, *vstr;
	int ln;

	vstr = conv_itoa(data_sh->counter);
	ln = _strlen(data_sh->argv[0]) + _strlen(vstr);
	ln += _strlen(data_sh->args[0]) + _strlen(data_sh->args[1]) + 23;
	err = malloc(sizeof(char) * (ln + 1));
	if (err == 0)
	{
		free(vstr);
		return (NULL);
	}
	_strcpy(err, data_sh->argv[0]);
	_strcat(err, ": ");
	_strcat(err, vstr);
	_strcat(err, ": ");
	_strcat(err, data_sh->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, data_sh->args[1]);
	_strcat(err, "\n\0");
	free(vstr);

	return (err);
}

/**
 * err_gcd - fghg generates an error message.
 * @data_sh: data shell.
 *
 * Return: error mess.
 */
char *err_gcd(shll_comm *data_sh)
{
	char *err, *vstr, *errmsg;
	int ln, ld;

	vstr = conv_itoa(data_sh->counter);
	if (data_sh->args[1][0] == '-')
	{
		errmsg = ": Illegal option ";
		ld = 2;
	}
	else
	{
		errmsg = ": can't cd to ";
		ld = _strlen(data_sh->args[1]);
	}

	ln = _strlen(data_sh->argv[0]) + _strlen(data_sh->args[0]);
	ln += _strlen(vstr) + _strlen(errmsg) + ld + 5;
	err = malloc(sizeof(char) * (ln + 1));

	if (err == 0)
	{
		free(vstr);
		return (NULL);
	}

	err = conc_err_msg(data_sh, errmsg, err, vstr);

	free(vstr);

	return (err);
}
