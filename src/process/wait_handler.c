/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:08:59 by eahn              #+#    #+#             */
/*   Updated: 2024/08/12 17:58:17 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * @brief Waits until all child processes have finished.
 * @param final_pid PID of the final child process to wait for
 * @param final_child_status Pointer to store the exit status of final child process
 * @return The exit status of final child process
 * - Uses waitpid with PID -1 to wait for any child process
 * - Loop continues until waitpid return -1,
	meaning all child processes finished
 */
static int	wait_for_all_children(pid_t final_pid, int *final_child_status)
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

/**
 * @brief Handles the exit status of the final child process.
 * @param final_child_status The exit status of the final child process
 * - If child process exited normally, exit code is child's exit status
 * - If child process exited by signal, exit code is set to 128 + signal number
 * For example, if exited by SIGQUIT, exit code is 128 + 3 = 131
 * - WTERMSIG returns nb of signal that caused child to terminate
 */
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
