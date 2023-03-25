/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:02:48 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/03 18:46:44 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_gv_end(t_mini *minishell, int i, int j)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	if (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j - 1] != '=')
			j++;
		while (minishell->mini_tools->envp[i][j] != '\0')
		{
			temp = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			str = ft_join_free(str, temp);
			free(temp);
		}
	}
	return (str);
}

char	*ft_gv_start(t_mini *minishell, char *temporary, char *variable, int j)
{
	int		i;
	char	*temp;

	i = 0;
	while (minishell->mini_tools->envp[i] != NULL)
	{
		while (minishell->mini_tools->envp[i][j] != '=')
		{
			temp = ft_char_to_str(minishell->mini_tools->envp[i][j++]);
			temporary = ft_join_free(temporary, temp);
			free(temp);
		}
		j = 0;
		temporary = ft_join_free(temporary, "=");
		if (ft_strncmp(variable, temporary, ft_strlen(temporary)) != 0)
		{
			free(temporary);
			temporary = ft_strdup("");
		}
		else
			break ;
		i++;
	}
	return (free(variable), free(temporary), ft_gv_end(minishell, i, j));
}

char	*ft_get_variable(char *variable, t_mini *minishell)
{
	int		j;
	char	*temporary;

	j = 0;
	if (variable[0] == '?' && variable[1] == '\0')
		return (ft_itoa(g_global->g_last_return_code));
	else
	{
		temporary = ft_strdup("");
		variable = ft_join_free(variable, "=");
	}
	return (ft_gv_start(minishell, temporary, variable, j));
}

char	*ft_capture_variable(char *input, t_mini *minishell)
{
	int		i;
	char	*str;
	char	*variable;
	char	*temp;

	i = 0;
	str = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] != '$')
		{
			temp = ft_char_to_str(input[i++]);
			str = ft_join_free(str, temp);
			free(temp);
		}
		else if (input[i++] == '$')
		{
			variable = ft_strdup("");
			while (input[i] != '\0' && input[i] != ' ' && input[i] != 34 \
				&& input[i] != 39 && input[i] != ':')
			{
				temp = ft_char_to_str(input[i++]);
				variable = ft_join_free(variable, temp);
				free(temp);
			}
			if (ft_to_do_quote(input) == 0)
				str = ft_join_free(str, "$");
			else
				variable = ft_get_variable(variable, minishell);
			str = ft_join_free(str, variable);
			free(variable);
		}
	}
	return (free(input), str);
}

char	*ft_replace_tilde(char *str, t_mini *minishell)
{
	int		i;
	char	*sf;
	char	*temp;

	i = 0;
	sf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] != '~')
		{
			temp = ft_char_to_str(str[i]);
			sf = ft_join_free(sf, temp);
			free(temp);
		}
		else
		{
			if (ft_to_do_tilde(str) != 0)
				sf = ft_join_free(sf, minishell->mini_tools->home_directory);
			else
				sf = ft_join_free(sf, "~");
		}
		i++;
	}
	free(str);
	return (sf);
}

char	**ft_check_variables(char **str, t_mini *minishell)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$') != NULL)
			str[i] = ft_capture_variable(str[i], minishell);
		i++;
	}
	return (str);
}
