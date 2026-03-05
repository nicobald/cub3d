/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 09:38:54 by laudinot          #+#    #+#             */
/*   Updated: 2025/12/16 15:22:38 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head -> content = content;
	head -> next = NULL;
	return (head);
}
/*
int main()
{
    t_list *node;
    int value = 42;

    node = ft_lstnew(&value);
    if (node != NULL) {
        printf("Content: %d\n", *(int *)node->content);
        printf("Next: %p\n", (void *)node->next);
    free(node);

    return 0;
}*/