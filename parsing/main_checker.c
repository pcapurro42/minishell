/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:05:44 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/24 17:18:38 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_deliver_input(char **strf);

char	*ft_analyze_input(char *input)
{
	int		i;
	char	*str;
	char	**strf;

	i = 0;
	str = ft_input_cleaner(input);
	if (str == NULL)
		return (NULL);

	strf = ft_split(str, ' ');
	strf = ft_repair_spaces_in_quotes(strf);

	if (ft_syntax_checker(strf) != 0)
		return (NULL);
	// if (ft_consistency_checker(strf) != 0)
	// 	return (NULL);
	// ft_deliver_input(strf);
	return (NULL);
}

	// while (strf[i] != NULL)
	// 	printf("%s\n", strf[i++]);

// "|"
// ">"
// ">>"
