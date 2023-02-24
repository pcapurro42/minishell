/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:55:57 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/24 17:17:39 by vdelafos         ###   ########.fr       */
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

static char	*ft_remove_simple_and_double_quotes(char *str)
{
	int	i;
	int	dquote;
	int	quote;

	i = 0;
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
			str[i] = ' ';
		}
		if (str[i] == 39 && dquote == 0)
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
			str[i] = ' ';
		}
		i++;
	}
	return (str);
}

static char	*ft_remove_spaces_inside_simple_and_double_quotes(char *str)
{
	int	i;
	int	dquote;
	int	quote;

	i = 0;
	dquote = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && dquote == 1)
			str[i] = -1;
		if (str[i] == ' ' && quote == 1)
			str[i] = -1;
		if (str[i] == 34 && quote == 0)
		{
			if (dquote == 0)
				dquote = 1;
			else
				dquote = 0;
		}
		if (str[i] == 39 && dquote == 0)
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		i++;
	}
	return (str);
}

char	*ft_prepare_for_split(char *str)
{
	str = ft_remove_spaces_inside_simple_and_double_quotes(str);
	str = ft_remove_simple_and_double_quotes(str);
	return (str);
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
			strf = ft_strjoin(strf, ft_char_to_str(' '));
			while (str[i] == '<' || str[i] == '>')
				strf = ft_strjoin(strf, ft_char_to_str(str[i++]));
			strf = ft_strjoin(strf, ft_char_to_str(' '));
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
			str = ft_strjoin(str, ft_char_to_str(' '));
		else
			str = ft_strjoin(str, ft_char_to_str(input[i]));
		i++;
	}
	str = ft_add_spaces_for_pipes_and_chevrons(str);
	return (str);
}

char	**ft_repair_string(char **strf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strf[i] != NULL)
	{
		while (strf[i][j] != '\0')
		{
			if (strf[i][j] == -1)
				strf[i][j] = ' ';
			j++;
		}
		i++;
		j = 0;
	}
	return (strf);
}