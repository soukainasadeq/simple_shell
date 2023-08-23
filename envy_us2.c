#include "main.h"

/**
 * Replace variables in a string.
 * @inp: Input string.
 * @data_shell: Shell data.
 *
 * Return: Replaced string.
 */
char *replace_str(char *inp, shll_comm *data_shell)
{
	int old_len, new_len;
	r_var *var_list, *index;
	char *status, *new_inp;

	status = conv_itoa(data_shell->stat);
	var_list = NULL;

	old_len = verify_vars(&var_list, inp, status, data_shell);

	if (var_list == NULL)
	{
		free(status);
		return (inp);
	}

	index = var_list;
	new_len = 0;

	while (index != NULL)
	{
		new_len += (index->len_val - index->len_var);
		index = index->next;
	}

	new_len += old_len;

	new_inp = malloc(sizeof(char) * (new_len + 1));
	new_inp[new_len] = '\0';

	new_inp = rpl_inp(&var_list, inp, new_inp, new_len);

	free(inp);
	free(status);
	free_value_ls(&var_list);

	return (new_inp);
}

/**
 * Unset an environment variable.
 * @datash: Shell data.
 *
 * Return: Success status.
 */
int _unsetenv(shll_comm *datash)
{
	int i, k, z;
	char **real_env;
	char *var_env, *name_env;

	if (datash->args[1] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}
	z = -1;
	for (i = 0; datash->_env[i]; i++)
	{
		var_env = _strdup(datash->_env[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			z = i;
		}
		free(var_env);
	}
	if (z == -1)
	{
		get_err(datash, -1);
		return (1);
	}
	real_env = malloc(sizeof(char *) * (i));
	for (i = k = 0; datash->_env[i]; i++)
	{
		if (i != z)
		{
			real_env[k] = datash->_env[i];
			k++;
		}
	}
	real_env[k] = NULL;
	free(datash->_env[z]);
	free(datash->_env);
	datash->_env = real_env;
	return (1);
}

/**
 * Set an environment variable.
 * @environ_name: Name of the environment variable.
 * @val: Value of the variable.
 * @data_sh: Shell data.
 *
 * Return: Void.
 */
void set_env(char *environ_name, char *val, shll_comm *data_sh)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; data_sh->_env[i]; i++)
	{
		var_env = _strdup(data_sh->_env[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, environ_name) == 0)
		{
			free(data_sh->_env[i]);
			data_sh->_env[i] = cp_info(name_env, val);
			free(var_env);
			return;
		}
		free(var_env);
	}

	data_sh->_env = _reallocdp(data_sh->_env, i, sizeof(char *) * (i + 2));
	data_sh->_env[i] = cp_info(environ_name, val);
	data_sh->_env[i + 1] = NULL;
}

/**
 * Set an environment variable (wrapper function).
 * @data_sh: Shell data.
 *
 * Return: Success status.
 */
int _setenv(shll_comm *data_sh)
{
	if (data_sh->args[1] == NULL || data_sh->args[2] == NULL)
	{
		get_err(data_sh, -1);
		return (1);
	}

	set_env(data_sh->args[1], data_sh->args[2], data_sh);

	return (1);
}

/**
 * Create an environment variable.
 * @alias_name: Name of the alias.
 * @val: Value of the alias.
 *
 * Return: Created string.
 */
char *cp_info(char *alias_name, char *val)
{
	char *new_str;
	int len_name, len_value, total_len;

	len_name = _strlen(alias_name);
	len_value = _strlen(val);
	total_len = len_name + len_value + 2;
	new_str = malloc(sizeof(char) * total_len);
	_strcpy(new_str, alias_name);
	_strcat(new_str, "=");
	_strcat(new_str, val);
	_strcat(new_str, "\0");

	return (new_str);
}
