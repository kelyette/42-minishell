/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/20 11:14:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// union u_data
// {
// 	t_args	*args;
// 	char	*field;
// 	t_token	*token;
// };

// typedef struct s_node
// {
// 	int				type;
// 	struct s_node	*lnode;
// 	struct s_node	*rnode;
// 	union u_data	data;
// }	t_node;

// enum	e_node_t
// {
// 	NT_Candidate = 0,
// 	NT_Cmd = 1,
// 	NT_Expand = TK_USD,
// 	NT_Assign = TK_Assign,
// 	NT_RdrOut = TK_Out,
// 	NT_RdrAppn = TK_Append,
// 	NT_RdrIn = TK_In,
// 	NT_HereDoc = TK_HereDoc,
// 	NT_Pipe = TK_Pipe,
// 	NT_And = TK_And,
// 	NT_Or = TK_Or,
// };

// should create a linked list, each node is a KEY and its VALUE
// When expansion $ is called, loop through this linked list to find the KEY and get its VALUE
void	case_assign(t_node *tree, int *i, char **envp)
{
	/* code to do assignement
	
	
	
	*/
}

// From the root of the tree, recursively apply the executor
void	executor(t_node *tree, int *i, char **envp)
{
	if (tree->type == NT_Candidate || tree == NULL)
		return ;
	else if (tree->type == NT_Or || tree->type == NT_And)
		case_operator(tree, i, envp);
	else if (tree->type == NT_Pipe)
		case_pipe(tree, i, envp);
	else if (tree->type == NT_RdrIn || tree->type == NT_HereDoc
			|| tree->type == NT_RdrOut || tree->type == NT_RdrAppn)
		case_redirection(tree, i, envp);
	else if (tree->type == NT_Assign)
		case_assign(tree, i, envp);
	else if (tree->type == NT_Expand)
		builtin_usd(tree, i, envp);
	else if (tree->type == NT_Cmd)
	{
		case_cmd(tree, i, envp);
		return ;
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	int	i;

	i = 0;
	executor(tree, &i, envp);
	return (0);
}
