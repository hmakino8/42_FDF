/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 04:37:34 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/19 00:55:25 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_print.h"

int	ft_putchar_pt(const unsigned char c, t_pt *pt)
{
	pt->total_output++;
	if (!pt->check_overflow)
		return (0);
	return (write(pt->fd, &c, 1));
}

unsigned long	is_neg(int n, t_pt *pt)
{
	long long	num;

	num = n;
	if (num < 0)
	{
		num = -num;
		pt->sign = '-';
	}
	return ((unsigned long)num);
}

int	ft_atoi_pt(const char *s1, t_pt *pt)
{
	unsigned int	num;

	num = 0;
	while ('0' <= s1[pt->idx] && s1[pt->idx] <= '9' && \
			num <= (unsigned int)INT_MAX + 1)
		num = num * 10 + (s1[pt->idx++] - '0');
	if ((unsigned int)INT_MAX < num)
	{
		pt->overflow = 1;
		num = 0;
	}
	return ((int)num);
}

int	ft_get_digit(unsigned long num, t_pt *pt)
{
	int	digit;

	if (pt->sign != '-' && pt->flag_plus)
		pt->sign = '+';
	digit = 1;
	while (pt->base <= num)
	{
		num /= pt->base;
		digit++;
	}
	if ((num && ((pt->flag_sharp && pt->spec == 'x') || \
			(pt->flag_sharp && pt->spec == 'X'))) || pt->spec == 'p')
		digit += 2;
	return (digit);
}

unsigned char	*ft_itoa_base(unsigned long num, t_pt *pt)
{
	int				len;
	unsigned char	*str;

	len = ft_get_digit(num, pt);
	str = (unsigned char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = num % pt->base + '0';
		if ('9' < str[len])
			str[len] = num % pt->base - 10 + 'a';
		if ('9' < str[len] && pt->spec == 'X')
			str[len] -= ('a' - 'A');
		num /= pt->base;
		pt->len++;
	}
	if ((pt->flag_sharp && pt->spec == 'x') || pt->spec == 'p')
		str[1] = 'x';
	if (pt->flag_sharp && pt->spec == 'X')
		str[1] = 'X';
	if ((size_t)INT_MAX + 1 < pt->prec + (0 < pt->sign) + pt->flag_space)
		pt->overflow = 1;
	return (str);
}
