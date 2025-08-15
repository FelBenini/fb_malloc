/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fb_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:29:16 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/13 11:33:41 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fb_malloc.h"

void	*fb_malloc(size_t size)
{
	static t_heap_region	*head;
	void					*request;
	void					*res;

	if (size <= 0)
		return (NULL);
	res = sbrk(0);
	request = sbrk(size);
	if (request == (void *)-1)
		return (NULL);
	assert(res == request);
	return (res);
}
#include <stdio.h>
int	main(void)
{
	char	*stuff;
	char	banana[6] = "banana";
	int		i = 0;
	stuff = (char *)fb_malloc(7);
	while (i < 6)
	{
		stuff[i] = banana[i];
		i++;
	}
	stuff[i] = '\0';
	printf("%s", stuff);
}
