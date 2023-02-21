//
// Created by Ali Yagmur on 2/20/23.
//

#ifndef MINISHELL_H
#define MINISHELL_H

# include "utils/get_next_line/get_next_line.h"
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

struct s_minishell
{
	struct sigaction	sig;
	int 				histo_fd;
	char				**env;
	int 				exit;
}	t_minishell;

void	ctrl_c();
void	ctrl_d();
void	go_to_end_of_file(int fd);
bool	write_to_histo(char *str, int fd);
bool	is_space(char c);

/* utils */

// ft_split //

char	**ft_split(char *s, char c);

// check_all_cmd //

int	ft_strcmp(char *a, char *b);
void check_all_cmd(char *line);

/* bulltin */

// exit //

void exit_shell(void);

// pwd //

void pwd(void);

// echo //

void echo(char **tab);

#endif
