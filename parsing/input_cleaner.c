/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:38:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/27 16:38:05 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_repair_spaces_in_quotes(char **strf)
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

char	*ft_add_spaces_for_pipes(char *str)
{
	int		i;
	char	*strf;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			strf = ft_strjoin(strf, " | ");
		else
			strf = ft_strjoin(strf, ft_char_to_str(str[i]));
		i++;
	}
	return (strf);
}

char	*ft_stick_chevrons(char *str)
{
	int		i;
	char	*strf;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
		{
			strf = ft_strjoin(strf, ft_char_to_str(str[i]));
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] != '<' && str[i] != '>')
				strf = ft_strjoin(strf, " ");
		}
		else
			strf = ft_strjoin(strf, ft_char_to_str(str[i++]));
	}
	return (strf);
}

char	*ft_remove_empty_quotes(char *str)
{
	int		i;
	char	*strf;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if ((str[i] == 34 && str[i + 1] == 34) || (str[i] == 39 && str[i + 1] == 39))
			i = i + 2;
		else
			strf = ft_strjoin(strf, ft_char_to_str(str[i++]));
	}
	return (strf);
}

char	*ft_input_cleaner(char *input)
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
	if (ft_quote_checker(str) != 0)
		return (NULL);
	str = ft_add_spaces_for_pipes(str);
	str = ft_hide_spaces_in_quotes(str);
	str = ft_remove_empty_quotes(str);
	str = ft_separate_chevrons(str);
	str = ft_stick_chevrons(str);
	return (str);
}
