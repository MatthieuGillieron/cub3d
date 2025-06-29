/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_rotate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:59:21 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 17:57:06 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	rotate_player(t_game *game, int direction)
{
	if (direction == 1)
		game->player.angle += 0.025;
	else
		game->player.angle -= 0.025;
	if (game->player.angle >= 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
}
