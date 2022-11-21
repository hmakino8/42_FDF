/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 04:38:31 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/20 03:24:06 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_substr_gnl(char const *s, size_t start, size_t len, t_gnl *gnl)
{
	size_t	idx;
	size_t	s_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen((char *)s);
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
	{
		gnl->signal = MALLOC_FAILURE;
		return (NULL);
	}
	idx = 0;
	while (s[start + idx] != '\0' && idx < len && start < s_len)
	{
		substr[idx] = s[start + idx];
		idx++;
	}
	substr[idx] = '\0';
	return (substr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2, t_gnl *gnl)
{
	size_t	idx;
	size_t	len_s1;
	size_t	len_s2;
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = NULL;
	if ((len_s1 / 2 + len_s2 / 2) + 1 < SIZE_MAX / 2)
		s3 = (char *)malloc(len_s1 + len_s2 + 1);
	if (s3 == NULL)
	{
		gnl->signal = MALLOC_FAILURE;
		return (NULL);
	}
	idx = 0;
	while (*s1)
		s3[idx++] = *s1++;
	while (*s2)
		s3[idx++] = *s2++;
	s3[idx] = '\0';
	return (s3);
}
