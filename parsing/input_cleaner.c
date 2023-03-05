/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:38:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/05 20:02:50 by vdelafos         ###   ########.fr       */
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

static char	*ft_substitute_str(char *str)
{
	int		i;
	int		dquote;
	int		quote;
	char	*strf;

	i = 0;
	dquote = 0;
	quote = 0;
	strf = ft_strdup("");
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
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != -1)
			strf = ft_strjoin(strf, ft_char_to_str(str[i]));
		i++;
	}
	return (strf);
}

char	**ft_remove_quotes(char **cmd_arg)
{
	int		i;

	i = 0;
	while (cmd_arg && cmd_arg[i] != NULL)
	{
		if (ft_strchr(cmd_arg[i], 34) != NULL || ft_strchr(cmd_arg[i], 39) != NULL)
			cmd_arg[i] = ft_substitute_str(cmd_arg[i]);
		i++;
	}
	return (cmd_arg);
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
	str = ft_separate_chevrons(str);
	str = ft_stick_chevrons(str);
	return (str);
}
