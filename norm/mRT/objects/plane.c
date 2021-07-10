/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:41:03 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:41:05 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	del_pln_o(void *something)
{
	free_gc(something);
}

int		plain_line_angle_coords(t_pln_o *pln, t_vec *line, double point[3])
{
	plain_line_coords(&pln->pln_s, line, point);
	if (vectors_codirection(point, line) == 0)
		return (-1);
	return (1);
}

double	pln_ray_angle(double cam[3], t_pln_o *pln, t_vec *line, double point[3])
{
	double	cam_cmp;
	double	light_cmp;

	light_cmp = plain_point_cmp(line->end, &pln->pln_s);
	cam_cmp = plain_point_cmp(cam, &pln->pln_s);
	if (light_cmp * cam_cmp > -0.00000001)
		return (pln_line_sin(line->vec, pln->pln_s.norm));
	return (-2.0);
	if (point[0] != point[0])
		point[0] += 0.1;
}

t_pln_o	*make_pln_o(double point[3], double vec[3], unsigned char color[4])
{
	t_pln_o	*new;
	int		cnt;

	new = (t_pln_o *)malloc_gc(sizeof(t_pln_o));
	new->angle_coords = plain_line_angle_coords;
	new->del_this = del_pln_o;
	cnt = -1;
	while (++cnt < 4)
		new->color[cnt] = color[cnt];
	cnt--;
	while (--cnt > -1)
		new->pln_s.norm[cnt] = vec[cnt];
	new->pln_s.x = -1.0 * point[0];
	new->pln_s.y = -1.0 * point[1];
	new->pln_s.z = -1.0 * point[2];
	new->ray_angle = pln_ray_angle;
	new->type = 'p';
	return (new);
}
