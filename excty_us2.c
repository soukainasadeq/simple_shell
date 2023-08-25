#include "main.h"

/**
 * exit_sh - BBBBB BBBBBBNNN
 * @datashell: DBBb bbbbbbbbjjjjjjjjj jjjjjjjjj hhhhha
 *             mmmm hhhhhhhhh bb
 *
 * Return: zzz z  z zzzz
 */
int exit_sh(shll_comm *datashell)
{
	unsigned int ustt;
	int isdgt, strln, bign;

	if (datashell->args[1] != NULL)
	{
		ustt = _atoi(datashell->args[1]);
		isdgt = _isdigit(datashell->args[1]);
		strln = _strlen(datashell->args[1]);
		bign = ustt > (unsigned int)INT_MAX;
		if (!isdgt || strln > 10 || bign)
		{
			get_err(datashell, 2);
			datashell->stat = 2;
			return (1);
		}
		datashell->stat = (ustt % 256);
	}
	return (0);
}

/**
 * execute_line - cccccnnn nnnnnnnnnnn nnnnnnnn
 * @datash: zzzzzz zzzzzz zzzzzzz
 *
 * Return: zzzzzzzzz zzz
 */
int execute_line(shll_comm *datash)
{
	int (*builtin)(shll_comm *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_bltn(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (command_exec(datash));
}

/**
 * err_environ - gggggggggg ggggggggg ggggggggggg gggggggggg gggggg ggg
 * @data_sh: ddddddddddddd   dddddddddddddddd d ddddddddddddd
 *
 * Return: eeeeeeeeee eeee eeeee
 */
char *err_environ(shll_comm *data_sh)
{
	int leng;
	char *er, *txt, *vst;

	vst = conv_itoa(data_sh->counter);
	txt = ": Unable to add/remove from environment\n";
	leng = _strlen(data_sh->argv[0]) + _strlen(vst);
	leng += _strlen(data_sh->args[0]) + _strlen(txt) + 4;
	er = malloc(sizeof(char) * (leng + 1));
	if (er == 0)
	{
		free(er);
		free(vst);
		return (NULL);
	}

	_strcpy(er, data_sh->argv[0]);
	_strcat(er, ": ");
	_strcat(er, vst);
	_strcat(er, ": ");
	_strcat(er, data_sh->args[0]);
	_strcat(er, txt);
	_strcat(er, "\0");
	free(vst);

	return (er);
}

/**
 * err_path126 - bbbbbbbbbbbbbbbbbb bbbbbbbbbbbbbb bbbbbbb
 *                opooooooooooooooo ooo oooooooooooo
 * @data_sh: dgggggggbbbbbbbbbbbb gbbbbbbbbg bgb bgggbbbbgbbb
 *
 * Return: Tdddddd dddddddd dddddddd
 */
char *err_path126(shll_comm *data_sh)
{
	int leng;
	char *vst, *er;

	vst = conv_itoa(data_sh->counter);
	leng = _strlen(data_sh->argv[0]) + _strlen(vst);
	leng += _strlen(data_sh->args[0]) + 24;
	er = malloc(sizeof(char) * (leng + 1));
	if (er == 0)
	{
		free(er);
		free(vst);
		return (NULL);
	}
	_strcpy(er, data_sh->argv[0]);
	_strcat(er, ": ");
	_strcat(er, vst);
	_strcat(er, ": ");
	_strcat(er, data_sh->args[0]);
	_strcat(er, ": Permission denied\n");
	_strcat(er, "\0");
	free(vst);
	return (er);
}

/**
 * conc_err_msg - cccccccccccc c ccccccccccccccccccccccccccccccc cccc
 * @data_sh: vvvvvvv bbbbbbbbbbbb bbbbbbbbbbbb bbbbbbbbb bbbbbj
 * @disp_msg: mmmmmmmmmm dkkkkkkkkkd k
 * @err: zzzzzzz zzzzzzz zzzzzz
 * @vstr: cccc cccccnes.
 *
 * Return: lllllll llll llll lllll llll ll
 */
char *conc_err_msg(shll_comm *data_sh, char *disp_msg, char *err, char *vstr)
{
	char *ilegal_flg;

	_strcpy(err, data_sh->argv[0]);
	_strcat(err, ": ");
	_strcat(err, vstr);
	_strcat(err, ": ");
	_strcat(err, data_sh->args[0]);
	_strcat(err, disp_msg);
	if (data_sh->args[1][0] == '-')
	{
		ilegal_flg = malloc(3);
		ilegal_flg[0] = '-';
		ilegal_flg[1] = data_sh->args[1][1];
		ilegal_flg[2] = '\0';
		_strcat(err, ilegal_flg);
		free(ilegal_flg);
	}
	else
	{
		_strcat(err, data_sh->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}
