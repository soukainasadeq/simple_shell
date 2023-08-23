#include "main.h"

/**
 * Verify if the variable is an environment variable.
 * @hd: Pointer to the head of variables.
 * @inp: Input string.
 * @shell_data: Shell data.
 *
 * Return: Void.
 */
void verify_env(r_var **hd, char *inp, shll_comm *shell_data)
{
	int len, cha, y, len_value;
	char **environment;

	environment = shell_data->_env;
	for (len = 0; environment[len]; len++)
	{
		for (y = 1, cha = 0; environment[len][cha]; cha++)
		{
			if (environment[len][cha] == '=')
			{
				len_value = _strlen(environment[len] + cha + 1);
				add_var_nd(hd, y, environment[len] + cha + 1, len_value);
				return;
			}

			if (inp[y] == environment[len][cha])
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
 * Replace input based on variables.
 * @hd: Pointer to variables.
 * @inp: Input string.
 * @new_inp: New input.
 * @numlen: Length of new input.
 *
 * Return: Replaced string.
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
 * Verify if a variable is $$ or $?
 * @header: Pointer to the header.
 * @inp: Input string.
 * @str: String.
 * @datashell: Shell data.
 *
 * Return: Number of characters.
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
 * Compare environment names.
 * @name_env: Name of the environment.
 * @name_ptr: Name to compare.
 *
 * Return: 0 or greater than 0.
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
