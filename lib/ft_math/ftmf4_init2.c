/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf4_init2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:16 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 21:13:59 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_math.h"

t_FTMFLOAT4	ftmf4_set_id(void)
{
	t_FTMFLOAT4	result;

	result.data[0] = 0;
	result.data[1] = 0;
	result.data[2] = 0;
	result.data[3] = 1;
	return (result);
}

t_FTMFLOAT4	ftmf4_set_rodrigues(float rad, t_FTMFLOAT4 axis)
{
	t_FTMFLOAT4	result;
	float		sin_half_rad;

	sin_half_rad = sinf(rad * 0.5);
	ftmf4_vnormalize(&axis);
	result.data[3] = cosf(rad * 0.5);
	result.data[0] = axis.data[0] * sin_half_rad;
	result.data[1] = axis.data[1] * sin_half_rad;
	result.data[2] = axis.data[2] * sin_half_rad;
	return (result);
}

// fixed x y z, euler 321
t_FTMFLOAT4	ftmf4_set_rpy(float roll, float pitch, float yaw)
{
	t_FTMFLOAT4	result;
	float		hsin[3];
	float		hcos[3];

	hsin[0] = sinf(roll * 0.5);
	hsin[1] = sinf(pitch * 0.5);
	hsin[2] = sinf(yaw * 0.5);
	hcos[0] = cosf(roll * 0.5);
	hcos[1] = cosf(pitch * 0.5);
	hcos[2] = cosf(yaw * 0.5);
	result.data[3] = hcos[0] * hcos[1] * hcos[2] + hsin[0] * hsin[1] * hsin[2];
	result.data[0] = hsin[0] * hcos[1] * hcos[2] - hcos[0] * hsin[1] * hsin[2];
	result.data[1] = hcos[0] * hsin[1] * hcos[2] + hsin[0] * hcos[1] * hsin[2];
	result.data[2] = hcos[0] * hcos[1] * hsin[2] - hsin[0] * hsin[1] * hcos[2];
	return (result);
}

t_FTMFLOAT4	ftmf4_qconjugate(const t_FTMFLOAT4 qtrn)
{
	t_FTMFLOAT4	result;

	result.data[0] = -qtrn.data[0];
	result.data[1] = -qtrn.data[1];
	result.data[2] = -qtrn.data[2];
	result.data[3] = qtrn.data[3];
	return (result);
}

t_FTMFLOAT4	ftmf4_qinverse(const t_FTMFLOAT4 qtrn)
{
	t_FTMFLOAT4	result;
	float		square_size;

	square_size = powf(ftmf4_qsize(qtrn), 2.0);
	result.data[0] = -qtrn.data[0] / square_size;
	result.data[1] = -qtrn.data[1] / square_size;
	result.data[2] = -qtrn.data[2] / square_size;
	result.data[3] = qtrn.data[3] / square_size;
	return (result);
}
