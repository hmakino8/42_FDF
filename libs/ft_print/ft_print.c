/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 04:24:44 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/19 00:54:18 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_print.h"

int	ft_printf(const char *format, ...)
{
	t_pt	pt;
	va_list	ap;

	pt.check_overflow = 0;
	while (pt.check_overflow < 2)
	{
		pt.fd = 1;
		pt.idx = 0;
		pt.total_output = 0;
		pt.overflow = 0;
		initialize_info(&pt);
		va_start(ap, format);
		scrape_hub(ap, format, &pt);
		va_end(ap);
		if (pt.overflow || (size_t)INT_MAX < pt.total_output)
			return (-1);
		pt.check_overflow++;
	}
	return ((int)pt.total_output);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_pt	pt;
	va_list	ap;

	pt.check_overflow = 0;
	while (pt.check_overflow < 2)
	{
		pt.fd = fd;
		pt.idx = 0;
		pt.total_output = 0;
		pt.overflow = 0;
		initialize_info(&pt);
		va_start(ap, format);
		scrape_hub(ap, format, &pt);
		va_end(ap);
		if (pt.overflow || (size_t)INT_MAX < pt.total_output)
			return (-1);
		pt.check_overflow++;
	}
	return ((int)pt.total_output);
}
