/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/02 21:08:20 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	main(int argc, char *argv[])
{
	t_data		*d;

	d = alloc_s_data();
	init_s_matrix(d->mx);
	check_argc(d, argc);
	get_matrix(d, argv[1]);
	init_s_camera(&d->cam, d->mx);
	init_s_mlx(d, d->mlx);
	rendering(d, d->mlx, d->mx);
	key_hook(d, d->mlx);
	mlx_loop(d->mlx->init);
	fdf_exit(d, NULL);
}
