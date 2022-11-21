/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 04:36:46 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/19 00:42:18 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_print.h"

static void	scrape_flag(const char *s1, t_pt *pt)
{
	pt->idx++;
	while (s1[pt->idx] == '-' || s1[pt->idx] == '+' || s1[pt->idx] == ' ')
	{
		if (s1[pt->idx] == '-')
			pt->flag_align = 1;
		if (s1[pt->idx] == '+')
			pt->flag_plus = 1;
		if (s1[pt->idx] == ' ' && !pt->flag_plus)
			pt->flag_space = 1;
		else
			pt->flag_space = 0;
		pt->idx++;
	}
	if (s1[pt->idx] == '#' || pt->spec == 'p')
	{
		pt->flag_sharp = 1;
		pt->idx++;
	}
	if (s1[pt->idx] == '0')
	{
		pt->flag_zero = 1;
		pt->idx++;
	}
}

static void	scrape_width_prec(va_list ap, const char *s1, t_pt *pt)
{
	if (s1[pt->idx] == '*')
	{
		pt->width = va_arg(ap, int);
		pt->idx++;
	}
	if ('0' <= s1[pt->idx] && s1[pt->idx] <= '9')
		pt->width = ft_atoi_pt(s1, pt);
	if (pt->width)
		pt->digit_width = ft_get_digit(pt->width, pt);
	if (!pt->overflow && s1[pt->idx] == '.')
	{
		pt->idx++;
		pt->has_prec = 1;
		if (s1[pt->idx] == '*')
		{
			pt->prec = va_arg(ap, int);
			pt->idx++;
		}
		if ('0' <= s1[pt->idx] && s1[pt->idx] <= '9')
			pt->prec = (size_t)ft_atoi_pt(s1, pt);
		pt->digit_prec = ft_get_digit(pt->prec, pt);
	}
}

static void	scrape_spec(va_list ap, const char *s1, t_pt *pt)
{
	if (s1[pt->idx] == '%' || s1[pt->idx] == 'c' || s1[pt->idx] == 's' || \
		s1[pt->idx] == 'i' || s1[pt->idx] == 'd' || s1[pt->idx] == 'u' || \
			s1[pt->idx] == 'p' || s1[pt->idx] == 'x' || s1[pt->idx] == 'X')
	{
		pt->spec = s1[pt->idx];
		if (s1[pt->idx] == '%' || s1[pt->idx] == 'c' || s1[pt->idx] == 's')
		{
			pt->spec_cs++;
			if (s1[pt->idx] == '%' || s1[pt->idx] == 'c')
				specifier_percent_c(ap, pt);
			else
				specifier_s(ap, pt);
		}
		else
		{
			if (s1[pt->idx] == 'p' || s1[pt->idx] == 'x' || s1[pt->idx] == 'X')
				pt->base = 16;
			specifier_idupx(ap, pt);
		}
		pt->idx++;
	}
}

void	scrape_hub(va_list ap, const char *s1, t_pt *pt)
{
	while (s1[pt->idx])
	{
		if (s1[pt->idx] != '%')
			ft_putchar_pt(s1[pt->idx++], pt);
		else if (s1[pt->idx + 1])
		{
			scrape_flag(s1, pt);
			scrape_width_prec(ap, s1, pt);
			if (pt->overflow)
				return ;
			scrape_spec(ap, s1, pt);
			initialize_info(pt);
		}
	}
}
