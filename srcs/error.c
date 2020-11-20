/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:01 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:02 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_error(int errno)
{
	if (errno == 0)
		write(1, "argument error\n", 15);
	else if (errno == -1)
		write(1, "file error\n", 11);
	else if (errno == -2)
		write(1, "map error\n", 10);
	else if (errno == -3)
		write(1, "R error\n", 8);
	else if (errno == -4)
		write(1, "color error\n", 12);
	else if (errno == -5)
		write(1, "invalid file\n", 13);
	else if (errno == -6)
		write(1, "no file\n", 8);
	else if (errno == -7)
		write(1, "malloc error\n", 10);
	else if (errno == -8)
		write(1, "too many items\n", 15);
	exit(0);
}
