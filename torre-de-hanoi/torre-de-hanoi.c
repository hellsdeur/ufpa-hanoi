#include <stdio.h>
#include <math.h>
#include <stdlib.h>



// Objetivo -> Mudar o esquema de matrizes

int x, i, j;

// Cria e zera a torre
int* criarTorre(int n){ // cria as tres torres em um array de 60 posi��es
    int i, c = 20 - n;
    static int torre[60];

    for (i = 0; i < 60; i++){ // coloca 0s nas 60 posi��es
        torre[i] = 0;
    }

    for (i = 19; i >= c; i--){ // coloca os discos de 1 a n na primeira torre
        torre[i] = n;
        n--;
    }

    return torre;
}

// Imprime a torre
void printTorre(int* t, int n){
    int i;
    int c = 20 - n;

    printf("\n\n");
    for (i = c; i < 20; i++){
        printf("| %d |   | %d |   | %d |\n", t[i], t[i + 20], t[i + 40]);
    }
    printf("\n\n");
}

// Verifica se a torre foi zerada
int verifTorreZerada(int* t, int o, int x){
    if (o == 1){
        if (t[19] != 0){ // se o �ltimo disco for n�o-nulo, ent�o a torre � n�o-nula
            return 1;
        }
        else{ // se n�o, ent�o a torre � nula
            return 0;
        }
    }
    else if (o == 2){
        if (t[39] != 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if (o == 3){
        if (t[59] != 0){
            return 1;
        }
        else{
            return 0;
        }
    }
}

// Verifica se o disco existe na torre
int verifDisco(int* t, int o, int pec){ // verifica a presen�a do disco na torre e se ele pode se mexer
    int i;
    if (o == 1){
        for(i = 0; i < 20; i++){
                if (t[i] == pec){
                    if (t[i-1] == 0 || i == 0){ // se a posi��o anterior aquele disco for 0, ou se o disco est� no topo da torre, ele pode se mexer
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
        }
        if (t[i] != pec){
            return 0;
        }
    }
    else if (o == 2){
        for(i = 20; i < 40; i++){
                if (t[i] == pec){
                    if (t[i-1] == 0 || i == 0){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
        }
        if (t[i] != pec){
            return 0;
        }
    }
    else if (o == 3){
        for(i = 40; i < 60; i++){
                if (t[i] == pec){
                    if (t[i-1] == 0 || i == 0){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
        }
        if (t[i] != pec){
            return 0;
        }
    }
}

// Verifica se a transferência é valida
int verifTransf(int*t, int d, int p){
    int i;
    if (d == 1){
        for (i = 19; i >= 0; i--){ // come�ando de baixo para cima na torre
            if (t[i - 1] == 0){ // se a pr�xima posi��o estiver vazia e...
                if (t[i] > p || t[i] == p || t[i] == 0){ // ... se o disco do topo for maior que o disco atual...
                    return 1; // ... � poss�vel transferir
                }
                else{
                    return 0;
                }
            }
        }
    }
    else if (d == 2){
        for (i = 39; i >= 20; i--){
            if (t[i - 1] == 0){
                if (t[i] > p || t[i] == p || t[i] == 0){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
    }
    else if (d == 3){
        for (i = 59; i >= 40; i--){
            if (t[i - 1] == 0){
                if (t[i] > p || t[i] == p || t[i] == 0){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
    }
}

// moverDiscos(torre, destino, peça, origem)
int moverDiscos(int *t, int d, int p, int o){
    int i;

    // ##   Origem
    // Se for da primeira torre
    if (o == 1){
        for (i = 0; i < 20; i++){ // para eliminar o disco da torre de origem, basta zerar
            if (t[i] == p){
                t[i] = 0;
            }
        }
    }
    // Se for da segunda torre
    else if (o == 2){
        for (i = 20; i < 40; i++){
            if (t[i] == p){
                t[i] = 0;
            }
        }
    }
    // Se for da terceira torre
    else if (o == 3){
        for (i = 40; i < 60; i++){
            if (t[i] == p){
                t[i] = 0;
            }
        }
    }

    // ##   Destino
    // Se for para primeira torre
    if (d == 1){
        for (i = 19; i >= 0; i--){ // come�ando de baixo para cima na torre
            if (t[i] == 0){ // se a posi��o tiver vazia, o disco � transferido e o loop � interrompido
                t[i] = p;
                break;
            }
        }
    }
    // Se for para segunda torre
    else if (d == 2){
        for (i = 39; i >= 20; i--){
            if (t[i] == 0){
                t[i] = p;
                break;
            }
        }
    }
    // Se for para a terceira torre
    else if (d == 3){
        for (i = 59; i >= 40; i--){
            if (t[i] == 0){
                t[i] = p;
                break;
            }
        }
    }

    // Retorna
    return t;
}

// Vê se a torre atual no jogo equivale à resposta. Se for o jogo termina
int verifResposta(int* t, int n){
    int i;
    int c;
    int r[20]; // array resposta de 20 elementos
    int k = 20 - n; // posi��o k do array, onde est� o valor 1

    for (i = 0; i < 20; i++){ // enchendo a matriz de zeros
        r[i] = 0;
    }

    for (i = 19; i >= k; i--){ // coloca os valores de 1 a n, a partir da posi��o k
        r[i] = n;
        n--;
    }

    for (i = 0; i < 20; i++){ // sempre que um elemento do array resposta for igual ao do array da torre 3, um contador � incrementado
        if (r[i] == t[i + 40]){
            c++;
        }
    }
    if (c == 20){ // se, para as 20 posi��es do array 3, tivermos 20 elementos iguais ao vetor resposta, ent�o o jogador vence
        return 1;
    }
    else{
        return 0; // caso contr�rio, continua jogando
    }
}

// Move o disco do topo da torre de origem para o topo da torre de destino
// move(letra_de_origem, letra_de_destino, torre_principal, )
void move(char ori, char des, int* t, int m){
    int i, j;
    int transf;
    int c = 20 - m;

    if (ori == 'A' && des == 'B'){
        for (i = 19; i >= 0; i--){
            if (t[i - 1] == 0){
                transf = t[i];
                t[i] = 0;
                break;
            }
        }
        for (j = 39; j >= 20; j--){
            if (t[j] == 0){
                t[j] = transf;
                break;
            }
        }
    }
    else if (ori == 'A' && des == 'C'){
        for (i = 19; i >= 0; i--){
            if (t[i - 1] == 0){
                transf = t[i];
                t[i] = 0;
                break;
            }
        }
        for (j = 59; j >= 40; j--){
            if (t[j] == 0){
                t[j] = transf;
                break;
            }
        }
    }
    else if (ori == 'B' && des == 'A'){
        for (i = 39; i >= 20; i--){
            if (t[i - 1] == 0){
                transf = t[i];
                t[i] = 0;
                break;
            }
        }
        for (j = 19; j >= 0; j--){
            if (t[j] == 0){
                t[j] = transf;
                break;
            }
        }
    }
    else if (ori == 'B' && des == 'C'){
        for (i = 39; i >= 20; i--){
            if (t[i - 1] == 0){
                transf = t[i];
                t[i] = 0;
                break;
            }
        }
        for (j = 59; j >= 40; j--){
            if (t[j] == 0){
                t[j] = transf;
                break;
            }
        }
    }
    else if (ori == 'C' && des == 'A'){
        for (i = 59; i >= 40; i--){
            if (t[i - 1] == 0){
                transf = t[i];
                t[i] = 0;
                break;
            }
        }
        for (j = 19; j >= 0; j--){
            if (t[j] == 0){
                t[j] = transf;
                break;
            }
        }
    }
    else if (ori == 'C' && des == 'B'){
        for (i = 59; i >= 40; i--){
            if (t[i - 1] == 0){
                transf = t[i];
                t[i] = 0;
                break;
            }
        }
        for (j = 39; j >= 20; j--){
            if (t[j] == 0){
                t[j] = transf;
                break;
            }
        }
    }

    printf("-----------------------------\n\n");
    for (i = c; i < 20; i++){
        printf("| %d |   | %d |   | %d |\n", t[i], t[i + 20], t[i + 40]);
    }
    printf("\n\n");
}

// Função que resolve o jogo sozinha a partir da recursão
void auto_hanoi(int n, int m, char ori, char des, char aux, int* tor){

    // Quando o disco 1 for movido para a torre 3, o jogo está quase terminando
    if (n == 1){
        move(ori, des, tor, m);
        return;
    }
    auto_hanoi(n-1, m, ori, aux, des, tor); // passo recursivo que usa a torre auxiliar como destino e a de destino como auxiliar
    move(ori, des, tor, m); // move o ultimo disco da torre de origem para a de destino
    auto_hanoi(n-1, m, aux, des, ori, tor); // recurs�o que usa a auxiliar como origem, e a origem como auxiliar
}

void hanoiInstructions()
{
    printf("\n\nA torre de Hanoi eh um jogo onde existem tres torres e n discos.\n");
                printf("O objetivo do jogo eh mover todos os discos da primeira para a\n");
                printf("ultima torre, utilizando a restante como torre auxiliar, seguindo\n");
                printf("as seguintes regras:\n");
                printf("   1. Apenas um disco pode ser movido de cada vez.\n");
                printf("   2. Cada movimento consiste de tirar o disco do topo\n");
                printf("      de uma das torres e posiciona-lo no topo de outra\n");
                printf("   3. Nenhum disco pode ser posicionado acima de um disco menor.\n\n");

}

void hanoiSolve()
{
    int i, c;       // Indexes
    int numDiscos;  // Número de discos

    printf("Digite a quantidade de discos: ");
    scanf("%d", &numDiscos);

    // O limite de discos é 20
    while(numDiscos <= 0 || numDiscos > 20){
        printf("ALERTA: Limite de discos = 20\n\n");
        printf("Digite a quantidade de discos: ");
        scanf("%d", &numDiscos);
    }

    int m = numDiscos;
    int c = 20 - numDiscos;
    int* torre_auto = criarTorre(numDiscos);

    printf("\n\n");
    printf("-----------------------------\n\n");
    for (i = c; i < 20; i++){
        printf("| %d |   | %d |   | %d |\n", torre_auto[i], torre_auto[i + 20], torre_auto[i + 40]);
    }
    printf("\n\n");

    auto_hanoi(numDiscos, m, 'A', 'C', 'B', torre_auto);

    printf("Torres de hanoi com %d discos, completados em %.lf rodadas.\n", numDiscos, pow(2, numDiscos) - 1);
    printf("------------------------------\n\n");
}

// Função que permite o usuário fazer as jogadas da torre de Hanoi
void hanoiPlay()
{
    int numDiscos;                                    // Variável que guarda a quantidade de discos
    int torreOrigem, torreDestino, torreDisco;        // Variáveis de torres     
    int verificaDisco, verificaTorresZeradas;         // Variáveis verificadoras
    int verificaTransferencia, verificaResposta = 0;  // Variáveis verificadoras
    int rodadas = 0;                                  // Contador de rodadas
    
    printf("Digite a quantidade de discos: ");
    scanf("%d", &numDiscos);

    // A quantidade de discos deve ser menor do que 20
    while(numDiscos <= 0 || numDiscos > 20){
        printf("ALERTA: Limite de discos = 20\n\n");
        printf("Digite a quantidade de discos: ");
        scanf("%d", &numDiscos);
    }

    int* torrePrincipal = criarTorre(numDiscos); // Ponteiro que guarda o array da torre

    printTorre(torrePrincipal, numDiscos);

    // Enquanto a verificadora de resposta retornar 0, o jogador continua jogando
    while(verificaResposta == 0){
        rodadas++;

        printf("-----------------------------\n\n");
        printf("Rodada %d\n\n", rodadas);

        printf("Qual a torre de origem? ");
        scanf("%d", &torreOrigem);

        verificaTorresZeradas = verifTorreZerada(torrePrincipal, torreOrigem, numDiscos); // verificar se a torre possui discos

        while(torreOrigem < 1 || torreOrigem > 3 || verificaTorresZeradas == 0){
            printf("ALERTA: Escolha uma torre nao-nula: {1, 2, 3}\n");

            printf("Qual a torre de origem? ");
            scanf("%d", &torreOrigem);
                        
            verificaTorresZeradas = verifTorreZerada(torrePrincipal, torreOrigem, numDiscos);
        }

        printf("Qual o disco a mover? "); // escolher o disco a mover
        scanf("%d", &torreDisco);
    
        verificaDisco = verifDisco(torrePrincipal, torreOrigem, torreDisco); // verificar se o disco est� na torre e no topo
                    
        while(torreDisco < 1 || torreDisco > numDiscos || verificaDisco == 0){
            printf("ALERTA: Disco invalido\n");
            printf("Qual o disco a mover? ");
            scanf("%d", &torreDisco);
            verificaDisco = verifDisco(torrePrincipal, torreOrigem, torreDisco);
        }

        printf("Qual a torre de destino? "); // usu�rio informa a torre de destino
        scanf("%d", &torreDestino);

        verificaTransferencia = verifTransf(torrePrincipal, torreDestino, torreDisco); // verificar se o disco do topo da torre de destino � maior que o disco que se deseja transferir
        
        while(verificaTransferencia == 0){
            printf("Impossivel colocar disco maior acima de menor\n");
            printf("Qual a torre de destino? ");
            scanf("%d", &torreDestino);
            verificaTransferencia = verifTransf(torrePrincipal, torreDestino, torreDisco);
        }

        torrePrincipal = moverDiscos(torrePrincipal, torreDestino, torreDisco, torreOrigem); // mover disco entre as torres de origem e destino

        printTorre(torrePrincipal, numDiscos);
        verificaResposta = verifResposta(torrePrincipal, numDiscos); // verificar a resposta
    }

    printf("------------------------------\n");
    printf("------------PARABÉNS----------\n");
    printf("------------------------------\n\n");
    printf("Torres de hanoi com %d discos, completados em %d rodadas.\n", numDiscos, rodadas);

    printf("------------------------------\n\n");
}

int main(){

    printf("------------------------------\n");
    printf("--------TORRES DE HANOI-------\n");
    printf("------------------------------\n\n");

    while (1){
        int menuChoice;

        printf("1 - Jogar\n2 - Modo Automatico\n3 - Regras\n4 - Sair\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &menuChoice);

        switch(menuChoice){
            // Opção de Jogar
            case 1:
                hanoiPlay();
                break;
            
            // Resolve sozinho
            case 2:
                hanoiSolve();
                break;

            // Instruções do jogo
            case 3:
                hanoiInstructions();
                break;
            
            // Sair do jogo
            case 4:
                return 0;
                break;
            }

        }

    return 0;
}