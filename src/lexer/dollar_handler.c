/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:38:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/04 16:34:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Placeholder for handling $?
char	*handle_exit_code(char *s, int i, t_env **env)
{
	int		count;
	char	*temp;
	char	*value;

	count = i;
	value = find_variable("?", env);
	if (value == NULL)
		return (NULL);
	temp = ft_strjoin_variable(s, value, count);
	free(value);
	if (temp == NULL)
		return (NULL);
	i++;
	value = ft_strjoin(temp, &(s[i + 1]));
	free(temp);
	if (value == NULL)
		return (NULL);
	return (value);
}

// Handle variable expansion without quotes
char	*case_dollar(char *s, int i, t_env **env)
{
	char	*expand;
	char	*final;

	expand = expand_variable(s, i, env);
	if (!expand)
		return (NULL);
	final = dollar_handler(expand, env);
	free(expand);
	return (final);
}

// No variable expansion inside single quotes
void	case_single_quotes(char *s, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
}

// Handle variable expansion inside double quotes
char	*case_double_quotes(char *s, int *i, t_env **env)
{
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$' && s[*i + 1])
			return (case_dollar(s, *i, env));
		(*i)++;
	}
	return (NULL);
}

// Handle variable expansion
char	*dollar_handler(char *s, t_env **env)
{
	int		i;
	char	*final;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			final = case_double_quotes(s, &i, env);
			if (final)
				return (final);
		}
		else if (s[i] == '\'')
			case_single_quotes(s, &i);
		else if (s[i] == '$' && s[i + 1])
		{
			final = case_dollar(s, i, env);
			if (final)
				return (final);
		}
		i++;
	}
	return (ft_strdup(s));
}
