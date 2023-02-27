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

char	***ft_share_out(char **str);

char	*ft_analyze_input(char *input)
{
	int		i;
	char	**str;

	i = 0;
	input = ft_input_cleaner(input);
	if (input == NULL)
		return (NULL);
	str = ft_split(input, ' ');
	str = ft_repair_spaces_in_quotes(str);
	if (ft_syntax_checker(str) != 0)
		return (NULL);
	while (str[i] != NULL)
		printf("%s\n", str[i++]);
	// if (ft_consistency_checker(str) != 0)
	// 	return (NULL);
	// ft_share_out(str);
	return (NULL);
}

// while (strf[i] != NULL)
// 	printf("%s\n", strf[i++]);
// "|"
// ">"
// ">>"
