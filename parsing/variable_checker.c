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
	if ((dquote % 2 != 0 && quote % 2 == 0) || (dquote % 2 == 0 && quote % 2 == 0) || (dquote == 0 && quote == 0) || (quote % 2 != 0 && dquote % 2 != 0 && c == 34))
		return (1);
	return (0);
}

char	*ft_get_variable(char *variable, t_mini *minishell)
{
	int		i;
	int		j;
	char	*temp;
	char	*str;

	i = 0;
	j = 0;
	if (variable[0] == '?' && variable[1] == '\0')
		return (ft_itoa(minishell->mini_tools->g_last_return_code));
	temp = ft_strdup("");
	variable = ft_strjoin(variable, "=");
	while (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
			temp = ft_strjoin(temp, ft_char_to_str(\
			minishell->mini_tools->envp[i][j++]));
		j = 0;
		temp = ft_strjoin(temp, "=");
		if (ft_strncmp(variable, temp, ft_strlen(temp)) != 0)
			temp = ft_strdup("");
		else
			break ;
		i++;
	}
	free(temp);
	str = ft_strdup("");
	if (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
			j++;
		j = j + 1;
		while (minishell->mini_tools->envp[i][j] != '\0')
			str = ft_strjoin(str, \
			ft_char_to_str(minishell->mini_tools->envp[i][j++]));
	}
	return (str);
}

char	*ft_replace(char *input, t_mini *minishell)
{
	int		i;
	char	*str;
	char	*variable;

	i = 0;
	str = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] != '$')
			str = ft_strjoin(str, ft_char_to_str(input[i++]));
		else
		{
			i = i + 1;
			variable = ft_strdup("");
			while (input[i] != '\0' && input[i] != ' ' && input[i] != 34 && input[i] != 39 && input[i] != 58)
				variable = ft_strjoin(variable, ft_char_to_str(input[i++]));
			if (ft_what_should_be_done(input) == 0)
				str = ft_strjoin(str, "$");
			else
				variable = ft_get_variable(variable, minishell);
			str = ft_strjoin(str, variable);
			free(variable);
		}
	}
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
