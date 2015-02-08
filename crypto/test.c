#include <stdio.h>
#include <string.h>
#include "crypto.h"
#include "type.h"

#define  Debug_msg printf


rtaMac_test(void)
{
 u8 Data[] = "123456789asdffgggggggggggrrrrrtttttttyyyyyoooooiiiiipppppqqqqqqmmmm";
 u8 DMac[] = {0x08,0x02,0xac,0xcf,0x23,0x3b,0xc8,0x89,0};
 u8 seed[] = {0xef,0x10,0x55,0x67,0};
 u8 key[16] = {0};
 u32 i;

 ratDmac_GetKey(DMac,seed,key);
 Debug_msg("key:\n");
 for(i = 0;i < 15;i++)
 Debug_msg("0x%x",key[i]);
 Debug_msg("\n");
 Debug_msg("Data: \n%s\n",Data);
 ratDmac_skip(key,12,0,Data,strlen(Data));
 Debug_msg("Encrypt Data:%s\n",Data);
 ratDmac_skip(key,12,0,Data,strlen(Data));
 Debug_msg("Decrypt Data: \n%s\n",Data);

}
main()
{
 rtaMac_test();
}
