/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:58:26 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/29 04:58:27 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_capture_variable_content(char *var, t_mini *minishell)
{
	int		j;
	char	*temporary;
	char	*tmp;
	char	*str;

	j = 0;
	if (var[0] == '?' && var[1] == '\0')
		return (free(var), ft_itoa(g_global->g_last_return_code));
	else
	{
		temporary = ft_strdup("");
		var = ft_join_free(var, "=");
	}
	str = ft_cv_start(minishell, temporary, var, j);
	tmp = ft_strtrim(str, " ");
	free(str);
	return (tmp);
}

char	*ft_capture_variable_name(char *str, int *i)
{
	char	*variable;
	char	*temp;

	variable = ft_strdup("");
	(*i)++;
	while (str[*i] != '\0' && ft_is_delimiter(str[*i]) == 0)
	{
		temp = ft_char_to_str(str[*i]);
		variable = ft_join_free(variable, temp);
		free(temp);
		(*i)++;
	}
	(*i)--;
	return (variable);
}

char	*ft_get_variable(char *str, t_mini *minishell)
{
	int		i;
	char	*strf;
	char	*variable;
	char	*temp;

	i = 0;
	strf = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] != '$' || (str[i] == '$' && ft_to_do_quote(str, i) == 0))
		{
			temp = ft_char_to_str(str[i]);
			strf = ft_join_free(strf, temp);
			free(temp);
		}
		else
		{
			variable = ft_capture_variable_name(str, &i);
			temp = ft_capture_variable_content(variable, minishell);
			strf = ft_join_free(strf, temp);
			free(temp);
		}
		i++;
	}
	return (free(str), strf);
}

void	ft_check_variables(char **str, t_mini *minishell)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$') != NULL)
			str[i] = ft_get_variable(str[i], minishell);
		i++;
	}
}
