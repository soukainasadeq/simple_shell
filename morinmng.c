#include "main.h"

/**
 * add_ln_nd_end -Adds a command line at the end of a line
 * @hd: the header of the linked list.
 * @cmd_line: Cmd line.
 * Return: Address of the header.
 */
line_list *add_ln_nd_end(line_list **hd, char *cmd_line)
{
	line_list *new, *tp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = cmd_line;
	new->next = NULL;
	tp = *hd;

	if (tp == NULL)
	{
		*hd = new;
	}
	else
	{
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = new;
	}

	return (*hd);
}

/**
 * free_line_ls - line list.
 * @hd: header.
 *
 * Return: void.
 */
void free_line_ls(line_list **hd)
{
	line_list *tp;
	line_list *curt;

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

/**
 * add_node_en - gggggggrvvvvv
 * @hd: Header gggggg.
 * @sp: Sep (; | &).
 *
 * Return: addr.
 */
sep_list *add_node_en(sep_list **hd, char sp)
{
	sep_list *new_sp, *tp;

	new_sp = malloc(sizeof(sep_list));
	if (new_sp == NULL)
		return (NULL);

	new_sp->sep = sp;
	new_sp->next = NULL;
	tp = *hd;

	if (tp == NULL)
	{
		*hd = new_sp;
	}
	else
	{
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = new_sp;
	}

	return (*hd);
}

/**
 * free_sp_ls - pffffffff.
 * @hd: erheadr list.
 *
 * Return: void.
 */
void free_sp_ls(sep_list **hd)
{
	sep_list *tp;
	sep_list *curt;

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
