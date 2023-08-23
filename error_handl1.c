#include "main.h"

/**
 * first_character - finds first character.
 * @inp: str input.
 * @index: index variable.
 *
 * Return: 0 or 1.
 */
int first_character(char *inp, int *index)
{

	for (*index = 0; inp[*index]; *index += 1)
	{
		if (inp[*index] == ' ' || inp[*index] == '\t')
			continue;

		if (inp[*index] == ';' || inp[*index] == '|' || inp[*index] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * disp_syn_err - shows a syn err.
 * @data_sh: data structure shell.
 * @inp: str input.
 * @index: index.
 * @boolean: uuflag to control.
 *
 * Return: void value.
 */
void disp_syn_err(shll_comm *data_sh, char *inp, int index, int boolean)
{
	char *mes, *mes2, *mes3, *error, *counter;
	int len;

	if (inp[index] == ';')
	{
		if (boolean == 0)
			mes = (inp[index + 1] == ';' ? ";;" : ";");
		else
			mes = (inp[index - 1] == ';' ? ";;" : ";");
	}

	if (inp[index] == '|')
		mes = (inp[index + 1] == '|' ? "||" : "|");

	if (inp[index] == '&')
		mes = (inp[index + 1] == '&' ? "&&" : "&");

	mes2 = ": Syntax error: \"";
	mes3 = "\" unexpected\n";
	counter = conv_itoa(data_sh->counter);
	len = _strlen(data_sh->argv[0]) + _strlen(counter);
	len += _strlen(mes) + _strlen(mes) + _strlen(mes) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, data_sh->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, mes2);
	_strcat(error, mes);
	_strcat(error, mes3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}

/**
 * ch_syn_err - eff intermediate function
 * @data_sh: ge data struct.
 * @inptrt: eef string input.
 *
 * Return: 1 or 0.
 */
int ch_syn_err(shll_comm *data_sh, char *inptrt)
{
	int begin = 0, fchar = 0, ind = 0;

	fchar = first_character(inptrt, &begin);
	if (fchar == -1)
	{
		disp_syn_err(data_sh, inptrt, begin, 0);
		return (1);
	}

	ind = sep_oper_error(inptrt + begin, 0, *(inptrt + begin));
	if (ind != 0)
	{
		disp_syn_err(data_sh, inptrt, begin + ind, 1);
		return (1);
	}

	return (0);
}

/**
 * dupl_chars - eecounts the repet
 * @inp: string.
 * @index: index to check.
 *
 * Return: number of repet.
 */
int dupl_chars(char *inp, int index)
{
	if (*(inp - 1) == *inp)
		return (dupl_chars(inp - 1, index + 1));

	return (index);
}

/**
 * sep_oper_error - hhfinds syntax errors.
 * @inp: string.
 * @index: index to check.
 * @lastchar: last char.
 *
 * Return: The index of the error. Returns 0 when there are no errors.
 */
int sep_oper_error(char *inp, int index, char lastchar)
{
	int count = 0;

	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (sep_oper_error(inp + 1, index + 1, lastchar));

	if (*inp == ';')
		if (lastchar == '|' || lastchar == '&' || lastchar == ';')
			return (index);

	if (*inp == '|')
	{
		if (lastchar == ';' || lastchar == '&')
			return (index);

		if (lastchar == '|')
		{
			count = dupl_chars(inp, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	if (*inp == '&')
	{
		if (lastchar == ';' || lastchar == '|')
			return (index);

		if (lastchar == '&')
		{
			count = dupl_chars(inp, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	return (sep_oper_error(inp + 1, index + 1, *inp));
}
