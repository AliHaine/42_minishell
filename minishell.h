//
// Created by Ali Yagmur on 2/20/23.
//

#ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/readline.h>
# include "utils/get_next_line/get_next_line.h"
# include <stdbool.h>
# include <fcntl.h>

struct s_minishell
{
	struct sigaction	sig;
	int 				histo_fd;
	char				**env;
	int 				exit;
}	t_minishell;

void	ctrl_c();
void	go_to_end_of_file(int fd);
bool	write_to_histo(char *str, int fd);
bool	is_space(char c);

#endif
