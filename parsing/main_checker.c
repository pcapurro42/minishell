/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:57:33 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/29 04:57:33 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_it_quoi(char *input)
{
	if (ft_strlen(input) == 4)
	{
		if ((input[0] == 'q' || input[0] == 'Q') \
			&& (input[1] == 'u' || input[1] == 'U') \
			&& (input[2] == 'o' || input[2] == 'O') \
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

	add_history(input);
	input = ft_input_cleaner(input);
	if (input == NULL)
	{
		g_global->g_last_return_code = 258;
		return (free(input), 1);
	}
	if (ft_is_it_quoi(input) == 1)
		return (free(input), ft_handle_quoi_feur(minishell), 0);
	str = ft_split(input, ' ');
	free(input);
	ft_repair_spaces_in_quotes(str);
	if (ft_pipe_checker(str) != 0 || ft_chevron_checker_b(str) != 0)
	{
		g_global->g_last_return_code = 258;
		pls_free(str);
		return (1);
	}
	ft_prepare_for_heredoc(str);
	ft_check_variables(str, minishell);
	minishell->cmd_lst = ft_share_off(str);
	ft_execution(minishell);
	return (pls_free(str), 0);
}
