/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler_helper_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:52:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/25 11:30:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// expand the $ by replacing the $variable by its value
char	*case_expand(char *s, int i, t_env **env)
{
	int		count;
	char	*temp;
	char	*value;

	count = i;
	i++;
	while (ft_isalnum(s[i]))
		i++;
	i--;
	temp = ft_substring(&(s[count + 1]), i - count);
	if (temp == NULL)
		return (NULL);
	value = find_variable(temp, env);
	free(temp);
	if (value == NULL)
		return (NULL);
	temp = ft_strjoin_variable(s, value, count);
	free(value);
	if (temp == NULL)
		return (NULL);
	value = ft_strjoin(temp, &(s[i + 1]));
	free(temp);
	if (value == NULL)
		return (NULL);
	return (value);
}

char	*ft_strjoin_variable(char *s1, char *s2, int i)
{
	char	*line;
	int		j;

	line = malloc(sizeof(char) * (i + ft_strlen(s2)) + 1);
	if (line == NULL)
		return (perror("Error"), NULL);
	j = 0;
	while (j < i)
	{
		line[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		line[j] = s2[i];
		j++;
		i++;
	}
	line[j] = '\0';
	return (line);
}

// find the value of the variable, return an empty string if no match
char	*find_variable(char *s, t_env **env)
{
	t_env	*temp;
	char	*line;

	temp = *env;
	line = ft_strdup("\0");
	if (line == NULL)
		return (perror("Error"), NULL);
	while (temp != NULL)
	{
		if (!ft_strncmp(s, temp->key, ft_strlen(s)))
		{
			free(line);
			line = ft_strdup(temp->value);
			if (line == NULL)
				return (perror("Error"), NULL);
			return (line);
		}
		temp = temp->next;
	}
	return (line);
}

// Expand variable
char	*expand_variable(char *s, int i, t_env **env)
{
	if (s[i + 1] == '?')
		return (handle_exit_code());
	if (ft_isalphabet(s[i + 1]) || s[i + 1] == '_')
		return (case_expand(s, i, env));
	return (NULL);
}
