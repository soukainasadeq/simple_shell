#include "main.h"

/**
 * splt_ln - split string.
 * @inp: Input string.
 * Return: String splitted.
 */
char **splt_ln(char *inp)
{
	size_t bsize;
	size_t y;
	char **toks;
	char *tok;

	bsize = TOK_BUFSIZE;
	toks = malloc(sizeof(char *) * (bsize));
	if (toks == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tok = _strtok(inp, TOK_DELIM);
	toks[0] = tok;

	for (y = 1; tok != NULL; y++)
	{
		if (y == bsize)
		{
			bsize += TOK_BUFSIZE;
			toks = _reallocdp(toks, y, sizeof(char *) * bsize);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tok = _strtok(NULL, TOK_DELIM);
		toks[y] = tok;
	}

	return (toks);
}

/**
 * split_cmds - command lines
 * @datashell: shell Data shell.
 * @inp: ggggggg.
 *
 * Return: 0 or 1.
 */
int split_cmds(shll_comm *datashell, char *inp)
{

	sep_list *hd_sp, *ls_sp;
	line_list *head_li, *list_li;
	int loop;

	hd_sp = NULL;
	head_li = NULL;

	add_nd(&hd_sp, &head_li, inp);

	ls_sp = hd_sp;
	list_li = head_li;

	while (list_li != NULL)
	{
		datashell->input = list_li->line;
		datashell->args = splt_ln(datashell->input);
		loop = execute_line(datashell);
		free(datashell->args);

		if (loop == 0)
			break;

		move_nxt(&ls_sp, &list_li, datashell);

		if (list_li != NULL)
			list_li = list_li->next;
	}

	free_sp_ls(&hd_sp);
	free_line_ls(&head_li);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * without_cmt - dgsgfDeletes comments.
 * @input: ttutu
 * Return: uuulu,b.
 */
char *without_cmt(char *input)
{
	int y, p_to;

	p_to = 0;
	for (y = 0; input[y]; y++)
	{
		if (input[y] == '#')
		{
			if (y == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[y - 1] == ' ' || input[y - 1] == '\t' || input[y - 1] == ';')
				p_to = y;
		}
	}

	if (p_to != 0)
	{
		input = _realloc(input, y, p_to + 1);
		input[p_to] = '\0';
	}

	return (input);
}

/**
 * looping_shll - uljjjlknknknhhh hhhhh
 * @data_shell: Dhhhhhhhhhhh hhhhhhh
 *
 * Return: hhhhhhhh hhhhh.
 */
void looping_shll(shll_comm *data_shell)
{
	int loop, int_f;
	char *ip;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		ip = read_line(&int_f);
		if (int_f != -1)
		{
			ip = without_cmt(ip);
			if (ip == NULL)
				continue;

			if (ch_syn_err(data_shell, ip) == 1)
			{
				data_shell->stat = 2;
				free(ip);
				continue;
			}
			ip = replace_str(ip, data_shell);
			loop = split_cmds(data_shell, ip);
			data_shell->counter += 1;
			free(ip);
		}
		else
		{
			loop = 0;
			free(ip);
		}
	}
}

/**
 * add_var_nd - hhhh hhh
 * @hd: kkk kkk
 * @lenvar: ss ssssss
 * @value: qqqq lllll
 * @lenval: ikn j;j
 *
 * Return: add.
 */
r_var *add_var_nd(r_var **hd, int lenvar, char *value, int lenval)
{
	r_var *newend, *tp;

	newend = malloc(sizeof(r_var));
	if (newend == NULL)
		return (NULL);

	newend->len_var = lenvar;
	newend->val = value;
	newend->len_val = lenval;

	newend->next = NULL;
	tp = *hd;

	if (tp == NULL)
	{
		*hd = newend;
	}
	else
	{
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = newend;
	}

	return (*hd);
}
