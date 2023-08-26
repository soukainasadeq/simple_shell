#include "main.h"

/**
 * replace_str - hhhhhhhhhhhhhhhhh hhhhhhhhhhh hhhhhhhhhh hh.
 * @inp: hhhhhhhh hhhh
 * @data_shell: rrrrrr bbbbbbe.
 *
 * Return: hhbb hbjsnjk sss
 */
char *replace_str(char *inp, shll_comm *data_shell)
{
	int oln, nln;
	r_var *hd, *ind;
	char *stat, *newinp;

	stat = conv_itoa(data_shell->stat);
	hd = NULL;

	oln = verify_vars(&hd, inp, stat, data_shell);

	if (hd == NULL)
	{
		free(stat);
		return (inp);
	}

	ind = hd;
	nln = 0;

	while (ind != NULL)
	{
		nln += (ind->len_val - ind->len_var);
		ind = ind->next;
	}

	nln += oln;

	newinp = malloc(sizeof(char) * (nln + 1));
	newinp[nln] = '\0';

	newinp = rpl_inp(&hd, inp, newinp, nln);

	free(inp);
	free(stat);
	free_value_ls(&hd);

	return (newinp);
}

/**
 * _unsetenv - hhhhhhhhhhhhhhhh hhhhhhhhhhhhhhh hhhhhhhhhhhh hhhhhhhhhh
 * @datash: sbhhhhhhhhh shbhsbjkbsjbhbs hsbjhbsbjks skjbkbnskksbh ns
 *
 * Return: hsbbhsbbshbs.
 */
int _unsetenv(shll_comm *datash)
{
	int i, k, z;
	char **real_env;
	char *varenv, *nmenv;

	if (datash->args[1] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}
	z = -1;
	for (i = 0; datash->_env[i]; i++)
	{
		varenv = _strdup(datash->_env[i]);
		nmenv = _strtok(varenv, "=");
		if (_strcmp(nmenv, datash->args[1]) == 0)
		{
			z = i;
		}
		free(varenv);
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
 * set_env - kkkkkkkk kkkkkkkkkkk kkkkk k.
 * @environ_name: Njjjjj j jj j j jjjjjjjjjjjjjjje.
 * @val: bbbbbbbbbbb bbbbbbbbbbb bbbbbbbb
 * @data_sh: BBBBBBBBBBBVBBBBBB cccccccccccc hhhhhhhhhhhhhh hhhs.
 *
 * Return: jhdhbdhbj.
 */
void set_env(char *environ_name, char *val, shll_comm *data_sh)
{
	int i;
	char *vrenv, *nmnv;

	for (i = 0; data_sh->_env[i]; i++)
	{
		vrenv = _strdup(data_sh->_env[i]);
		nmnv = _strtok(vrenv, "=");
		if (_strcmp(nmnv, environ_name) == 0)
		{
			free(data_sh->_env[i]);
			data_sh->_env[i] = cp_info(nmnv, val);
			free(vrenv);
			return;
		}
		free(vrenv);
	}

	data_sh->_env = _reallocdp(data_sh->_env, i, sizeof(char *) * (i + 2));
	data_sh->_env[i] = cp_info(environ_name, val);
	data_sh->_env[i + 1] = NULL;
}

/**
 * _setenv - hddddd hd h hhhhhhhhhbbb bbb
 *           bbbbbbbb vvvvvvvvvv .
 * @data_sh: bbbbbbbbb sssssssssss sssssss ssssssss
 *
 * Return: mmmmmmmm mmmm
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
 * cp_info - nnnnnnnnnn nnnnnnnnnnnnnnnnn nnnnnnnnnnnnnnnn nnnnnnnnnn nnnnn n.
 * @alias_name: hhhhhhhhhhhhh hhhhhhhhhhhhhhhd bbbbbbbbdhb
 * @val: jjjjjjjjjj jjjjjjjjjjjjjjj sbbbbbbbbbbss s.
 *
 * Return: mmmmmmmmm sllllllllls lllllllllslm
 */
char *cp_info(char *alias_name, char *val)
{
	char *nw;
	int lenname, lenvalue, ln;

	lenname = _strlen(alias_name);
	lenvalue = _strlen(val);
	ln = lenname + lenvalue + 2;
	nw = malloc(sizeof(char) * (ln));
	_strcpy(nw, alias_name);
	_strcat(nw, "=");
	_strcat(nw, val);
	_strcat(nw, "\0");

	return (nw);
}
