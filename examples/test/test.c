#include <stdio.h>
#include <cfreesrp.h>

int main()
{
    freesrp_status_t stat = CFREESRP_SUCCESS;

    stat = freesrp_init();

    if(stat != CFREESRP_SUCCESS)
    {
        printf("Could not connect to FreeSRP!\n");
    }
    else
    {
        printf("Connected to FreeSRP!\n");
    }

    freesrp_deinit();
}
