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

char	*ft_hide_spaces_in_quotes(char *str)
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
		}
		if (str[i] == 39 && dquote == 0)
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		if (str[i] == ' ' && dquote == 1)
			str[i] = -1;
		if (str[i] == ' ' && quote == 1)
			str[i] = -1;
		i++;
	}
	return (str);
}

char	*ft_separate_chevrons(char *str)
{
	int		i;
	char	*strf;
	char	*fstr;
	char	*temp1;
	char	*temp2;

	i = 0;
	strf = ft_strdup("");
	fstr = ft_strdup("");
	ft_check_malloc(strf);
	ft_check_malloc(fstr);
	while (str[i] != '\0')
	{
		if ((str[i] == '>' || str[i] == '<') && (str[i - 1] != '<'
				&& str[i - 1] != '>') && (str[i - 1] != ' ')
			&& (str[i - 1] != 34) && (str[i - 1] != 39))
		{
			temp1 = ft_strdup(strf);
			ft_check_malloc(temp1);
			free(strf);
			strf = ft_strjoin(temp1, " ");
			ft_check_malloc(strf);
			free(temp1);
			temp1 = ft_strdup(strf);
			ft_check_malloc(temp1);
			free(strf);
			temp2 = ft_char_to_str(str[i]);
			strf = ft_strjoin(temp1, temp2);
			ft_check_malloc(strf);
			free(temp1);
			free(temp2);
		}
		else
		{
			temp1 = ft_strdup(strf);
			ft_check_malloc(temp1);
			free(strf);
			temp2 = ft_char_to_str(str[i]);
			strf = ft_strjoin(temp1, temp2);
			ft_check_malloc(strf);
			free(temp1);
			free(temp2);
		}
		i++;
	}
	i = 0;
	free(str);
	while (strf[i] != '\0')
	{
		if ((strf[i] == '>' || strf[i] == '<') && (strf[i + 1] != '<'
				&& strf[i + 1] != '>') && (strf[i + 1] != ' ')
			&& (str[i + 1] != 34) && (str[i + 1] != 39))
		{
			temp1 = ft_strdup(fstr);
			ft_check_malloc(temp1);
			free(fstr);
			temp2 = ft_char_to_str(strf[i]);
			fstr = ft_strjoin(temp1, temp2);
			ft_check_malloc(fstr);
			free(temp1);
			free(temp2);
			temp1 = ft_strdup(fstr);
			ft_check_malloc(temp1);
			free(fstr);
			fstr = ft_strjoin(temp1, " ");
			ft_check_malloc(fstr);
			free(temp1);
		}
		else
		{
			temp1 = ft_strdup(fstr);
			ft_check_malloc(temp1);
			free(fstr);
			temp2 = ft_char_to_str(strf[i]);
			fstr = ft_strjoin(temp1, temp2);
			ft_check_malloc(fstr);
			free(temp1);
			free(temp2);
		}
		i++;
	}
	free(strf);
	return (fstr);
}

void	ft_prepare_for_heredoc(char **str)
{
	int		i;
	char	*temp;
	char	*temp_one;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strncmp(str[i], "<<", 3) == 0 && str[i + 1][0] == '$' && (i == 0 || str[i - 1][0] == '|'))
		{
			temp = ft_strdup(str[i + 1]);
			ft_check_malloc(temp);
			free(str[i + 1]);
			str[i + 1] = ft_strdup("'");
			ft_check_malloc(str[i + 1]);
			temp_one = ft_strdup(str[i + 1]);
			ft_check_malloc(temp_one);
			free(str[i + 1]);
			str[i + 1] = ft_strjoin(temp_one, temp);
			ft_check_malloc(str[i + 1]);
			free(temp);
			free(temp_one);
			temp_one = ft_strdup(str[i + 1]);
			ft_check_malloc(temp_one);
			free(str[i + 1]);
			str[i + 1] = ft_strjoin(temp_one, "'");
			ft_check_malloc(str[i + 1]);
			free(temp_one);
		}
		i++;
	}
}
