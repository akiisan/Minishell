/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:14:09 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 00:11:08 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

char	*ft_cutequotes(char *line)
{
	int n;
	char *l;

	l = NULL;

	n = ft_strlen(line);
	if ((n - 2) > 0)
	{
		l = ft_substr(line, 1, n-1);
		return (l);
	}
	return (NULL);
}

void	ft_addarg(char **str, t_cm **cutcm)
{
	int	i;
	int n;
	char **strt;
	t_cm *newcut;
	int ii;


	ii = 0;
	n = 0;
	newcut = NULL;
	i = 0;
	
	while (str[i])
	{
		
		n = 0;
		while (str[i] && ft_strcmp(str[i], "|") != 0 && ft_strcmp(str[i], ";") != 0)
		{
			n++;
			i++;
		}
		if (n > 0)
		{
			strt = malloc(sizeof(char*) * (n+1));
			strt[n] = NULL;
			n--;
			ii = i-1;
			while (n >= 0)
			{
				strt[n] = str[ii];
				n--;
				ii--;
			}
			newcut = ft_cmnew(strt);
			ft_cmadd_back(cutcm, newcut);
		}
		if (str[i])
		{
			strt = malloc(sizeof(char*) * 2);
			strt[0] = str[i];
			strt[1] = NULL;
			newcut = ft_cmnew(strt);
			ft_cmadd_back(cutcm, newcut);
			i++;
		}	
	}
}

void	ft_addcmd(t_cm *cutcm, t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	while (cutcm)
	{
		if (cutcm->next && ft_strcmp(cutcm->next->str[0], "|") == 0)
		{
			tmp = ft_tcmdnew(cutcm->str);
			tmp->type = PIPED;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next->next;
		}
		else if (cutcm->next && ft_strcmp(cutcm->next->str[0], ";") == 0)
		{
			tmp = ft_tcmdnew(cutcm->str);
			tmp->type = BREAK;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next->next;
		}
		else
		{
			tmp = ft_tcmdnew(cutcm->str);
			tmp->type = END;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next;
		}
	}
}

void	ft_cutcmd(t_cmd **cmd, char *line, t_env *env)
{
	char **str;
	t_cm *cutcm;


	cutcm = NULL;
	str = ft_strtok(line, "|;><");
	
	if (!ft_delquotes(str, env))
	{
		*cmd = NULL;
		return ;
	}
	if (!str)
	{	
		*cmd = NULL;
		return ;
	}
	ft_addarg(str, &cutcm);
	ft_addcmd(cutcm, cmd);
}