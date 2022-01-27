/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:33:46 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/27 19:54:22 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signals_work(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	signals_fot_first(int signal)
{
	(void)signal;
	g_ex_flag = 130;
	write(1, "\n", 1);
}

static void	signals_for_second(int signal)
{
	(void)signal;
	g_ex_flag = 131;
	printf("Quit: 3\n");
}

void	signals_first(void)
{
	signal(SIGINT, signals_work);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_second(void)
{
	signal(SIGINT, signals_fot_first);
	signal(SIGQUIT, signals_for_second);
}
