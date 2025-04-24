/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:38:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 18:46:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	case_exit_code(void)
{
	printf("repalce this with exit code\n");
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

// edit this to handle $? later
char	*dollar_handler_helper(char	*s, int i, t_env **env)
{
	char	*expand;
	char	*final;

	if (s[i + 1] == '?')
		case_exit_code();
	else if (ft_isalphabet(s[i + 1]) || s[i + 1] == '_')
	{
		expand = case_expand(s, i, env);
		if (expand == NULL)
			return (NULL);
		final = dollar_handler(expand, env);
		free(expand);
		return (final);
	}
}

// handle variable expansion
// NOTE: Not handle $? yet, would segfault.
char	*dollar_handler(char *s, t_env **env)
{
	int		i;
	char	*final;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		else if (s[i] == '$' && s[i + 1] != '\0')
		{
			final = dollar_handler_helper(s, i, env);
			return (final);
		}
		i++;
	}
	return (ft_strdup(s));
}
