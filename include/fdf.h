/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:08:02 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/25 14:57:48 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../libs/include/libft.h"
# include "../libs/include/ft_print.h"
# include "../libs/include/get_next_line.h"

# define STD_OUT 1
# define STD_ERROR 2

typedef struct s_map
{
	int		width;
	int		height;
	int		allocsize;
	int		*coord;
	int		*color;
	char	**info;
}	t_map;

typedef struct	s_data
{
	int		elemcnt;
	char	**elem;
	t_map	m;
}				t_data;

/* * * * * * * *
 *   main dir  *
 * * * * * * * */

/* main.c */

#endif
