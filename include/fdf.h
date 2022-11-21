/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:08:02 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/22 05:06:24 by hiroaki          ###   ########.fr       */
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

//enum e_signal {};

//enum e_command {};

typedef struct s_arr
{
	int	*init;
	int	*sort;
	int	*comp;
	int	*cmds;
}	t_arr;

typedef struct s_lst
{
	int				val;
	bool			part;
	struct s_lst	*next;
}	t_lst;

typedef struct s_data
{
}	t_data;

/* * * * * * * *
 *   main dir  *
 * * * * * * * */

/* main.c */

#endif
