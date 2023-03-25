/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 01:35:09 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/25 01:35:10 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*ft_substitute_str_end(char *str)
{
	int		i;
	char	*strf;
	char	*temp;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] != -1)
		{
			temp = ft_char_to_str(str[i]);
			strf = ft_join_free(strf, temp);
			free(temp);
		}
		i++;
	}
	return (strf);
}

char	*ft_substitute_str(char *str)
{
	int		i;
	int		dquote;
	int		quote;
	char	*strf;

	i = 0;
	dquote = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && quote % 2 == 0)
		{
			str[i] = -1;
			dquote++;
		}
		if (str[i] == 39 && dquote % 2 == 0)
		{
			str[i] = -1;
			quote++;
		}
		i++;
	}
	strf = ft_substitute_str_end(str);
	return (strf);
}

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

char	**ft_remove_quotes(char **cmd_arg)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (cmd_arg && cmd_arg[i] != NULL)
	{
		if (ft_strchr(cmd_arg[i], 34) != NULL \
			|| ft_strchr(cmd_arg[i], 39) != NULL)
		{
			new_arg = ft_substitute_str(cmd_arg[i]);
			free(cmd_arg[i]);
			cmd_arg[i] = new_arg;
		}
		i++;
	}
	return (cmd_arg);
}
