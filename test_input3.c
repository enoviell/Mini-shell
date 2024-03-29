/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpecci <gpecci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:50:10 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/27 12:36:03 by gpecci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_half(t_varie *var, char *s, char c)
{
	var->newstr[var->z++] = s[var->i];
	var->j = var->i + 1;
	while (s[var->j] == ' ')
	{
		if (s[var->j] == '\0')
			break ;
		var->j++;
	}
	if (s[var->j] != c)
	{
		var->newstr[var->z++] = ' ';
		var->i = var->j;
	}
	else
	{
		var->i = var->j;
		var->newstr[var->z++] = s[var->i++];
		var->newstr[var->z++] = ' ';
	}
}

void	second_half(t_varie *var, char *s)
{
	var->newstr[var->z++] = ' ';
	if (s[var->i + 1] != ' ')
	{
		var->newstr[var->z++] = s[var->i++];
		if (s[var->i] == '<' || s[var->i] == '>')
			var->newstr[var->z++] = s[var->i++];
		if (s[var->i] != '<' && s[var->i] != '>')
			var->newstr[var->z++] = ' ';
	}
}
