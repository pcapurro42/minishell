/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:10:54 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/22 06:11:56 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_empty_checker(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			j++;
		i++;
	}
	printf("%d\n", j);
	printf("%zu\n", ft_strlen(str));
	if ((size_t)j == ft_strlen(str))
		return (printf("Error! Not enough inputs.\n"));
	return (0);
}

int	ft_quote_checker(char *str)
{
	int	i;
	int	dquote;
	int	quote;

	i = 0;
	dquote = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
			dquote++;
		if (str[i] == 39)
			quote++;
		i++;
	}
	if (dquote % 2 != 0 || quote % 2 != 0)
		return (printf("Syntax error! Quotes are not closed.\n"));
	return (0);
}

int	ft_pipe_chevron_checker(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '|' && str[i - 1] == '|')
			|| (str[i] == '|' && str[i + 1] == '\0'))
			return (printf("Syntax error! Unexpected pipe.\n"));
		i++;
	}
	i = 0;
	return (0);
}

int	ft_syntax_checker(char *str)
{
	if (ft_empty_checker(str) != 0)
		return (1);
	if (ft_quote_checker(str) != 0)
		return (1);
	if (ft_pipe_chevron_checker(str) != 0)
		return (1);
	return (0);
}
