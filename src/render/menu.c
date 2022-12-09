/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/09 18:05:44 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	operation_key_menu1(t_mlx *mlx, int *x, int *y)
{
	mlx_string_put(mlx->init, mlx->win, *x, *y, 0xB0E0E6, \
	"       Operation Key       ");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 60, 0xE6E6FA, \
	"- Exit           =>     ESC");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 50, 0xE6E6FA, \
	"- Zoom           =>   + / -");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 50, 0xE6E6FA, \
	"- Move");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   up            =>      K");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   down          =>      J");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   left          =>      H");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   right         =>      L");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 50, 0xE6E6FA, \
	"- Rotate");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   x axis        =>  S / W");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   y axis        =>  D / E");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   z axis        =>  F / R");
}

static void	operation_key_menu2(t_mlx *mlx, int *x, int *y)
{
	mlx_string_put(mlx->init, mlx->win, *x, *y += 50, 0xE6E6FA, \
	"- Adjust depth   =>  < / >");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 50, 0xE6E6FA, \
	"- Projection");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   default       =>     I");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   init axis     =>     U");
	mlx_string_put(mlx->init, mlx->win, *x, *y += 30, 0xE6E6FA, \
	"   parallel      =>     P");
}

void	put_menu(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 10;
	y = 50;
	operation_key_menu1(mlx, &x, &y);
	operation_key_menu2(mlx, &x, &y);
}
