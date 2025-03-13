#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

#define max_limit 100

int bit_to_dec(int bits){
	int bitred = 7;
	int sum = 0;
	while(bits!=0){
		sum += (int)pow(2,bitred);
		bitred--;
		bits--;
	}
	return sum;
}

void main(){

    int subnet_mask;
    char string[max_limit];
    int total_address = 0;
    int mask_arr[4] = {};
    int net_arr[4] = {};
    int wild_arr[4] = {};
    int broadcast_arr[4] = {};
    printf("Enter the IP Address: ");
    scanf("%[^\n]",string); 
    char* string_tok = strtok(string,".");
   // printf("%s\n",string_tok);
    int i=0;
    char* array[4];
    int ip_arr[4];
    while(string_tok != NULL){
        array[i++] = string_tok;
        string_tok = strtok(NULL,".");
    }
    for(int j=0; j<4; j++){
        char* cache = array[j];
        int res = 0;
        for(int k=0; k<strlen(cache); k++){
		if(!isdigit(cache[k])){
			printf("Invalid data found.\n");
			while(getchar()!='\n');
			return;
		}
            	res = res * 10 + cache[k] - '0'; 
        }
	if(res<0 || res>255){
		printf("Invalid Ip Range.\n");
		return;
	}	
        ip_arr[j] = res;
    }
    
recalc:
    printf("Enter the Subnet Mask[1-32]: ");
    if(scanf("%d",&subnet_mask)!=1){
	printf("Invalid entry, Enter only Integer\n");
	while(getchar()!='\n');
	return;
    }

    if(subnet_mask<1 || subnet_mask>32){
	printf("Enter mask between 1-32\n\n");
	goto recalc;
    }
	
    
    int idx = 0;
    int subnet_mask_t = subnet_mask;
    total_address = (int)pow(2,(32-subnet_mask)) - 2;

    while(subnet_mask!=0){
	if(subnet_mask<8){
		mask_arr[idx++] = bit_to_dec(subnet_mask % 8);
		subnet_mask = 0;
		break;
	}
	mask_arr[idx] = 255;
	idx++;
	subnet_mask-=8;
    }
    
    printf("\n");
    printf("Ip Address:   ");
    for(int j=0; j<4; j++){
	if(j==3){
		printf("%d",ip_arr[j]);
		continue;
	}
        printf("%d.",ip_arr[j]);
    }
    printf("\n");
    printf("Mask Address: ");
    for(int i=0; i<4; i++){
        if(i==3){
                printf("%d",mask_arr[i]);
                continue;
        }
    	    printf("%d.",mask_arr[i]);
    }
    
    printf("\n");
	
    printf("WildCard:     ");
    for(int i=0; i<4; i++){
	wild_arr[i] = 255-mask_arr[i];
	if(i==3){
	        printf("%d",wild_arr[i]);
		continue;
	}
	printf("%d.",wild_arr[i]);
    }

	
    printf("\n\n");

    if(subnet_mask_t==32) goto down;

    printf("Network:      ");    
    for(int i=0; i<4; i++){
	net_arr[i] = ip_arr[i] & mask_arr[i];
        if(i==3){
                printf("%d",net_arr[i]);
                continue;
        }
	printf("%d.",net_arr[i]);
    }


    for(int i=0; i<4; i++){
	broadcast_arr[i] = net_arr[i] | wild_arr[i];
    }

    printf("\n");

    printf("Min Host:     ");
    for(int i=0; i<4; i++){
	if(i==3){
		if(subnet_mask_t==31){
			printf("%d ",net_arr[i]);
			continue;
		}
		printf("%d",net_arr[i]+1);
		continue;
	}
	printf("%d.",net_arr[i]);
    }
	
    printf("\n");
  
    printf("Max Host:     ");
    for(int i=0; i<4; i++){
	if(i==3){
		if(subnet_mask_t==31){
			printf("%d ",broadcast_arr[i]);
			continue;
		}
		printf("%d",broadcast_arr[i]-1);
		continue;
	}
	printf("%d.",broadcast_arr[i]);
    }

    printf("\n");

    if(subnet_mask_t==31) goto down;

    printf("BroadCast:    ");
    for(int i=0; i<4; i++){
        if(i==3){
                printf("%d",broadcast_arr[i]);
                continue;
        }
	printf("%d.",broadcast_arr[i]);
    }
    printf("\n");
down:
    if(subnet_mask_t==32) total_address = 1;
    if(subnet_mask_t==31) total_address = 2;
    printf("Hosts/Net:    %d\n\n",abs(total_address));

}
