/*****************************************************************************\
 *  debugger.c - Definitions needed for parallel debugger
 *****************************************************************************
 *  Copyright (C) 2002-2007 The Regents of the University of California.
 *  Copyright (C) 2008-2010 Lawrence Livermore National Security.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Mark Grondona <grondona1@llnl.gov>, et. al.
 *  CODE-OCEC-09-009. All rights reserved.
 *
 *  This file is part of SLURM, a resource management program.
 *  For details, see <https://slurm.schedmd.com/>.
 *  Please also read the included file: DISCLAIMER.
 *
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  In addition, as a special exception, the copyright holders give permission
 *  to link the code of portions of this program with the OpenSSL library under
 *  certain conditions as described in each individual source file, and
 *  distribute linked combinations including the two. You must obey the GNU
 *  General Public License in all respects for all of the code used other than
 *  OpenSSL. If you modify file(s) with this exception, you may extend this
 *  exception to your version of the file(s), but you are not obligated to do
 *  so. If you do not wish to do so, delete this exception statement from your
 *  version.  If you delete this exception statement from all source files in
 *  the program, then also delete it here.
 *
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
\*****************************************************************************/

#include "config.h"

#include <signal.h>

#if defined HAVE_BG_FILES
/* Use symbols from the runjob.so library provided by IBM.
 * Do NOT use debugger symbols local to the srun command */

#else

#include "src/common/log.h"

#include "debugger.h"
#include "srun_job.h"
#include "launch.h"

/*
 *  Instantiate extern variables from debugger.h
 */
MPIR_PROCDESC *MPIR_proctable;
int MPIR_proctable_size;
volatile int MPIR_debug_state;
int MPIR_being_debugged;
int MPIR_i_am_starter;
int MPIR_acquired_pre_main;
char *totalview_jobid  = NULL;
char *totalview_stepid = NULL;

#ifdef DEBUGGER_PARTIAL_ATTACH
  int MPIR_partial_attach_ok;
#endif

void MPIR_Breakpoint(srun_job_t *job)
{
	/*
	 * This just notifies parallel debugger that some event of
	 *  interest occurred.
	 */
	debug("In MPIR_Breakpoint");
	launch_g_fwd_signal(SIG_DEBUG_WAKE);
}
#endif