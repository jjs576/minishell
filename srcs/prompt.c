/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:02:09 by jjoo              #+#    #+#             */
/*   Updated: 2020/11/27 18:48:14 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_info *info)
{
	ft_printf("pwd : %s\n",info->pwd);
	ft_printf("envpwd : %s\n",env_search(&info->env, "PWD")->value);
}
