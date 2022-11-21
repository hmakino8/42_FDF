/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 04:24:44 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/18 23:02:34 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_print.h"

void	initialize_info(t_pt *pt)
{
	pt->width = 0;
	pt->prec = 0;
	pt->spec = 0;
	pt->spec_cs = 0;
	pt->base = 10;
	pt->sign = 0;
	pt->digit_width = 0;
	pt->digit_prec = 0;
	pt->flag_zero = 0;
	pt->flag_align = 0;
	pt->flag_plus = 0;
	pt->flag_space = 0;
	pt->flag_sharp = 0;
	pt->has_prec = 0;
	pt->len = 0;
	pt->ch = 0;
}
