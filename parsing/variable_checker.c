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

int	ft_to_do_quote(char *input)
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

int	ft_to_do_tilde(char *input)
{
	int		i;
	int		dquote;
	int		quote;
	char	c;

	i = 0;
	dquote = 0;
	quote = 0;
	c = 0;
	while (input[i] != '~')
	{
		if (c == 0 && (input[i] == 34 || input[i] == 39))
			c = input[i];
		if (input[i] == 34 && quote % 2 == 0)
			dquote++;
		if (input[i] == 39 && dquote % 2 == 0)
			quote++;
		i++;
	}
	if (dquote % 2 != 0 || quote % 2 != 0)
		return (0);
	return (1);
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
		return (temporary);
	}
	temporary = ft_strdup("");
	temp1 = ft_strdup(variable);
	free(variable);
	variable = ft_strjoin(temp1, "=");
	free(temp1);
	while (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
		{
			temp1 = ft_strdup(temporary);
			free(temporary);
			temp2 = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			temporary = ft_strjoin(temp1, temp2);
			free(temp1);
			free(temp2);
		}
		j = 0;
		temp1 = ft_strdup(temporary);
		free(temporary);
		temporary = ft_strjoin(temp1, "=");
		free(temp1);
		if (ft_strncmp(variable, temporary, ft_strlen(temporary)) != 0)
		{
			free(temporary);
			temporary = ft_strdup("");
		}
		else
			break ;
		i++;
	}
	free(variable);
	free(temporary);
	str = ft_strdup("");
	if (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
			j++;
		j = j + 1;
		while (minishell->mini_tools->envp[i][j] != '\0')
		{
			temp1 = ft_strdup(str);
			free(str);
			temp2 = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			str = ft_strjoin(temp1, temp2);
			free(temp1);
			free(temp2);
		}
	}
	return (str);
}

char	*ft_replace_quote(char *input, t_mini *minishell)
{
	int		i;
	char	*str;
	char	*variable;
	char	*temp1;
	char	*temp2;

	i = 0;
	str = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] != '$')
		{
			temp1 = ft_strdup(str);
			free(str);
			temp2 = ft_char_to_str(input[i++]);
			str = ft_strjoin(temp1, temp2);
			free(temp1);
			free(temp2);
		}
		else
		{
			i = i + 1;
			variable = ft_strdup("");
			while (input[i] != '\0' && input[i] != ' ' && input[i] != 34 && input[i] != 39 && input[i] != 58)
			{
				temp1 = ft_strdup(variable);
				free(variable);
				temp2 = ft_char_to_str(input[i++]);
				variable = ft_strjoin(temp1, temp2);
				free(temp1);
				free(temp2);
			}
			if (ft_to_do_quote(input) == 0)
			{
				temp1 = ft_strdup(str);
				free(str);
				str = ft_strjoin(temp1, "$");
				free(temp1);
			}
			else
				variable = ft_get_variable(variable, minishell);
			temp1 = ft_strdup(str);
			free(str);
			str = ft_strjoin(temp1, variable);
			free(temp1);
			free(variable);
		}
	}
	free(input);
	return (str);
}

char	*ft_replace_tilde(char *str, t_mini *minishell)
{
	int		i;
	char	*strf;
	char	*temp;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] != '~')
			strf = ft_strjoin(strf, ft_char_to_str(str[i]));
		else
		{
			if (ft_to_do_tilde(str) != 0)
			{
				temp = ft_strdup(strf);
				free(strf);
				strf = ft_strjoin(temp, minishell->mini_tools->home_directory);
				free(temp);
			}
			else
			{
				temp = ft_strdup(strf);
				free(strf);
				strf = ft_strjoin(temp, "~");
				free(temp);
			}
		}
		i++;
	}
	free(str);
	return (strf);
}

char	**ft_check_variables(char **str, t_mini *minishell)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$') != NULL)
			str[i] = ft_replace_quote(str[i], minishell);
		i++;
	}
	return (str);
}
