/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:00:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/18 20:01:24 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	fork_error_exit(void)
{
	int	ret;

	ret = fork();
	if (ret < 0)
	{
		perror("fork");
		exit(1);
	}
	return (ret);
}
