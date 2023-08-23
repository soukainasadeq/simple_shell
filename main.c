#include "main.h"

/**
 * main - hello boys
 * @argc: hhhhhhhhh babay.
 * @argv: hhhhhhh saraha.
 *
 * Return: maso9akchs.
 */
int main(int argc, char **argv)
{
	shll_comm datash;
	(void)argc;

	signal(SIGINT, get_sigint);
	set_datashell(&datash, argv);
	looping_shll(&datash);
	empty_data(&datash);
	if (datash.stat < 0)
		return (255);
	return (datash.stat);
}
