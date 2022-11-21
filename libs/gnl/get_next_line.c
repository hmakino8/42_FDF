/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 04:28:39 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/20 02:21:21 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd, int *signal)
{
	static char	*stock[OPEN_MAX];
	size_t		stock_len;
	t_gnl		gnl;

	gnl.fd = fd;
	gnl.signal = NORMAL;
	gnl.ret = NULL;
	locate_line_feed(&stock[gnl.fd], &gnl);
	split_buffer(&stock[gnl.fd], &gnl);
	if (gnl.signal == END_OF_FILE)
	{
		if (!(stock[gnl.fd] != NULL && *stock[gnl.fd] == '\0'))
		{
			stock_len = ft_strlen(stock[gnl.fd]);
			gnl.ret = ft_substr_gnl(stock[gnl.fd], 0, stock_len, &gnl);
		}
		free(stock[gnl.fd]);
		stock[gnl.fd] = NULL;
	}
	*signal = gnl.signal;
	return (gnl.ret);
}

void	locate_line_feed(char **stock, t_gnl *gnl)
{
	char	*tmp;

	if (BUFFER_SIZE <= 0 || gnl->fd < 0 || OPEN_MAX < gnl->fd)
	{
		gnl->signal = ERROR;
		return ;
	}
	if (*stock == NULL)
		*stock = ft_substr_gnl("", 0, 0, gnl);
	if (gnl->signal == MALLOC_FAILURE)
		return ;
	gnl->locate = 0;
	while (gnl->locate == 0 && gnl->signal == NORMAL)
	{
		tmp = ft_strchr(*stock, '\n');
		if (tmp == NULL)
			load_buffer(stock, gnl);
		else
			gnl->locate = tmp - *stock + 1;
	}
}

void	load_buffer(char **stock, t_gnl *gnl)
{
	gnl->buf = (char *)malloc(BUFFER_SIZE + 1UL);
	if (gnl->buf == NULL)
	{
		gnl->signal = MALLOC_FAILURE;
		free (*stock);
		return ;
	}
	gnl->byte = read(gnl->fd, gnl->buf, BUFFER_SIZE);
	if (gnl->byte < 0)
	{
		gnl->signal = ERROR;
		free(*stock);
		*stock = NULL;
	}
	if (gnl->byte == 0)
		gnl->signal = END_OF_FILE;
	if (gnl->signal != NORMAL)
	{
		free(gnl->buf);
		gnl->buf = NULL;
	}
	else
		gnl->buf[gnl->byte] = '\0';
	joint_buffer(stock, gnl);
}

void	joint_buffer(char **stock, t_gnl *gnl)
{
	char	*tmp;

	if (gnl->signal != NORMAL)
		return ;
	tmp = ft_strjoin_gnl(*stock, gnl->buf, gnl);
	free(*stock);
	if (gnl->signal == MALLOC_FAILURE)
		return ;
	*stock = ft_substr_gnl(tmp, 0, ft_strlen(tmp), gnl);
	free(gnl->buf);
	gnl->buf = NULL;
	free(tmp);
}

void	split_buffer(char **stock, t_gnl *gnl)
{
	size_t	len;
	char	*tmp;

	if (gnl->locate == 0 || gnl->signal != NORMAL)
		return ;
	gnl->ret = ft_substr_gnl(*stock, 0, gnl->locate, gnl);
	if (gnl->signal == MALLOC_FAILURE)
	{
		free(*stock);
		return ;
	}
	len = 0;
	len = ft_strlen(*stock) - gnl->locate;
	tmp = ft_substr_gnl(*stock, gnl->locate, len, gnl);
	free(*stock);
	if (gnl->signal == MALLOC_FAILURE)
		return ;
	*stock = ft_substr_gnl(tmp, 0, len, gnl);
	free(tmp);
}
