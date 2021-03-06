/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:19 by edessain          #+#    #+#             */
/*   Updated: 2019/12/14 11:23:37 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_free(char **string, int nb)
{
	if (*string)
	{
		free(*string);
		*string = NULL;
	}
	return (nb);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)&str[i] + 1);
		i++;
	}
	if (c == 0)
		return ((char *)&str[i] + 1);
	return (NULL);
}

char	*ft_strndup(const char *str, const char c)
{
	int		i;
	int		j;
	char	*src;

	i = 0;
	j = 0;
	if (str == NULL)
		return (ft_strndup("", '\0'));
	while (str[j] != c)
		j++;
	src = malloc((j + 1) * sizeof(*src));
	if (src == 0)
		return (0);
	while (str[i] != '\0' && str[i] != c)
	{
		src[i] = str[i];
		i++;
	}
	src[i] = '\0';
	return (src);
}

int		ft_read(int fd, char **line, char *rest)
{
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	if (rest != NULL)
		if ((*line = ft_strndup(rest, '\0')) == NULL)
			return (ft_free(&rest, -1));
	if (rest == NULL)
		if ((*line = ft_strndup("", '\0')) == NULL)
			return (-1);
	while ((ft_strchr(*line, '\n') == NULL) &&
			(ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		tmp = *line;
		buf[ret] = '\0';
		if ((*line = ft_strjoin(*line, buf)) == NULL)
			return (ft_free(&rest, -1));
		ft_free(&tmp, 1);
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	static char	*rest[FOPEN_MAX];
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if ((ret = ft_read(fd, line, rest[fd])) == -1)
		return (ft_free(&rest[fd], -1));
	if (rest[fd] != NULL)
		ft_free(&rest[fd], 1);
	if ((rest[fd] = ft_strndup(ft_strchr(*line, '\n'), '\0')) == NULL)
		return (ft_free(&rest[fd], -1));
	if (ft_strchr(*line, '\n') == NULL)
		return (ft_free(&rest[fd], 0));
	tmp = *line;
	if ((*line = ft_strndup(*line, '\n')) == NULL)
		return (ft_free(&rest[fd], -1));
	free(tmp);
	tmp = NULL;
	return (1);
}
