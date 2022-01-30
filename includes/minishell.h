/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:08:07 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 07:47:35 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "signal.h"
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MAX 0	
# define MIN 1

int	g_ex_flag;

typedef struct s_structher
{
	int					if_heredoc;
	int					fd[2];
}				t_structher;

typedef struct s_structredir
{
	int					x_num;
	int					x_fd;
	int					r_num;
	int					r_fd;
	int					l_num;
	int					l_fd;
}				t_structredir;

typedef struct s_structenv
{
	char				*key;
	char				*value;
	struct s_structenv	*next;
	int					flag;
	int					equality;
}				t_structenv;

typedef struct s_shell
{
	t_structenv			*env_mass;
	t_structredir		redir;
	t_structher			her;
	char				**full_path;
	char				**cmd;
	char				**temp;
	char				**splitted_cmd;
	char				*line;
	char				*home;
	int					**fd;
	int					i;
	int					num_cmd;
	int					num_pipe;
	int					if_pipe;
	int					error;
	int					ex_flag;
	struct s_shell		*next;
}				t_shell;

void	signals_first(void);
void	signals_second(void);
void	syntax(t_shell *shell);
char	*gap(char *str, int *i);
void	error_output(char *str);
void	env_work(t_shell *shell);
char	*slash(char *str, int *i);
char	*exsts(char *str, int *i);
void	env_error_msg(t_shell *shell);
void	checking_path(t_shell *shell);
char	*prepare_cmd(char *str, int i);
int		env_size(t_shell *shell, int i);
void	check_quotes(char *str, int *i);
void	fd_work(t_shell *shell, int flag);
void	rl_replace_line(const char *a, int b);
void	env_parser(t_shell *shell, char	**env);
void	pipe_work(t_shell *shell, int i, int j);
void	begin(t_shell *shell, char **env, int i);
void	pipe_executor(char **env, t_shell *shell);
char	*tilde(char *str, int *i, t_shell *shell);
char	*dollar(char *str, int *i, t_shell *shell);
char	*finder(char *str, int *i, t_shell *shell);
void	cleaning_company(t_shell *shell, int flag);
char	*redirect(t_shell *shell, char *str, int i);
char	*double_gap(char *str, int *i, t_shell *shell);
char	*find_key_value(char *tmp_key, t_shell *shell);
char	**env_constructor(t_shell *shell, int i, int j);
char	*heredoc(t_shell *shell, char *str, int i, int j);
void	cmd_parser(t_shell *shell, char *str, int i, int j);
void	ft_lstadd_back_env(t_structenv **lst, t_structenv *new);
void	cmd_executor(char **env, t_shell *shell, int pid, int res);
char	**two_dimension_check(char	**arr, char *str, int *j, int i);
void	ft_pwd(t_shell *shell);

void	ft_export_with_param(t_shell *shell, int i, int j);
void	ft_export_without_param(t_shell *shell, int i, int j);
void	ft_env(t_shell	*shell, int fd);
void	ft_echo(t_shell *shell, int i);
void	ft_unset(t_shell	*shell);
void	ft_exit(t_shell	*shell);
void	ft_cd(t_shell	*shell);

#endif