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

static t_list	*choose_fd(int fd, t_list **fd_list)
{
	t_list *curr;

	curr = *fd_list;
	while (curr)
	{
		if ((int)curr->content_size == fd)
			return (curr);
		curr = curr->next;
	}
	if (!(curr = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	curr->next = NULL;
	curr->content = (char*)malloc(1);
	((char*)curr->content)[0] = '\0';
	curr->content_size = fd;
	ft_lstadd(fd_list, curr);
	return (curr);
}

static int		handle_saved_line(char **line, t_list **curr)
{
	char	*tmp;
	size_t	len;

	len = ft_strldup_until(line, (*curr)->content, '\n');
	if (((char*)(*curr)->content)[len] == '\n')
		tmp = ft_strdup((*curr)->content + len + 1);
	else
		tmp = ft_strdup((*curr)->content + len);
	free((*curr)->content);
	(*curr)->content = tmp;
	if (((char*)(*curr)->content)[0] == '\0')
		ft_memdel(&(*curr)->content);
	return (1);
}

static int		free_fully_read_fd(t_list **fd_list, size_t curr_fd, char **l)
{
	t_list *this;
	t_list *prev;

	this = *fd_list;
	prev = *fd_list;
	if (this->content_size == curr_fd)
		*fd_list = this->next;
	else
		while (this->next)
		{
			prev = this;
			this = this->next;
			if (this->content_size == curr_fd)
				break ;
		}
	prev->next = this->next;
	(this->content) ? free(this->content) : (0);
	free(this);
	if (*l)
		free(*l);
	this = NULL;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*fd_list = NULL;
	t_list			*curr;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				reads;

	if (fd < 0 || fd > OPEN_MAX || !line || read(fd, buff, 0) < 0
	|| !(curr = choose_fd(fd, &fd_list)))
		return (-1);
	MALLCHECK(*line = ft_strnew(0));
	curr->content = (!curr->content) ? (ft_strnew(0)) : curr->content;
	if (ft_strchr(curr->content, '\n'))
		return (handle_saved_line(line, &curr));
	while ((reads = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[reads] = '\0';
		MALLCHECK(tmp = ft_strjoin(curr->content, buff));
		free(curr->content);
		curr->content = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (reads == 0 && (!(curr->content) || ((char*)curr->content)[0] == '\0'))
		return (free_fully_read_fd(&fd_list, curr->content_size, line));
	return (handle_saved_line(line, &curr));
}
