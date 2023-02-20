/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:06:17 by vdelafos          #+#    #+#             */
/*   Updated: 2022/12/11 17:41:10 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	if (s[i] == (char) c)
		return (i);
	return (-1);
}

char	*get_next_line_ret_neg(char *save, int ret)
{
	char	*line;

	if (save == NULL || save[0] == '\0' || ret < 0)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	else
	{
		line = ft_strdup(save);
		free(save);
		save = NULL;
		return (line);
	}
}

char	*get_next_line_ret_pos(char *buf, char *save, int ret)
{
	char	*temp;

	buf[ret] = '\0';
	if (save == NULL)
		save = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(save, buf);
		free(save);
		save = temp;
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*temp;
	char		*line;
	char		buf[BUFFER_SIZE + 1];
	int			ret;

	while (ft_strchr_i(save, '\n') == -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
		{
			line = get_next_line_ret_neg(save, ret);
			save = NULL;
			return (line);
		}
		save = get_next_line_ret_pos(buf, save, ret);
	}
	line = malloc((ft_strchr_i(save, '\n') + 1) * sizeof(*line) + 1);
	if (line == NULL)
		return (free(save), save = NULL);
	ft_strlcpy(line, save, ft_strchr_i(save, '\n') + 2);
	temp = ft_strdup(&(save[ft_strchr_i(save, '\n') + 1]));
	free(save);
	save = temp;
	return (line);
}
