/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/02 16:02:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// coords, 3D vector, rgb
bool intersect_plane(t_ray *ray, t_objs *plane, t_obj_data *obj_data)
{
    double radius;
    t_vec3	oc;

    radius = plane->diameter / 2;
    oc = minus(ray->place, plane->center);
    obj_data->a = dot_product(ray->vector, ray->vector);
    obj_data->b = 2.0 * dot_product(oc, ray->vector);
    obj_data->c = dot_product(oc, oc) - radius * radius;
    obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;

    if (obj_data->d < 0)
        return (false);	// No intersection
    else 
    {
        obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
        obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);
        if (obj_data->root1 < obj_data->root2)
            obj_data->t = obj_data->root1;
        else
            obj_data->t = obj_data->root2;
        return (true); // Intersection found
    }
}
