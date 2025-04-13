/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf44_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:04:57 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 21:15:28 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_FTMFLOAT4X4	ftmf44_set_scale(t_FTMFLOAT4 row_vec)
{
	t_FTMFLOAT4X4	result;

	result = ftmf44_set_zero();
	result.data[0][0] = row_vec.data[0];
	result.data[1][1] = row_vec.data[1];
	result.data[2][2] = row_vec.data[2];
	result.data[3][3] = 1;
	return (result);
}

t_FTMFLOAT4X4	ftmf44_set_translate(t_FTMFLOAT4 row_vec)
{
	t_FTMFLOAT4X4	result;

	result = ftmf44_set_id();
	result.data[3][0] = row_vec.data[0];
	result.data[3][1] = row_vec.data[1];
	result.data[3][2] = row_vec.data[2];
	return (result);
}

/*
pos : position vector of the camera
target : view target vector of the position that camera is looking at
*/
t_FTMFLOAT4X4	ftmf44_set_view(t_FTMFLOAT4 pos, t_FTMFLOAT4 target,
		t_FTMFLOAT4 up)
{
	t_FTMFLOAT4X4	result;

	*(t_FTMFLOAT4 *)(result.data[2]) = ftmf4_vsub(target, pos);
	ftmf4_vnormalize((t_FTMFLOAT4 *)(result.data[2]));
	*(t_FTMFLOAT4 *)(result.data[0])
		= ftmf4_vcross(up, *(t_FTMFLOAT4 *)(result.data[2]));
	ftmf4_vnormalize((t_FTMFLOAT4 *)(result.data[0]));
	*(t_FTMFLOAT4 *)(result.data[1])
		= ftmf4_vcross(*(t_FTMFLOAT4 *)(result.data[2]),
			*(t_FTMFLOAT4 *)(result.data[0]));
	result.data[0][3] = -ftmf4_vdot(pos, *(t_FTMFLOAT4 *)(result.data[0]));
	result.data[1][3] = -ftmf4_vdot(pos, *(t_FTMFLOAT4 *)(result.data[1]));
	result.data[2][3] = -ftmf4_vdot(pos, *(t_FTMFLOAT4 *)(result.data[2]));
	result.data[3][0] = 0.0;
	result.data[3][1] = 0.0;
	result.data[3][2] = 0.0;
	result.data[3][3] = 1.0;
	ftmf44_transpose(&result);
	return (result);
}
