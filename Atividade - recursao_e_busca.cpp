#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 86400

typedef struct pilha Pilha;

typedef struct time{
    short HH;	
    short MM;
    short SS;
} Time;

struct t_timetable{
    char cidade[100];
    Time horario;
    
};

struct pilha{
    int qtd;
    struct t_timetable dados[MAX];
};

Pilha* cria_Pilha(){
    Pilha *fp;
    fp = (Pilha*) malloc(sizeof(struct pilha));
    if(fp != NULL)
        fp->qtd = 0;
    return fp;
}

void deleteTime(Pilha* fp,Time t){
     int k,i = 0;
     while((i < fp->qtd) && (fp->dados[i].horario.HH*60*60 + fp->dados[i].horario.MM*60 + fp->dados[i].horario.SS != t.SS  +  t.HH*60*60 + t.MM*60))
     i++;
     for(k=i; k< fp->qtd-1; k++)
        fp->dados[k] = fp->dados[k+1];
     fp->qtd--;
}

int libera_Pilha(Pilha* fp){
	if(fp != NULL)
    	free(fp);
    return 1;
}


int put(Pilha* fp, Time t, char *cidade){
    if(fp == NULL)
        return 0;
    if(fp->qtd == MAX)
        return 0;
    if(*cidade == NULL){
        deleteTime(fp, t);
        return 0;
    }
    int k,i = 0;
    while(i < fp->qtd && (fp->dados[i].horario.HH*60*60 + fp->dados[i].horario.MM*60 + fp->dados[i].horario.SS < t.SS  +  t.HH*60*60 + t.MM*60)){
        i++;
    }
    for(k = fp->qtd-1; k >= i; k--)
        fp->dados[k+1] = fp->dados[k];

    strcpy(fp->dados[i].cidade, cidade);
    fp->dados[i].horario = t;
    fp->qtd++;
    return 1;
	}

int deleteTime_max(Pilha* fp){
     if(fp == NULL)
        return 0;
    if(fp->qtd == 0)
        return 0;
    fp->qtd--;
    return 1;
}

int indice(Pilha* fp, Time t) {
     if(fp == NULL)
        return 0;
    int i = 0;
    while((i < fp->qtd) && (fp->dados[i].horario.HH*60*60 + fp->dados[i].horario.MM*60 + fp->dados[i].horario.SS != t.SS  +  t.HH*60*60 + t.MM*60))
        i++;
    if(i == fp->qtd)//elemento nao encontrado
        return -1;

    return i;
}


int deleteTime_min(Pilha* fp){
   if(fp == NULL)
        return 0;
    if(fp->qtd == 0)
        return 0;
    int k = 0;
    for(k=0; k< fp->qtd-1; k++)
        fp->dados[k] = fp->dados[k+1];
    fp->qtd--;
    return 1;
}
int size(Pilha* fp){
    if(fp == NULL)
        return -1;
    else
        return fp->qtd;
}
char* get(Pilha* fp, Time t){
   
   int i = indice(fp,t);
    if(i >= 0){
      return fp->dados[i].cidade;
    }
    return NULL;

}

Time select(Pilha* fp, int indice){
    return fp->dados[indice - 1].horario;
}

bool contains(Pilha* fp, Time t){
    int i = indice(fp,t);
    if(i >= 0){
      return true;
    }
    return false;

} 

Time min(Pilha* fp){
    return fp->dados[0].horario;
}
Time max(Pilha* fp){
   return fp->dados[fp->qtd-1].horario;
}
Time ceiling(Pilha* fp,Time t){
   int i = 0;
   while((i < fp->qtd) && (fp->dados[i].horario.HH*60*60 + fp->dados[i].horario.MM*60 + fp->dados[i].horario.SS <= t.SS  +  t.HH*60*60 + t.MM*60))
   i++;
   return fp->dados[i].horario;
}

Time floor(Pilha* fp,Time t){
   int i = fp->qtd-1;
   while((i >=0 ) && (fp->dados[i].horario.HH*60*60 + fp->dados[i].horario.MM*60 + fp->dados[i].horario.SS >= t.SS  +  t.HH*60*60 + t.MM*60))
   i--;
   return fp->dados[i].horario;
}

int rank(Pilha* fp,Time t){
   int i = indice(fp,t);
   if(i > 0){
    return i;
   }
   return 0;
 
}


int size_range(Pilha* fp, Time t1, Time t2){
    int time1 =  t1.SS  +  t1.HH*60*60 + t1.MM*60;
    int time2 =  t2.SS  +  t2.HH*60*60 + t2.MM*60;
    int timeIntervalo,total = 0;
    for (int i = 0; i < fp->qtd; i++)
    {
        timeIntervalo = fp->dados[i].horario.HH*60*60 + fp->dados[i].horario.MM*60 + fp->dados[i].horario.SS;
        if(timeIntervalo > time1 && timeIntervalo < time2){
            total++;
        }
       
    }
  
   return total;
}
bool is_Empty(Pilha* fp){
    if(fp == NULL)
        return false;
    return true;
}

void imprime_Pilha(Pilha* fp){
    if(fp == NULL)
        return;
    int i;
    for(i=fp->qtd-1; i >=0 ; i--){
        printf("\nHora: %d:%d:%d \tCidade: %s\n",fp->dados[i].horario.HH,fp->dados[i].horario.MM,fp->dados[i].horario.SS,fp->dados[i].cidade);
    }
}

