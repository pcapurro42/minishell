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

// int	ft_empty_checker(char *str)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
// 			j++;
// 		if (str[i] == ' ')
// 			k++;
// 		i++;
// 	}
// 	if ((size_t)j == ft_strlen(str) - k)
// 		return (printf("Error! Not enough inputs.\n"));
// 	return (0);
// }

// int	ft_quote_checker(char *str)
// {
// 	int	i;
// 	int	dquote;
// 	int	quote;

// 	i = 0;
// 	dquote = 0;
// 	quote = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == 34)
// 			dquote++;
// 		if (str[i] == 39)
// 			quote++;
// 		i++;
// 	}
// 	if (dquote % 2 != 0 || quote % 2 != 0)
// 		return (printf("Syntax error! Quotes are not closed.\n"));
// 	return (0);
// }

// int	ft_pipe_chevron_checker(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	**strf;

// 	i = 0;
// 	j = 0;
// 	strf = ft_split(str, ' ');
// 	while (strf[i] != NULL)
// 	{
// 		if ((strf[i][0] == '|' && strf[i - 1][0] == '|') || (strf[i][0] == '|' && strf[i + 1] == NULL))
// 			return (printf("Syntax error! Unexpected pipe.\n"));
// 		i++;
// 	}
// 	i = 0;
// 	while (strf[i] != NULL)
// 	{
// 		if ((strf[i][0] == '<' || strf[i][0] == '>') && ft_strlen(strf[i]) > 2)
// 			return (printf("Error!\n"));
// 		if ((strf[i][0] == '<' || strf[i][0] == '>') && ft_strlen(strf[i]) > 2 && strf[i][1] != strf[i][0])
// 			return (printf("Error!\n"));
// 		i++;
// 	}
// 	return (0);
// }

int	ft_syntax_checker(char *str)
{
	return (0);
}
