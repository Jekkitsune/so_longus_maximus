/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:38:53 by fparis            #+#    #+#             */
/*   Updated: 2023/11/07 16:25:58 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(char const *s1, char const *set)
{
	int	i;
	int	to_remove;
	int	start;

	i = 0;
	to_remove = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		to_remove++;
		i++;
	}
	start = i;
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i > start)
	{
		to_remove++;
		i--;
	}
	return (ft_strlen(s1) - to_remove);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	char	*res;

	if (set[0] == '\0')
		return (ft_strdup(s1));
	if (set == NULL || s1 == NULL)
		return ((char *)s1);
	len = get_len(s1, set);
	res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	return (ft_memcpy(res, s1 + i, len));
}
