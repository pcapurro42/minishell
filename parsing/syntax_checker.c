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

static int	ft_quote_checker(char *str)
{
	int	i;
	int	dquote;
	int	quote;
	int	count;

	i = 0;
	dquote = 0;
	quote = 0;
	count = 0;
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
		return (printf("Syntax error! Quotes are not closed.\n"));
	return (0);
}

static int ft_pipe_checker(char *strf)
{
	char	**str;
    int 	i;

    i = 0;
	str = ft_split(strf, ' ');
    while (str[i] != NULL)
    {
        if (str[i][0] == '|')
		{
			if (i == 0 || str[i + 1] == NULL || str[i - 1][0] == '|' || str[i + 1][0] == '|')
				return (printf("Error! Unexpected pipe.\n"));
		}
		i++;
    }
    return (0);
}

static int	ft_chevron_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if ((str[i + 1] == '>' || str[i + 1] == '<') && (str[i + 2] == '>' || str[i + 2] == '<'))
				return (printf("Error! Unexpected chevron.\n"));
		}
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '>' || str[i] == '<') && (str[i + 1] == '>' || str[i + 1] == '<'))
		{
			if (str[i + 1] != str[i])
				return (printf("Error! Unexpected chevron.\n"));
		}
		i++;
	}
	return (0);
}

int	ft_syntax_checker(char *str)
{
	if (ft_quote_checker(str) != 0)
		return (1);
	if (ft_pipe_checker(str) != 0)
		return (1);
	if (ft_chevron_checker(str) != 0)
		return (1);
	return (0);
}
