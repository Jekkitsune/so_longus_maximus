/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:31:02 by fparis            #+#    #+#             */
/*   Updated: 2023/11/06 13:37:19 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_i;

	if (lst == NULL)
		return (NULL);
	lst_i = lst;
	while (lst_i->next != NULL)
		lst_i = lst_i->next;
	return (lst_i);
}
