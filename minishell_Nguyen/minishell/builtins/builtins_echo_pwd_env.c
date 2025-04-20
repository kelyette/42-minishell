/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_pwd_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:53:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/20 18:35:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// // placeholder for dollar case
// char	*replace_dollar(char *str)
// {
// 	char	*new_str;

// 	new_str = malloc(sizeof(char) * 12);
//  if (new_str == NULL)
//  	return (perror("Error"), NULL);
// 	new_str = "hello world";
// 	free(str);
// 	return (new_str);
// }

// int	check_dollar(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '\'')
// 		return (0);
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$' && !ft_isspace(str[i + 1]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }


// case echo
int	builtin_echo(t_node *node)
{
	int	flag;

	flag = 0;
	node->data = node->data->next;
	if (!ft_strncmp(node->data->str, "-n", 3))
	{
		flag = 1;
		node->data = node->data->next;
	}
	while (node->data != NULL)
	{
		// if(check_dollar(node->data->str))
		// {
		// 	node->data->str = replace_dollar(node->data->str);
		// 	if (node->data->str == NULL)
		// 		return (1);
		// }
		printf("%s", node->data->str);
		if (node->data->next != NULL)
			printf(" ");
		node->data = node->data->next;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

// case env
void	builtin_env(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL && *envp == NULL)
		return ;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

// case pwd
int	builtin_pwd(void)
{
	char	*line;

	line = getcwd(NULL, 0);
	if (line == NULL)
		return (perror("Error"), 1);
	printf("%s\n", line);
	free(line);
	return (0);
}
