/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:10:54 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/24 14:22:11 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quote_checker(char *str)
{
	int	i;
	int	dquote;
	int	quote;
	int	count;

	i = 0;
	count = 0;
	dquote = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && quote == 0)
		{
			if (dquote == 0)
				dquote = 1;
			else
				dquote = 0;
			count++;
		}
		if (str[i] == 39 && dquote == 0)
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
			count++;
		}
		i++;
	}
	if (count % 2 != 0)
		return (printf("minishell: syntax error for unclosed quotes\n"));
	return (0);
}

int	ft_pipe_checker(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == '|')
		{
			if (i == 0 || i == ft_dstrlen(str) - 1
				|| str[i - 1][0] == '|' || str[i + 1][0] == '|')
				// || str[i - 1][0] == '>' || str[i - 1][0] == '<'
				// || str[i + 1][0] == '>' || str[i + 1][0] == '<')
				return (printf("minishell: syntax error near unexpected token '|'\n"));
		}
		i++;
	}
	return (0);
}

int	ft_chevron_checker(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == '<' || str[i][0] == '>')
		{
			if (i == ft_dstrlen(str) - 1)
				return (printf("minishell: syntax error near unexpected token '%c'\n", str[i][0]));
			if (i != 0)
				if (str[i + 1][0] == '<' || str[i + 1][0] == '>'
					|| str[i - 1][0] == '<' || str[i - 1][0] == '>')
					return (printf("minishell: syntax error near unexpected token '%c'\n", str[i][0]));
			if (i == 0)
				if (str[i + 1][0] == '<' || str[i + 1][0] == '>')
					return (printf("minishell: syntax error near unexpected token '%c'\n", str[i][0]));
			if (ft_strlen(str[i]) >= 3)
				return (printf("minishell: syntax error near unexpected token '%c'\n", str[i][0]));
		}
		i++;
	}
	return (0);
}

int	ft_syntax_checker(char **str)
{
	if (ft_pipe_checker(str) != 0)
		return (1);
	if (ft_chevron_checker(str) != 0)
		return (1);
	return (0);
}
