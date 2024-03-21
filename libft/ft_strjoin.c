/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:17:37 by fparis            #+#    #+#             */
/*   Updated: 2023/11/02 15:33:55 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	res = malloc(size * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}
