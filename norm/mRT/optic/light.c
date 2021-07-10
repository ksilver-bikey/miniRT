/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:04:09 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 11:04:11 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	*fiat_lux(double coords[3], unsigned char color[4], double intens)
{
	t_light	*new;
	t_light	*runner;
	int		cnt;

	new = (t_light *)malloc_gc(sizeof(t_light));
	cnt = 4;
	runner = fg_win()->lights;
	while (--cnt > -1)
		new->color[cnt] = color[cnt];
	while (++cnt < 3)
		new->crds[cnt] = coords[cnt];
	new->intens = intens;
	if (runner == NULL)
		fg_win()->lights = new;
	else
	{
		while (runner->next != NULL)
			runner = runner->next;
		runner->next = new;
	}
	new->type = 'l';
	return (new);
}

int		obj_rev(t_vec *pix_light, t_mro *act_obj, t_obj_cam *cam)
{
	t_mro	*obj;
	double	point[3];
	int		angle;
	double	len;

	obj = fg_win()->objects;
	while (obj != NULL)
	{
		if (obj != act_obj)
		{
			angle = obj->angle_coords(obj, pix_light, point);
			if (angle > 0)
			{
				len = point_point_dist(point, pix_light->start);
				if (len > 0.0000000001 && len < pix_light->len + 0.0000000001)
					return (0);
			}
		}
		obj = obj->next;
	}
	return (1);
	if (cam == NULL)
		angle++;
}

void	color_equation(t_light *light, unsigned char *color, double brightness)
{
	int				cnt;
	int				bigest;
	unsigned int	temp[4];
	double			coef;

	cnt = -1;
	while (++cnt < 4)
		temp[cnt] = (unsigned int)(light->color[cnt] + color[cnt]) * brightness;
	bigest = 0;
	while (--cnt > -1)
		if (temp[cnt] > temp[bigest])
			bigest = cnt;
	coef = (double)temp[bigest] / 255;
	if (temp[bigest] > 255u)
		while (++cnt < 4)
			temp[cnt] = (unsigned char)((double)temp[cnt] / coef);
	else
		while (++cnt < 4)
			temp[cnt] = (unsigned char)temp[cnt];
	while (--cnt > -1)
		if (color[cnt] < temp[cnt])
			color[cnt] = temp[cnt];
}

void	renormalize(t_vec *vec)
{
	double	div;

	div = 1 / vec->len;
	vec->vec[0] *= div;
	vec->vec[1] *= div;
	vec->vec[2] *= div;
	triple_copy(vec->end, vec->start);
	triple_summ(vec->end, vec->vec);
	vec->len = 1.0;
}

void	et_lux_fit(t_pixel_step *pix, unsigned char *color, t_mro *obj,\
																t_obj_cam *cam)
{
	t_light	*light;
	t_vec	pix_light;
	double	angle;
	int		check;

	light = fg_win()->lights;
	while (light != NULL)
	{
		mrt_fill_vector(pix->point, light->crds, &pix_light);
		check = 1;
		if (light->type == 'd')
			check = dot_light_gate(light, &pix_light);
		if (obj_rev(&pix_light, obj, cam) == 1 && check == 1)
		{
			angle = obj->ray_angle(cam->crds, obj, &pix_light, pix->point);
			if (angle > -1.9)
				color_equation(light, color,\
			ft_mod_db((light->intens * 150 * angle) / pix_light.len));
		}
		light = light->next;
	}
}
