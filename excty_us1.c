#include "main.h"

/**
 * Search for a command in the environment.
 * @command: Name of the command.
 * @_env: Environment variables.
 *
 * Return: Path of the command or NULL.
 */
char *_whch(char *command, char **_env)
{
    char *path_name, *ptrpath, *tkn_path, *directory;
    int ln_dir, ln_cmd, ind;
    struct stat st;

    path_name = get_environ("PATH", _env);
    if (path_name)
    {
        ptrpath = _strdup(path_name);
        ln_cmd = _strlen(command);
        tkn_path = _strtok(ptrpath, ":");
        ind = 0;
        while (tkn_path != NULL)
        {
            if (check_current_directory(path_name, &ind))
                if (stat(command, &st) == 0)
                    return (command);
            ln_dir = _strlen(tkn_path);
            directory = malloc(ln_dir + ln_cmd + 2);
            _strcpy(directory, tkn_path);
            _strcat(directory, "/");
            _strcat(directory, command);
            _strcat(directory, "\0");
            if (stat(directory, &st) == 0)
            {
                free(ptrpath);
                return (directory);
            }
            free(directory);
            tkn_path = _strtok(NULL, ":");
        }
        free(ptrpath);
        if (stat(command, &st) == 0)
            return (command);
        return (NULL);
    }
    if (command[0] == '/')
        if (stat(command, &st) == 0)
            return (command);
    return (NULL);
}

/**
 * Check if a directory exists in the PATH.
 * @filepath: Path pointer.
 * @index: Index to check.
 *
 * Return: 1 if the directory exists, 0 otherwise.
 */
int check_current_directory(char *filepath, int *index)
{
    if (filepath[*index] == ':')
        return (1);

    while (filepath[*index] != ':' && filepath[*index])
    {
        *index += 1;
    }

    if (filepath[*index])
        *index += 1;

    return (0);
}

/**
 * Check for errors related to command permissions.
 * @dir_dest: Destination directory.
 * @datashell: Data struct.
 *
 * Return: 1 if there's an error, 0 otherwise.
 */
int check_error_command(char *dir_dest, shll_comm *datashell)
{
    if (dir_dest == NULL)
    {
        get_error(datashell, 127);
        return (1);
    }

    if (_strcmp(datashell->args[0], dir_dest) != 0)
    {
        if (access(dir_dest, X_OK) == -1)
        {
            get_error(datashell, 126);
            free(dir_dest);
            return (1);
        }
        free(dir_dest);
    }
    else
    {
        if (access(datashell->args[0], X_OK) == -1)
        {
            get_error(datashell, 126);
            return (1);
        }
    }

    return (0);
}

/**
 * Execute a command.
 * @datashell: Relevant data.
 *
 * Return: 1 on success, 0 on failure.
 */
int command_exec(shll_comm *datashell)
{
    pid_t pidm, wpid;
    int stt, ex;
    char *dire;
    (void)wpid;

    ex = is_executable(datashell);
    if (ex == -1)
        return (1);
    if (ex == 0)
    {
        dire = _whch(datashell->args[0], datashell->_env);
        if (check_error_command(dire, datashell) == 1)
            return (1);
    }

    pidm = fork();
    if (pidm == 0)
    {
        if (ex == 0)
            dire = _whch(datashell->args[0], datashell->_env);
        else
            dire = datashell->args[0];
        execve(dire + ex, datashell->args, datashell->_env);
    }
    else if (pidm < 0)
    {
        perror(datashell->argv[0]);
        return (1);
    }
    else
    {
        do {
            wpid = waitpid(pidm, &stt, WUNTRACED);
        } while (!WIFEXITED(stt) && !WIFSIGNALED(stt));
    }

    datashell->stat = stt / 256;

    return (1);
}

/**
 * Determine if a command is executable.
 * @datashell: Data structure.
 *
 * Return: 0 if it's not executable, otherwise a positive number.
 */
int is_executable(shll_comm *datashell)
{
    struct stat status;
    int ind;
    char *inp;

    inp = datashell->args[0];
    for (ind = 0; inp[ind]; ind++)
    {
        if (inp[ind] == '.')
        {
            if (inp[ind + 1] == '.')
                return (0);
            if (inp[ind + 1] == '/')
                continue;
            else
                break;
        }
        else if (inp[ind] == '/' && ind != 0)
        {
            if (inp[ind + 1] == '.')
                continue;
            ind++;
            break;
        }
        else
            break;
    }
    if (ind == 0)
        return (0);

    if (stat(inp + ind, &status) == 0)
        return (ind);
    get_error(datashell, 127);

    return (-1);
}
