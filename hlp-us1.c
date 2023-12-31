#include "main.h"

/**
 * disp_help_cd - displajy help information.
 *
 * Return: none
 */
void disp_help_cd(void)
{
	char *hlp = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help_alias - display Help information.
 *
 * Return: void
 */
void disp_help_alias(void)
{
	char *hlp = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help - display Help information.
 *
 * Return: void
 */
void disp_help(void)
{
	char *hlp = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help_env - display Help information env
 *
 * Return: void
 */
void disp_help_env(void)
{
	char *hlp = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help_setenv - display Help information buil setenv
 *
 * Return: no return
 */
void disp_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
