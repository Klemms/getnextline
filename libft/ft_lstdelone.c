/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 20:09:47 by cababou           #+#    #+#             */
/*   Updated: 2018/01/11 19:13:20 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **elementlist)
{
	t_list	*tmpelement;

	if ((*elementlist)->next != NULL)
	{
		tmpelement = (*elementlist)->next;
		tmpelement->prev = (*elementlist)->prev;
		while ((*elementlist)->next != NULL)
		{
			tmpelement->index--;
			tmpelement = (*elementlist)->next;
		}
	}
	free((*elementlist)->content);
	free(*elementlist);
}
