/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:55:32 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/28 15:36:09 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils/get_next_line/get_next_line.h"
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

typedef struct s_minishell
{
	int					histo_fd;
	char				**env;
	char				**bash;
	int					exit;
	int					stat;
	int					cmd_nbr;
	struct s_cmds		*cmds_f;
}	t_minishell;

typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	char			*cmd_args;
	int				w;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_three_int
{
	int	a;
	int	b;
	int	c;
}	t_t_i;

t_minishell	g_ms;

void		ctrl_c(void);
void		ctrl_bs(void);
void		go_to_end_of_file(int fd);
bool		write_to_histo(char *str, int fd);
bool		main_parsing(char *line);

// little_func //

int			get_origine(char *cmds);
bool		is_redir_char(char c);

// very_little_func //

void		init_three_int(struct s_three_int *ti);
int			free_str_rzero(char *str);
bool		is_space(char c);
bool		is_contain_pipe(char *str);
bool		is_pipe_or_redir(char c);

// error_manager //

int			check_all(char *cmds, struct s_three_int ti);
bool		check_all_quote(struct s_cmds *ti, int i, int size);
bool		check_error_redir(t_cmds *cmd);

// manager //

bool		pipe_main(void);
bool		redirection_main(int pipes[][2], t_cmds *cmd, t_t_i ti);
bool	is_unused(t_cmds *cmds);

// pipe_utils //

bool		pipe_init(int pipes[][2]);
void		close_all_pipes(int pipes[][2]);

// redir utile //

void		write_to_file(int fd, char *s);

// parse_utils //

char		*ft_strjoin_parse(char *s1, char *s2);
char		*get_current_word(char *s, int *a);
int			get_args_size(char **args);

// cmds_struct //

void		connect_struct(t_cmds *new);
void		free_words_struct(struct s_cmds *cmds);
void		parc_struct_tester(struct s_cmds *cmds);

// utils //

char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strcmp(char *a, char *b);
int			check_is_empty(char *str);
void		ft_putstr(char *s, int fd);
void		free_tt(char **str);

// utils2 //

int			check_path(char *argv, char **env, int n);
int			ft_tablen(char **tab);
int			char_cmp(char *str, char *reject);

// utils3 //

int			str_copy(char *dst, char *src, int size);
char		**copy_env(char **env, int size);
char		**print_sorted_strings(char **env, int size);
char		*ft_join(char *s1, char *s2);
char		*ft_sjoin(char *s1, char *s2);

// ft_split //

char		*ft_strdup(const char *s1);
char		**ft_split(char *s, char c);

// ft_itoa + ft_atoi //

char		*ft_itoa(int nbr);
int			ft_atoi(const char *str);

// check_all_cmd //

int			get_cmd(char *cmd);
void		check_all_cmd(t_cmds *cmd);

// trime_quotation //

int			update(char c, int *in_q);
int			var_c(char *s, int i);

// Env_conv //

char		*env_conversion(char *str, char **env, int i, int j);
int			simp_char(char c, char *reject);

/* bulltin */

// execve //

int			ft_execve(t_cmds *cmd, char **env);

// exit //

int			check_exit(char *h);
int			check_cmd_is_right(int fd);
char		*histo_pars(char *histo);

// pwd //

void		pwd(void);
char		*g_d_e(void);
char		*gde(void);
char		*g_pwd(void);

// echo //

void		echo(char **tab, char **env, int i, int j);

// env //

void		print_env(char **env);
char		*ft_getenv(char **env, char *path);

// unset //

int			unset(char **path, char **env, int i, int x);

// export //

void		export(char *cmd, char **arg,char **env, int i);
char		*remplace_env(char **env, char *path);

// cd //

int	cd(char *cmd, char **arg, char **env);

#endif
