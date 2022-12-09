/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/09 17:36:46 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	init_axis(t_camera *cam)
{
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
}

void	init_fd(t_data *d, int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (fd <= 0)
		fdf_exit(d, "Failed to open file.");
}

void	init_s_mlx(t_data *d, t_mlx *mlx)
{
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->data_addr = NULL;
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, SCR_WIDTH, SCR_HEIGHT, "FdF");
	mlx->img = mlx_new_image(mlx->init, SCR_WIDTH, SCR_HEIGHT);
	mlx->data_addr = \
	mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	if (!mlx->init || !mlx->win || !mlx->img || !mlx->data_addr)
	{
		mlx_destroy_window(mlx->init, mlx->win);
		mlx_destroy_image(mlx->init, mlx->img);
		free(mlx->data_addr);
		free(mlx->init);
		fdf_exit(d, "Malloc Failure");
	}
}

void	init_s_camera(t_camera *cam, t_matrix *mx)
{
	int	width_ratio;
	int	height_ratio;

	width_ratio = SCR_WIDTH / mx->width / 2;
	height_ratio = SCR_HEIGHT / mx->height / 2;
	cam->zoom = ft_min(width_ratio, height_ratio) + 2;
	init_axis(cam);
	cam->x_et = 0;
	if (mx->depth_max > 50)
	{
		cam->y_et = -500;
		cam->z_div = 0.05;
	}
	else
	{
		cam->y_et = -100;
		cam->z_div = 0.8;
	}
	cam->projection = INIT;
}

void	init_s_matrix(t_matrix *mx)
{
	mx->width = 0;
	mx->height = 0;
	mx->depth_max = INT_MIN;
	mx->depth_min = INT_MAX;
	mx->coord_infocnt = 0;
	mx->elem = NULL;
	mx->line = NULL;
	mx->gnl = NULL;
	mx->coord = NULL;
	mx->color = NULL;
	mx->coord_info = NULL;
}
