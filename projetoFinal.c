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

void startRaid(char **mat,char **mAnt,int nL,int nC){ //Comeca a invasão
    if(nL >= 20 && nC >= 20){ //tamanho minimo de matriz para ter invasores
        int xInic = nL/1.5f, yInic = nC/1.5f;
        char padrao[5][5]={{ORG,ORG,ORG,VAZ,ORG},{ORG,VAZ,VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ ,ORG,ORG},{VAZ,ORG,ORG,VAZ,ORG},{ORG,VAZ,ORG,VAZ,ORG}}; // Paul Callahan's 5×5 infinite growth pattern
        for(int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                mat[xInic+i][yInic+j]=padrao[i][j];
    }else{
        printf("Não foi possivel inicializar inimigos (tamanhos de matrizes muito pequenos)");
        Sleep(500);
    }
}

void jogaJogoVida(Tab *mat)
{
  char **mAnt;
  int c;
  Tab m = *mat;
  system(CLEAN);
  imprimeMatriz(m.m,m.nL,m.nC);  //imprimindo na tela a matriz inicial
  mAnt = alocaMatriz(m.nL,m.nC);

  for(c=1;c<=m.ciclosVida;c++) // roda até quandos ciclos o usuario quiser.
  {
        copiaMatriz(mAnt,m.m,m.nL,m.nC);
        atualizaMat(m.m,mAnt,m.nL,m.nC); 
        system(CLEAN);
        imprimeMatriz(m.m,m.nL,m.nC);
        Sleep((int)1000/m.ciclosVida);
        if(c == 20)
            startRaid(m.m,mAnt,m.nL,m.nC);
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

void inic(char **m, int nL, int nC, char *modo) //LER ARQUIVOS
{   
    int i,j, xInic=nL/2, yInic=nC/2, size, l = 1, lmax = 0, maxc = 0;
    char chr;
    FILE *fp; //INICIA UM TIPO DE ARQUIVO
    char **padrao;
    char txt[] = ".txt";
    char mod[TAM];

    strcpy(mod, modo); //MUDA A VARIAVEL mod PARA O NOME SELECIONADO NA FUNÇÃO QUE A CHAMA
    strcat(mod, txt); //ADICIONA O .TXT AO FINAL DA SENTENÇA
    fp = fopen(mod, "r"); //ABRE O ARQUIVO

    if(fp == NULL){ //CASO NAO CONSIGA ABRIR, DA ERRO E ENCERRA
        printf("Error opening");
        exit(1);
    }

    chr = getc(fp); //PEGA AO PRIMEIRO CARACTERE 

    while (chr != EOF) //RODA ATE EOF (End Of File - Final do Arquivo) - este while serve para pegar o tamanho da matriz de dentro do arquivo
    {   
        if (chr == '\n'){ //QUANDO FOR QUEBRA DE LINHAS
            l++; //CONTA LINHAS
        }
        if(((int)chr)-48 > maxc && chr != ',' && chr != '\n')//COMPARA PARA VER O TAMANHO DA MATRIZ HORIZONTALMENTE
            maxc = ((int)chr)-48;
        chr = getc(fp); //PROX CARACTERE
    }
    padrao = alocaMatriz(l, maxc); //ALOCA MATRIZ DE ACORDO COM O TAMANHO
    limpaMatriz(padrao,l,maxc);
    lmax = l;
    l = 0;
    rewind(fp); //VOLTA AO INICIO DO ARQUIVO
    chr = getc(fp); //PEGA O PRIMEIRO CARACTERE
    while (chr != EOF) //RODA ATE EOF (End Of File - Final do Arquivo)
    {
        if (chr == '\n'){ //QUANDO FOR QUEBRA DE LINHAS
            l++; //CONTA LINHAS
        }
        if (chr != ',' && chr != '\n'){
            padrao[l][((int)chr)-49] = ORG; //INSERE NA VARIAVEL PADRAO O QUE O ARQUIVO CARREGA CONSIGO
        }
        chr = getc(fp); //PROX CARACTERE
    }

    limpaMatriz(m,nL,nC);

    for(i=0;i<l+1;i++){
        for(j=0;j<maxc;j++){
            m[xInic+i][yInic+j]=padrao[i][j]; //INSERE A VARIAVEL PADRAP NA NOSSA MATRIZ PRINCIPAL
        }
    }
    fclose(fp); //Fecha arquivo
}