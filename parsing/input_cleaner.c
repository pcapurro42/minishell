/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:38:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/21 18:28:19 by vdelafos         ###   ########.fr       */
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
	char	*temp1;
	char	*temp2;

	i = 0;
	strf = ft_strdup("");
	ft_check_malloc(strf);
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			temp1 = ft_strdup(strf);
			ft_check_malloc(temp1);
			free(strf);
			strf = ft_strjoin(temp1, " | ");
			ft_check_malloc(strf);
			free(temp1);
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
	free(str);
	return (strf);
}

char	*ft_stick_chevrons(char *str)
{
	int		i;
	char	*strf;
	char	*temp1;
	char	*temp2;

	i = 0;
	strf = ft_strdup("");
	ft_check_malloc(strf);
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
		{
			temp1 = ft_strdup(strf);
			ft_check_malloc(temp1);
			free(strf);
			temp2 = ft_char_to_str(str[i]);
			strf = ft_strjoin(temp1, temp2);
			ft_check_malloc(strf);
			free(temp1);
			free(temp2);
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] != '<' && str[i] != '>')
			{
				temp1 = ft_strdup(strf);
				ft_check_malloc(temp1);
				free(strf);
				strf = ft_strjoin(temp1, " ");
				ft_check_malloc(strf);
				free(temp1);
			}
		}
		else
		{
			temp1 = ft_strdup(strf);
			ft_check_malloc(temp1);
			free(strf);
			temp2 = ft_char_to_str(str[i++]);
			strf = ft_strjoin(temp1, temp2);
			ft_check_malloc(strf);
			free(temp1);
			free(temp2);
		}
	}
	free(str);
	return (strf);
}

char	*ft_substitute_str(char *str)
{
	int		i;
	int		dquote;
	int		quote;
	char	*strf;
	char	*temp1;
	char	*temp2;

	i = 0;
	dquote = 0;
	quote = 0;
	strf = ft_strdup("");
	ft_check_malloc(strf);
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
	return (strf);
}

char	**ft_remove_quotes(char **cmd_arg)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (cmd_arg && cmd_arg[i] != NULL)
	{
		if (ft_strchr(cmd_arg[i], 34) != NULL || ft_strchr(cmd_arg[i], 39) != NULL)
		{
			new_arg = ft_substitute_str(cmd_arg[i]);
			free(cmd_arg[i]);
			cmd_arg[i] = new_arg;
		}
		i++;
	}
	return (cmd_arg);
}

char	*ft_input_cleaner(char *input)
{
	int		i;
	char	*str;
	char	*temp1;
	char	*temp2;

	i = 0;
	str = ft_strdup("");
	ft_check_malloc(str);
	while (input[i] != '\0')
	{
		if (input[i] < 33 || input[i] > 126)
		{
			temp1 = ft_strdup(str);
			ft_check_malloc(temp1);
			free(str);
			str = ft_strjoin(temp1, " ");
			ft_check_malloc(str);
			free(temp1);
		}
		else
		{
			temp1 = ft_strdup(str);
			ft_check_malloc(temp1);
			free(str);
			temp2 = ft_char_to_str(input[i]);
			str = ft_strjoin(temp1, temp2);
			ft_check_malloc(str);
			free(temp2);
			free(temp1);
		}
		i++;
	}
	if (ft_quote_checker(str) != 0)
		return (free(str), NULL);
	str = ft_add_spaces_for_pipes(str);
	str = ft_hide_spaces_in_quotes(str);
	str = ft_separate_chevrons(str);
	str = ft_stick_chevrons(str);
	return (str);
}
