/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:53:10 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 10:53:17 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "../minirt.h"

typedef struct			s_mrt_object
{
	int					(*angle_coords)(struct s_mrt_object *obj, t_vec *line,\
															double *point);
	void				(*del_this)(void *something);
	double				(*ray_angle)(double cam[3], struct s_mrt_object *obj,\
													t_vec *line, double *point);
	unsigned char		color[4];
	char				type;
	struct s_mrt_object	*next;
}						t_mro;

typedef struct			s_obj_tri
{
	int					(*angle_coords)(struct s_obj_tri *tri, t_vec *line,\
															double point[3]);
	void				(*del_this)(void *something);
	double				(*ray_angle)(double cam[3], struct s_obj_tri *tri,\
												t_vec *line, double point[3]);
	unsigned char		color[4];
	char				type;
	struct s_mrt_object	*next;
	double				points[3][3];
	double				max;
	struct s_vec		lines[3];
	struct s_pln		plain;
	struct s_pln		borders[3];
	double				opposite[3];
}						t_tri;

typedef struct			s_sphere
{
	int					(*angle_coords)(struct s_sphere *sph, t_vec *line,\
															double point[3]);
	void				(*del_this)(void *something);
	double				(*ray_angle)(double cam[3], struct s_sphere *sph,\
												t_vec *line, double point[3]);
	unsigned char		color[4];
	char				type;
	struct s_mrt_object	*next;
	double				crd[3];
	double				rd;
	char				camera;
	struct s_pln		plain;
}						t_sph;

typedef struct			s_cyl
{
	int					(*angle_coords)(struct s_cyl *cyl, t_vec *line,\
															double point[3]);
	void				(*del_this)(void *something);
	double				(*ray_angle)(double cam[3], struct s_cyl *cyl,\
												t_vec *line, double point[3]);
	unsigned char		color[4];
	char				type;
	struct s_mrt_object	*next;
	double				rd;
	double				crds[3];
	double				height;
	char				camera;
	double				ins_area;
	double				top_cmp;
	double				bot_cmp;
	double				proj_len;
	double				norm[3];
	int					last_point;
	struct s_pln		plain;
	struct s_vec		vector;
	struct s_pln		top;
	struct s_pln		bot;
}						t_cyl;

typedef struct			s_pln_object
{
	int					(*angle_coords)(struct s_pln_object *pln, t_vec *line,\
															double point[3]);
	void				(*del_this)(void *something);
	double				(*ray_angle)(double cam[3], struct s_pln_object *pln,\
												t_vec *line, double point[3]);
	unsigned char		color[4];
	char				type;
	struct s_mrt_object	*next;
	struct s_pln		pln_s;
}						t_pln_o;

typedef struct			s_square
{
	int					(*angle_coords)(struct s_square *sqr, t_vec *line,\
															double point[3]);
	void				(*del_this)(void *something);
	double				(*ray_angle)(double cam[3], struct s_square *sqr,\
												t_vec *line, double point[3]);
	unsigned char		color[4];
	char				type;
	struct s_mrt_object	*next;
	double				size;
	double				crds[3];
	double				corners[4][3];
	struct s_vec		line[4];
	struct s_pln		pln_s;
}						t_sqr;

typedef struct			s_obj_camera
{
	double				crds[3];
	char				type;
	double				fov;
	double				cam_vec[3];
	double				field_center[3];
	int					*field;
	double				screen_point[4][3];
	double				ray_step_v[3];
	double				ray_step_h[3];
	int					act_step[3];
	double				act_line[3];
	int					num;
	int					(*step)(struct s_obj_camera *cam);
	struct s_vec		temp_vec;
	struct s_vec		act_vec;
	struct s_obj_camera	*next;
	struct s_obj_camera	*prev;
}						t_obj_cam;

double					sqr_ray_angle(double cam[3], t_sqr *sqr, t_vec *line,\
															double point[3]);
int						square_line_angle_coords(t_sqr *sqr, t_vec *line,\
															double point[3]);
double					sphere_ray_angle(double cam[3], t_sph *sph,\
												t_vec *line, double point[3]);
int						cyl_line_coords(t_cyl *cyl, t_vec *line, double *point);
int						cyl_return(double temp_point[3][3], t_vec *line,\
														int angle[3], int res);
int						tw_points_cmp(double point1[3], double point2[3]);
int						to_top_or_not_to_top(t_cyl *cyl, t_vec *line);
int						cyl_side(t_cyl *cyl, t_vec *line, t_vec *perp,\
														double side_point[3]);
void					cyl_side_two(double side_point[3], t_vec *tmp,\
														double inside_cyl_len);
void					cyl_side_one(double side_point[3], t_vec *tmp,\
														double inside_cyl_len);
int						cyl_top(t_cyl *cyl, t_vec *line, double top_point[3]);
int						cyl_bot(t_cyl *cyl, t_vec *line, double bot_point[3]);
t_cyl					*make_cyl(double dm_hg[3], double crd[3],\
										double norm[3], unsigned char color[4]);
double					cyl_ray_angle(double cam[3], t_cyl *cyl, t_vec *line,\
															double point[3]);
double					cyl_ray_angle_two(t_cyl *cyl, t_vec *line,\
										double point[3], double light_cmp[2]);
void					cylinder_s_top(t_cyl *cyl);
void					cylinder_s_plain(t_cyl *cyl, t_vec *line);
double					cyl_top_angle(t_cyl *cyl, t_vec *line,\
															double light_cmp);
double					cyl_bot_angle(t_cyl *cyl, t_vec *line,\
															double light_cmp);
double					cyl_side_angle(t_cyl *cyl, t_vec *line,\
															double point[3]);
void					cam_point_calc_z(t_obj_cam *new, double side_vector[3],\
														double top_vector[3]);
void					cam_step(t_obj_cam *new);
void					left_right_corner(double left[3], double right[3],\
															t_obj_cam *new);
void					top_vector_z(double top_vector[3], double cam[3]);
void					side_vector_z(double side_vector[3], double cam[3]);
void					print_line(t_vec *line);
t_pln_o					*make_pln_o(double point[3], double vec[3],\
														unsigned char color[3]);
t_sph					*make_sph(double crd[3], double diameter,\
														unsigned char color[4]);
int						sphere_line_coords(t_sph *shp, t_vec *line, \
															double point[3]);
int						cyl_line_coords(t_cyl *cyl, t_vec *line,\
															double point[3]);
t_cyl					*make_cyl(double dm_hg[3], double crd[3],\
										double norm[3], unsigned char color[4]);
t_obj_cam				*make_camera(double crds[3], double fov, double\
																	cam_vec[3]);
void					triple_diff(double main[3], double additional[3]);
void					triple_summ(double main[3], double additional[3]);
void					triple_copy(double main[3], double additional[3]);
t_tri					*make_triangle(double point_one[3], \
			double point_two[3], double point_three[3], unsigned char color[4]);
t_sqr					*make_square(double point[3], double vec[3], unsigned\
													char color[4], double size);

#endif
