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
#include "../libft/libft.h"

static t_fd_list	*choose_fd(int fd, t_fd_list **list)
{
	t_fd_list *new_node;

	new_node = *list;
	while (new_node)
	{
		if (new_node->fd == fd)
			return (new_node);
		new_node = new_node->next;
	}
	if (!(new_node = malloc(sizeof(t_fd_list))))
		return (NULL);
	new_node->next = NULL;
	new_node->line = NULL;
	new_node->fd = fd;
	new_node->next = *list;
	*list = new_node;
	return (new_node);
}

static int		handle_saved_line(char **line, t_fd_list **node)
{
	size_t			ret_len;
	const char		*nl_ptr = ft_strchr((*node)->line, '\n');
	char			*tmp;

	ret_len = nl_ptr ? nl_ptr - (*node)->line : ft_strlen((*node)->line);
	*line = ft_strndup((*node)->line, ret_len);
	tmp = NULL;
	if (((*node)->line)[ret_len] == '\n')
		tmp = ft_strdup((*node)->line + ret_len + 1);
	free((*node)->line);
	(*node)->line = tmp;
	return (1);
}

static int		free_fully_read_fd(t_fd_list **list, int fd)
{
	t_fd_list *this;
	t_fd_list *prev;

	this = *list;
	prev = *list;
	if (this->fd == fd)
		*list = this->next;
	else
		while (this->next)
		{
			prev = this;
			this = this->next;
			if (this->fd == fd)
				break ;
		}
	prev->next = this->next;
	free(this);
	this = NULL;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_fd_list	*fd_list;
	t_fd_list			*node;
	char				buff[BUFF_SIZE + 1];
	char				*tmp;
	int					reads;

	if (fd < 0 || !line || read(fd, buff, 0) < 0
	|| !(node = choose_fd(fd, &fd_list)))
		return (-1);
	if (node->line && ft_strchr(node->line, '\n'))
		return (handle_saved_line(line, &node));
	while ((reads = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[reads] = '\0';
		tmp = (node->line) ? ft_strjoin(node->line, buff) : ft_strdup(buff);
		free(node->line);
		node->line = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (reads == 0 && !node->line)
		return (free_fully_read_fd(&fd_list, node->fd));
	return (handle_saved_line(line, &node));
}
