/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmf4_qoperate2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:57:35 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/05 20:36:30 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_math.h"

t_FTMFLOAT4	*ftmf4_qnormalize(t_FTMFLOAT4 *pqtrn)
{
	float	qtrn_size;

	qtrn_size = ftmf4_qsize(*pqtrn);
	if (qtrn_size != 1.0 && qtrn_size != 0.0)
	{
		pqtrn->data[0] /= qtrn_size;
		pqtrn->data[1] /= qtrn_size;
		pqtrn->data[2] /= qtrn_size;
		pqtrn->data[3] /= qtrn_size;
	}
	return (pqtrn);
}

// make prow_vec as a pure quaternion and rotate,
// after rotate, bring it back
t_FTMFLOAT4	*ftmf4_qrotate(t_FTMFLOAT4 *prow_vec, t_FTMFLOAT4 qtrn)
{
	t_FTMFLOAT4	q_inverse;
	float		is_point;

	is_point = prow_vec->data[3];
	prow_vec->data[3] = 0;
	ftmf4_qnormalize(&qtrn);
	q_inverse = ftmf4_qconjugate(qtrn);
	*prow_vec = ftmf4_qmult(qtrn, *prow_vec);
	*prow_vec = ftmf4_qmult(*prow_vec, q_inverse);
	prow_vec->data[3] = is_point;
	return (prow_vec);
}

t_FTMFLOAT4X4	ftmf4_qtom(const t_FTMFLOAT4 qtrn)
{
	t_FTMFLOAT4X4	result;

	result = ftmf44_set_id();
	result.data[0][0] = 2 * (powf(qtrn.data[3], 2.0)
			+ powf(qtrn.data[0], 2.0) - 0.5);
	result.data[0][1] = 2 * (qtrn.data[3] * qtrn.data[2]
			+ qtrn.data[0] * qtrn.data[1]);
	result.data[0][2] = 2 * (qtrn.data[0] * qtrn.data[2]
			- qtrn.data[3] * qtrn.data[1]);
	result.data[1][0] = 2 * (qtrn.data[0] * qtrn.data[1]
			- qtrn.data[3] * qtrn.data[2]);
	result.data[1][1] = 2 * (powf(qtrn.data[3], 2.0)
			+ powf(qtrn.data[1], 2.0) - 0.5);
	result.data[1][2] = 2 * (qtrn.data[3] * qtrn.data[0]
			+ qtrn.data[1] * qtrn.data[2]);
	result.data[2][0] = 2 * (qtrn.data[3] * qtrn.data[1]
			+ qtrn.data[0] * qtrn.data[2]);
	result.data[2][1] = 2 * (qtrn.data[1] * qtrn.data[2]
			- qtrn.data[3] * qtrn.data[0]);
	result.data[2][2] = 2 * (powf(qtrn.data[3], 2.0)
			+ powf(qtrn.data[2], 2.0) - 0.5);
	return (result);
}
