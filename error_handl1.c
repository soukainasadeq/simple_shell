#include "main.h"

/**
 * Identify the first significant character.
 * @inp: Input string.
 * @index: Index variable.
 *
 * Return: 0 or 1.
 */
int first_significant_character(char *inp, int *index)
{
    for (*index = 0; inp[*index]; *index += 1)
    {
        if (inp[*index] == ' ' || inp[*index] == '\t')
            continue;

        if (inp[*index] == ';' || inp[*index] == '|' || inp[*index] == '&')
            return (-1);

        break;
    }

    return (0);
}

/**
 * Display syntax error message.
 * @data_sh: Shell data structure.
 * @inp: Input string.
 * @index: Index.
 * @boolean: Flag to control.
 *
 * Return: void value.
 */
void display_syntax_error(shll_comm *data_sh, char *inp, int index, int boolean)
{
    char *message, *message2, *message3, *error, *counter;
    int len;

    if (inp[index] == ';')
    {
        if (boolean == 0)
            message = (inp[index + 1] == ';' ? ";;" : ";");
        else
            message = (inp[index - 1] == ';' ? ";;" : ";");
    }

    if (inp[index] == '|')
        message = (inp[index + 1] == '|' ? "||" : "|");

    if (inp[index] == '&')
        message = (inp[index + 1] == '&' ? "&&" : "&");

    message2 = ": Syntax error: \"";
    message3 = "\" unexpected\n";
    counter = conv_itoa(data_sh->counter);
    len = _strlen(data_sh->argv[0]) + _strlen(counter);
    len += _strlen(message) + _strlen(message) + _strlen(message) + 2;

    error = malloc(sizeof(char) * (len + 1));
    if (error == 0)
    {
        free(counter);
        return;
    }
    _strcpy(error, data_sh->argv[0]);
    _strcat(error, ": ");
    _strcat(error, counter);
    _strcat(error, message2);
    _strcat(error, message);
    _strcat(error, message3);
    _strcat(error, "\0");

    write(STDERR_FILENO, error, len);
    free(error);
    free(counter);
}

/**
 * Check syntax errors related to separators.
 * @data_sh: Shell data structure.
 * @input_str: Input string.
 *
 * Return: 1 or 0.
 */
int check_separator_syntax_error(shll_comm *data_sh, char *input_str)
{
    int begin = 0, first_char = 0, ind = 0;

    first_char = first_significant_character(input_str, &begin);
    if (first_char == -1)
    {
        display_syntax_error(data_sh, input_str, begin, 0);
        return (1);
    }

    ind = separator_operator_error(input_str + begin, 0, *(input_str + begin));
    if (ind != 0)
    {
        display_syntax_error(data_sh, input_str, begin + ind, 1);
        return (1);
    }

    return (0);
}

/**
 * Count consecutive duplicated characters.
 * @inp: String.
 * @index: Index to check.
 *
 * Return: Number of consecutive duplicates.
 */
int count_consecutive_duplicates(char *inp, int index)
{
    if (*(inp - 1) == *inp)
        return (count_consecutive_duplicates(inp - 1, index + 1));

    return (index);
}

/**
 * Check for syntax errors related to separator operators.
 * @inp: String.
 * @index: Index to check.
 * @last_char: Last character.
 *
 * Return: The index of the error. Returns 0 when there are no errors.
 */
int separator_operator_error(char *inp, int index, char last_char)
{
    int count = 0;

    if (*inp == '\0')
        return (0);

    if (*inp == ' ' || *inp == '\t')
        return (separator_operator_error(inp + 1, index + 1, last_char));

    if (*inp == ';')
        if (last_char == '|' || last_char == '&' || last_char == ';')
            return (index);

    if (*inp == '|')
    {
        if (last_char == ';' || last_char == '&')
            return (index);

        if (last_char == '|')
        {
            count = count_consecutive_duplicates(inp, 0);
            if (count == 0 || count > 1)
                return (index);
        }
    }

    if (*inp == '&')
    {
        if (last_char == ';' || last_char == '|')
            return (index);

        if (last_char == '&')
        {
            count = count_consecutive_duplicates(inp, 0);
            if (count == 0 || count > 1)
                return (index);
        }
    }

    return (separator_operator_error(inp + 1, index + 1, *inp));
}
