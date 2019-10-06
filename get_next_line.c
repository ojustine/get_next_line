/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 15:09:44 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/02 18:34:48 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_list	*choose_fd(int fd, t_list *fd_list)
{
	t_list *root;
	t_list *ret;

	root = fd_list;
	while (fd_list && fd_list->content_size != fd)
		fd_list = fd_list->next;
	if (!fd_list)
	{
		if (!(fd_list = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		fd_list->next = NULL;
		fd_list->content_size = fd;
	}
	ret = fd_list;
	fd_list = root;
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*fd_list = NULL;
	t_list			*curr;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				reads;

	if (fd < 0 || !line || BUFF_SIZE < 1 ||	!(curr = choose_fd(fd, fd_list)))
		return (-1);
	while ((reads = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[reads] = '\0';
		if (curr->content == NULL)
			curr->content = ft_strnew(0);
		tmp = ft_strjoin(curr->content, buff);
		free(curr->content);
		curr->content = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (reads < 0)
		return (-1);
	else if (reads == 0 && (curr->content == NULL || curr->content == '\0'))
		return (0);
}
