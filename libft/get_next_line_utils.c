/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:04:48 by fparis            #+#    #+#             */
/*   Updated: 2024/02/08 20:27:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_mallocat(char *src, char *new)
{
	char	*res;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	res = malloc(ft_strlen(src) + ft_strlen(new) + 1);
	while (res && src && src[i])
	{
		res[i] = src[i];
		i++;
	}
	while (res && new && new[i2])
	{
		res[i + i2] = new[i2];
		i2++;
	}
	free(src);
	if (new)
		free(new);
	if (res)
		res[i + i2] = '\0';
	return (res);
}

void	ft_free(char **lst1, char **lst2)
{
	if (lst1 && *lst1)
	{
		free(*lst1);
		*lst1 = NULL;
	}
	if (lst2 && *lst2)
	{
		free(*lst2);
		*lst2 = NULL;
	}
}
