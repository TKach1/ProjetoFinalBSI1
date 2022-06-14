#include "GameModes.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void desalocaMatriz(char **m,int nL){
    for(int i = 0; i<nL; i++){
        free(m[i]);
    }
    free(m);
}
char** alocaMatriz(int nL,int nC){
    char** m;
    m = (char**) malloc (nL * sizeof(char*));
    for(int i= 0;i<nL;i++){
        m[i] = (char*) malloc (nC * sizeof(char));
    }
    return m;
}
void imprimeMatriz(char **mAtual,int nL,int nC){
    int i,j;
    for(i=0;i<nL;i++){
        for(j=0;j<nC;j++){
            printf("%c",mAtual[i][j]);
        }
        printf("\n");
    }
}
void byebye(char **mat, int nL){
    desalocaMatriz(mat,nL);
    printf("\nSaindo...");
    Sleep(100);
    exit(0);
}
void limpaMatriz(char **m, int nL, int nC){
    int i,j;
    for(i=0;i<nL;i++)
     for(j=0;j<nC;j++)
        m[i][j]=VAZ;
}
void menuInicJogo(char **mat, int nL, int nC){
    int opcao;

    printf("(1)Bloco\n(2)Blinker\n(3)Sapo\n(4)Glider\n(5)LWSS\n(0)Sair\nEntre com a opcao: ");
    scanf("%d",&opcao);
    switch(opcao)
    {
        case 1:   inicBloco(mat,nL,nC); break;
        case 2:   inicBlinker(mat,nL,nC); break;
        case 3:   inicSapo(mat,nL,nC); break;
        case 4:   inicGlider(mat,nL,nC); break;
        case 5:   inicLWSS(mat,nL,nC); break;
        default: byebye(mat,nL); break;
    }
        imprimeMatriz(mat,nL,nC);// TO DO

        printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo..."); while(getchar()!='\n'); getchar();

}
void copiaMatriz(char **mAnt,char **mAtual,int nL,int nC){
    int i,j;
    for(i=0;i<nL;i++)
        for(j=0;j<nC;j++)
            mAnt[i][j]=mAtual[i][j];
}
void atualizaMat(char **mAtual,char **mAnt,int nL,int nC){
    int l, c;
    int vizinhos = 0;
    //printf("\n\n\n\n\nIMPRIMINDO\n\n\n\n\n\n\n\n\n");
    //imprimeMatriz(mAnt,nL,nC);
    //getchar();
    for(l = 0; l<nL; l++){
        for(c = 0; c<nC; c++){
            vizinhos = 0;
            /*EXPLICAÇÃO
                1 2 3       . . .
                4 5 6   =   . # .
                7 8 9       . . .

                EX: 1 = mAnt[l+1][c-1];

                O número representa qual posição está sendo
                verificada, tendo como base o organismo na posição
                "5".
            */
            if(l != 0){
                if(c != 0){
                    if(mAnt[l-1][c-1] == ORG){ // 1
                        vizinhos++;
                    }
                }
                if(mAnt[l-1][c] == ORG){ // 2
                    vizinhos++;
                }
                if(c != (nC-1)){
                    if(mAnt[l-1][c+1] == ORG){ // 3
                        vizinhos++;
                    }
                }
            }
            if(c != 0){
                if(mAnt[l][c-1] == ORG){ // 4
                    vizinhos++;
                }
            }
            if(c != (nC-1)){    
                if(mAnt[l][c+1] == ORG){ // 6
                    vizinhos++;
                }
            }
            if(l != (nL-1)){
                if(c != 0){
                    if(mAnt[l+1][c-1] == ORG){ // 7
                        vizinhos++;
                    }
                }
                if(mAnt[l+1][c] == ORG){ // 8
                    vizinhos++;
                }
                if(c != (nC-1)){ 
                    if(mAnt[l+1][c+1] == ORG){ // 9
                        vizinhos++;
                    }
                }
            }
            if(vizinhos>3){
                mAtual[l][c] = VAZ;
            }if(vizinhos<2){
                mAtual[l][c] = VAZ;
            }if(mAnt[l][c] == VAZ && vizinhos == 3){
                mAtual[l][c] = ORG;
            }
            //printf("%d, %d\n", l , c);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Parte a ser completada //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void jogaJogoVida(char **mAtual, int nL, int nC, int nCiclos)
{
  char **mAnt;
  int c;

  //imprimindo na tela a matriz inicial
  system(CLEAN);
  imprimeMatriz(mAtual,nL,nC); //TO DO
  // getchar();
  mAnt = alocaMatriz(nL,nC); //TO DO

  for(c=1;c<=nCiclos;c++)
  {
        copiaMatriz(mAnt,mAtual,nL,nC);
        atualizaMat(mAtual,mAnt,nL,nC); 
        system(CLEAN);
        imprimeMatriz(mAtual,nL,nC);
        Sleep(100);
  }
  desalocaMatriz(mAnt,nL);
}


int main()
{

    char **mat;

    int nL = 0,nC = 0,nCiclos = 0;

    //TODO la�o INdeterminado que repete enquanto o usuario quiser continuar jogando:
    //cada jogo equivale a nCiclos de um padr�o de inicializacao
    //por exemplo o usuario pode escolher jogar nCiclos do padr�o Sapo
    // quando terminar jogar mais nCiclos do padr�o Blinker
    // depois encerrar o programa
    printf("\nDigite o Tamanho da Matriz (Largura): ");
    scanf("%d", &nC);
    printf("\nDigite o Tamanho da Matriz (Altura): ");
    scanf("%d", &nL);
    printf("\nDigite o Numero de Ciclos: ");
    scanf("%d", &nCiclos);

    mat = alocaMatriz(nL,nC);

    while(1 > 0){
        menuInicJogo(mat,nL,nC);
        jogaJogoVida(mat,nL,nC,nCiclos); 
    }//fim do laco indeterminado

}

////////////////////////////////////////////////////////
//inicios///////////////////////////////////////////////
////////////////////////////////////////////////////////

void inicBlinker(char **m, int nL, int nC)
{
    char padrao[1][3]={{ORG,ORG,ORG}};
    int i,j, xInic=nL/2, yInic=nC/2;

    limpaMatriz(m,nL,nC);

    for(i=0;i<1;i++)
        for(j=0;j<3;j++)
        m[xInic+i][yInic+j]=padrao[i][j];
}
void inicBloco(char **m, int nL, int nC)
{
    char padrao[2][2]={{ORG,ORG},{ORG,ORG}};
    int i,j,xInic=nL/2, yInic=nC/2;


    limpaMatriz(m,nL,nC);


    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
            m[xInic+i][yInic+j]=padrao[i][j];
}
void inicSapo(char **m, int nL, int nC)
{

    char padrao[2][4]={{VAZ,ORG,ORG,ORG},{ORG,ORG,ORG,VAZ}};
    int i,j,xInic=nL/2, yInic=nC/2;

    limpaMatriz(m,nL,nC);


    for(i=0;i<2;i++)
        for(j=0;j<4;j++)
            m[xInic+i][yInic+j]=padrao[i][j];

}
void inicGlider(char **m, int nL, int nC)
{
    char padrao[3][3]={{ORG,ORG,ORG},{ORG,VAZ,VAZ},{VAZ,ORG,VAZ}};
    int i,j,xInic,yInic;

    limpaMatriz(m,nL,nC);

    xInic=nL-4;
    yInic=nC-4;

    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            m[xInic+i][yInic+j]=padrao[i][j];
}
void inicLWSS(char **m, int nL, int nC)
{
    char padrao[4][5]={{VAZ,ORG,VAZ,VAZ,ORG},{ORG,VAZ,VAZ,VAZ,VAZ},{ORG,VAZ,VAZ,VAZ,ORG},{ORG,ORG,ORG,ORG,VAZ}};
    int i,j,xInic,yInic;

    limpaMatriz(m,nL,nC);

    xInic=nL-5;
    yInic=nC-6;

    for(i=0;i<4;i++)
        for(j=0;j<5;j++)
            m[xInic+i][yInic+j]=padrao[i][j];
}
