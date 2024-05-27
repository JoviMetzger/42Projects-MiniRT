/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/27 18:46:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

bool	intersect_cyl_plane(t_ray *ray, t_objs *plane, t_hit_data *hit_data)
{
	t_vec3	oc;
	double denom;

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		oc = minus(plane->center, ray->place);
		hit_data->t = dot_product(oc, plane->vector) / denom;
		if (hit_data->t >= EPSILON)
			return (true);
	}
	return (false);
}

/**
 * if t is negative, no intersection found
 * 
 * 			t = -X|V / D|V
 * 
 * 			x = ray origin - center point of a shape
 *			v = plane normal
 * 			d = ray direction
 */
bool	intersect_plane(t_ray *ray, t_objs *plane, t_hit_data *hit_data)
{
	t_vec3	oc;
	double denom;

	denom = dot_product(ray->vector, plane->vector);
	if (fabs(denom) > EPSILON)
	{
		oc = minus(plane->center, ray->place);
		hit_data->t = dot_product(oc, plane->vector) / denom;
		if (hit_data->t >= EPSILON)
			return (check_closest(hit_data));
	}
	return (false);
}
