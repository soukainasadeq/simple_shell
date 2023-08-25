#include "main.h"

/**
<<<<<<< HEAD
 * exit_sh - Exits the shell.
 * @datashell: Data structure for the shell.
 *
 * Return: Returns the exit status.
 */
int exit_sh(shll_comm *datashell)
{
    unsigned int exit_status;
    int is_digit, str_len, is_big_number;

    if (datashell->args[1] != NULL)
    {
        exit_status = _atoi(datashell->args[1]);
        is_digit = _isdigit(datashell->args[1]);
        str_len = _strlen(datashell->args[1]);
        is_big_number = exit_status > (unsigned int)INT_MAX;

        if (!is_digit || str_len > 10 || is_big_number)
        {
            get_error(datashell, 2);
            datashell->stat = 2;
            return (1);
        }

        datashell->stat = (exit_status % 256);
    }
    return (0);
}

/**
 * execute_line - Executes a command line.
 * @datash: Data structure for the shell.
 *
 * Return: Returns 1 on success, 0 on failure.
 */
int execute_line(shll_comm *datash)
{
    int (*builtin)(shll_comm *datash);

    if (datash->args[0] == NULL)
        return (1);

    builtin = get_builtin(datash->args[0]);

    if (builtin != NULL)
        return (builtin(datash));

    return (command_exec(datash));
}

/**
 * err_environ - Generates an error message related to environment variables.
 * @data_sh: Data structure for the shell.
 *
 * Return: Returns the error message.
 */
char *err_environ(shll_comm *data_sh)
{
    int length;
    char *error, *text, *vstr;

    vstr = conv_itoa(data_sh->counter);
    text = ": Unable to add/remove from environment\n";
    length = _strlen(data_sh->argv[0]) + _strlen(vstr);
    length += _strlen(data_sh->args[0]) + _strlen(text) + 4;

    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(error);
        free(vstr);
        return (NULL);
    }

    _strcpy(error, data_sh->argv[0]);
    _strcat(error, ": ");
    _strcat(error, vstr);
    _strcat(error, ": ");
    _strcat(error, data_sh->args[0]);
    _strcat(error, text);
    _strcat(error, "\0");
    free(vstr);

    return (error);
}

/**
 * err_path126 - Generates an error message for permission denied.
 * @data_sh: Data structure for the shell.
 *
 * Return: Returns the error message.
 */
char *err_path126(shll_comm *data_sh)
{
    int length;
    char *vstr, *error;

    vstr = conv_itoa(data_sh->counter);
    length = _strlen(data_sh->argv[0]) + _strlen(vstr);
    length += _strlen(data_sh->args[0]) + 24;

    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(error);
        free(vstr);
        return (NULL);
    }

    _strcpy(error, data_sh->argv[0]);
    _strcat(error, ": ");
    _strcat(error, vstr);
    _strcat(error, ": ");
    _strcat(error, data_sh->args[0]);
    _strcat(error, ": Permission denied\n");
    _strcat(error, "\0");
    free(vstr);

    return (error);
}

/**
 * conc_err_msg - Concatenates error message.
 * @data_sh: Data structure for the shell.
 * @disp_msg: Display message.
 * @err: Error message.
 * @vstr: Version string.
 *
 * Return: Returns the concatenated error message.
 */
char *conc_err_msg(shll_comm *data_sh, char *disp_msg, char *err, char *vstr)
{
    char *illegal_flag;

    _strcpy(err, data_sh->argv[0]);
    _strcat(err, ": ");
    _strcat(err, vstr);
    _strcat(err, ": ");
    _strcat(err, data_sh->args[0]);
    _strcat(err, disp_msg);

    if (data_sh->args[1][0] == '-')
    {
        illegal_flag = malloc(3);
        illegal_flag[0] = '-';
        illegal_flag[1] = data_sh->args[1][1];
        illegal_flag[2] = '\0';
        _strcat(err, illegal_flag);
        free(illegal_flag);
    }
    else
    {
        _strcat(err, data_sh->args[1]);
    }

    _strcat(err, "\n");
    _strcat(err, "\0");
    return (err);
=======
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
>>>>>>> 28ae644db923355e8dd413330740df4c531cecb0
}
