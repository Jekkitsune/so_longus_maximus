/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:25:30 by fparis            #+#    #+#             */
/*   Updated: 2023/11/10 14:25:31 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*res_start;

	if (!lst || !f || !del)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	res_start = res;
	if (res == NULL)
	{
		ft_lstclear(&res, del);
		return (NULL);
	}
	lst = lst->next;
	while (lst)
	{
		res->next = ft_lstnew(f(lst->content));
		if (res->next == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		res = res->next;
		lst = lst->next;
	}
	return (res_start);
}
