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

static int	ft_qc_main(char *str, int dquote, int quote, int count)
{
	int	i;

	i = 0;
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
	return (count);
}

int	ft_quote_checker(char *str)
{
	int	dquote;
	int	quote;
	int	count;

	count = 0;
	dquote = 0;
	quote = 0;
	if (ft_qc_main(str, dquote, quote, count) % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error for unclosed quotes\n", 2);
		return (1);
	}
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
			if (i == 0 || i == ft_dstrlen(str) - 1)
				return (ft_putstr_fd("minishell: syntax error \
near unexpected token '|'\n", 2), 1);
			if (str[i - 1][0] == '|' || str[i + 1][0] == '|')
				return (ft_putstr_fd("minishell: syntax error \
near unexpected token '|'\n", 2), 1);
			if (str[i - 1][0] == '<' || str[i - 1][0] == '>')
				return (ft_putstr_fd("minishell: syntax error \
near unexpected token '|'\n", 2), 1);
		}
		i++;
	}
	return (0);
}

int	ft_chevron_checker_a(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			i = i + 1;
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				break ;
			else
			{
				while (str[i] == ' ')
					i++;
				if (str[i] == '<' || str[i] == '>' || str[i] == '|')
					return (ft_printf_error("minishell: syntax error near \
unexpected token '%c'\n", str[i]));
				else
					i = i + 1;
			}
		}
		else
			i++;
	}
	return (0);
}

int	ft_chevron_checker_b(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if ((str[i][0] == '<' || str[i][0] == '>'))
		{
			if (ft_strlen(str[i]) >= 3)
				return (ft_printf_error("minishell: syntax error near \
unexpected token '%c'\n", str[i][ft_strlen(str[i]) - 1]));
			if (i == ft_dstrlen(str) - 1)
				return (ft_putstr_fd("minishell: syntax error near \
unexpected token 'newline'\n", 2), 1);
			if (i != 0)
				if (str[i + 1][0] == '<' || str[i + 1][0] == '>'
					|| str[i - 1][0] == '<' || str[i - 1][0] == '>')
					return (ft_printf_error("minishell: syntax error near \
unexpected token '%c'\n", str[i][0]));
			if (i == 0)
				if (str[i + 1][0] == '<' || str[i + 1][0] == '>')
					return (ft_printf_error("minishell: syntax error near \
unexpected token '%c'\n", str[i][0]));
		}
		i++;
	}
	return (0);
}
