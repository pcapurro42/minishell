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

void	*ft_analyze_input(char *input, t_mini *minishell)
{
	int		i;
	char	**str;
	// char	***fstr;

	i = 0;
	input = ft_input_cleaner(input);
	if (input == NULL)
		return (NULL);
	str = ft_split(input, ' ');
	str = ft_repair_spaces_in_quotes(str);
	if (ft_syntax_checker(str) != 0)
		return (NULL);
	str = ft_check_variables(str, minishell);
	minishell->cmd_lst = ft_share_off(str);
	ft_execution(minishell);
	return (NULL);
}

	// while (str[i] != NULL)
	// 	printf("%s\n", str[i++]);

		// fstr = ft_share_off(str);
	// printf("== DOUBLE TABLEAU ==\n");
	// while (str[i] != NULL)
	// 	printf("%s\n", str[i++]);
	// printf("\n== TRIPLE TABLEAU ==\n");
	// int f = 0;
	// int g = 0;
	// while (fstr[f] != NULL)
	// {
	// 	printf("\nTABLEAU %d\n", f + 1);
	// 	while (fstr[f][g] != NULL)
	// 		printf("%s\n", fstr[f][g++]);
	// 	g = 0;
	// 	f++;
	// }
	// minishell->cmd_lst = fstr;