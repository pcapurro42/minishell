/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:55:57 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/22 06:55:59 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	if (!str)
		exit(1);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_remove_simple_and_double_quotes(char *str)
{
	int	i;
	int	dquote;
	int	quote;
	int	count;

	i = 0;
	dquote = 0;
	quote = 0;
	while (str[i] != NULL)
	{
		if (str[i] == 34 && quote == 0)
		{
			if (dquote == 0)
				dquote = 1;
			else
				dquote = 0;
			str[i] = -1;
		}
		if (str[i] == 39 && dquote == 0)
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
			str[i] = -1;
		}
		i++;
	}
	return (0);
}

static char	*ft_add_spaces_for_pipes_and_chevrons(char *str)
{
	int		i;
	char	*strf;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			strf = ft_strjoin(strf, " | ");
			i++;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			strf = ft_strjoin(strf, " ");
			while (str[i] == '<' || str[i] == '>')
				strf = ft_strjoin(strf, ft_char_to_str(str[i++]));
			strf = ft_strjoin(strf, " ");
		}
		else
			strf = ft_strjoin(strf, ft_char_to_str(str[i++]));
	}
	return (strf);
}

char	*ft_clean_input(char *input)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] < 33 || input[i] > 126)
			str = ft_strjoin(str, " ");
		else
			str = ft_strjoin(str, ft_char_to_str(input[i]));
		i++;
	}
	str = ft_add_spaces_for_pipes_and_chevrons(str);
	return (str);
}
