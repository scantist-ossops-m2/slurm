/* 
 * reconfigure.c - request that slurmctld re-read the configuration files
 *
 * author: moe jette, jette@llnl.gov
 */

#ifdef have_config_h
#  include <config.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <src/api/slurm.h>
#include <src/common/slurm_protocol_api.h>


int
slurm_reconfigure ()
{
	int msg_size ;
	int rc ;
	slurm_fd sockfd ;
	slurm_msg_t request_msg ;
	slurm_msg_t response_msg ;
	return_code_msg_t* rc_msg ;
	/* init message connection for message communication with controller */

	if ( ( sockfd = slurm_open_controller_conn ( SLURM_PORT ) ) == SLURM_SOCKET_ERROR )
		return SLURM_SOCKET_ERROR ;	

	/* send request message */
	request_msg . msg_type = REQUEST_RECONFIGURE ;

	if ( ( rc = slurm_send_controller_msg ( sockfd , & request_msg ) ) == SLURM_SOCKET_ERROR )
		return SLURM_SOCKET_ERROR ;	

	/* receive message */
	if ( ( msg_size = slurm_receive_msg ( sockfd , & response_msg ) ) == SLURM_SOCKET_ERROR )
		return SLURM_SOCKET_ERROR ;	

	/* shutdown message connection */
	if ( ( rc = slurm_shutdown_msg_conn ( sockfd ) ) == SLURM_SOCKET_ERROR )
		return SLURM_SOCKET_ERROR ;	

	switch ( response_msg . msg_type )
	{
		case RESPONSE_SLURM_RC:
			rc_msg = ( return_code_msg_t * ) response_msg . data ; 
			return rc_msg->return_code ;
			break ;
		default:
			return SLURM_UNEXPECTED_MSG_ERROR ;
			break ;
	}

	return SLURM_SUCCESS ;
}

