/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_hander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:08:59 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 16:47:08 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

// wait until all children have finished
// pid_t waitpid(pid_t pid, int *status, int options);
// pid: -1 wait for any child process
// status: finished child process status (WINEXITED, WIFSIGNALED)
// options: 0 wait until the child process is finished
// return: pointer to exit status of final child process
int	wait_for_all_children(pid_t final_pid, int *final_child_status)
{
	int		child_status;
	pid_t	current_pid;

	current_pid = 0;
	while (current_pid != -1)
	{
		current_pid = waitpid(-1, &child_status, 0);
		if (current_pid == final_pid)
			*final_child_status = child_status;
	}
	return (*final_child_status);
}

// WIFEXITED returns true if child terminated normally
// WIFFSIGNALED returns true if child terminated by signal
// WTERMSIG returns nb of signal that caused child to terminate
void	handle_final_child(int final_child_status)
{
	t_mini	*mini;
	mini = get_mini();
	if (WIFEXITED(final_child_status)) // successful exit
		mini->exit_code = WEXITSTATUS(final_child_status);
	else if (WIFSIGNALED(final_child_status))
	{
		mini->exit_code = WTERMSIG(final_child_status) + 128;
		if (mini->exit_code == 131) // 128 + 3 SIGQUIT
			ft_putendl_fd("SIGQUT", STDERR_FILENO);
	}
	else
		mini->exit_code = EXIT_FAILURE;
}

void	wait_for_children(void)
{
	int		final_child_status;
	pid_t	final_pid;
	t_mini	*mini;

	mini = get_mini();
	final_child_status = 0;
	final_pid = ((t_cmd *)(ft_lstlast(mini->cmd_list)->content))->pid;
	wait_for_all_children(final_pid, &final_child_status);
	handle_final_child(final_child_status);
}
