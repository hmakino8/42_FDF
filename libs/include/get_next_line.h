/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 04:36:17 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/20 03:23:58 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define NORMAL 1
# define END_OF_FILE 0
# define ERROR -1
# define MALLOC_FAILURE -2

typedef struct s_gnl
{
	int			fd;
	int			signal;
	ssize_t		byte;
	size_t		locate;
	char		*ret;
	char		*buf;
}	t_gnl;

//get_next_line.c
char	*get_next_line(int fd, int *signal);
void	locate_line_feed(char **stock, t_gnl *gnl);
void	load_buffer(char **stock, t_gnl *gnl);
void	joint_buffer(char **stock, t_gnl *gnl);
void	split_buffer(char **stock, t_gnl *gnl);
//get_next_line_utils.c
char	*ft_substr_gnl(char const *s, size_t start, size_t len, t_gnl *gnl);
char	*ft_strjoin_gnl(char const *s1, char const *s2, t_gnl *gnl);

#endif
