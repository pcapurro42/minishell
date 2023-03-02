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
	int		dquote;
	int		quote;
	char	c;

	i = 0;
	dquote = 0;
	quote = 0;
	c = 0;
	while (input[i] != '$')
	{
		if (c == 0 && (input[i] == 34 || input[i] == 39))
			c = input[i];
		if (input[i] == 34)
			dquote++;
		if (input[i] == 39)
			quote++;
		i++;
	}
	if ((dquote % 2 != 0 && quote % 2 == 0) || (dquote % 2 == 0 && quote % 2 == 0) || (dquote == 0 && quote == 0) || (quote % 2 != 0 && dquote % 2 != 0 && c == 34))
		return (1);
	return (0);
}

// MÉTHODE :
// - On analyse seulement tout ce qui se situe à gauche du '$'
// - On compte le nombre de sinple quotes et de double quotes
// Quatre cas possible (écrit dans le même ordre que le if final pour plus de compréhension) :
// 1. Si dquote = impaire, squote = paire, le quote à prendre en compte est le double quote (return 1)
// 2. Si squote = paire, dquote = paire, c'est comme si il n'y avait aucune quote (return 1)
// 3. Si squote = impaire, dquote = impaire, le 1er quote en partant de la gauche est prioritaire (on regarde 'c' qui nous a servi à stocker le premier quote rencontré)
// 4. Si dquote = paire, squote = impaire, le quote à prendre en compte est le simple quote (return 0)

// return 0 = on laisse le contenu de variable tel quel
// return 1 = on remplace le contenu de variable par sa variable

// Là c'était juste pour détecter, remplacer si nécessaire ça va être un enfer sur Terre paix à mon âme...

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
