/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 15:10:12 by ojustine          #+#    #+#             */
/*   Updated: 2019/10/02 15:17:29 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 512
# define MALLCHECK(x) if (!(x)) return (-1);

# include <limits.h>
# include <stdlib.h>
# include <string.h>

int	get_next_line(const int fd, char **line);

# if (BUFF_SIZE < 1)
#  error "BUFF_SIZE must be strictly positive"
# endif
# if (BUFF_SIZE > SIZE_MAX)
#  warning "BUFF_SIZE current value may cause a stack overflow"
# endif
#endif
