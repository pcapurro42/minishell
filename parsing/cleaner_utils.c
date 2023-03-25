/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:52:23 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/27 16:52:24 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_inside_quotes(char *str, int i, int quote, int dquote)
{
	int	j;

	j = 0;
	while (str[j] != '\0' && j != i)
	{
		if (str[j] == 34 && quote == 0)
		{
			if (dquote == 0)
				dquote = 1;
			else
				dquote = 0;
		}
		if (str[j] == 39 && dquote == 0)
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		j++;
	}
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	return (0);
}

char	*ft_hide_spaces_in_quotes(char *str)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && ft_inside_quotes(str, i, quote, dquote) == 1)
			str[i] = -1;
		i++;
	}
	return (str);
}

char	*ft_separate_chevrons(char *str)
{
	int		i;
	int		quote;
	int		dquote;
	char	*strf;
	char	*temp;

	i = 0;
	quote = 0;
	dquote = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (ft_inside_quotes(str, i, quote, dquote) != 1)
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

void	ft_prepare_for_heredoc(char **str)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	j = 0;
	k = 1;
	while (str[i] != NULL)
	{
		if (ft_strncmp(str[i], "<<", 3) == 0 && str[i + 1][0] == '$' \
			&& (i == 0 || str[i - 1][0] == '|'))
		{
			temp = ft_strdup(str[i + 1]);
			free(str[i + 1]);
			str[i + 1] = malloc(sizeof(char) * (ft_strlen(temp) + 2) + 1);
			str[i + 1][0] = 39;
			while (temp[j] != '\0')
				str[i + 1][k++] = temp[j++];
			str[i + 1][k] = 39;
			str[i + 1][k + 1] = '\0';
		}
		i++;
	}
}
