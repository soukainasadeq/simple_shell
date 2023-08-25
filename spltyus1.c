#include "main.h"

/**
 * move_nxt -  Move to the next cmd.
 * @lis_s: Sedjparator list.
 * @lis_l: Command line list.
 * @data_shell: Data structure.
 * Return: No return value.
 */
void move_nxt(sep_list **lis_s, line_list **lis_l, shll_comm *data_shell)
{
	int lop_s;
	sep_list *lst_s;
	line_list *lst_l;

	lop_s = 1;
	lst_s = *lis_s;
	lst_l = *lis_l;

	while (lst_s != NULL && lop_s)
	{
		if (data_shell->stat == 0)
		{
			if (lst_s->sep == '&' || lst_s->sep == ';')
				lop_s = 0;
			if (lst_s->sep == '|')
				lst_l = lst_l->next, lst_s = lst_s->next;
		}
		else
		{
			if (lst_s->sep == '|' || lst_s->sep == ';')
				lop_s = 0;
			if (lst_s->sep == '&')
				lst_l = lst_l->next, lst_s = lst_s->next;
		}
		if (lst_s != NULL && !lop_s)
			lst_s = lst_s->next;
	}
	*lis_s = lst_s;
	*lis_l = lst_l;
}

/**
 * swp_character - weSwaps characters
 * @inp: string input.
 * @boolean: Type of swap
 * Return: swpstring.
 */
char *swp_character(char *inp, int boolean)
{
	int y;

	if (boolean == 0)
	{
		for (y = 0; inp[y]; y++)
		{
			if (inp[y] == '|')
			{
				if (inp[y + 1] != '|')
					inp[y] = 16;
				else
					y++;
			}

			if (inp[y] == '&')
			{
				if (inp[y + 1] != '&')
					inp[y] = 12;
				else
					y++;
			}
		}
	}
	else
	{
		for (y = 0; inp[y]; y++)
		{
			inp[y] = (inp[y] == 16 ? '|' : inp[y]);
			inp[y] = (inp[y] == 12 ? '&' : inp[y]);
		}
	}
	return (inp);
}

/**
 * add_nd - Adds sepa
 * @hd_s: separator list.
 * @hd_l: command list.
 * @inp: string input.
 *
 * Return: nothing.
 */
void add_nd(sep_list **hd_s, line_list **hd_l, char *inp)
{
	int y;
	char *cmd_line;

	inp = swp_character(inp, 0);

	for (y = 0; inp[y]; y++)
	{
		if (inp[y] == ';')
			add_node_en(hd_s, inp[y]);

		if (inp[y] == '|' || inp[y] == '&')
		{
			add_node_en(hd_s, inp[y]);
			y++;
		}
	}

	cmd_line = _strtok(inp, ";|&");
	do {
		cmd_line = swp_character(cmd_line, 1);
		add_ln_nd_end(hd_l, cmd_line);
		cmd_line = _strtok(NULL, ";|&");
	} while (cmd_line != NULL);
}

/**
 * read_line - string read.
 * @int_eof: ykfkhfgvh.
 *
 * Return: none.
 */
char *read_line(int *int_eof)
{
	char *ip = NULL;
	size_t buf = 0;

	*int_eof = getline(&ip, &buf, stdin);

	return (ip);
}

/**
 * free_value_ls - r_var list.
 * @hd: list.
 * Return: Nom.
 */
void free_value_ls(r_var **hd)
{
	r_var *tp;
	r_var *curt;

	if (hd != NULL)
	{
		curt = *hd;
		while ((tp = curt) != NULL)
		{
			curt = curt->next;
			free(tp);
		}
		*hd = NULL;
	}
}
