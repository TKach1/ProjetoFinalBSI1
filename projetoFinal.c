#include "GameModes.h" //biblioteca para inicializar os modos já feitos pela prof

/* 
                        RESUMO
    O programa funciona com duas matrizes (antiga e atual), sendo a antiga um copia da
    ultima atualização da Atual, sendo usada apenas para verificação para atualizar a Atual.

    Para saber como é feita a verificação ir para void atualizaMat.
*/

typedef struct tab{
    char nomeJogo[TAM]; //o nome do jogo deve ser relativo ao padrao
                        //de inicializacao. Por exemplo, JogoSapo ou JogoBloco
    int ciclosVida; // Define quanto cada jogo vai rodar (ciclos)
    int nL,nC; //dimensoes do tabuleiro linhas x colunas
    char **m;   //Atenção! Essa matriz terá que ser alocada dinamicamente
                //para que a funcao que inicializa possa funcionar
}Tab;

void desalocaMatriz(char **m,int nL){ //O NOME JA DIZ MUITA COISA (Libera espaço na RAM + notinha de bom dev)
    for(int i = 0; i<nL; i++){
        free(m[i]);
    }
    free(m);
}
char** alocaMatriz(int nL,int nC){ //O NOME JA DIZ MUITA COISA
    char** m;
    m = (char**) malloc (nL * sizeof(char*));
    for(int i= 0;i<nL;i++){
        m[i] = (char*) malloc (nC * sizeof(char));
    }
    return m;
}
void imprimeMatriz(char **mAtual,int nL,int nC){ //O NOME JA DIZ MUITA COISA
    int i,j;
    for(i=0;i<nL;i++){
        for(j=0;j<nC;j++){
            printf("%c",mAtual[i][j]);
        }
        printf("\n");
    }
}

void byebye(char **mat, int nL){ // QUITA DO PROGRAMA
    desalocaMatriz(mat,nL);
    printf("\nSaindo...");
    Sleep(100);
    exit(0);
}
void limpaMatriz(char **m, int nL, int nC){ // DEFINE A MATRIZ TODA COM "."
    int i,j;
    for(i=0;i<nL;i++)
     for(j=0;j<nC;j++)
        m[i][j]=VAZ;
}
void menuInicJogo(Tab *mat){ // MENU INICIAL
    int opcao;
    printf("(1)Bloco\n(2)Blinker\n(3)Sapo\n(4)Glider\n(5)LWSS\n(0)Sair\nEntre com a opcao: ");
    scanf("%d",&opcao);

    Tab m = *mat;
    switch(opcao)
    {
        case 1:   inic(m.m,m.nL,m.nC, "Bloco"); strcpy(m.nomeJogo, "Bloco"); break;
        case 2:   inic(m.m,m.nL,m.nC, "Blinker"); strcpy(m.nomeJogo, "Blinker"); break;
        case 3:   inic(m.m,m.nL,m.nC, "Sapo"); strcpy(m.nomeJogo, "Sapo"); break;
        case 4:   inic(m.m,m.nL,m.nC, "Glider"); strcpy(m.nomeJogo, "Glider"); break;
        case 5:   inic(m.m,m.nL,m.nC, "LWSS"); strcpy(m.nomeJogo, "LWSS"); break;
        default: byebye(m.m,m.nL); break; // CASO QQL COISA FOR DIGITADA SEM SER 1,2,3,4,5 ELE SAI DO PROGRAMA
    }
        *mat = m;
        printf("%s \n", m.nomeJogo);
        imprimeMatriz(m.m,m.nL,m.nC);

        printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo..."); while(getchar()!='\n'); getchar();

}
void copiaMatriz(char **mAnt,char **mAtual,int nL,int nC){ // COPIA A MATRIZ NOVA PARA A ANTIGA
    int i,j;
    for(i=0;i<nL;i++)
        for(j=0;j<nC;j++)
            mAnt[i][j]=mAtual[i][j];
}
void atualizaMat(char **mAtual,char **mAnt,int nL,int nC){ //FUNCAO MAIS IMPORTANTE
    int l, c;
    int vizinhos = 0;
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

                l = Linhas
                c = Colunas

                mAnt = matriz apenas para verificação

                mAtual = matriz que será atualizada para impressão e para salvar em arquivo
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

void jogaJogoVida(Tab *mat)
{
  char **mAnt;
  int c;
  Tab m = *mat;
  //imprimindo na tela a matriz inicial
  system(CLEAN);
  imprimeMatriz(m.m,m.nL,m.nC);
  mAnt = alocaMatriz(m.nL,m.nC);

  for(c=1;c<=m.ciclosVida;c++) // roda até quandos ciclos o usuario quiser.
  {
        copiaMatriz(mAnt,m.m,m.nL,m.nC);
        atualizaMat(m.m,mAnt,m.nL,m.nC); 
        system(CLEAN);
        imprimeMatriz(m.m,m.nL,m.nC);
        Sleep((int)1000/m.ciclosVida);
  }
  desalocaMatriz(mAnt,m.nL);
}

int main()
{
    int j;
    Tab *mat;

    printf("\nDigite quantos jogos você quer jogar: ");
    scanf("%d", &j);

    mat = ( Tab *) malloc ( j * sizeof ( Tab ));

    for(int i = 0; i < j; i++){
        printf("\nDigite o Tamanho da Matriz (Largura): ");
        scanf("%d", &mat[i].nC);
        printf("\nDigite o Tamanho da Matriz (Altura): ");
        scanf("%d", &mat[i].nL);
        printf("\nDigite o Numero de Ciclos: ");
        scanf("%d", &mat[i].ciclosVida);
        mat[i].m = alocaMatriz(mat[i].nL, mat[i].nL);
        menuInicJogo(&mat[i]);
        jogaJogoVida(&mat[i]); 
        printf("O jogo anterior foi: %s \n", mat[i].nomeJogo);
    }

}

////////////////////////////////////////////////////////
//inicios///////////////////////////////////////////////
////////////////////////////////////////////////////////

void inic(char **m, int nL, int nC, char *modo)
{   
    int i,j, xInic=nL/2, yInic=nC/2, size, l = 1, lmax = 0, maxc = 0;
    char chr;
    FILE *fp;
    char **padrao;
    char txt[] = ".txt";
    char mod[TAM];

    strcpy(mod, modo);
    strcat(mod, txt);
    fp = fopen(mod, "r");

    if(fp == NULL){
        printf("Error opening");
        exit(1);
    }

    chr = getc(fp);

    while (chr != EOF)
    {   
        if (chr == '\n'){
            l++;
        }
        if(((int)chr)-48 > maxc && chr != ',' && chr != '\n')
            maxc = ((int)chr)-48;
        chr = getc(fp);
    }
    padrao = alocaMatriz(l, maxc);
    limpaMatriz(padrao,l,maxc);
    lmax = l;
    l = 0;
    rewind(fp);
    chr = getc(fp);
    while (chr != EOF)
    {
        if (chr == '\n'){
            l++;
        }
        if (chr != ',' && chr != '\n'){
            padrao[l][((int)chr)-49] = ORG;
        }
        chr = getc(fp);
    }

    limpaMatriz(m,nL,nC);

    for(i=0;i<l+1;i++){
        for(j=0;j<maxc;j++){
            m[xInic+i][yInic+j]=padrao[i][j];
        }
    }
    fclose(fp);
}