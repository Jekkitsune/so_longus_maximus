/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:47:03 by fparis            #+#    #+#             */
/*   Updated: 2024/02/14 14:58:54 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_middle_str(char *src, int start, int end)
{
	size_t		i;
	char		*res;
	size_t		size;
	int			src_len;

	i = 0;
	src_len = ft_strlen(src);
	size = src_len - start - end;
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[size] = '\0';
	while (i < ft_strlen(src) && i < size)
	{
		res[i] = src[i + start];
		i++;
	}
	return (res);
}
