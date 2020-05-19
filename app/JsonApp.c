#include <cJSON.h>
#include <stdlib.h> 

//int create_js(void)
//{
//    cJSON *root;
//	cJSON * js_body ;
//    const char *const body = "body";
//	cJSON_Hooks hooks;
//	char *s;
//	
//    hooks.malloc_fn = pvPortMalloc;
//     hooks.free_fn = vPortFree;
//    cJSON_InitHooks(&hooks);
//	
//    /*create json string root*/
//    root = cJSON_CreateObject();
//    if(!root) {
//        printf("get root faild !\n");
//        goto EXIT;
//    }else printf("get root success!\n");


//        cJSON_AddItemToObject(root, body, js_body=cJSON_CreateObject());
//        cJSON_AddStringToObject(js_body,"name","xiaohui");
//        cJSON_AddNumberToObject(js_body,"value",600);
//        
//        s = cJSON_PrintUnformatted(root);
//      //  if(s){
//            printf("create js string is %s\n",s);
//	        send(0,s,strlen(s));	
//            vPortFree(s);
//        //}
//        
//        cJSON_Delete(root);
//    

//    return 0;
//EXIT:
//    return -1;
//}

