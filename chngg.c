#include "main.h"

/**
 * Change the current directory based on the arguments.
 * @data_sh: Shell data
 *
 * Returns: 1 or 0.
 */
int changedir_shell(shll_comm *data_sh)
{
	int is_home, is_tilde, is_double_dash;
	char *target_directory = data_sh->args[1];

	if (target_directory != NULL)
	{
		is_home = _strcmp("$HOME", target_directory);
		is_tilde = _strcmp("~", target_directory);
		is_double_dash = _strcmp("--", target_directory);
	}

	if (target_directory == NULL || !is_home || !is_tilde || !is_double_dash)
	{
		change_to_home_directory(data_sh);
		return (1);
	}

	if (_strcmp("-", target_directory) == 0)
	{
		change_to_previous_directory(data_sh);
		return (1);
	}

	if (_strcmp(".", target_directory) == 0 || _strcmp("..", target_directory) == 0)
	{
		change_to_parent_directory(data_sh);
		return (1);
	}

	change_to_specific_directory(data_sh);

	return (1);
}

/**
 * Change to the parent directory.
 * @data_sh: Pointer to the structure's data
 *
 * Returns: void.
 */
void change_to_parent_directory(shll_comm *data_sh)
{
	char current_path[PATH_MAX];
	char *target_directory, *prev_directory, *tokenized_path;

	getcwd(current_path, sizeof(current_path));
	prev_directory = _strdup(current_path);
	set_env("OLDPWD", prev_directory, data_sh);
	target_directory = data_sh->args[1];
	if (_strcmp(".", target_directory) == 0)
	{
		set_env("PWD", prev_directory, data_sh);
		free(prev_directory);
		return;
	}
	if (_strcmp("/", current_path) == 0)
	{
		free(prev_directory);
		return;
	}
	tokenized_path = prev_directory;
	rev_string(tokenized_path);
	tokenized_path = _strtok(tokenized_path, "/");
	if (tokenized_path != NULL)
	{
		tokenized_path = _strtok(NULL, "\0");

		if (tokenized_path != NULL)
			rev_string(tokenized_path);
	}
	if (tokenized_path != NULL)
	{
		chdir(tokenized_path);
		set_env("PWD", tokenized_path, data_sh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data_sh);
	}
	data_sh->stat = 0;
	free(prev_directory);
}

/**
 * Change to a specific directory.
 * @data_sh: Pointer to the data structure
 *
 * Returns: None.
 */
void change_to_specific_directory(shll_comm *data_sh)
{
	char current_path[PATH_MAX];
	char *target_directory, *current_directory, *new_directory;

	getcwd(current_path, sizeof(current_path));

	target_directory = data_sh->args[1];
	if (chdir(target_directory) == -1)
	{
		get_err(data_sh, 2);
		return;
	}

	current_directory = _strdup(current_path);
	set_env("OLDPWD", current_directory, data_sh);

	new_directory = _strdup(target_directory);
	set_env("PWD", new_directory, data_sh);

	free(current_directory);
	free(new_directory);

	data_sh->stat = 0;

	chdir(target_directory);
}
