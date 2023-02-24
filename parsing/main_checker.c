/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:05:44 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/24 16:47:30 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_deliver_input(char **str);

char	*ft_analyze_input(char *input)
{
	int		i;
	char	*str;
	char	**strf;

	i = 0;
	str = ft_clean_input(input);
	if (ft_syntax_checker(str) != 0)
	{
		free(str);
		return (NULL);
	}
	str = ft_remove_simple_and_double_quotes(str);
	strf = ft_split(str, ' ');
	free(str);
	// if (ft_consistency_checker(strf) != 0)
	// {
	// 	pls_free(strf);
	// 	return (NULL);
	// }
	// ft_deliver_input(strf);
	return (NULL);
}

// "|"
// ">"
// ">>"
