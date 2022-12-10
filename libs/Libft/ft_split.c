/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:30:41 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/10 13:40:49 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	free_all_element(void **v, int cnt)
{
	int	i;

	i = -1;
	while (v && ++i < cnt)
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

char	**ft_split(char *s, char c, int *cnt)
{
	char	**split;

	if (!s)
		return (NULL);
	*cnt = element_cnt(s, c);
	split = (char **)malloc((*cnt + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[*cnt] = NULL;
	element_cpy(s, split, c, *cnt);
	return (split);
}
