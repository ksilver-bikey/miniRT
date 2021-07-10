/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:42:05 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 00:42:09 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../minirt.h"

typedef struct	s_vec
{
	double		start[3];
	double		end[3];
	double		vec[3];
	double		len;
}				t_vec;

typedef struct	s_gaus_ex
{
	double		f_un;
	double		s_un;
	double		t_un;
	double		free;
}				t_gaus;

typedef struct	s_pln
{
	double		x;
	double		y;
	double		z;
	double		norm[3];
}				t_pln;

double			point_line_cmp(double point[3], t_vec *vec);
double			two_rays_angle(double vec1[3], double vec2[3]);
double			point_point_dist(double point1[3], double point2[3]);
double			ft_sqrt(double x);
void			gaus_fill(double f_s_t[3], double free, t_gaus *gau);
void			vec_scolar(double vec1[3], double vec2[3], double tmp[3]);
void			point_line_perp(t_vec *line, double point[3],\
														double perp_base[3]);
void			perp_lines_vec(t_vec *vec1, t_vec *vec2, double res[3]);
void			gaus_ex(t_gaus *fr, t_gaus *se, t_gaus *th, double result[3]);
void			mrt_fill_vector_less(double *start, double *end, t_vec *new);
void			vec_normalize(double vec[3], double res[3]);
double			pln_line_sin(double vec1[3], double vec2[3]);
double			line_line_dist(t_vec *vec1, t_vec *vec2);
double			point_line_dist(double point[3], t_vec *vec);
void			fill_normalize(t_vec *vec, t_vec *new);
double			vec_cos(double vec1[3], double vec2[3]);
double			*xyz(double x, double y, double z, double *xyz);
double			vec_scalar_mp(double vec1[3], double vec2[3]);
void			mrt_canalize(void);
double			vec_len(double vec[3]);
int				vectors_codirection(double point[3], t_vec *line);
int				vec_codir(double *vec1, double *vec2);
int				plain_line_coords(t_pln *pln, t_vec *vec,\
														double empty_point[3]);
t_vec			*normalize(t_vec *vec);
double			point_plain_dist(double point[3], t_pln *pln);
void			fill_plain_eq_norm(t_vec *vec, double point[3], t_pln *pln);
t_pln			*make_plain_eq_norm(t_vec *vec, double point[3]);
double			point_plain_dist(double point[3], t_pln *pln);
double			plain_point_cmp(double coords[3], t_pln *pln);
t_pln			*make_plain_equation(double point[3], double vec1[3],\
																double vec2[3]);
void			fill_plain_equation(double point[3], double vec1[3],\
													double vec2[3], t_pln *pln);
void			mrt_fill_vector(double *start, double *end, t_vec *new);
t_vec			*mrt_make_vector(double start[3], double end[3]);
double			sq_pw(double num);
t_vec			*perp_line(t_vec *vec1, t_vec *vec2, t_vec *res);
void			gaus_sort_rev(t_gaus *(*line)[3], int num, int cnt);
void			gaus_one_more_thing(t_gaus *(*line)[3], int cnt);
void			fr_st(t_gaus *(*line)[3], int top, int bot);
void			se_st(t_gaus *(*line)[3], int top, int bot);
void			trpr(double point[3], char *str);

#endif
