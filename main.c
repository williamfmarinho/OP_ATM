#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

#define LEITURA 0
#define ESCRITA 1
#define processos 4
#define espera 1


void adicionarValor(int conta[], int i, int valor){
    conta[i] += valor;
  }
void removerValor(int conta[], int i, int valor){
  conta[i] -= valor;
  if (conta[i] < 0)
      conta[i] = 0;
}
int pegarValor(int conta[], int i){
  return conta[i];
}

void mostrarContas(int conta[]){
  printf("\n");
  for (int i = 0; i < 6; i++)
    printf("Conta: %d, saldo: %d\n",i,conta[i]);
}



int main(void){
  int fd[processos][2];
  int fd_retorno[processos][2];
  pid_t pid[4];
  for (int i = 0; i < processos; i++){
    if (pipe(fd[i]) < 0){
        perror("Erro na criacao do pipe\n");
      exit(1);
    }
    if (pipe(fd_retorno[i]) < 0){
        perror("Erro na criacao do pipe de retorno\n");
      exit(1);
    }
  }
  for (int i = 0; i < processos; i++){
    if ((pid[i] = fork()) < 0){
        perror("Erro no fork\n");
      exit(1);
    }
    else
    if (pid[i] == 0){
      if (i == 0){
          close(fd[0][LEITURA]);
          char instrucao[20];
          char retorno[10];
          int P;
          int S;
          int T;
          int contador = 5;
          FILE *f0 = fopen("0.txt", "r");
          while(contador > 0){
            
            fscanf(f0, "%d,%d,%d", &P, &S, &T);
            write(fd[0][ESCRITA], &P, sizeof(P));
            //printf ("ATM 1 - Instrucao: %d\n", P);
            read(fd_retorno[0][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 1 - Chegou retorno!\n");
            write(fd[0][ESCRITA], &S, sizeof(S));
            //printf ("ATM 1 - Instrucao: %d\n", S);
            read(fd_retorno[0][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 1 - Chegou retorno!\n");
            write(fd[0][ESCRITA], &T, sizeof(T));
            //printf ("ATM 1 - Instrucao: %d\n", T);
            read(fd_retorno[0][LEITURA], retorno, sizeof(retorno)+1);
            contador --;
            
          }
        exit(0);
      }
      if (i == 1){
        close(fd[1][LEITURA]);
          char instrucao[20];
          char retorno[10];
          int P;
          int S;
          int T;
          int contador = 5;
          FILE *f1 = fopen("1.txt", "r");
          while(contador > 0){
            
            fscanf(f1, "%d,%d,%d", &P, &S, &T);
            write(fd[1][ESCRITA], &P, sizeof(P));
            //printf ("ATM 2 - Instrucao: %d\n", P);
            read(fd_retorno[1][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 2 - Chegou retorno!\n");
            write(fd[1][ESCRITA], &S, sizeof(S));
            //printf ("ATM 2 - Instrucao: %d\n", S);
            read(fd_retorno[1][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 2 - Chegou retorno!\n");
            write(fd[1][ESCRITA], &T, sizeof(T));
            //printf ("ATM 2 - Instrucao: %d\n", T);
            read(fd_retorno[1][LEITURA], retorno, sizeof(retorno)+1);
            contador --;
            
          }
        exit(0);
      }        
      if (i == 2){
        close(fd[2][LEITURA]);
          char instrucao[20];
          char retorno[10];
          int P;
          int S;
          int T;
          int contador = 5;
          FILE *f2 = fopen("2.txt", "r");
          while(contador > 0){
            
            fscanf(f2, "%d,%d,%d", &P, &S, &T);
            write(fd[2][ESCRITA], &P, sizeof(P));
            //printf ("ATM 1 - Instrucao: %d\n", P);
            read(fd_retorno[2][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 1 - Chegou retorno!\n");
            write(fd[2][ESCRITA], &S, sizeof(S));
            //printf ("ATM 1 - Instrucao: %d\n", S);
            read(fd_retorno[2][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 1 - Chegou retorno!\n");
            write(fd[2][ESCRITA], &T, sizeof(T));
            //printf ("ATM 1 - Instrucao: %d\n", T);
            read(fd_retorno[2][LEITURA], retorno, sizeof(retorno)+1);
            contador --;
            
          }
        exit(0);
      }
      if (i == 3){
        close(fd[3][LEITURA]);
          char instrucao[20];
          char retorno[10];
          int P;
          int S;
          int T;
          int contador = 5;
          FILE *f3 = fopen("3.txt", "r");
          while(contador > 0){
            
            fscanf(f3, "%d,%d,%d", &P, &S, &T);
            write(fd[3][ESCRITA], &P, sizeof(P));
            //printf ("ATM 1 - Instrucao: %d\n", P);
            read(fd_retorno[3][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 1 - Chegou retorno!\n");
            write(fd[3][ESCRITA], &S, sizeof(S));
            //printf ("ATM 1 - Instrucao: %d\n", S);
            read(fd_retorno[3][LEITURA], retorno, sizeof(retorno)+1);
            //printf ("ATM 1 - Chegou retorno!\n");
            write(fd[3][ESCRITA], &T, sizeof(T));
            //printf ("ATM 1 - Instrucao: %d\n", T);
            read(fd_retorno[3][LEITURA], retorno, sizeof(retorno)+1);
            contador --;
            
          }
        exit(0);
        }
      }

  }
    

  
  //--------------------------------------------------------------------------//
if (getpid() != pid[0] && getpid() != pid[1] && getpid() != pid[2] && getpid() != pid[3]) {
  //Zerando todas as contas
  int conta[6];
  for (int i = 0; i < 6; i++)
    conta[i] = 0;

  close(fd[0][ESCRITA]);
  close(fd[1][ESCRITA]);
  close(fd[2][ESCRITA]);
  close(fd[3][ESCRITA]);
  close(fd_retorno[0][LEITURA]);
  close(fd_retorno[1][LEITURA]);
  close(fd_retorno[2][LEITURA]);
  close(fd_retorno[3][LEITURA]);

  
  char retorno[10];
  strcpy(retorno, "OK");
  int instrucao;
  int i_conta;
  int dinheiros;
  int n_operacoes_servidor = 3;
  
  for (int j = 0; j < n_operacoes_servidor; j++){
    for (int i = 0; i < processos; i++){
  
      
    read(fd[i][LEITURA], &instrucao, sizeof(instrucao));
    //printf("Pai: Instrucao: %d\n", instrucao);
    write(fd_retorno[i][ESCRITA], retorno, strlen(retorno));
    //sleep(espera);
    
    read(fd[i][LEITURA], &i_conta, sizeof(i_conta));
    //printf("Pai: i_conta: %d\n", i_conta);
    write(fd_retorno[i][ESCRITA], retorno, strlen(retorno));
    //sleep(espera);
    
    read(fd[i][LEITURA], &dinheiros, sizeof(dinheiros));
    //printf("Pai: dinheiros: %d\n", dinheiros);
    write(fd_retorno[i][ESCRITA], retorno, strlen(retorno));
    //sleep(espera);
    
    
    if (!instrucao){
      adicionarValor(conta, i_conta, dinheiros);
      printf("Adicionou %d na conta %d\n", dinheiros, i_conta);
      }
    else{
      removerValor(conta, i_conta, dinheiros);
      printf("Removeu %d da conta %d\n", dinheiros, i_conta);
      }
    }
  }


  
  mostrarContas(conta);
  exit(0);
  
  }
  return 0;
}