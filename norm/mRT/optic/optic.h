/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:04:31 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 11:04:33 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIC_H
# define OPTIC_H
# include "../minirt.h"

typedef struct		s_light
{
	double			crds[3];
	unsigned char	color[4];
	double			intens;
	char			type;
	double			ext_point[3];
	double			ext_rd;
	struct s_pln	plain;
	struct s_light	*next;
}					t_light;

typedef struct		s_dot_light_pack
{
	double			intens;
	unsigned char	color[4];
	double			light_angle;
}					t_dot_light_pack;

t_light				*fiat_lux(double coords[3], unsigned char color[4], double\
																		intens);
void				et_lux_fit(t_pixel_step *pix, unsigned char *color,\
													t_mro *obj, t_obj_cam *cam);
t_light				*mrt_make_dot(double coords[3], double vec[3],\
														t_dot_light_pack dlp);
int					dot_light_gate(t_light *dot_l, t_vec *line);

#endif
