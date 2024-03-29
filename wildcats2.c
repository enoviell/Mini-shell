/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcats2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpecci <gpecci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:50:22 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/29 16:05:27 by gpecci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	d = c;
	while (s[i] != '\0' && s[i] != d)
		i++;
	if (s[i] == '\0' && d != '\0')
		return (-1);
	return (i);
}

static int	generate_argument(t_args *cur, char **ret)
{
	int	i;

	if (ret != NULL)
	{
		free(cur->argument);
		cur->argument = NULL;
		i = 1;
		cur->argument = ft_strdup(ret[0]);
		while (ret[i] != NULL)
		{
			cur->argument = ft_strjoin_mini(cur->argument,
					ret[i], FREE, NO_FREE);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	support(t_args *cur)
{
	if(cur->argument[0] == '(' && cur->argument[ft_strlen(cur->argument) - 1] == ')')
	{
		cur->argument = ft_strtrim(cur->argument, "(");
		cur->argument = ft_strtrim(cur->argument, ")");
	}
	if (ft_strcmp((cur->command), "echo") != 0 && cur->argument[0] == '\"')
		cur->argument = ft_strtrim(cur->argument, "\"");
	else if (ft_strcmp((cur->command), "echo") != 0
		&& cur->argument[0] == '\'')
		cur->argument = ft_strtrim(cur->argument, "\'");
}

void	wild(t_shell *mini)
{
	t_args	*cur;
	int		i;
	char	**ret;

	i = -1;
	cur = *mini->list;
	ret = NULL;
	while (cur != NULL)
	{
		if (cur->argument != NULL && cur->command != NULL)
			support(cur);
		if (cur->argument != NULL && my_strchr(cur->argument, '*') != -1)
			i = my_strchr(cur->argument, '*');
		if (cur->argument != NULL && i != -1
			&& (apices(cur->argument, '\"', i) == 1
				&& apices(cur->argument, '\'', i) == 1))
		{
			ret = wildone(mini, cur);
			if (generate_argument(cur, ret) == 1)
				free_matrix(ret);
		}
		if (cur->next == NULL)
			return ;
		cur = cur->next;
	}
}
