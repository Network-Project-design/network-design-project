#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <time.h>
#include "iniparser/src/iniparser.h" 
#define MAXSZ 200

int port;
char *TheServerI;
char TheServerIp[100];
char *TheUserIdWhichIsChanged;
char *ThePassIdchange;
char ThetUserIdWhichIsChanged[100];
char ThetPassIdchange[100];
char UpdtTheIniStrng[100];
char userId[100];
char pass[100];

            char date[10];
             char user[5];
             char size[5];
             char TheResult[200];
             int len,pos,s=0,ll;
             int p;
             

void access_client_ini(char * ini_name);
void update_client_ini(char * ini_name,int Selecteddd);
void auth_client_ini(char * ini_name);
int main()
{
    access_client_ini("client.ini"); 
 int sockfd;

 struct sockaddr_in serverAddress;

int n,TheAuthhFlag=1,TheMenueeFlagg=1,TheMenueeOption;
char Message1[MAXSZ];
char Message2[MAXSZ];
char TheAuthhResultt[100];
char SendforWhomeeee[MAXSZ];
char TheMessageSndToWhomeee[MAXSZ];
char ToConfirmToTheSend[2];
char TheDrrOption[1];
int drID;
char CheckinggForTheDeleteeee[2];
char TheReadedMessage[100];
sockfd=socket(AF_INET,SOCK_STREAM,0);
memset(&serverAddress,0,sizeof(serverAddress));
serverAddress.sin_family=AF_INET;
serverAddress.sin_addr.s_addr=inet_addr(TheServerIp);
serverAddress.sin_port=htons(port);
connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

 while(1)
 {

n=recv(sockfd,Message2,MAXSZ,0);
if (recv > 0) 
printf("s: %s\n ",Message2);        

    while(TheAuthhFlag==1)
    {
    printf("Enter your User ID : ");
    fgets(userId,MAXSZ,stdin);
    if(userId[0]=='#')
    break;
    n=strlen(userId)+1;
    send(sockfd,userId,n,0);
    
    printf("Enter your Password : ");
        fgets(pass,MAXSZ,stdin);
    if(pass[0]=='#')
    break;
    n=strlen(pass)+1;
    send(sockfd,pass,n,0);
    

           n=recv(sockfd,Message2,MAXSZ,0);
           if (recv > 0) 
           strcpy(TheAuthhResultt,Message2);
           printf("s : %s\n",TheAuthhResultt);
           if(strlen(TheAuthhResultt)<40)
           TheAuthhFlag=-1;

           }
           int TheMenueeFlagg=1;
            auth_client_ini("client.ini");
            while(TheMenueeFlagg!=-1)
            {
           printf("Hello %s\nPlease choose your option:\n1)Read/Delete Messages\n2)Write Message to User\n3)Change config parameters\n4)Quit\nOption->",userId);
           scanf("%d",&TheMenueeOption);
           if(TheMenueeOption==1)
           {
          strcpy(Message2,"");
           n=1;
          send(sockfd,"1",n,0); 
          
         int TheCounterr=0;
         int Beginn1=0;
         int ToBegin2;
         int end;
         char fromWho[Beginn1];
         char dateunixaa[10];
         int TheBeginnFlagg=0;
         char Messages[100][100];
          while(strcmp(Message2,"finish")!=0){
          
          n=recv(sockfd,Message2,MAXSZ,0);
        
          if (recv > 0) 
          {
          if((strcmp(Message2,"finish")!=0)&&(TheCounterr!=0)&&(TheCounterr!=1))
           {
            end=strlen(Message2);
            
             for(p=Beginn1;p<strlen(Message2);p++)
             {
                     if(Message2[p]=='_'&&(TheBeginnFlagg==0))
                     {
                     Beginn1=p;
                     TheBeginnFlagg=1;
                     }
                     if(Message2[p]=='_')
                     ToBegin2=p;
             }
             strcpy(Messages[TheCounterr-2],Message2);
  
             strncat(TheResult,date,10);  
             for(s=0;s<5;s++)
             {
              user[s]=Messages[TheCounterr-2][s+11];
             }   
         
            strncat(TheResult,"From:",5); 
             strncat(TheResult,user,5); 
              strncat(TheResult,",",1); 
             for(s=0;s<10;s++)
             {
              date[s]=Messages[TheCounterr-2][s];
             }   
         
              char date2[10];
              strncpy(date2,date,10);
              struct tm  ts;
              char  dateConverted[80];

       time_t now = (time_t) strtol(date2, NULL, 10); 
           
            ts = *localtime(&now);
                 strftime(dateConverted, sizeof(dateConverted), "%Y-%m-%d %H:%M:%S", &ts);
                 strncat(TheResult,"Date:",5);
                 strcat(TheResult,dateConverted);
                  strncat(TheResult,",",1); 
        
     
              for(s=0;Messages[TheCounterr-2][s+17]!='.';s++)
             {
              size[s]=Messages[TheCounterr-2][s+17];
             }   
         
            strncat(TheResult,"Size:",5);
             strncat(TheResult,size,2); 
             strncat(TheResult,"Byte.",5);

                    printf("\n%d) %s",TheCounterr-1,TheResult);           
                 
             }
            TheCounterr++;
           }
           }
           strcpy(Message2,"");
           strcpy(TheReadedMessage,"");
           printf("\n");
           printf("Type R for Reading, D for deleting ->");
           scanf("%s",&TheDrrOption);
           n=2;
           send(sockfd,TheDrrOption,n,0); 
           printf("\nType ID of the message");
           scanf("%d",&drID);
           if(TheDrrOption[0]=='R'||TheDrrOption[0]=='r')
           {
           for(ll=0;ll<=TheCounterr;ll++)
            {
                 if(drID==ll)
                 {
   
                  n=strlen(Messages[ll-1])+1;
                 send(sockfd,Messages[ll-1],n,0);
            strcpy(Message2,"");
            strcpy(TheReadedMessage,"");
            n=recv(sockfd,Message2,MAXSZ,0);
            if (recv > 0) 
            {
            strcpy(TheReadedMessage,Message2);
            printf("Your Message :%s   \n",TheReadedMessage);    
            }
                 }
            }

              
           }
           if(TheDrrOption[0]=='D'||TheDrrOption[0]=='d')
           {

           for(ll=0;ll<=TheCounterr;ll++)
            {
              if(drID==ll)
              {
                 printf("Are you sure that you want to delet message<%d> (Y OR N)\n",ll);
                 scanf("%s",&CheckinggForTheDeleteeee);
                 n=2;
          send(sockfd,CheckinggForTheDeleteeee,n,0);
                 if(CheckinggForTheDeleteeee[0]=='y'||CheckinggForTheDeleteeee[0]=='Y')
                 {
                  printf("The file has been removed successfully\n");
                  n=strlen(Messages[ll-1])+1;
                 send(sockfd,Messages[ll-1],n,0);
                 }
                if(CheckinggForTheDeleteeee[0]=='N'||CheckinggForTheDeleteeee[0]=='n')
                 {
                  printf("we have cancelled delete operation\n");/////done cancelingg 
                 }

              
            }
           }
           }
               TheMenueeOption=9;
           }
           if(TheMenueeOption==2)
              {
        n=1;
    send(sockfd,"2",n,0); 

        printf("Give Target UserId: ");

    scanf("%s",&SendforWhomeeee

    n=strlen(SendforWhomeeee)+1;
    send(sockfd,SendforWhomeeee,n,0);    

   printf("Please Type Text: ");

    scanf("%s",&TheMessageSndToWhomeee);
    if(TheMessageSndToWhomeee[0]=='#')
    break;
    n=strlen(TheMessageSndToWhomeee)+1;
    send(sockfd,TheMessageSndToWhomeee,n,0);

   printf("Would you like to Send message to %s? (Y/N)",SendforWhomeeee);//Y for yes and N for nooooo
 
    scanf(" %s",&ToConfirmToTheSend);
    if(ToConfirmToTheSend[0]=='#')
    break;
    n=strlen(ToConfirmToTheSend)+1;
    send(sockfd,ToConfirmToTheSend,n,0);

       }
       if(TheMenueeOption==3)
       {
       access_client_ini("client.ini");
          int Selecteddd;
          char checkSelection[2];
         printf("Would you change any following value?\n1)TargetServer : %s\n2)TargetPort : %d\n3)userId : %s\n4)Passwd : %s\nOption->",TheServerIp,port,ThetUserIdWhichIsChanged,ThetPassIdchange);
       scanf("%d",&Selecteddd);
       if(Selecteddd==1)
       {
       printf("\nPlease give new TargetServer->");
       scanf("%s",&UpdtTheIniStrng);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
        update_client_ini("client.ini",Selecteddd);
        }
               if(Selecteddd==2)
       {
       printf("\nPlease give new TargetPort ->");
       scanf("%s",&UpdtTheIniStrng);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
        update_client_ini("client.ini",Selecteddd);
        }
        if(Selecteddd==3)
       {
       printf("\nPlease give new User Id  ->");
       scanf("%s",&UpdtTheIniStrng);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
       {
        update_client_ini("client.ini",Selecteddd);
          n=strlen(UpdtTheIniStrng)+1;
         send(sockfd,UpdtTheIniStrng,n,0);
        }
        }
                               if(Selecteddd==4)
       {
       printf("\nPlease give new Passwd  ->");
       scanf("%s",&UpdtTheIniStrng);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
        update_client_ini("client.ini",Selecteddd);
        }
       }
       if(TheMenueeOption==4)
       {
                                 n=1;
    send(sockfd,"4",n,0); 
              TheMenueeFlagg=-1;
         printf("\nAu revoir!\n");///finalllyyyyyyy!! 
       }

            }

  
  
 }

 return 0;
}
void access_client_ini(char * ini_name)
{
     strcpy(TheServerIp,"");
     strcpy(ThetUserIdWhichIsChanged,"");
     strcpy(ThetPassIdchange,"");
     
    dictionary  *   ini ;
     
    ini = iniparser_load(ini_name);
    if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n", ini_name);
        
    }
    iniparser_dump(ini, stderr);

    port = iniparser_getint(ini, "client:TargetPort", -1);

    TheServerI=iniparser_getstring(ini, "client:TargetServer", NULL);
    
    strncpy(TheServerIp, TheServerI,  strlen(TheServerI));
 
     TheUserIdWhichIsChanged=iniparser_getstring(ini, "client:UserID", NULL);
    
    strncpy(ThetUserIdWhichIsChanged, TheUserIdWhichIsChanged,  strlen(TheUserIdWhichIsChanged));
    
        ThePassIdchange=iniparser_getstring(ini, "client:Passwd", NULL);
    
    strncpy(ThetPassIdchange, ThePassIdchange,  strlen(ThePassIdchange));
}
void update_client_ini(char * ini_name,int Selecteddd)
{

     
         dictionary  *   ini ;

    ini = iniparser_load(ini_name);
  if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n", ini_name);
        
    }
               FILE *finp = fopen("client.ini", "w");
      fclose(finp);
    if(Selecteddd==1)
    {
iniparser_set(ini,"client:TargetServer",UpdtTheIniStrng);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
    if(Selecteddd==2)
    {
iniparser_set(ini,"client:TargetPort",UpdtTheIniStrng);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
        if(Selecteddd==3)
    {
iniparser_set(ini,"client:User ID",UpdtTheIniStrng);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
        if(Selecteddd==4)
    {
iniparser_set(ini,"client:Passwd",UpdtTheIniStrng);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
    	
 
}
void auth_client_ini(char * ini_name)
{

     
         dictionary  *   ini ;

    ini = iniparser_load(ini_name);
    if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n", ini_name);
        
    }
               FILE *finp = fopen("client.ini", "w");
      fclose(finp);

iniparser_set(ini,"client:UserID",userId);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);

iniparser_set(ini,"client:Passwd",pass);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
}
