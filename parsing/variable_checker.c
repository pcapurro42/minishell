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

char	*ft_get_variable(char *var, t_mini *minishell)
{
	int		j;
	char	*temporary;

	j = 0;
	if (var[0] == '?' && var[1] == '\0')
		return (ft_itoa(g_global->g_last_return_code));
	else
	{
		temporary = ft_strdup("");
		var = ft_join_free(var, "=");
	}
	return (ft_gv_start(minishell, temporary, var, j));
}

char	*ft_cv_end(t_mini *minishell, char *in, char *str, char *var)
{
	if (ft_to_do_quote(in) == 0)
		str = ft_join_free(str, "$");
	else
		var = ft_get_variable(var, minishell);
	str = ft_join_free(str, var);
	free(var);
	return (str);
}

char	*ft_cv_heart(t_mini *minishell, char *in, char *str, char *var)
{
	int		i;
	char	*temp;

	i = 0;
	while (in[i] != '\0')
	{
		if (in[i] != '$')
		{
			temp = ft_char_to_str(in[i++]);
			str = ft_join_free(str, temp);
			free(temp);
		}
		else if (in[i++] == '$')
		{
			while (in[i] != '\0' && in[i] != ' ' && in[i] != 34 && in[i] != 39 \
				&& in[i] != ':' && in[i] != '$' && in[i] != ']' && in[i] != '[')
			{
				temp = ft_char_to_str(in[i++]);
				var = ft_join_free(var, temp);
				free(temp);
			}
			str = ft_cv_end(minishell, in, str, var);
		}
	}
	return (free(in), str);
}

char	*ft_capture_variable(char *in, t_mini *minishell)
{
	char	*str;
	char	*var;
	char	*temp;

	var = ft_strdup("");
	temp = ft_strjoin("$", in);
	free(in);
	str = ft_cv_heart(minishell, temp, ft_strdup(""), var);
	temp = ft_strtrim(str, " ");
	free(str);
	str = ft_strjoin("'", temp);
	free(temp);
	str = ft_join_free(str, "'");
	return (str);
}

char	**ft_check_variables(char **str, t_mini *minishell)
{
	int		i;
	int		j;
	char	**str_tmp;

	i = 0;
	j = -1;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$') != NULL)
		{
			str_tmp = ft_split(str[i], '$');
			free(str[i]);
			while (str_tmp[++j] != NULL)
				str_tmp[j] = ft_capture_variable(str_tmp[j], minishell);
			j = 0;
			str[i] = ft_strdup("");
			while (str_tmp[j] != NULL)
				str[i] = ft_join_free(str[i], str_tmp[j++]);
			pls_free(str_tmp);
		}
		i++;
	}
	return (str);
}