int main(){    
    int menu;
    Pilha* fp = cria_Pilha();
    
    do {
        printf("\n1. put");
        printf("\n2.  get");
        printf("\n3.  deleteTime");
        printf("\n4.  contains");
        printf("\n5.  is_empty");
        printf("\n6.  size");
        printf("\n7.  min");
        printf("\n8.  max");
        printf("\n9.  floor");
        printf("\n10. ceiling");
        printf("\n11.  rank");
        printf("\n12.  select");
        printf("\n13.  deleteTime_min");
        printf("\n14.  deleteTime_max");
        printf("\n15.  size_range");
        printf("\n16.  Imprimir a lista");
        printf("\n17.  Sair");
        printf("\n");
        
        scanf("%d", &menu);
        fflush(stdin);
        switch(menu) {
            case 1:
            	{
            		char cidade[100];
            		Time  t;
                    int hora,minuto,segundo;
            		printf("\nhora: ");
                	scanf("%d", &hora);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
                	fflush(stdin);
                	printf("\nDigite a cidade: ");
                	fflush(stdin);
                	gets(cidade);
                	put(fp, t, cidade);
                	printf("\nT_timetable inserido com sucesso.");
                    fflush(stdin);
            		break;
				}
		    case 2:
				{
					Time  t;
                    int hora,minuto,segundo;
            		printf("\nhora: ");
                	scanf("%d", &hora);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                	fflush(stdin);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
                   
                    printf("\thora: %s\n", get(fp, t));
                    break;

				}
			case 3:
				{
                    Time  t;
                    int hora,minuto,segundo;
                    printf("\nhora: ");
                	scanf("%d", &hora);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                	fflush(stdin);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
					deleteTime(fp, t);
					break;
				}
			case 4:
				{
                    Time  t;
                    int hora,minuto,segundo;
					printf("\nhora: ");
                	scanf("%d", &hora);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                	fflush(stdin);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
                    if(contains(fp, t) == true){
                        printf("\nExiste: ");
                        break;
                    }
					printf("\nnao existe: ");
					break;
				}
                case 5:
				{
            
                    if(is_Empty(fp) == true){
                        printf("\nHa dados: ");
                        break;
                    }
					printf("\nnvazia: ");
					break;
				}
                case 6:
				{
                   printf("\tCidade: %d\n" ,size(fp)); 
                   break;
				}
                case 7:
				{
                   Time  t = min(fp);
                   printf("\nHora: %d:%d:%d",t.HH,t.MM,t.SS);
                   break;
                }
                 case 8:
				{ 
                    Time  t = max(fp);
                    printf("\nHora: %d:%d:%d",t.HH,t.MM,t.SS);
                    break;
				}
                 case 9:
				{
                    Time  t;
                    int hora,minuto,segundo;
            		printf("\nhora: ");
                	scanf("%d", &hora);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                    fflush(stdin);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
                    Time TimeFloor = floor(fp,t);
                    printf("\nHora: %d:%d:%d",TimeFloor.HH,TimeFloor.MM,TimeFloor.SS);
                    break;
                }
                 case 10:
				{ 
                    Time  t;
                    int hora,minuto,segundo;
            		printf("\nhora: ");
                	scanf("%d", &hora);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                    fflush(stdin);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
                    Time TimeCeiling = ceiling(fp,t);
                    printf("\nHora: %d:%d:%d",TimeCeiling.HH,TimeCeiling.MM,TimeCeiling.SS);
                    break;
				}
                case 11: {
                    
                    Time  t;
                    int hora,minuto,segundo;
					printf("\nhora: ");
                	scanf("%d", &hora);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                	fflush(stdin);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
                    printf("\nNumero de chaves a menos e de : %d",rank(fp,t));
                    break;
                } case 12: {
                      int indice = 0;
                      scanf("%d", &indice);
                      Time t = select(fp,indice);
                      printf("\nHora: %d:%d:%d",t.HH,t.MM,t.SS);
                      break;
                }
                case 13: {
                      deleteTime_min(fp);
                      break;
                }
                case 14: {
                     deleteTime_max(fp);
                    break;
                }
                 case 15: {
                    Time  t;
                    int hora,minuto,segundo;
                    Time t2;
                    int hora2,minuto2,segundo2;
                
					printf("\nhora: ");
                	scanf("%d", &hora);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo);
                	fflush(stdin);
					printf("\nhora: ");
                	scanf("%d", &hora2);
                    fflush(stdin);
                	printf("\nminuto: ");
					scanf("%d", &minuto2);
                	fflush(stdin);
					printf("\nsegundo: ");
					scanf("%d", &segundo2);
                	fflush(stdin);
                    t.HH = hora;
                    t.MM = minuto;
                    t.SS = segundo;
                    t2.HH = hora2;
                    t2.MM = minuto2;
                    t2.SS = segundo2;
                    printf("\nNumero entre o intevalo e de  : %d", size_range(fp, t, t2));
                    break;

                }
                 case 16: {
                     imprime_Pilha(fp);
                     break;
                }
			     case 17: 
				{
					libera_Pilha(fp);
					return -1;
				}
			default:
				printf("\nOpcao invalida.");
		}
	} while(menu != 17 );
    return 0;
  }
