/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:23:58 by fparis            #+#    #+#             */
/*   Updated: 2023/11/10 14:24:02 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst && *lst && del)
	{
		if (lst[0]->next)
			ft_lstclear(&(lst[0]->next), del);
		ft_lstdelone(lst[0], del);
		lst[0] = NULL;
	}
	else if (lst)
		lst[0] = NULL;
}
