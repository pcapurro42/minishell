/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:05:44 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/16 02:46:32 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_it_quoi(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strlen(input) == 4)
	{
		if ((input[0] == 'q' || input[0] == 'Q')
		&& (input[1] == 'u' || input[1] == 'U')
		&& (input[2] == 'o' || input[2] == 'O')
		&& (input[3] == 'i' || input[3] == 'I'))
			return (1);
	}
	return (0);
}

void	ft_handle_quoi_feur(t_mini *minishell)
{
	if (minishell->mini_tools->quoifeur == 0)
		printf("feur\n");
	if (minishell->mini_tools->quoifeur == 1)
		printf("feur ! 🤣\n");
	if (minishell->mini_tools->quoifeur == 2)
		printf("feur !! 🤣🤣\n");
	if (minishell->mini_tools->quoifeur == 3)
		printf("feur !! 🤣😹 (tu l'as ? 😹😹)\n");
	if (minishell->mini_tools->quoifeur == 4)
		printf("feur !!!!! 🤣🤣😹😹😹 (tu l'as ou pas ? 🤣)\n");
	if (minishell->mini_tools->quoifeur > 4)
		printf("minishell: feur: command not found (you broke feur...)\n");
	minishell->mini_tools->quoifeur++;
}

int	ft_analyze_input(char *input, t_mini *minishell)
{
	char	**str;
	char	***strf;

	input = ft_input_cleaner(input);
	if (input == NULL)
		return (free(input), 1);
	if (ft_is_it_quoi(input) == 1)
		return (free(input), ft_handle_quoi_feur(minishell), 0);
	str = ft_split(input, ' ');
	free(input);
	ft_check_malloc(str);
	ft_repair_spaces_in_quotes(str);
	if (ft_syntax_checker(str) != 0)
		return (pls_free(str), 1);
	ft_check_variables(str, minishell);
	strf = ft_share_off(str);
	minishell->cmd_lst = strf;
	pls_free(str);
	ft_execution(minishell);
	return (0);
}
