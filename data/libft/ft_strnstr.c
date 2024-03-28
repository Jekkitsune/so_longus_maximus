/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:00:16 by fparis            #+#    #+#             */
/*   Updated: 2023/11/02 19:15:43 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	i2;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		i2 = 0;
		while ((i + i2) < len && big[i + i2] == little[i2])
		{
			if (little[i2 + 1] == '\0')
				return ((char *)(big + i));
			i2++;
		}
		i++;
	}
	return (NULL);
}
