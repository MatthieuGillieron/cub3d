/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_cast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:36:04 by mg                #+#    #+#             */
/*   Updated: 2025/06/26 15:40:20 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	init_ray_vars(t_game *game, double ray_angle,
	t_ray_pos *pos, t_ray_dir *dir)
{
	pos->pos_x = (double)game->player.x + 0.5;
	pos->pos_y = (double)game->player.y + 0.5;
	pos->map_x = (int)pos->pos_x;
	pos->map_y = (int)pos->pos_y;
	dir->ray_dir_x = cos(ray_angle);
	dir->ray_dir_y = sin(ray_angle);
	dir->delta_dist_x = (dir->ray_dir_x == 0) ? 1e30 : fabs(1 / dir->ray_dir_x);
	dir->delta_dist_y = (dir->ray_dir_y == 0) ? 1e30 : fabs(1 / dir->ray_dir_y);
	if (dir->ray_dir_x < 0)
	{
		dir->step_x = -1;
		dir->side_dist_x = (pos->pos_x - pos->map_x) * dir->delta_dist_x;
	}
	else
	{
		dir->step_x = 1;
		dir->side_dist_x = (pos->map_x + 1.0 - pos->pos_x) * dir->delta_dist_x;
	}
	if (dir->ray_dir_y < 0)
	{
		dir->step_y = -1;
		dir->side_dist_y = (pos->pos_y - pos->map_y) * dir->delta_dist_y;
	}
	else
	{
		dir->step_y = 1;
		dir->side_dist_y = (pos->map_y + 1.0 - pos->pos_y) * dir->delta_dist_y;
	}
}

static int	perform_dda(t_game *game, t_ray_pos *pos, t_ray_dir *dir, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (dir->side_dist_x < dir->side_dist_y)
		{
			dir->side_dist_x += dir->delta_dist_x;
			pos->map_x += dir->step_x;
			*side = 0;
		}
		else
		{
			dir->side_dist_y += dir->delta_dist_y;
			pos->map_y += dir->step_y;
			*side = 1;
		}
		if (game->map[pos->map_y] && game->map[pos->map_y][pos->map_x] == '1')
			hit = 1;
	}
	return (hit);
}

t_ray_hit	cast_ray(t_game *game, double ray_angle)
{
	t_ray_hit	hit;
	t_ray_pos	pos;
	t_ray_dir	dir;
	int			side;

	init_ray_vars(game, ray_angle, &pos, &dir);
	perform_dda(game, &pos, &dir, &side);
	if (side == 0)
		hit.distance = (pos.map_x - pos.pos_x + (1 - dir.step_x) / 2) / dir.ray_dir_x;
	else
		hit.distance = (pos.map_y - pos.pos_y + (1 - dir.step_y) / 2) / dir.ray_dir_y;
	if (side == 0)
		hit.wall_x = pos.pos_y + hit.distance * dir.ray_dir_y;
	else
		hit.wall_x = pos.pos_x + hit.distance * dir.ray_dir_x;
	hit.wall_x -= floor(hit.wall_x);
	hit.map_x = pos.map_x;
	hit.map_y = pos.map_y;
	hit.side = side;
	return (hit);
}
