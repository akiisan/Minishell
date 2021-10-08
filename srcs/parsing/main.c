/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:18:37 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/08 22:26:39 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void sig_handler(int signum)
{
  printf("\n");
  rl_replace_line("", 0);
	rl_on_new_line();

}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char			*cmd;
	t_minishell		minishell;
	t_cmd			*ccmd;

	ccmd = NULL;
	cmd = NULL;
	ft_init_minishell(&minishell, envp);
	while(minishell.exit == 0)
	{
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		signal(SIGINT,sig_handler);
		if (cmd != NULL)
		{
			if (cmd && cmd[0] != '\0')
				add_history(cmd);
			ft_cutcmd(&ccmd,cmd,minishell.env);
			if (ccmd)
			{
				minishell.ret = exec_cmds(ccmd, &minishell);
				free(cmd);
				ft_freecmd(ccmd);
				ccmd = NULL;
			}
		}
		else
			exit(0);
	}
	ft_clean_all(&minishell);
	//Faut tout free
	return (minishell.ret);
}