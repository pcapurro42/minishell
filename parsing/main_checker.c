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

int	ft_analyze_input(char *input, t_mini *minishell)
{
	int		i;
	char	**str;

	i = 0;
	input = ft_input_cleaner(input);
	if (input == NULL)
		return (free(input), 1);
	str = ft_split(input, ' ');
	ft_check_malloc(str);
	str = ft_repair_spaces_in_quotes(str);
	if (ft_syntax_checker(str) != 0)
		return (pls_free(str), 1);
	str = ft_check_variables(str, minishell);
	minishell->cmd_lst = ft_share_off(str);
	pls_free(str);
	ft_execution(minishell);
	return (0);
}

// exit $USER '$USER' "'$USER'" << EOF ls >> f ls > > f cat | ls|grep "fefeqf  fq      fefeqef" ' fqfeqfeqfe f  fq'