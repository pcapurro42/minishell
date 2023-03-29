/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_checker_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:08:43 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/25 00:08:44 by pcapurro         ###   ########.fr       */
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

char	*ft_gv_end(t_mini *minishell, int i, int j)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	if (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j - 1] != '=')
			j++;
		while (minishell->mini_tools->envp[i][j] != '\0')
		{
			temp = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			str = ft_join_free(str, temp);
			free(temp);
		}
	}
	return (str);
}

char	*ft_gv_start(t_mini *minishell, char *tmp, char *var, int j)
{
	int		i;
	char	*temp;

	i = 0;
	while (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
		{
			temp = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			tmp = ft_join_free(tmp, temp);
			free(temp);
		}
		j = 0;
		tmp = ft_join_free(tmp, "=");
		if (ft_strncmp(var, tmp, ft_strlen(tmp)) != 0)
		{
			free(tmp);
			tmp = ft_strdup("");
		}
		else
			break ;
		i++;
	}
	return (free(var), free(tmp), ft_gv_end(minishell, i, j));
}
