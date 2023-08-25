#include "main.h"

/**
 * disp_help_general - ggggggggggg gggjjgggdgggg gg gggggggggggg gggggggg ggggg
 *
 * Return: Vggg
 */
void disp_help_general(void)
{
	char *hep = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "unsetenv [variable]\n";
	write(STDOUT_FILENO, hep, _strlen(hep));
}
/**
 * disp_help_exit - hhhhhhhhhhhhhhhhh hhhhhhhhhhh vavhbjt
 *
 * Return: Vddd
 */
void disp_help_exit(void)
{
	char *hep = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, hep, _strlen(hep));
}

/**
 * display_unsetenv - ccccccccc cccbbbbb bbbbbbbbbb bbbbbbbbbbn
 *
 * Return: Vxxx
 */
void display_unsetenv(void)
{
	char *hep = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, hep, _strlen(hep));
	hep = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, hep, _strlen(hep));
}

/**
 * get_sigint - xxxxxxxxxxx xxxxxxxx xxxxxxxxxxx x
 * @sig: xxxxxxxxxndler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * get_ln - zzzzzzzzz zzzzzz z zzzzzzzzzzzzze
 * @lnptr: Pzzzzzzzzzz zzzzzzzzzariable
 * @num: Poinzzzzzzzzz zzzzz of zzzzzzzzzzble
 * @buf: String thabbbbb bbbbbbbbbbbb bbbbbbbe
 * @size_b: gggggg ggggg bbbbr
 * Return: nothing
 */
void get_ln(char **lnptr, size_t *num, char *buf, size_t size_b)
{

	if (*lnptr == NULL)
	{
		if (size_b > BUFSIZE)
			*num = size_b;

		else
			*num = BUFSIZE;
		*lnptr = buf;
	}
	else if (*num < size_b)
	{
		if (size_b > BUFSIZE)
			*num = size_b;
		else
			*num = BUFSIZE;
		*lnptr = buf;
	}
	else
	{
		_strcpy(*lnptr, buf);
		free(buf);
	}
}
