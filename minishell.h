/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:55:32 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/11 18:06:53 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define P1 S_IRWXU
# define P2 S_IRWXG

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
	int					old;
	char				**bash;
	int					exit;
	int					stat;
	int					cmd_nbr;
	int 				on_cmd;
	struct s_cmds		*cmds_f;
	struct s_env		*list_env;
}	t_minishell;

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
	struct s_env	*past;
}	t_env;

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

typedef struct s_helper
{
	struct s_cmds	*t_c;
	t_t_i			ti;
}	t_helper;

typedef struct s_pipe
{
	pid_t		pid[20];
	int			pipefd[3][2];
	t_env		*l;
	t_t_i		ti;
}	t_pipe;

t_minishell	g_ms;

bool		pid_tab_growth(t_pipe *pipes, int val);
void		parse_helper(char *str);
void		ctrl_c(void);
void		ctrl_bs(void);
void		signal_main();
void		go_to_end_of_file(int fd);
void		histo_main(char *histo);
bool		main_parsing(char *line);

// little_func //

int			get_origine(char *cmds);
bool		is_redir_char(char c);

// very_little_func //

void		init_three_int(struct s_three_int *ti);
bool		is_space(char c);
void		add_env_var(t_env **lst, char *path);

// error_manager //

int			check_all(char *cmds, struct s_three_int ti);
bool		check_all_quote(struct s_cmds *ti, int i, int size);
bool		check_error_redir(t_cmds *cmd);

// manager //

bool		exec_manager(t_env *l);
void		origin_four_start(t_helper h, int pipes[][2], t_env *l, int fd);
void		r_exec_single(t_helper h, int origin, int fd, t_env *l);
void		r_exec(int pipes[][2], t_helper h, int origin, t_env *l);
bool		pipe_main(t_env *list);
void		redirection_main(int pipes[][2], t_cmds *cmd, t_t_i ti, t_env *l);
bool		is_unused(t_cmds *cmds);

// execution_utils //



// pipe_utils //

bool		pipe_init(int pipes[][2]);
void		close_all_pipes(int pipes[3][2]);
bool		is_unused(t_cmds *cmds);

// redir utile //

void		stdou_redirection(int origin, char *name);
void		stdin_redirection(int origin, char *name, char *cmd);

// parse_utils //

char		*ft_strjoin_parse(char *s1, char *s2);
char		*get_current_word(char *s, int *a, int i, int q);
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
int			check_path_lst(char *argv, t_env *lst, int n);;
int			char_cmp(char *str, char *reject);
int			char_ccmp(char c, char *reject);

// utils3 //

bool		single_fork(t_cmds *cmd, t_t_i ti, t_env *list);
char		**copy_env(t_env *list, int size);
char		*remplace_part(char *s, char *remplace, int start, int end);
char		**print_sorted_strings(t_env *list, int i, int j);
char		*ft_join(char *s1, char *s2);
char		*ft_sjoin(char *s1, char *s2);

// cd_utils //

char		*grattage(void);
void		get_free(char **get, int i);
char		**get_null(int i);

// ft_split //

char		*ft_strdup(const char *s1);
char		**ft_split(char *s, char c);

// ft_itoa + ft_atoi //

char		*ft_itoa(int nbr);
int			ft_atoi(const char *str);

// check_all_cmd //

int			get_cmd(char *cmd);
void		check_all_cmd(t_cmds *cmd, t_env *list);

// trime_quotation //

int			update(char c, int *in_q);
int			var_c(char *s, int i);

// Env_conv //

char		*env_conversion(char *str, char **env, int i, int j);
int			simp_char(char c, char *reject);

/* bulltin */

// execve //

int			ft_execve(t_cmds *cmd, t_env *lst);

// exit //

int			check_exit(t_cmds *cmd);
int			check_cmd_is_right(int fd);
char		*histo_pars(char *histo);

// pwd //

void		pwd(void);
char		*g_d_e(void);
char		*gde(void);
char		*g_pwd(void);

// echo //

void		echo(char **tab, int i, int j);
t_env		*lst_copy_tab(char **env);

// env //

void		print_env(t_cmds *cmd, t_env *list);
char		*ft_getenv(char **env, char *path);

// unset //

int			unset(char **path, t_env *list, int x);

// export //

void		export(char **arg, t_env *list, int i);
void		remplace_env(char **env, char *path);

// cd //

int			cd(char *cmd, char **arg, char **env);

// lst

void		ft_lstadd_back(t_env **list, char *str);
t_env		*ft_lstlast(t_env *list);
t_env		*ft_lstnew(char *str);
t_env		*lst_copy_tab(char **env);
void		ft_lst_back(t_env **lst);
int			ft_lst_size(t_env *lst);
char		**copy_with_lst(t_env *lst);
void		remplace_lst(t_env *lst, char *path);
void		free_list(t_env **head);

char **convert_args(t_cmds *cmd);
char *new_line(char *arg);
int size_tab(char **args);
char **convert_args_env(t_cmds *cmd, t_env *lst);

#endif
