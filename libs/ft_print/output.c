/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 04:29:38 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/19 00:41:04 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_print.h"

void	output(unsigned char *args, t_pt *pt)
{
	while (!pt->flag_align && !pt->flag_zero && 0 < pt->width--)
		ft_putchar_pt(' ', pt);
	if (!pt->spec_cs && !pt->sign && pt->flag_space)
		ft_putchar_pt(' ', pt);
	if (!pt->spec_cs && pt->sign)
		ft_putchar_pt(pt->sign, pt);
	while ((pt->has_prec < 0 && 0 < (int)pt->prec--) || \
		(!pt->flag_align && pt->flag_zero && 0 < pt->width--))
		ft_putchar_pt('0', pt);
	while (0 < pt->len--)
		ft_putchar_pt(*args++, pt);
	while (pt->flag_align && !pt->flag_zero && 0 < pt->width--)
		ft_putchar_pt(' ', pt);
	while (pt->flag_align && pt->flag_zero && 0 < pt->width--)
		ft_putchar_pt('0', pt);
}

void	specifier_percent_c(va_list ap, t_pt *pt)
{
	unsigned char	*args;

	args = malloc(2);
	if (!args)
		return ;
	if (pt->spec == 'c')
	{
		pt->ch = va_arg(ap, int);
		if (!pt->ch)
			args[0] = '\0';
	}
	if (pt->spec == '%')
		pt->ch = '%';
	if (pt->ch)
		args[0] = pt->ch;
	args[1] = '\0';
	pt->len = 1;
	if (pt->width)
		pt->width -= (int)pt->len;
	output(args, pt);
	free(args);
}

void	specifier_s(va_list ap, t_pt *pt)
{
	unsigned char	*args;

	args = va_arg(ap, unsigned char *);
	if (!args)
		args = (unsigned char *)"(null)";
	while (args && args[pt->len] && pt->len <= (size_t)INT_MAX + 1 && \
			!(pt->has_prec && (!pt->digit_prec || !pt->prec)))
		pt->len++;
	if ((size_t)INT_MAX < pt->len)
		pt->overflow = 1;
	else
	{
		if (pt->prec && pt->prec < pt->len)
			pt->len = pt->prec;
		if (pt->width)
			pt->width -= (int)pt->len;
		output(args, pt);
	}
}

void	specifier_idupx(va_list ap, t_pt *pt)
{
	unsigned char	*args;

	if (pt->spec == 'i' || pt->spec == 'd')
		args = ft_itoa_base(is_neg(va_arg(ap, int), pt), pt);
	if (pt->spec == 'u' || pt->spec == 'x' || pt->spec == 'X')
		args = ft_itoa_base(va_arg(ap, unsigned int), pt);
	if (pt->spec == 'p')
		args = ft_itoa_base(va_arg(ap, unsigned long), pt);
	if (pt->flag_zero && (pt->has_prec || pt->flag_align))
		pt->flag_zero = 0;
	if (*args == '0' && pt->has_prec && (!pt->digit_prec || !pt->prec))
		pt->len = 0;
	if (pt->width && pt->prec && pt->len < pt->prec)
		pt->width -= ((int)pt->prec + (0 < pt->sign) + pt->flag_space);
	else if (pt->width)
		pt->width -= (pt->len + (0 < pt->sign) + pt->flag_space);
	if (pt->len < pt->prec)
	{
		pt->has_prec = -1;
		pt->prec -= pt->len;
	}
	if (!pt->overflow)
		output(args, pt);
	free(args);
}
