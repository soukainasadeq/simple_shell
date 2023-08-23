#include "main.h"

/**
 * Generate a 404 error message.
 * @data_sh: Relevant data.
 * Return: Error message.
 */
char *error_404(shll_comm *data_sh)
{
    char *err_message, *vstr;
    int ln;

    vstr = conv_itoa(data_sh->counter);
    ln = _strlen(data_sh->argv[0]) + _strlen(vstr);
    ln += _strlen(data_sh->args[0]) + 16;
    err_message = malloc(sizeof(char) * (ln + 1));
    if (err_message == NULL)
    {
        free(err_message);
        free(vstr);
        return (NULL);
    }
    _strcpy(err_message, data_sh->argv[0]);
    _strcat(err_message, ": ");
    _strcat(err_message, vstr);
    _strcat(err_message, ": ");
    _strcat(err_message, data_sh->args[0]);
    _strcat(err_message, ": not found\n");
    _strcat(err_message, "\0");
    free(vstr);

    return (err_message);
}

/**
 * Generate a shell exit error message.
 * @data_sh: Shell data.
 * Return: Error message.
 */
char *error_shell_exit(shll_comm *data_sh)
{
    char *err_message, *vstr;
    int ln;

    vstr = conv_itoa(data_sh->counter);
    ln = _strlen(data_sh->argv[0]) + _strlen(vstr);
    ln += _strlen(data_sh->args[0]) + _strlen(data_sh->args[1]) + 23;
    err_message = malloc(sizeof(char) * (ln + 1));
    if (err_message == NULL)
    {
        free(vstr);
        return (NULL);
    }
    _strcpy(err_message, data_sh->argv[0]);
    _strcat(err_message, ": ");
    _strcat(err_message, vstr);
    _strcat(err_message, ": ");
    _strcat(err_message, data_sh->args[0]);
    _strcat(err_message, ": Illegal number: ");
    _strcat(err_message, data_sh->args[1]);
    _strcat(err_message, "\n\0");
    free(vstr);

    return (err_message);
}

/**
 * Generate a GCD error message.
 * @data_sh: Shell data.
 * Return: Error message.
 */
char *error_gcd(shll_comm *data_sh)
{
    char *err_message, *vstr, *error_msg;
    int ln, ld;

    vstr = conv_itoa(data_sh->counter);
    if (data_sh->args[1][0] == '-')
    {
        error_msg = ": Illegal option ";
        ld = 2;
    }
    else
    {
        error_msg = ": can't cd to ";
        ld = _strlen(data_sh->args[1]);
    }

    ln = _strlen(data_sh->argv[0]) + _strlen(data_sh->args[0]);
    ln += _strlen(vstr) + _strlen(error_msg) + ld + 5;
    err_message = malloc(sizeof(char) * (ln + 1));

    if (err_message == NULL)
    {
        free(vstr);
        return (NULL);
    }

    err_message = concatenate_error_message(data_sh, error_msg, err_message, vstr);

    free(vstr);

    return (err_message);
}
