$NetBSD$

* Add PF and IPFilter support

--- pmlist.c.orig	2006-10-01 15:58:32.000000000 +0000
+++ pmlist.c
@@ -1,5 +1,6 @@
 #include <stdlib.h>
 #include <sys/wait.h>
+#include <string.h>
 #include <unistd.h>
 #include <upnp/upnp.h>
 #include "globals.h"
@@ -12,6 +13,10 @@
 #include "iptc.h"
 #endif
 
+#if defined(USE_PF) || defined(USE_IPFILTER)
+#include <stdio.h>
+#endif
+
 struct portMap* pmlist_NewNode(int enabled, long int duration, char *remoteHost,
 			       char *externalPort, char *internalPort,
 			       char *protocol, char *internalClient, char *desc)
@@ -249,7 +254,7 @@ int pmlist_AddPortMapping (int enabled, 
 
 	iptc_add_rule("nat", g_vars.preroutingChainName, protocol, g_vars.extInterfaceName, NULL, NULL, NULL, NULL, externalPort, "DNAT", buffer, TRUE);
 	free(buffer);
-#else
+#elif defined(USE_IPTABLES)
 	char command[COMMAND_LEN];
 	int status;
 	
@@ -281,6 +286,26 @@ int pmlist_AddPortMapping (int enabled, 
 	    wait(&status);		
 	  }
 	}
+#else
+	char rules[COMMAND_LEN];
+	char command[COMMAND_LEN];
+	GetIpAddressStr(ExternalIPAddress, g_vars.extInterfaceName);
+#if defined(USE_PF)
+	snprintf(command, sizeof(command), "/sbin/pfctl -a upnpd/%s-%s-%s-%s-%s-%s -f -", g_vars.extInterfaceName, protocol, ExternalIPAddress, externalPort, internalClient, internalPort);
+	FILE *pf = popen(command, "w");
+	if (pf == NULL) return 0;
+	snprintf(rules, sizeof(rules), "rdr pass on %s proto %s from any to %s port %s -> %s port %s", g_vars.extInterfaceName, protocol, ExternalIPAddress, externalPort, internalClient, internalPort);
+	trace(3, "%s", rules);
+	fprintf(pf, "%s\n", rules);
+	pclose(pf);
+#elif defined(USE_IPFILTER)
+	FILE *ipnat = popen("/usr/sbin/ipnat -f -", "w");
+	if (ipnat == NULL) return 0;
+	snprintf(rules, sizeof(rules), "rdr %s %s/32 port %s -> %s port %s %s\n", g_vars.extInterfaceName, ExternalIPAddress, externalPort, internalClient, internalPort, protocol);
+	trace(3, "%s", rules);
+	fprintf(ipnat, rules);
+	pclose(ipnat);
+#endif
 #endif
     }
     return 1;
@@ -301,7 +326,7 @@ int pmlist_DeletePortMapping(int enabled
 
 	iptc_delete_rule("nat", g_vars.preroutingChainName, protocol, g_vars.extInterfaceName, NULL, NULL, NULL, NULL, externalPort, "DNAT", buffer);
 	free(buffer);
-#else
+#elif defined(USE_IPTABLES)
 	char command[COMMAND_LEN];
 	int status;
 	
@@ -335,6 +360,28 @@ int pmlist_DeletePortMapping(int enabled
 	    wait(&status);		
 	  }
 	}
+#elif defined(USE_PF)
+	char anchor[COMMAND_LEN];
+	snprintf(anchor, sizeof(anchor), "upnpd/%s-%s-%s-%s-%s-%s", g_vars.extInterfaceName, protocol, ExternalIPAddress, externalPort, internalClient, internalPort);
+	trace(3, "flush anchor %s", anchor);
+	{
+		int status;
+		char *args[] =  {"pfctl", "-a", anchor, "-F", "all"};
+		if(!fork()) {
+			int rc = execv("/sbin/pfctl", args);
+			exit(rc);
+		} else {
+			wait(&status);
+		}
+	}
+#elif defined(USE_IPFILTER)
+	char rules[COMMAND_LEN];
+	FILE *ipnat = popen("/usr/sbin/ipnat -rf -", "w");
+	if (ipnat == NULL) return 0;
+	snprintf(rules, sizeof(rules), "rdr %s %s/32 port %s -> %s port %s %s\n", g_vars.extInterfaceName, ExternalIPAddress, externalPort, internalClient, internalPort, protocol);
+	trace(3, "remove %s", rules);
+	fprintf(ipnat, rules);
+	pclose(ipnat);
 #endif
     }
     return 1;
