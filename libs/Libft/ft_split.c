/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:30:41 by hiroaki           #+#    #+#             */
/*   Updated: 2022/11/25 15:29:28 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	free_all_element(void **v, int cnt)
{
	int	i;

	i = -1;
	while (++i < cnt)
	{
		free(v[i]);
		v[i] = NULL;
	}
	free(v);
}

static size_t	element_cnt(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s++ != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
	}
	return (cnt);
}

static void	element_cpy(char *s, char **split, char c, int cnt)
{
	int		i;
	size_t	len;

	i = 0;
	while (*s && i < cnt)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (s[len] && s[len] != c)
			len++;
		if (len)
		{
			split[i] = ft_substr(s, 0, len);
			if (!split[i])
				return (free_all_element((void **)&split[i], cnt));
			i++;
		}
		s += len;
	}
}

//#include <stdio.h>
//
//static char	**ret_duplicate(char **split, char *s, int *cnt)
//{
//	*cnt = 1;
//	split = (char **)malloc(2 * sizeof(char *));
//	if (!split)
//		return (NULL);
//	split[0] = ft_strdup(s);
//	if (!split[0])
//	{
//		free_all_element((void **)split, 2);
//		return (NULL);
//	}
//	//printf("%s\n", split[0]);
//	split[1] = NULL;
//	return (split);
//}

char	**ft_split(char *s, char c, int *cnt)
{
	char	**split;

	split = NULL;
	if (!s)
		return (NULL);
	*cnt = element_cnt(s, c);
	//if (!*cnt)
	//	return (ret_duplicate(split, s, cnt));
	split = (char **)malloc((*cnt + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[*cnt] = NULL;
	element_cpy(s, split, c, *cnt);
	return (split);
}
