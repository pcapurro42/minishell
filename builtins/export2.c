/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:42 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/20 16:56:27 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_verify_errors_export_2(char *name_str)
{
	int	i;

	i = 0;
	if ((name_str[i] == '#' || name_str[i] == '&' || \
	name_str[i] == '_' || name_str[i] == '*') && name_str[1] == '\0')
		return (1);
	if (name_str[i] == '\0')
		return (1);
	while (name_str[i] != '=' && name_str[i] != '\0')
	{
		if ((ft_isalpha(name_str[i]) == 0 && \
		ft_isdigit(name_str[i]) == 0) && name_str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_verify_errors_export(char *str)
{
	char	*name_str;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_check_malloc(name_str);
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
	{
		name_str = ft_strdup(str);
		ft_check_malloc(name_str);
	}
	if (ft_verify_errors_export_2(name_str) == 1)
	{
		free(name_str);
		return (1);
	}
	free(name_str);
	return (0);
}

static int	ft_verify_characters_export_2(char *str, char *name_str)
{
	int	i;

	i = 0;
	if ((name_str[i] == '#' || name_str[i] == '&' || \
	name_str[i] == '_' || name_str[i] == '*') && name_str[1] == '\0')
		return (1);
	if (name_str[i] == '\0')
		return (printf("minishell: export: '%s': \
not a valid identifier\n", str));
	while (name_str[i] != '=' && name_str[i] != '\0')
	{
		if ((ft_isalpha(name_str[i]) == 0 && \
		ft_isdigit(name_str[i]) == 0) && name_str[i] != '_')
			return (printf("minishell: export: '%s': \
not a valid identifier\n", str));
		i++;
	}
	return (0);
}

int	ft_verify_characters_export(char *str)
{
	char	*name_str;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_check_malloc(name_str);
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
	{
		name_str = ft_strdup(str);
		ft_check_malloc(name_str);
	}
	if (ft_verify_characters_export_2(str, name_str) == 1)
	{
		free(name_str);
		return (1);
	}
	free(name_str);
	return (0);
}
