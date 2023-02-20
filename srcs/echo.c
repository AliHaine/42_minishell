#include "minishell.h"

/* bulltin echo part 2 */

int echo_2(char **tab, int bulltin)
{
	int i;
	int x;

	i = 1;
	x = 2;
	if (tab[i][0] == '-' && tab[i][1] == 'n')
	{
		bulltin = 1;
		while (tab[i][x])
		{
			if (tab[i][x] == 'n')
				x++;
			else
			{
				return (0);
			}
		}
	}
	return (1);
}

/* bulltin echo */

void echo(char **tab)
{
	int i;
	int bulltin;

	i = 1;
	bulltin = echo_2(tab, bulltin);

	if (bulltin == 1)
		i++;
	while (tab[i])
	{
		printf("%s", tab[i++]);
		if (tab[i])
			printf(" ");
	}
	if (bulltin == 0)
		printf("\n");
}