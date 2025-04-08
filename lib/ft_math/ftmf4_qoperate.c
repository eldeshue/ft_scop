/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf4_qoperate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:46:36 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/05 17:12:31 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_math.h"

t_FTMFLOAT4	ftmf4_qadd(const t_FTMFLOAT4 q1, const t_FTMFLOAT4 q2)
{
	t_FTMFLOAT4	result;

	result.data[0] = q1.data[0] + q2.data[0];
	result.data[1] = q1.data[1] + q2.data[1];
	result.data[2] = q1.data[2] + q2.data[2];
	result.data[3] = q1.data[3] + q2.data[3];
	return (result);
}

t_FTMFLOAT4	ftmf4_qsub(const t_FTMFLOAT4 q1, const t_FTMFLOAT4 q2)
{
	t_FTMFLOAT4	result;

	result.data[0] = q1.data[0] - q2.data[0];
	result.data[1] = q1.data[1] - q2.data[1];
	result.data[2] = q1.data[2] - q2.data[2];
	result.data[3] = q1.data[3] - q2.data[3];
	return (result);
}

t_FTMFLOAT4	ftmf4_qmult(const t_FTMFLOAT4 q1, const t_FTMFLOAT4 q2)
{
	t_FTMFLOAT4	result;

	result.data[3] = q1.data[3] * q2.data[3] - q1.data[0] * q2.data[0]
		- q1.data[1] * q2.data[1] - q1.data[2] * q2.data[2];
	result.data[0] = q1.data[3] * q2.data[0] + q1.data[0] * q2.data[3]
		+ q1.data[1] * q2.data[2] - q1.data[2] * q2.data[1];
	result.data[1] = q1.data[3] * q2.data[1] + q1.data[1] * q2.data[3]
		+ q1.data[2] * q2.data[0] - q1.data[0] * q2.data[2];
	result.data[2] = q1.data[3] * q2.data[2] + q1.data[2] * q2.data[3]
		+ q1.data[0] * q2.data[1] - q1.data[1] * q2.data[0];
	return (result);
}

float	ftmf4_qsize(const t_FTMFLOAT4 qtrn)
{
	return (sqrt(powf(qtrn.data[0], 2.0) + powf(qtrn.data[1], 2.0)
			+ powf(qtrn.data[2], 2.0) + powf(qtrn.data[3], 2.0)));
}
