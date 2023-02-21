#include "../minishell.h"

/* -n -n -n -n error */

/* bulltin echo part 2 */

static int echo_2(char **tab, int bulltin)
{
	int i;
	int x;

	i = bulltin + 1;
	x = 2;
	if (tab[i][0] == '-' && tab[i][1] == 'n')
	{
		while (tab[i][x])
		{
			if (tab[i][x] == 'n')
				x++;
			else
			{
				return (bulltin);
			}
		}
		return (echo_2(tab, bulltin + 1));
	}
	return (bulltin);
}

// bulltin echo

void echo(char **tab)
{
	int i;
	int bulltin;

	i = 1;
	bulltin = 0;
	if(!tab[i])
	{
		printf("\n");
		return ;
	}
	bulltin = echo_2(tab, bulltin);
	printf("bulltin = %d\n", bulltin);
	if (bulltin > 0)
		i += bulltin;
	while (tab[i])
	{
		printf("%s", tab[i++]);
		if (tab[i])
			printf(" ");
	}
	if (bulltin == 0)
		printf("\n");
}