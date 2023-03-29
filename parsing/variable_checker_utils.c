/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_checker_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:08:43 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/25 00:08:44 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_to_do_quote(char *input)
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
		if (input[i] == 34 && quote % 2 == 0)
			dquote++;
		if (input[i] == 39 && dquote % 2 == 0)
			quote++;
		i++;
	}
	if ((dquote % 2 != 0 && quote % 2 == 0)
		|| (dquote % 2 == 0 && quote % 2 == 0)
		|| (dquote == 0 && quote == 0)
		|| (quote % 2 != 0 && dquote % 2 != 0 && c == 34))
		return (1);
	return (0);
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
			if (ft_in_out_quotes(str, i) != 1)
				sf = ft_join_free(sf, minishell->mini_tools->home_directory);
			else
				sf = ft_join_free(sf, "~");
		}
		i++;
	}
	free(str);
	return (sf);
}
