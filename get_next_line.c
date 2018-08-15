/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 21:15:42 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/14 22:42:00 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_new_line(char **s, char **line, int fd)
{
	char	*hold;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		hold = ft_strdup(s[fd] + len + 1);
		free(s[fd]);
		s[fd] += (len + 1);
		s[fd] = hold;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*s[FD_LIM];
	char		buf[BUFF_SIZE + 1];
	char		*hold;
	int			num_read;

	if (fd < 0 || line == NULL || fd > FD_LIM)
		return (-1);
	while ((num_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[num_read] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		hold = ft_strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = hold;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (num_read < 0)
		return (-1);
	else if (num_read == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
		return (0);
	return (ft_new_line(s, line, fd));
}
