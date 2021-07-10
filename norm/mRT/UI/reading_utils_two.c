/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:32:32 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 11:32:35 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int			mrt_read_block(char *line)
{
	int	cnt;
	int	spaces;

	cnt = 0;
	while (line[cnt] == ' ')
		cnt++;
	spaces = cnt;
	if (line[cnt] == '-')
		cnt++;
	while (ft_isdigit(line[cnt]))
		cnt++;
	if (line[cnt] == '.')
		cnt++;
	while (ft_isdigit(line[cnt]))
		cnt++;
	if (spaces == cnt)
		cnt = -1;
	return (cnt);
}

void		mrt_dot_light_read(char *line)
{
	char				**str;
	double				crds[3];
	double				norm_vec[3];
	t_dot_light_pack	dlp;

	str = ft_split(line, ' ');
	if (str[0] == NULL || str[1] == NULL || str[2] == NULL || str[3] == NULL ||\
		str[4] == NULL || str[5] == NULL || str[6] != NULL)
		mrt_input_error(5, line);
	if (mrt_read_coords(str[1], crds) == 0)
		mrt_input_error(9, line);
	if (mrt_read_coords(str[2], norm_vec) == 0)
		mrt_input_error(10, line);
	if (mrt_read_block(str[3]) != (int)ft_strlen(str[3]))
		mrt_input_error(12, line);
	dlp.light_angle = ft_atod(str[3]);
	if (mrt_read_block(str[4]) != (int)ft_strlen(str[4]))
		mrt_input_error(5, line);
	dlp.intens = ft_atod(str[4]);
	if (mrt_read_color(str[5], dlp.color) == 0)
		mrt_input_error(11, line);
	(dlp.light_angle == 180.0) ? dlp.light_angle = 179.9 : 1;
	mrt_make_dot(crds, norm_vec, dlp);
	mrt_reading_data_clean(str);
}

static int	crd_cmp(double one[3], double two[3])
{
	if (one[0] != two[0])
		return (0);
	if (one[1] != two[1])
		return (0);
	if (one[2] != two[2])
		return (0);
	return (1);
}

static int	cl_check(t_mro *forward, t_mro *act)
{
	if (act->type == 'c' && crd_cmp(((t_cyl *)forward)->crds,\
													((t_cyl *)act)->crds) == 1)
	{
		if (((t_cyl *)forward)->rd == ((t_cyl *)act)->rd &&\
						((t_cyl *)forward)->height == ((t_cyl *)act)->height)
			return (1);
	}
	else if (act->type == 'k' && crd_cmp(((t_sqr *)forward)->crds,\
												((t_sqr *)act)->crds) == 1)
	{
		if (((t_sqr *)forward)->size == ((t_sqr *)act)->size)
			return (1);
	}
	else if (act->type == 's' && crd_cmp(((t_sph *)forward)->crd,
			((t_sph *)act)->crd) == 1 && ((t_sph *)forward)->rd ==\
														((t_sph *)act)->rd)
		return (1);
	else if (act->type == 't')
		if (crd_cmp(((t_tri *)forward)->points[0], ((t_tri *)act)->points[0])\
	== 1 && crd_cmp(((t_tri *)forward)->points[1], ((t_tri *)act)->points[1])\
	== 1 && crd_cmp(((t_tri *)forward)->points[2], ((t_tri *)act)->points[2])\
	== 1)
			return (1);
	return (0);
}

void		mrt_obj_cleaner(void)
{
	t_mro	*forward;
	t_mro	*backward;
	t_mro	*act;

	act = fg_win()->objects;
	while (act != NULL)
	{
		forward = act->next;
		backward = act;
		while (forward != NULL)
		{
			if (forward->type == act->type && cl_check(forward, act) == 1)
			{
				forward = forward->next;
				free_gc(backward->next);
				backward->next = forward;
			}
			backward = forward;
			if (forward != NULL)
				forward = forward->next;
		}
		act = act->next;
	}
}
