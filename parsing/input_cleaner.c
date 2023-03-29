/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 02:29:55 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/25 02:29:56 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_add_spaces_for_pipes(char *str)
{
	int		i;
	char	*strf;
	char	*temp;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '|' && ft_in_out_quotes(str, i) != 1)
			strf = ft_join_free(strf, " | ");
		else
		{
			temp = ft_char_to_str(str[i]);
			strf = ft_join_free(strf, temp);
			free(temp);
		}
		i++;
	}
	free(str);
	return (strf);
}

char	*ft_hide_things(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && ft_in_out_quotes(str, i) == 1)
			str[i] = -1;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && str[i + 1] == '|' && ft_in_out_quotes(str, i) != 1)
		{
			if (i == 0 || (str[i - 1] != '>' && str[i - 1] != '<'))
				str[i + 1] = ' ';
		}
		i++;
	}
	return (str);
}

char	*ft_separate_chevrons(char *str)
{
	int		i;
	char	*strf;
	char	*temp;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (ft_in_out_quotes(str, i) != 1)
			if (str[i] == '>' || str[i] == '<'
				|| (i != 0 && (str[i - 1] == '<' || str[i - 1] == '>')))
				strf = ft_join_free(strf, " ");
		temp = ft_char_to_str(str[i]);
		strf = ft_join_free(strf, temp);
		free(temp);
		i++;
	}
	free(str);
	return (strf);
}

char	*ft_stick_chevrons(char *str)
{
	int		i;
	char	*strf;
	char	*temp;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && ft_in_out_quotes(str, i) != 1)
		{
			temp = ft_char_to_str(str[i++]);
			strf = ft_join_free(strf, temp);
			while (str[i] == ' ')
				i++;
			if (str[i] != '<' && str[i] != '>')
				strf = ft_join_free(strf, " ");
		}
		else
		{
			temp = ft_char_to_str(str[i++]);
			strf = ft_join_free(strf, temp);
		}
		free(temp);
	}
	return (free(str), strf);
}

char	*ft_input_cleaner(char *input)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	str = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] < 33 || input[i] > 126)
			str = ft_join_free(str, " ");
		else
		{
			temp = ft_char_to_str(input[i]);
			str = ft_join_free(str, temp);
			free(temp);
		}
		i++;
	}
	if (ft_quote_checker(str) != 0 || ft_chevron_checker_a(str) != 0)
		return (free(str), NULL);
	str = ft_hide_things(str);
	str = ft_add_spaces_for_pipes(str);
	str = ft_separate_chevrons(str);
	str = ft_stick_chevrons(str);
	return (str);
}
