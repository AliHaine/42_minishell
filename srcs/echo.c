#include "../minishell.h"

// guillemet // 

/* var type $PATH and var '"$PATH"' 'PATH' */

/* trime cote */

static int get_env_var(char **env, char *var)
{
	int len;
	int i;
	int j;

	j = 0;
	len = 0;
	i = 0;
	while (var[j] != '=' && var[j])
		j++;
	while (env[i])
	{
		len = 0;
		while (var[len])
		{
			if (env[i][len] && env[i][len] == var[len])
				len++; 
			else
				break;
			if (env[i][len] && env[i][len] == '=' && len < j)
				return (1);
		}
		i++;
	}
	return (0);
}

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

	// pour les guillemet : en cour //

	/*while (tab[i])
		trime_quotation(tab[i++]);*/
	i = 1;
	bulltin = echo_2(tab, bulltin);
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