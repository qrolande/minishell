#include	"../includes/minishell.h"

static int	cmd_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	ft_echo(t_shell		*shell)
{
	int		i;
	int 	n;
	
	i = 1;
	n = 0;
	if (shell->cmd[i])
		if (!ft_strcmp(shell->cmd[i], "-n"))
			n = 1;
	while (shell->cmd[i])
	{
		ft_putstr_fd(shell->cmd[i + n], 1);
		i++;
		if (i + n < cmd_len(shell->cmd))
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}