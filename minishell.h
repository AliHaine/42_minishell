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

// little_func //

bool	is_space(char c);
bool	is_blank(char *str);
void	free_tt(char **str);

// pipe_manager //

bool	pipe_main(struct s_minishell *ms, char *cmds);

// utils //

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);

// ft_split //

char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);

// check_all_cmd //

int	ft_strcmp(char *a, char *b);
int get_cmd(char *cmd);
void check_all_cmd(char *line, char **env, struct s_minishell *ms);

/* bulltin */

// exit //

void exit_shell(void);

// pwd //

void pwd(void);
char *g_d_e(void);

/* 

en cour

void trime_quotation(char *str);

*/

// echo //

void echo(char **tab);

// env //

void print_env(char **env);

// unset //

int unset(char *path, char **env, int i);

// export //

void export(char **argv, char **env);

// cd //

int cd(char **cmd, char **env);

#endif
