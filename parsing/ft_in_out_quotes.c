/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:06:47 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/29 02:06:48 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_iq_main(char *str, int i, int quote, int dquote)
{
	int	j;

	j = 0;
	while (str[j] != '\0' && j != i)
	{
		if (str[j] == 34 && quote == 0)
		{
			if (dquote == 0)
				dquote = 1;
			else
				dquote = 0;
		}
		if (str[j] == 39 && dquote == 0)
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		j++;
	}
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	return (0);
}

int	ft_in_out_quotes(char *str, int i)
{
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	if (ft_iq_main(str, i, quote, dquote) != 0)
		return (1);
	return (0);
}
