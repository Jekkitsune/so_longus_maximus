/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:54:23 by fparis            #+#    #+#             */
/*   Updated: 2023/11/08 16:08:51 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*str;
	unsigned int		i;

	i = 0;
	if (s == NULL || !f)
		return (NULL);
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
