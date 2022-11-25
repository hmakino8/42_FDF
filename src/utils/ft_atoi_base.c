/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 23:44:45 by hiroaki           #+#    #+#             */
/*   Updated: 2022/11/26 03:59:16 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <stdio.h>

static bool	is_overflow(unsigned long num, int sign)
{
	if ((sign > 0 && num > LONG_MAX) || \
		(sign < 0 && num > (LONG_MAX + 1UL)))
		return (true);
	return (false);
}

static bool	is_valid_base(char *str, int base, bool *ok)
{
	if (base == 16)
	{
		if (ft_strncmp(str, "0X", 2) && ft_strncmp(str, "0x", 2))
			return (false);
		else
			str += 2;
	}
	return (true);
}

static int	conv_decimal_digit(char c, int base)
{
	int			d;
	const char	*digits;

	digits = ft_strdup("0123456789ABCDEF");
	if (!digits)
		return (-1);
	d = -1;
	while (digits[++d])
	{
		if (digits[d] == c)
			break ;
		if (!digits[d])
		{
			free((void *)digits);
			return (-1);
		}
	}
	free((void *)digits);
	return (d);
}

static int	convert_num(char *str, int base, int sign, bool *ok)
{
	int				d;
	unsigned long	num;

	num = 0;
	while (1)
	{
		d = conv_decimal_digit(*(str++), base);
		if (d < 0)
			return (-1);
		num = num * base + d;
		if (is_overflow(num, sign))
			return (-1);
		if (!*str)
			break ;
	}
	*ok = true;
	return ((int)num * sign);
}

int	ft_atoi_base(char *str, int base, bool *ok)
{
	int	sign;

	sign = 1;
	*ok = false;
	if (!str || !is_valid_base(str, base, ok))
		return (-1);
	else if (base == 16)
		str += 2;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*(str++) == '-')
			sign = -1;
	}
	return (convert_num(str, base, sign, ok));
}
