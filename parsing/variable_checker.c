/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:02:48 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/03 18:46:44 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_what_should_be_done(char *input)
{
	int		i;
	int		dquote;
	int		quote;
	char	c;

	i = 0;
	dquote = 0;
	quote = 0;
	c = 0;
	while (input[i] != '$')
	{
		if (c == 0 && (input[i] == 34 || input[i] == 39))
			c = input[i];
		if (input[i] == 34 && quote % 2 == 0)
			dquote++;
		if (input[i] == 39 && dquote % 2 == 0)
			quote++;
		i++;
	}
	if ((dquote % 2 != 0 && quote % 2 == 0)
		|| (dquote % 2 == 0 && quote % 2 == 0)
		|| (dquote == 0 && quote == 0)
		|| (quote % 2 != 0 && dquote % 2 != 0 && c == 34))
		return (1);
	return (0);
}

char	*ft_get_variable(char *variable, t_mini *minishell)
{
	int		i;
	int		j;
	char	*temporary;
	char	*temp1;
	char	*temp2;
	char	*str;

	i = 0;
	j = 0;
	if (variable[0] == '?' && variable[1] == '\0')
	{
		temporary = ft_itoa(g_global->g_last_return_code);
		ft_check_malloc(temporary);
		return (temporary);
	}
	temporary = ft_strdup("");
	ft_check_malloc(temporary);
	temp1 = ft_strdup(variable);
	ft_check_malloc(temp1);
	free(variable);
	variable = ft_strjoin(temp1, "=");
	ft_check_malloc(variable);
	free(temp1);
	while (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
		{
			temp1 = ft_strdup(temporary);
			ft_check_malloc(temp1);
			free(temporary);
			temp2 = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			temporary = ft_strjoin(temp1, temp2);
			ft_check_malloc(temporary);
			free(temp1);
			free(temp2);
		}
		j = 0;
		temp1 = ft_strdup(temporary);
		ft_check_malloc(temp1);
		free(temporary);
		temporary = ft_strjoin(temp1, "=");
		ft_check_malloc(temporary);
		free(temp1);
		if (ft_strncmp(variable, temporary, ft_strlen(temporary)) != 0)
		{
			free(temporary);
			temporary = ft_strdup("");
			ft_check_malloc(temporary);
		}
		else
			break ;
		i++;
	}
	free(variable);
	free(temporary);
	str = ft_strdup("");
	ft_check_malloc(str);
	if (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
			j++;
		j = j + 1;
		while (minishell->mini_tools->envp[i][j] != '\0')
		{
			temp1 = ft_strdup(str);
			ft_check_malloc(temp1);
			free(str);
			temp2 = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			str = ft_strjoin(temp1, temp2);
			ft_check_malloc(str);
			free(temp1);
			free(temp2);
		}
	}
	return (str);
}

char	*ft_replace(char *input, t_mini *minishell)
{
	int		i;
	char	*str;
	char	*variable;
	char	*temp1;
	char	*temp2;

	i = 0;
	str = ft_strdup("");
	ft_check_malloc(str);
	while (input[i] != '\0')
	{
		if (input[i] != '$')
		{
			temp1 = ft_strdup(str);
			ft_check_malloc(temp1);
			free(str);
			temp2 = ft_char_to_str(input[i++]);
			str = ft_strjoin(temp1, temp2);
			ft_check_malloc(str);
			free(temp1);
			free(temp2);
		}
		else
		{
			i = i + 1;
			variable = ft_strdup("");
			ft_check_malloc(variable);
			while (input[i] != '\0' && input[i] != ' ' && input[i] != 34 && input[i] != 39 && input[i] != 58)
			{
				temp1 = ft_strdup(variable);
				ft_check_malloc(temp1);
				free(variable);
				temp2 = ft_char_to_str(input[i++]);
				variable = ft_strjoin(temp1, temp2);
				ft_check_malloc(variable);
				free(temp1);
				free(temp2);
			}
			if (ft_what_should_be_done(input) == 0)
			{
				temp1 = ft_strdup(str);
				ft_check_malloc(temp1);
				free(str);
				str = ft_strjoin(temp1, "$");
				ft_check_malloc(str);
				free(temp1);
			}
			else
				variable = ft_get_variable(variable, minishell);
			temp1 = ft_strdup(str);
			ft_check_malloc(temp1);
			free(str);
			str = ft_strjoin(temp1, variable);
			ft_check_malloc(str);
			free(temp1);
			free(variable);
		}
	}
	free(input);
	return (str);
}

char	**ft_check_variables(char **str, t_mini *minishell)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$') != NULL)
			str[i] = ft_replace(str[i], minishell);
		i++;
	}
	return (str);
}
