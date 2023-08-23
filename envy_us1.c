#include "main.h"

/**
 * verify_env - verify if the variable is envir var.
 * @hd: the head.
 * @inp: Inp str feww.
 * @shell_data: Data shell.
 *
 * Return: void value.
 */
void verify_env(r_var **hd, char *inp, shll_comm *shell_data)
{
	int l, cha, y, l_value;
	char **_env;

	_env = shell_data->_env;
	for (l = 0; _env[l]; l++)
	{
		for (y = 1, cha = 0; _env[l][cha]; cha++)
		{
			if (_env[l][cha] == '=')
			{
				l_value = _strlen(_env[l] + cha + 1);
				add_var_nd(hd, y, _env[l] + cha + 1, l_value);
				return;
			}

			if (inp[y] == _env[l][cha])
				y++;
			else
				break;
		}
	}

	for (y = 0; inp[y]; y++)
	{
		if (inp[y] == ' ' || inp[y] == '\t' || inp[y] == ';' || inp[y] == '\n')
			break;
	}

	add_var_nd(hd, y, NULL, 0);
}

/**
 * rpl_inp - lsjhuiosh.
 * @hd: jhygfdf.
 * @inp: Inp str.
 * @new_inp: New input.
 * @numlen: New length uohod.
 *
 * Return: sdfd Replaced string.
 */
char *rpl_inp(r_var **hd, char *inp, char *new_inp, int numlen)
{
	r_var *index;
	int y, k, n;

	index = *hd;
	for (k = y = 0; y < numlen; y++)
	{
		if (inp[k] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_inp[y] = inp[k];
				k++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (n = 0; n < index->len_var; n++)
					k++;
				y--;
			}
			else
			{
				for (n = 0; n < index->len_val; n++)
				{
					new_inp[y] = index->val[n];
					y++;
				}
				k += (index->len_var);
				y--;
			}
			index = index->next;
		}
		else
		{
			new_inp[y] = inp[k];
			k++;
		}
	}

	return (new_inp);
}

/**
 * verify_vars - verify if typvariable is $$ or $?
 * @header: hhhhhsd.
 * @inp: Inp str.
 * @str: string.
 * @datashell: Data shell.
 *
 * Return: nym of chractere.
 */
int verify_vars(r_var **header, char *inp, char *str, shll_comm *datashell)
{
	int y, leftst, leftpd;

	leftst = _strlen(str);
	leftpd = _strlen(datashell->pid);

	for (y = 0; inp[y]; y++)
	{
		if (inp[y] == '$')
		{
			if (inp[y + 1] == '?')
				add_var_nd(header, 2, str, leftst), y++;
			else if (inp[y + 1] == '$')
				add_var_nd(header, 2, datashell->pid, leftpd), y++;
			else if (inp[y + 1] == '\n')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[y + 1] == '\0')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[y + 1] == ' ')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[y + 1] == '\t')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[y + 1] == ';')
				add_var_nd(header, 0, NULL, 0);
			else
				verify_env(header, inp + y, datashell);
		}
	}

	return (y);
}
/**
 * compare_envname - Comp the envi
 * @name_env: dd Name of the env.
 * @name_ptr: efdName to comp.
 *
 * Return: 0 or bigger than 0.
 */
int compare_envname(const char *name_env, const char *name_ptr)
{
	int ind;

	for (ind = 0; name_env[ind] != '='; ind++)
	{
		if (name_env[ind] != name_ptr[ind])
		{
			return (0);
		}
	}

	return (ind + 1);
}
