extern "C" {
#include "iwlib.h"		/* Header */
}

/**************************** CONSTANTS ****************************/

/*
 * Error codes defined for setting args
 */
#define IWERR_ARG_NUM		-2
#define IWERR_ARG_TYPE		-3
#define IWERR_ARG_SIZE		-4
#define IWERR_ARG_CONFLICT	-5
#define IWERR_SET_EXT		-6
#define IWERR_GET_EXT		-7

/**************************** VARIABLES ****************************/

/*
 * Ugly, but deal with errors in set_info() efficiently...
 */
static int	errarg;
static int	errmax;

static int
set_essid_info(int		skfd,
	       char *		ifname,
	       char *		args[],		/* Command line args */
	       int		count)		/* Args count */
{
  struct iwreq		wrq;
  int			i = 1;
  char			essid[IW_ESSID_MAX_SIZE + 1];
  int			we_kernel_version;

  if((!strcasecmp(args[0], "off")) ||
     (!strcasecmp(args[0], "any")))
    {
      wrq.u.essid.flags = 0;
      essid[0] = '\0';
    }
  else
    if(!strcasecmp(args[0], "on"))
      {
	/* Get old essid */
	memset(essid, '\0', sizeof(essid));
	wrq.u.essid.pointer = (caddr_t) essid;
	wrq.u.essid.length = IW_ESSID_MAX_SIZE + 1;
	wrq.u.essid.flags = 0;
	if(iw_get_ext(skfd, ifname, SIOCGIWESSID, &wrq) < 0)
	  return(IWERR_GET_EXT);
	wrq.u.essid.flags = 1;
      }
    else
      {
	i = 0;

	/* '-' or '--' allow to escape the ESSID string, allowing
	 * to set it to the string "any" or "off".
	 * This is a big ugly, but it will do for now */
	if((!strcmp(args[0], "-")) || (!strcmp(args[0], "--")))
	  {
	    if(++i >= count)
	      return(IWERR_ARG_NUM);
	  }

	/* Check the size of what the user passed us to avoid
	 * buffer overflows */
	if(strlen(args[i]) > IW_ESSID_MAX_SIZE)
	  {
	    errmax = IW_ESSID_MAX_SIZE;
	    return(IWERR_ARG_SIZE);
	  }
	else
	  {
	    int		temp;

	    wrq.u.essid.flags = 1;
	    strcpy(essid, args[i]);	/* Size checked, all clear */
	    i++;

	    /* Check for ESSID index */
	    if((i < count) &&
	       (sscanf(args[i], "[%i]", &temp) == 1) &&
	       (temp > 0) && (temp < IW_ENCODE_INDEX))
	      {
		wrq.u.essid.flags = temp;
		++i;
	      }
	  }
      }
  /* Get version from kernel, device may not have range... */
  we_kernel_version = iw_get_kernel_we_version();

  /* Finally set the ESSID value */
  wrq.u.essid.pointer = (caddr_t) essid;
  wrq.u.essid.length = strlen(essid);
  if(we_kernel_version < 21)
    wrq.u.essid.length++;

  if(iw_set_ext(skfd, ifname, SIOCSIWESSID, &wrq) < 0)
    return(IWERR_SET_EXT);

  /* Var args */
  return(i);
}
int sockets_open(void)
	{
	  int		sock;

	      sock = socket(AF_INET6, SOCK_DGRAM, 0);
	      if(sock >= 0)
		return sock;

	  return -1;
	}

}
int main(char** argv,int argc){
	return set_essid_info(int		skfd,
	       char *		ifname,
	       char *		args[],		/* Command line args */
	       int		count)	;
}
