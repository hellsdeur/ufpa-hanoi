#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int x, i, j;

int* criarTorre(int n){ // cria as tres torres em um array de 60 posições
    int i, c = 20 - n;
    static int torre[60];

    for (i = 0; i < 60; i++){ // coloca 0s nas 60 posições
        torre[i] = 0;
    }

    for (i = 19; i >= c; i--){ // coloca os discos de 1 a n na primeira torre
        torre[i] = n;
        n--;
    }

    return torre;
}

void printTorre(int* t, int n){
    int i;
    int c = 20 - n;

    printf("\n\n");
    for (i = c; i < 20; i++){
        printf("| %d |   | %d |   | %d |\n", t[i], t[i + 20], t[i + 40]);
    }
    printf("\n\n");
}

int verifTorreZerada(int* t, int o, int x){
    if (o == 1){
        if (t[19] != 0){ // se o último disco for não-nulo, então a torre é não-nula
            return 1;
        }
        else{ // se não, então a torre é nula
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

int verifDisco(int* t, int o, int pec){ // verifica a presença do disco na torre e se ele pode se mexer
    int i;
    if (o == 1){
        for(i = 0; i < 20; i++){
                if (t[i] == pec){
                    if (t[i-1] == 0 || i == 0){ // se a posição anterior aquele disco for 0, ou se o disco está no topo da torre, ele pode se mexer
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

int verifTransf(int*t, int d, int p){
    int i;
    if (d == 1){
        for (i = 19; i >= 0; i--){ // começando de baixo para cima na torre
            if (t[i - 1] == 0){ // se a próxima posição estiver vazia e...
                if (t[i] > p || t[i] == p || t[i] == 0){ // ... se o disco do topo for maior que o disco atual...
                    return 1; // ... é possível transferir
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

int moverDiscos(int *t, int d, int p, int o){
    int i;

    if (o == 1){
        for (i = 0; i < 20; i++){ // para eliminar o disco da torre de origem, basta zerar
            if (t[i] == p){
                t[i] = 0;
            }
        }
    }
    else if (o == 2){
        for (i = 20; i < 40; i++){
            if (t[i] == p){
                t[i] = 0;
            }
        }
    }
    else if (o == 3){
        for (i = 40; i < 60; i++){
            if (t[i] == p){
                t[i] = 0;
            }
        }
    }

    if (d == 1){
        for (i = 19; i >= 0; i--){ // começando de baixo para cima na torre
            if (t[i] == 0){ // se a posição tiver vazia, o disco é transferido e o loop é interrompido
                t[i] = p;
                break;
            }
        }
    }
    else if (d == 2){
        for (i = 39; i >= 20; i--){
            if (t[i] == 0){
                t[i] = p;
                break;
            }
        }
    }
    else if (d == 3){
        for (i = 59; i >= 40; i--){
            if (t[i] == 0){
                t[i] = p;
                break;
            }
        }
    }

    return t;
}

int verifResposta(int* t, int n){ // checar se a torre atual é equivalente a torre da resposta
    int i;
    int c;
    int r[20]; // array resposta de 20 elementos
    int k = 20 - n; // posição k do array, onde está o valor 1

    for (i = 0; i < 20; i++){ // enchendo a matriz de zeros
        r[i] = 0;
    }

    for (i = 19; i >= k; i--){ // coloca os valores de 1 a n, a partir da posição k
        r[i] = n;
        n--;
    }

    for (i = 0; i < 20; i++){ // sempre que um elemento do array resposta for igual ao do array da torre 3, um contador é incrementado
        if (r[i] == t[i + 40]){
            c++;
        }
    }
    if (c == 20){ // se, para as 20 posições do array 3, tivermos 20 elementos iguais ao vetor resposta, então o jogador vence
        return 1;
    }
    else{
        return 0; // caso contrário, continua jogando
    }
}

void move(char ori, char des, int* t, int m){ // movendo o disco do topo da torre de origem para o topo da torre de destino
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

void auto_hanoi(int n, int m, char ori, char des, char aux, int* tor){ // função recursiva que resolve o problema
    if (n == 1){ // caso base, onde o disco 1 eh movido diretamente para a torre 3
        move(ori, des, tor, m);
        return;
    }
    auto_hanoi(n-1, m, ori, aux, des, tor); // passo recursivo que usa a torre auxiliar como destino e a de destino como auxiliar
    move(ori, des, tor, m); // move o ultimo disco da torre de origem para a de destino
    auto_hanoi(n-1, m, aux, des, ori, tor); // recursão que usa a auxiliar como origem, e a origem como auxiliar
}

int main(){
    printf("------------------------------\n");
    printf("--------TORRES DE HANOI-------\n");
    printf("------------------------------\n\n");

    while (1){
        int x; // variável que guarda a quantidade de discos
        int ori, des, pec; // variáveis de torres, ori: torre de origem; des: torre de destino; pec: peça a mexer
        int vd, vtz; // variáveis verificadoras, vd: verifica disco na torre; vtz: verifica torres zeradas
        int vt, vr = 0; // variáveis verificadoras, vt: verifica possib. de transferencia; vr: verifica resposta
        int counter = 0; // contador de rodadas

        int menu;
        printf("1 - Jogar\n2 - Modo Automatico\n3 - Regras\n4 - Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &menu);
        switch(menu){
        case 1:
            printf("Digite a quantidade de discos: ");
            scanf("%d", &x);
            while(x <= 0 || x > 20){
                printf("ALERTA: Limite de discos = 20\n\n");
                printf("Digite a quantidade de discos: ");
                scanf("%d", &x);
            }

            int* torre = criarTorre(x); // ponteiro que guarda o array da torre

            printTorre(torre, x);

            while(vr == 0){ // enquanto a verificadora de resposta retornar 0, o jogador continua jogando
                counter++; // contador de rodadas
                printf("-----------------------------\n\n");
                printf("Rodada %d\n\n", counter);

                printf("Qual a torre de origem? "); // usuário informa a torre de origem
                scanf("%d", &ori);
                vtz = verifTorreZerada(torre, ori, x); // verificar se a torre possui discos
                while(ori < 1 || ori > 3 || vtz == 0){
                    printf("ALERTA: Escolha uma torre nao-nula: {1, 2, 3}\n");
                    printf("Qual a torre de origem? ");
                    scanf("%d", &ori);
                    vtz = verifTorreZerada(torre, ori, x);
                }

                printf("Qual o disco a mover? "); // escolher o disco a mover
                scanf("%d", &pec);
                vd = verifDisco(torre, ori, pec); // verificar se o disco está na torre e no topo
                while(pec < 1 || pec > x || vd == 0){
                    printf("ALERTA: Disco invalido\n");
                    printf("Qual o disco a mover? ");
                    scanf("%d", &pec);
                    vd = verifDisco(torre, ori, pec);
                }

                printf("Qual a torre de destino? "); // usuário informa a torre de destino
                scanf("%d", &des);
                vt = verifTransf(torre, des, pec); // verificar se o disco do topo da torre de destino é maior que o disco que se deseja transferir
                while(vt == 0){
                    printf("Impossivel colocar disco maior acima de menor\n");
                    printf("Qual a torre de destino? ");
                    scanf("%d", &des);
                    vt = verifTransf(torre, des, pec);
                }

                torre = moverDiscos(torre, des, pec, ori); // mover disco entre as torres de origem e destino

                printTorre(torre, x);
                vr = verifResposta(torre, x); // verificar a resposta
            }

            printf("------------------------------\n");
            printf("------------PARABENS----------\n");
            printf("------------------------------\n\n");
            printf("Torres de hanoi com %d discos, completados em %d rodadas.\n", x, counter);
            printf("------------------------------\n\n");
            break;

        case 2:
            printf("Digite a quantidade de discos: ");
            scanf("%d", &x);
            while(x <= 0 || x > 20){
                printf("ALERTA: Limite de discos = 20\n\n");
                printf("Digite a quantidade de discos: ");
                scanf("%d", &x);
            }

            int m = x;
            int c = 20 - x;
            int* torre_auto = criarTorre(x);

            printf("\n\n");
            printf("-----------------------------\n\n");
            for (i = c; i < 20; i++){
                printf("| %d |   | %d |   | %d |\n", torre_auto[i], torre_auto[i + 20], torre_auto[i + 40]);
            }
            printf("\n\n");

            auto_hanoi(x, m, 'A', 'C', 'B', torre_auto);

            printf("Torres de hanoi com %d discos, completados em %.lf rodadas.\n", x, pow(2, x) - 1);
            printf("------------------------------\n\n");
            break;

        case 3:
            printf("\n\nA torre de Hanoi eh um jogo onde existem tres torres e n discos.\n");
            printf("O objetivo do jogo eh mover todos os discos da primeira para a\n");
            printf("ultima torre, utilizando a restante como torre auxiliar, seguindo\n");
            printf("as seguintes regras:\n");
            printf("   1. Apenas um disco pode ser movido de cada vez.\n");
            printf("   2. Cada movimento consiste de tirar o disco do topo\n");
            printf("      de uma das torres e posiciona-lo no topo de outra\n");
            printf("   3. Nenhum disco pode ser posicionado acima de um disco menor.\n\n");
            break;

        case 4:
            exit(1);
            break;
        }
    }

    return 0;
}