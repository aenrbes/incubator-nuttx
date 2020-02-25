/****************************************************************************
 * net/can/can_setsockopt.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <debug.h>

#include <netpacket/can.h>

#include <nuttx/net/net.h>
#include <nuttx/net/can.h>

#include "socket/socket.h"
#include "utils/utils.h"
#include "can/can.h"

#ifdef CONFIG_NET_CANPROTO_OPTIONS

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: can_setsockopt
 *
 * Description:
 *   can_setsockopt() sets the CAN-protocol option specified by the
 *   'option' argument to the value pointed to by the 'value' argument for
 *   the socket specified by the 'psock' argument.
 *
 *   See <netinet/can.h> for the a complete list of values of CAN protocol
 *   options.
 *
 * Input Parameters:
 *   psock     Socket structure of socket to operate on
 *   option    identifies the option to set
 *   value     Points to the argument value
 *   value_len The length of the argument value
 *
 * Returned Value:
 *   Returns zero (OK) on success.  On failure, it returns a negated errno
 *   value to indicate the nature of the error.  See psock_setcockopt() for
 *   the list of possible error values.
 *
 ****************************************************************************/

int can_setsockopt(FAR struct socket *psock, int option,
                   FAR const void *value, socklen_t value_len)
{
  FAR struct can_conn_s *conn;
  int ret;
  int count = 0;

  DEBUGASSERT(psock != NULL && value != NULL && psock->s_conn != NULL);
  conn = (FAR struct can_conn_s *)psock->s_conn;

  if (psock->s_type != SOCK_RAW)
    {
      nerr("ERROR:  Not a RAW CAN socket\n");
      return -ENOTCONN;
    }

  switch (option)
    {
      case CAN_RAW_FILTER:
        if (value_len % sizeof(struct can_filter) != 0)
          {
            ret = -EINVAL;
          }

        if (value_len > CAN_RAW_FILTER_MAX * sizeof(struct can_filter))
          {
            ret = -EINVAL;
          }

        count = value_len / sizeof(struct can_filter);

        /* FIXME pass filter to driver */

        break;

      case CAN_RAW_ERR_FILTER:
        break;

      case CAN_RAW_LOOPBACK:
        break;

      case CAN_RAW_RECV_OWN_MSGS:
        break;

      case CAN_RAW_FD_FRAMES:
        break;

      case CAN_RAW_JOIN_FILTERS:
        break;

      default:
        nerr("ERROR: Unrecognized CAN option: %d\n", option);
        ret = -ENOPROTOOPT;
        break;
    }

  return ret;
}

#endif /* CONFIG_NET_CANPROTO_OPTIONS */