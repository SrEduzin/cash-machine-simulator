#include <stdio.h>
#include <stdlib.h>

struct banco
{
    char empresa[20];
    int carteira, notas200, notas100, notas50, notas20, notas10, notas5, notas2;
}b;
void menu();
void criar();
void gerenciar();

//editor de bancos para o caixa eletrônico.

//início
int main(){
    FILE * bank;
    bank = fopen("bancos.txt", "rb");
    if (bank == NULL){
        fclose(bank);
        printf("criando arquivos...\n");
        getchar();
        bank = fopen("bancos.txt", "wb");
        fclose(bank);
    }
    menu();
    return 0;
}
void menu(){
    int op;
    printf("________ESCOLHA UMA ACAO__________\n\n\n");
    printf("1 - CRIAR\n2 - GERENCIAR\n\n0 - sair\n");
    printf("_________________________Digito: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        criar();
        break;
    case 2:
        gerenciar();
        break;
    default:
        exit(1);
        break;
    }
}
void criar(){
    FILE * bank;
    printf("_____________CRIAR BANCO_____________\n");
    printf("digite o nome do banco: ");
    fflush(stdin);
    fgets(b.empresa, sizeof(b.empresa),stdin);
    printf("digite o saldo do banco: ");
    fflush(stdin);
    scanf("%d", &b.carteira);
    printf("digite as notas do banco: \n(notas de 200), (notas de 100), (notas de 50), (notas de 20), (notas de 10), (notas de 5), (notas de 2)\n");
    fflush(stdin);
    scanf("%d%d%d%d%d%d%d", &b.notas200, &b.notas100, &b.notas50, &b.notas20, &b.notas10, &b.notas5, &b.notas2);
    bank = fopen("bancos.txt", "ab+");
    fseek(bank, 0, SEEK_END);
    fwrite(&b, sizeof(struct banco),1,bank);
    fclose(bank);
    printf("\nBanco criado com sucesso!");
}
void gerenciar(){
    int i = 0, op = 0, saldo;
    char nome[20];
    FILE * bank = fopen("bancos.txt", "rw+b");
    while (feof(bank) == 0)
    {
        fseek(bank,i*sizeof(struct banco),SEEK_SET);
        fread(&b,sizeof(struct banco),1,bank);
        if(feof(bank) == 0){
        printf("________CONTA %d_______", i);
        printf("\nBanco: %s\nSaldo: %d\n\n",b.empresa, b.carteira);
        printf("______________Notas de dinheiro_____________");
        printf("\nnotas de 200: %d\tnotas de 100: %d\tnotas de 50: %d\tnotas de 20: %d\nnotas de 10: %d\tnotas de 5: %d\t\tnotas de 2: %d", b.notas200, b.notas100, b.notas50, b.notas20, b.notas10, b.notas5, b.notas2);
        printf("\n_______________________\n");
        }
        i++;
    }
    printf("Digite o id para editar: ");
    fflush(stdin);
    scanf("%d", &op);
    fseek(bank,op*sizeof(struct banco),SEEK_SET);
    fread(&b,sizeof(struct banco),1,bank);
    printf("Mudar %s", &b.empresa);
    fflush(stdin);
    fgets(b.empresa,20,stdin);
    printf("Mudar %s", &b.empresa);
    printf("Mudar saldo de: \"%d\" para: ", b.carteira);
    scanf("%d", &b.carteira);
    printf("Banco editado com sucesso!");
    fseek(bank,op*sizeof(struct banco),SEEK_SET);
    fwrite(&b,sizeof(struct banco),1,bank);
    getchar();
    fclose(bank);
    menu();
}
