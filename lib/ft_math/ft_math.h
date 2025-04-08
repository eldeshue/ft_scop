/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:40:15 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 16:15:08 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

/* ------------------------------------------------------------- */
// 4 by 4, float
// basic matrix object for 42 graphics project.
// lhs coordinate
typedef struct s_FTMFLOAT4X4
{
	float		data[4][4];
}				t_FTMFLOAT4X4;

/* ------------------------------------------------------------- */
// 4 float
// vector and quaternion object for 42 graphics project
typedef struct s_FTMFLOAT4
{
	float		data[4];
}				t_FTMFLOAT4;

/* ----------------------- matrix ------------------------------ */

// init
t_FTMFLOAT4X4	ftmf44_set_zero(void);
t_FTMFLOAT4X4	ftmf44_set_id(void);
t_FTMFLOAT4X4	ftmf44_set_angle_x(float rad);
t_FTMFLOAT4X4	ftmf44_set_angle_y(float rad);
t_FTMFLOAT4X4	ftmf44_set_angle_z(float rad);
t_FTMFLOAT4X4	ftmf44_set_view(t_FTMFLOAT4 pos, t_FTMFLOAT4 target,
					t_FTMFLOAT4 up);

t_FTMFLOAT4X4	ftmf44_set_scale(t_FTMFLOAT4 row_vec);
t_FTMFLOAT4X4	ftmf44_set_translate(t_FTMFLOAT4 row_vec);

// operate
t_FTMFLOAT4X4	ftmf44_add(const t_FTMFLOAT4X4 *pm1, const t_FTMFLOAT4X4 *pm2);
t_FTMFLOAT4X4	ftmf44_sub(const t_FTMFLOAT4X4 *pm1, const t_FTMFLOAT4X4 *pm2);
t_FTMFLOAT4X4	ftmf44_mult(const t_FTMFLOAT4X4 *pm1, const t_FTMFLOAT4X4 *pm2);
void			ftmf44_transpose(t_FTMFLOAT4X4 *pm);

// transform
t_FTMFLOAT4X4	*ftmf44_scale(t_FTMFLOAT4 *prow_vec, t_FTMFLOAT4X4 *ptarget);
t_FTMFLOAT4X4	*ftmf44_translate(t_FTMFLOAT4X4 *ptarget,
					t_FTMFLOAT4 *prow_vec);
t_FTMFLOAT4		ftmf44_affine(t_FTMFLOAT4 *prow_vector,
					t_FTMFLOAT4X4 *pmatrix);

/* ----------------------- vector ------------------------------ */
// basically, row vector

// init1
t_FTMFLOAT4		ftmf4_set_vector(float x, float y, float z, float w);
int				ftmf4_is_vector(t_FTMFLOAT4 *pvec);
int				ftmf4_is_point(t_FTMFLOAT4 *pvec);
int				ftmf4_is_zero(t_FTMFLOAT4 *pvec);

// basic vector operation
t_FTMFLOAT4		ftmf4_vadd(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2);
t_FTMFLOAT4		ftmf4_vsub(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2);
float			ftmf4_vsize(const t_FTMFLOAT4 *pvec);
float			ftmf4_vdot(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2);
t_FTMFLOAT4		ftmf4_vcross(const t_FTMFLOAT4 v1, const t_FTMFLOAT4 v2);
t_FTMFLOAT4		*ftmf4_vnormalize(t_FTMFLOAT4 *pvec);

/* --------------------- quaternion --------------------------- */

// for vector compatibility, data[3] is a real part
// reference from https://eltgroup.tistory.com/30

// init2
t_FTMFLOAT4		ftmf4_set_id(void);
t_FTMFLOAT4		ftmf4_set_rodrigues(float rad, t_FTMFLOAT4 axis);
t_FTMFLOAT4		ftmf4_set_rpy(float roll, float pitch, float yaw);
t_FTMFLOAT4		ftmf4_qconjugate(const t_FTMFLOAT4 qtrn);
t_FTMFLOAT4		ftmf4_qinverse(const t_FTMFLOAT4 qtrn);

// basic quaternion operation
t_FTMFLOAT4		ftmf4_qadd(const t_FTMFLOAT4 q1, const t_FTMFLOAT4 q2);
t_FTMFLOAT4		ftmf4_qsub(const t_FTMFLOAT4 q1, const t_FTMFLOAT4 q2);
t_FTMFLOAT4		ftmf4_qmult(const t_FTMFLOAT4 q1, const t_FTMFLOAT4 q2);
float			ftmf4_qsize(const t_FTMFLOAT4 qtrn);

t_FTMFLOAT4		*ftmf4_qnormalize(t_FTMFLOAT4 *pqtrn);
t_FTMFLOAT4		*ftmf4_qrotate(t_FTMFLOAT4 *prow_vec, t_FTMFLOAT4 qtrn);
t_FTMFLOAT4X4	ftmf4_qtom(const t_FTMFLOAT4 qtrn);

#endif
