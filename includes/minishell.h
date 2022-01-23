/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:08:07 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/23 14:57:33 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "signal.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

# define LEFT_FLAG 1
# define RIGHT_FLAG 2
# define X_RIGHT_FLAG 3

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

//void	rl_replace_line();
void	syntax(t_shell *shell);
char	*gap(char *str, int *i);
char	*slash(char *str, int *i);
char	*exsts(char *str, int *i);
void	checking_path(t_shell *shell);
char	*prepare_cmd(char *str, int i);
void	check_quotes(char *str, int *i);
void	fd_work(t_shell *shell, int flag);
void	env_parser(t_shell *shell, char	**env);
void	pipe_work(t_shell *shell, int i, int j);
void	begin(t_shell *shell, char **env, int i);
void	pipe_executor(char **env, t_shell *shell);
char	*tilde(char *str, int *i, t_shell *shell);
char	*dollar(char *str, int *i, t_shell *shell);
char	*finder(char *str, int *i, t_shell *shell);
void	cleaning_company(t_shell *shell, int flag);
char	*redirect(t_shell *shell, char *str, int *i);
char	*double_gap(char *str, int *i, t_shell *shell);
char	*find_key_value(char *tmp_key, t_shell *shell);
char	**env_constructor(t_shell *shell, int i, int j);
void	cmd_executor(char **env, t_shell *shell, int pid);
void	cmd_parser(t_shell *shell, char *str, int i, int j);
char	**two_dimension_check(char	**arr, char *str, int *j, int i);

// akatlyn

int		builtin_func(t_shell *shell);
void	ft_pwd(void);
void	ft_echo(t_shell *shell);

#endif