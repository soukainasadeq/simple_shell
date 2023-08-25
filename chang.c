#include "main.h"

/**
 * changedir_shell - switch the curr directory.
 * @data_sh: data shell
 *
 * Return: 1 or 0.
 */
int changedir_shell(shll_comm *data_sh)
{
	int inh1, inh2, isd;
	char *directory = data_sh->args[1];

	if (directory != NULL)
	{
		inh1 = _strcmp("$HOME", directory);
		inh2 = _strcmp("~", directory);
		isd = _strcmp("--", directory);
	}

	if (directory == NULL || !inh1 || !inh2 || !isd)
	{
		changedir_to_home(data_sh);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		changedir_prev(data_sh);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		chandir_dor(data_sh);
		return (1);
	}

	cd_to_dist(data_sh);

	return (1);
}
/**
 * chandir_dor - switch to the parent dir.
 * @data_sh: Point data structure
 *
 * Return: void value.
 */
void chandir_dor(shll_comm *data_sh)
{
	char pwd[PATH_MAX];
	char *directory, *chp_printwd, *chp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	chp_printwd = _strdup(pwd);
	set_env("OLDPWD", chp_printwd, data_sh);
	directory = data_sh->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", chp_printwd, data_sh);
		free(chp_printwd);
		return;
	}
	if (_strcmp("/", chp_printwd) == 0)
	{
		free(chp_printwd);
		return;
	}
	chp_strtok_pwd = chp_printwd;
	rev_string(chp_strtok_pwd);
	chp_strtok_pwd = _strtok(chp_strtok_pwd, "/");
	if (chp_strtok_pwd != NULL)
	{
		chp_strtok_pwd = _strtok(NULL, "\0");

		if (chp_strtok_pwd != NULL)
			rev_string(chp_strtok_pwd);
	}
	if (chp_strtok_pwd != NULL)
	{
		chdir(chp_strtok_pwd);
		set_env("PWD", chp_strtok_pwd, data_sh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data_sh);
	}
	data_sh->stat = 0;
	free(chp_printwd);
}

/**
 * cd_to_dist - switch to a dir.
 * @data_sh: Pointer to the data struct
 *
 * Return: none value.
 */
void cd_to_dist(shll_comm *data_sh)
{
	char printwd[PATH_MAX];
	char *directory, *ch_pwd, *ch_dir;

	getcwd(printwd, sizeof(printwd));

	directory = data_sh->args[1];
	if (chdir(directory) == -1)
	{
		get_err(data_sh, 2);
		return;
	}

	ch_pwd = _strdup(printwd);
	set_env("OLDPWD", ch_pwd, data_sh);

	ch_dir = _strdup(directory);
	set_env("PWD", ch_dir, data_sh);

	free(ch_pwd);
	free(ch_dir);

	data_sh->stat = 0;

	chdir(directory);
}

/**
 * changedir_prev - switch to the pre directory jjl.
 * @data_sh: Data shell
 *
 * Return: none value.
 */
void changedir_prev(shll_comm *data_sh)
{
	char pwd[PATH_MAX];
	char *w_pwd, *w_oldpwd, *ch_pwd, *ch_oldpwd;

	getcwd(pwd, sizeof(pwd));
	ch_pwd = _strdup(pwd);

	w_oldpwd = get_environ("OLDPWD", data_sh->_env);

	if (w_oldpwd == NULL)
		ch_oldpwd = ch_pwd;
	else
		ch_oldpwd = _strdup(w_oldpwd);

	set_env("OLDPWD", ch_pwd, data_sh);

	if (chdir(ch_oldpwd) == -1)
		set_env("PWD", ch_pwd, data_sh);
	else
		set_env("PWD", ch_oldpwd, data_sh);

	w_pwd = get_environ("PWD", data_sh->_env);

	write(STDOUT_FILENO, w_pwd, _strlen(w_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(ch_pwd);
	if (w_oldpwd)
		free(ch_oldpwd);

	data_sh->stat = 0;

	chdir(w_pwd);
}
/**
 * changedir_to_home - switch to the home dir.
 * @data_sh: Data relevant to the env.
 *
 * Return: void value.
 */
void changedir_to_home(shll_comm *data_sh)
{
	char *print_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	print_pwd = _strdup(pwd);

	home = get_environ("HOME", data_sh->_env);

	if (home == NULL)
	{
		set_env("OLDPWD", print_pwd, data_sh);
		free(print_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_err(data_sh, 2);
		free(print_pwd);
		return;
	}

	set_env("OLDPWD", print_pwd, data_sh);
	set_env("PWD", home, data_sh);
	free(print_pwd);
	data_sh->stat = 0;
}
