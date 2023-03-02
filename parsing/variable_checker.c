/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:02:48 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/01 22:02:49 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_what_should_be_done(char *input)
{
	int		i;

	i = 0;
	while (input[i] != '\0')
		i++;
	return (1);
}

// 0 = on laisse le contenu de variable tel quel
// 1 = on remplace le contenu de variable par sa variable

static char	*ft_get_variable(char *variable, t_mini *minishell)
{
	int		i;
	int		j;
	char	*temp;
	char	*str;

	i = 0;
	j = 0;
	if (variable[0] == '?' && variable[1] == '\0')
		return (ft_itoa(g_last_return_code));
	temp = ft_strdup("");
	while (minishell->envp[i] != NULL)
	{
		while (minishell->envp[i][j] != '=')
			temp = ft_strjoin(temp, ft_char_to_str(minishell->envp[i][j++]));
		j = 0;
		if (ft_strncmp(variable, temp, ft_strlen(variable)) != 0)
			temp = ft_strdup("");
		else
			break ;
		i++;
	}
	free(temp);
	str = ft_strdup("");
	if (minishell->envp[i] != NULL)
	{
		while (minishell->envp[i][j] != '=')
			j++;
		j = j + 1;
		while (minishell->envp[i][j] != '\0')
			str = ft_strjoin(str, ft_char_to_str(minishell->envp[i][j++]));
	}
	return (str);
}

static char	*ft_replace(char *input, t_mini *minishell)
{
	int		i;
	char	*str;
	char	*variable;

	i = 0;
	str = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] != '$')
			str = ft_strjoin(str, ft_char_to_str(input[i++]));
		else
		{
			i = i + 1;
			variable = ft_strdup("");
			while (input[i] != '\0' && input[i] != ' ' && input[i] != 34 && input[i] != 39 && input[i] != 58)
				variable = ft_strjoin(variable, ft_char_to_str(input[i++]));
			if (ft_what_should_be_done(input) == 0)
				str = ft_strjoin(str, "$");
			else
				variable = ft_get_variable(variable, minishell);
			str = ft_strjoin(str, variable);
			free(variable);
		}
	}
	return (str);
}

char	**ft_check_variables(char **str, t_mini *minishell)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$') != NULL)
			str[i] = ft_replace(str[i], minishell);
		i++;
	}
	return (str);
}
