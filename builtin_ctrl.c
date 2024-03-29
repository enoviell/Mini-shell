/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpecci <gpecci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:45:20 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/29 14:53:38 by gpecci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_exit(t_shell *mini, t_args *node)
{
	printf("exit\n");
	if (node->argument != NULL)
	{
		exit(ft_atoi(node->argument) % 256);
		clear_mini(mini, 1);
	}
	exit(0);
}

void	builtin_exec(t_shell *mini, t_args *node, char *temp)
{
	if (ft_strcmp(temp, "echo") == 0)
		command_echo(mini, node);
	if (ft_strcmp(temp, "cd") == 0)
		command_cd(mini, node, node->argument);
	else if (ft_strcmp(temp, "pwd") == 0)
		command_pwd(mini, node);
	else if (ft_strcmp(temp, "export") == 0)
		command_export(mini, node->argument);
	else if (ft_strcmp(temp, "unset") == 0)
		command_unset(mini, node->argument);
	else if (ft_strcmp(temp, "env") == 0)
		command_env(mini);
	else if (ft_strcmp(temp, "exit") == 0)
		command_exit(mini, node);
}

int	check_builtin_presence(t_shell *mini, char *command)
{
	int	j;

	j = 1;
	if (command == NULL)
		return (-127);
	if (ft_strcmp(command, "cd") == 0)
		j = 0;
	else if (ft_strcmp(command, "pwd") == 0)
		j = 0;
	else if (ft_strcmp(command, "export") == 0)
		j = 0;
	else if (ft_strcmp(command, "unset") == 0)
		j = 0;
	else if (ft_strcmp(command, "env") == 0)
		j = 0;
	else if (ft_strcmp(command, "echo") == 0)
		j = 0;
	else if (ft_strcmp(command, "exit") == 0)
		j = 0;
	if (j == 0)
		mini->command_presence = 1;
	return (j);
}

void	command_env2(t_shell *mini, char *dollar)
{
	int		j;
	char	*argument;

	j = 0;
	while (mini->new_envp[j] != NULL)
	{
		argument = ft_strjoin(dollar, mini->new_envp[j], NO_FREE, NO_FREE);
		if (!(*mini->list)->argument)
			printf("%s\n", mini->new_envp[j]);
		else if (ft_strncmp(argument, (*mini->list)->argument,
				ft_strlen((*mini->list)->argument)) == 0)
			printf("%s\n", mini->new_envp[j]);
		free(argument);
		j++;
	}
}

void	pipe_signal_utils(t_shell *mini, t_pipex *pipes, t_args *cur,
		char ***commands)
{
	no_pipes(mini, pipes, cur, commands);
	first_command_in_pipe(pipes, cur, commands);
	last_command_in_pipe(pipes, cur, commands);
	mid_command_in_pipe(pipes, cur, commands);
}
