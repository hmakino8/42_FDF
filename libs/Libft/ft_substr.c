/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:25:39 by hiroaki           #+#    #+#             */
/*   Updated: 2022/11/20 03:33:21 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	slen;
	unsigned int	dlen;
	char			*ret;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_strdup(""));
	dlen = slen - start;
	if (len < dlen)
		dlen = len;
	ret = (char *)malloc(dlen + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, dlen + 1);
	return (ret);
}
