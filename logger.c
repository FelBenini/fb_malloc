/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:07:29 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/20 14:19:44 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fb_malloc.h"
#include <stdio.h>

void	log_list(t_allocated_block	**lst)
{
	t_allocated_block	*block;
	static int			iteration;
	int					node;

	block = *lst;
	node = 1;
	printf("\n\n-----ITERATION Nº %d----\n", iteration + 1);
	while(block)
	{
		printf("\nBlock nº %d:-----------------------\n", node);
		printf("Size: %-5d Next: %-10p Prev: %-10p free: %-5d", (int)block->size, block->next, block->prev, block->is_freed);
		printf(" current: %p", block);
		block = block->next;
		node++;
	}
	iteration++;
}
