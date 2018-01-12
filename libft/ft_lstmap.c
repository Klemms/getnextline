/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 20:10:46 by cababou           #+#    #+#             */
/*   Updated: 2017/12/13 20:10:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*buf;

	if (lst == NULL)
		return (NULL);
	buf = (t_list *)malloc(sizeof(t_list));
	buf = f(lst);
	if (lst->next != NULL)
		buf->next = ft_lstmap(lst->next, *f);
	return (buf);
}
