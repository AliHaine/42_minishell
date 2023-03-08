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
# include <dirent.h>
#include <string.h>
#include <errno.h>

struct s_minishell
{
	struct sigaction	sig;
	int 				histo_fd;
	char				**env;
	int 				exit;
	struct s_cmds	*cmds_f;
}	t_minishell;

struct s_cmds
{
	char *cmd;
	int w;
	struct s_cmds *next;
	struct s_cmds *prev;
}	t_cmds;

struct s_three_int
{
	int	a;
	int b;
	int c;
}	t_three_int;

void	ctrl_c();
void	ctrl_d();
void	go_to_end_of_file(int fd);
bool	write_to_histo(char *str, int fd);

// little_func //

bool	is_blank(char *str);
int get_allstr_word_size(char *str);
int get_origine(char *cmds);

// very_little_func //

void	init_three_int(struct s_three_int *ti);
int	free_str_rzero(char *str);
bool	is_space(char c);
void	free_tt(char **str);
bool	is_contain_pipe(char *str);
bool is_pipe_or_et(char c);

// error_manager //

int check_all(char *cmds, struct s_three_int ti);
int	check_all_pipe_cmds(char *cmds, struct s_three_int ti);
bool	check_all_quote(struct s_cmds *ti);

// pipe_manager //

bool	pipe_main(struct s_minishell *ms, char *cmds);

// pipe_utils //

char *get_cmds_path(char *cmds);
char **get_args_cmds(char *cmds);
int get_cmd_pipe(char *cmd);

// cmds_struct //

void	free_words_struct(struct s_cmds *cmds);
bool	new_words_node(struct s_cmds *cmds, char *str, int size);
int 	get_nbr_of_cmds(struct s_cmds *cmds);
bool	first_words_node(struct s_cmds *cmds, char *str, int size);
void	parc_struct_tester(struct s_cmds *cmds);

// utils //

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strcmp(char *a, char *b);

// utils2 //

int	str_copy(char *dst, char *src, int size);
//int check_path(char *argv, char **env, int n);
int ft_tablen(char **tab);
int char_cmp(char *str, char *reject);
void	*ft_memmove(void *dst, const void *src, size_t len);

// ft_split //

char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);

// check_all_cmd //

int get_cmd(char *cmd);
void check_all_cmd(char *line, char **env, struct s_minishell *ms);

// trime_quotation //

void convert_quotes(char *str);

// Env_conv //

char *env_conversion(char *str, char **env);
int simp_char(char c, char *reject);

/* bulltin */

// exit //

void exit_shell(void);

// pwd //

void pwd(void);
char *g_d_e(void);

// echo //

void echo(char **tab, char **env);

// env //

void print_env(char **env);
char *ft_getenv(char **env, char *path);

// unset //

int unset(char **path, char **env, int i, int x);

// export //

void export(char **argv, char **env, int i);

// cd //

int cd(char **cmd, char **env);

#endif
