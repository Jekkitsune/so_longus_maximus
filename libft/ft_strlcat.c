/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:13:03 by fparis            #+#    #+#             */
/*   Updated: 2023/11/07 17:15:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	i_src;
	size_t	len_src;

	len_dst = 0;
	len_src = 0;
	if ((dst == NULL || src == NULL) && size == 0)
		return (0);
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst > size)
		return (len_src + size);
	i = len_dst;
	i_src = 0;
	while (i + 1 < size && src[i_src])
	{
		dst[i] = src[i_src];
		i++;
		i_src++;
	}
	dst[i] = '\0';
	return (len_dst + len_src);
}
