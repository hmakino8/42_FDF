/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_settings.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:37:11 by hiroaki           #+#    #+#             */
/*   Updated: 2023/02/27 21:01:51 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_SETTINGS_H
# define FDF_SETTINGS_H

/* Output */
# define STD_OUT	1
# define STD_ERROR	2

/* Width/Height */
# define SCR_HEIGHT	1080
# define SCR_WIDTH	1920
# define MENU_WIDTH	180

/* Projection */
# define INIT		1
# define PARALLEL	2

/* Color */
# define NO_COLOR		0x0
# define DEEPPINK		0xFF1493
# define INDIGO			0x165E83
# define BLACKDIAMOND	0x252A2D

/* Direction key */
# define KEY_UP		0xFF52
# define KEY_DOWN	0xFF54
# define KEY_LEFT	0xFF51
# define KEY_RIGHT	0xFF53

/* Main alphabet key */
# define KEY_E	0x0065
# define KEY_S	0x0073
# define KEY_D	0x0064
# define KEY_F	0x0066
# define KEY_H	0x0068
# define KEY_I	0x0069
# define KEY_J	0x006A
# define KEY_K	0x006B
# define KEY_L	0x006C
# define KEY_R	0x0072
# define KEY_P	0x0070
# define KEY_U	0x0075
# define KEY_W	0x0077

/* Main symbol key */
# define KEY_ESC	0xFF1B
# define KEY_PLUS	0x003D
# define KEY_MINUS 	0x002D
# define KEY_LESS 	0x002C
# define KEY_GRATER	0x002E

#endif
