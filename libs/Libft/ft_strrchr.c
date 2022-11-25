/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:37:42 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/26 01:08:25 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	ch;

	ch = (char)c;
	len = ft_strlen(s);
	if (!ch)
		return ((char *)&s[len]);
	while (len--)
	{
		if (s[len] == ch)
			return ((char *)&s[len]);
	}
	return (NULL);
}
