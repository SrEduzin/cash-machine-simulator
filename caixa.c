#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct banco
{
    char empresa[20];
    int cateira, notas200, notas100, notas50, notas20, notas10, notas5, notas2;
} b;
struct conta
{
    char nome[40], numeroC[16], bconta[20], cpf[13];
    int saldo, senha, dia, mes, ano;

} pessoa;

void menu();
void cadastrar();
void login();
void opcoes(FILE *dados, int i);
void sacar(FILE *dados, int i);
void depositar(FILE *dados, int i);
void transferir(FILE *dados, int i);
void listadebancos(FILE *bancos);
int comp(char comp1[16], char comp2[16]);
int verificarbanco(FILE *bank, FILE *dados);

int main(void)
{
    FILE *dados = fopen("contas.txt", "rb");
    if (dados == NULL)
    {
        fclose(dados);
        printf("criando arquivos...\n");
        getchar();
        FILE *dados = fopen("contas.txt", "wb");
    }
    fclose(dados);
    menu();
    return 0;
}
void menu()
{
    int op;
    do
    {
        //system("cls");
        printf("\n_____________BEM-VINDO AO CAIXA ELETRONICO!______________\n\n");
        printf("\n1 - CADASTRAR\n2 - ENTRAR\n\n\n\n0 - ENCERRRAR\n");
        printf("______________________________________Digito: ");
        fflush(stdin);
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            cadastrar();
            break;

        case 2:
            login();
            break;
        case 0:
            exit(1);
            break;
        default:
            fprintf(stderr, "Digite um comando valido!");
            getchar();
        }
    } while (op != 0);
}
void cadastrar()
{
    int eb, i;
    char nome[40], bconta[20], op, numerocartao[16], cpf[13];
    int saldo, senha, dia, mes, ano;
    do
    {
        FILE *dados;
        FILE *bancos;
        system("cls");
        printf("_______________CADASTRO_____________\n");
        printf("Nome completo: \n");
        fflush(stdin);
        getchar();
        fgets(nome, sizeof(nome), stdin);
        printf("-------------------------------------\n");
        dados = fopen("contas.txt", "rwb");
        do
        {
            i = 0;
            printf("CPF: \n");
            fflush(stdin);
            scanf("%s", &cpf);
            while (feof(dados) == 0)
            {
                fseek(dados, i * sizeof(struct conta), SEEK_SET);
                fread(&pessoa, sizeof(struct conta), 1, dados);
                if (strcmp(cpf, pessoa.cpf) == 0)
                {
                    printf("CPF invalido!\n");
                    break;
                }
                i++;
            }
        } while (strcmp(pessoa.cpf, cpf) == 0);
        fclose(dados);
        printf("-------------------------------------\n");
        printf("Data de Nascimento: (dd mm aaaa)\n");
        fflush(stdin);
        scanf("%d%d%d", &dia, &mes, &ano);
        printf("-------------------------------------\n");
        printf("Bancos:\n");
        listadebancos(bancos);
        printf("Escolha um banco pelo numero:\n _____________Digito: ");
        fflush(stdin);
        scanf("%d", &eb);
        eb--;
        bancos = fopen("bancos.txt", "rb");
        fseek(bancos, eb * sizeof(struct banco), SEEK_SET);
        fread(&b, sizeof(struct banco), 1, bancos);
        strcpy(bconta, b.empresa);
        printf("Seu Banco: %s\n", bconta);
        fclose(bancos);
        printf("-------------------------------------\n");
        dados = fopen("contas.txt", "rwb");
        do
        {
            i = 0;
            printf("Numero do Cartao: \n");
            fflush(stdin);
            scanf("%s", &numerocartao);
            while (feof(dados) == 0)
            {
                fseek(dados, i * sizeof(struct conta), SEEK_SET);
                fread(&pessoa, sizeof(struct conta), 1, dados);
                if (strcmp(numerocartao, pessoa.numeroC) == 0)
                {
                    printf("Esse cartao ja existe!\n");
                    break;
                }
                i++;
            }
        } while (strcmp(numerocartao, pessoa.numeroC) == 0);
        fclose(dados);

        printf("-------------------------------------\n");
        printf("Digite uma senha: (apenas numeros)\n");
        fflush(stdin);
        scanf("%d", &senha);
        printf("-------------------------------------\n");
        printf("Tem certeza desse cadastro? (S/n)\n");
        fflush(stdin);
        scanf("%c", &op);
        printf("-------------------------------------\n");
        if (op == 'n')
            menu();
        else
            dados = fopen("contas.txt", "ab+");
        strcpy(pessoa.nome, nome);
        printf("%s", pessoa.nome);
        strcpy(pessoa.cpf, cpf);
        pessoa.dia = dia;
        pessoa.mes = mes;
        pessoa.ano = ano;
        strcpy(pessoa.numeroC, numerocartao);
        strcpy(pessoa.bconta, bconta);
        pessoa.senha = senha;
        pessoa.saldo = 0;
        fseek(dados, 0, SEEK_END);
        fwrite(&pessoa, sizeof(struct conta), 1, dados);
        fclose(dados);
        menu();
    } while (op != 1);
}
void login()
{
    system("clear");
    char num[16], op, op2;
    int i = 0, senhaC;
    do
    {
        i = 0;
        FILE *dados = fopen("contas.txt", "rw+b");
        printf("----------LOGIN----------\n");
        printf("Digite o numero do cartao: \n");
        fflush(stdin);
        scanf("%s", &num);
        while (feof(dados) == 0)
        {
            fseek(dados, i * sizeof(struct conta), SEEK_SET);
            fread(&pessoa, sizeof(struct conta), 1, dados);
            if (strcmp(pessoa.numeroC, num) == 0)
            {
                do
                {
                    printf("\nUSUARIO: %s\nSENHA: ", pessoa.nome);
                    fflush(stdin);
                    scanf("%d", &senhaC);
                    if (senhaC == pessoa.senha)
                    {
                        printf("\nentrando...");

                        opcoes(dados, i);
                    }
                    printf("\nsenha incorreta! Tentar novamente? (S/n)");
                    fflush(stdin);
                    scanf("%c", &op2);
                    if (op2 == 'n')
                    {
                        fclose(dados);
                        menu();
                    }
                } while (op2 != 'n');
            }
            i++;
        }
        fclose(dados);
        printf("Usuario nao encontrado!\nDeseja tentar outro? (S/n)\n");
        fflush(stdin);
        getchar();
        scanf("%c", &op);
        if (op == 'n')
            menu();
    } while (op != 'n');
}
void opcoes(FILE *dados, int i)
{
    system("clear");
    int op;
    printf("_______________________________SELECIONE A OPCAO DESEJADA_____________________________\n");
    printf("SALDO: %d R$\t\t\t\t\t\t\tNOME: %s", pessoa.saldo, pessoa.nome);
    printf("BANCO: %s", pessoa.bconta);
    printf("CPF: %s", pessoa.cpf);
    printf("\t\t\t\t\t\tNascimento: %2d/%2d/%4d\n", pessoa.dia, pessoa.mes, pessoa.ano);
    printf("\n\n1 - SACAR\n2 - DEPOSITAR\n3 - TRANSFERIR\n\n0 - SAIR\n");
    printf("______________________________________Digito: ");
    fflush(stdin);
    scanf("%d", &op);
    switch (op)
    {
    case 0:
        fclose(dados);
        menu();
        break;
    case 1:
        sacar(dados, i);
        break;
    case 2:
        depositar(dados, i);
        break;
    case 3:
        transferir(dados, i);
        break;

    default:
        printf("digite uma acao valida!");
        break;
    }
}
void sacar(FILE *dados, int i)
{
    system("clear");
    int valor, op, cb;
    char R;
    do
    {
        FILE *bank = fopen("bancos.txt", "rw+b");
        cb = verificarbanco(bank, dados);
        printf("--------------------SACAR--------------------\n");
        printf("SALDO: %d \t\t\tNOME: %s\n\n", pessoa.saldo, pessoa.nome);
        printf("\nquanto deseja sacar?:");
        scanf("%d", &valor);
        printf("\ntem certeza dessa transacao?(S/n)\n valor: %i\n", valor);
        fflush(stdin); // ignora lixo do buffer
        R = getchar();
        if (R == 'n')
            printf("cancelando transacao...");
        else
        {
            if (pessoa.saldo >= valor)
            {
                if (b.cateira >= valor)
                {
                    pessoa.saldo = pessoa.saldo - valor;
                    fseek(bank, cb * sizeof(struct banco), SEEK_SET);
                    fread(&b, sizeof(struct banco), 1, bank);
                    b.cateira = b.cateira + valor;
                    fseek(bank, cb * sizeof(struct banco), SEEK_SET);
                    fwrite(&b, sizeof(struct banco), 1, bank);
                    fseek(dados, i * sizeof(struct conta), SEEK_SET);
                    fwrite(&pessoa, sizeof(struct conta), 1, dados);
                    printf("TRANSACAO CONLUIDA\nretire o dinheiro...");
                    fclose(bank);
                    fflush(stdin);
                    getchar();
                    opcoes(dados, i);
                }
                else
                {
                    printf("Esse banco ta sem dinheiro KKKKK");
                    fclose(bank);
                    opcoes(dados, i);
                }
            }
            else
            {
                printf("Voce nao tem saldo suficiente para essa transacao\n");
                printf("Deseja colocar outro valor? (1 - sim, 0 - nao)\n");
                fflush(stdin);
                scanf("%d", &op);
            }
        }
    } while (op != 0);
    opcoes(dados, i);
}
void depositar(FILE *dados, int i)
{
    system("clear");
    int valor, op, cb;
    char R;
    do
    {
        FILE *bank = fopen("bancos.txt", "rw+b");
        cb = verificarbanco(bank, dados);
        printf("--------------------DEPOSITAR--------------------\n");
        printf("SALDO: %d \t\t\tNOME: %s\n\n", pessoa.saldo, pessoa.nome);
        printf("\nquanto deseja depositar?:");
        scanf("%d", &valor);
        printf("\nVoce quer depositar %d R$?(S/n)\n", valor);
        fflush(stdin); // ignora lixo do buffer
        R = getchar();
        if (R == 'n')
        {
            printf("cancelando deposito...");
            opcoes(dados, i);
        }
        else
        {
            if (b.cateira >= valor)
            {
                pessoa.saldo = pessoa.saldo + valor;
                fseek(bank, cb * sizeof(struct banco), SEEK_SET);
                fread(&b, sizeof(struct banco), 1, bank);
                b.cateira = b.cateira - valor;
                fseek(bank, cb * sizeof(struct banco), SEEK_SET);
                fwrite(&b, sizeof(struct banco), 1, bank);
                fseek(dados, i * sizeof(struct conta), SEEK_SET);
                fwrite(&pessoa, sizeof(struct conta), 1, dados);
                printf("DEPOSITO CONCLUIDO!\nfoi depositado %d R$ em sua conta.\n", valor);
                fclose(bank);
                fflush(stdin);
                getchar();
                opcoes(dados, i);
            }
            else
            {
                printf("Esse banco ta sem dinheiro KKKKK");
                fclose(bank);
                opcoes(dados, i);
            }
        }
    } while (1);
}
void transferir(FILE *dados, int i)
{
    int end = 0, t = 0, valor;
    char num[16], r, op;
    do
    {
        system("clear");
        fseek(dados, i * sizeof(struct conta), SEEK_SET);
        fread(&pessoa, sizeof(struct conta), 1, dados);
        printf("_____________TRANSFERIR____________\n");
        printf("Qual o valor desejado? ");
        fflush(stdin);
        scanf("%d", &valor);
        printf("Digite o numero do cartao para Transferir: ");
        fflush(stdin);
        scanf("%s", &num);
        if (pessoa.saldo >= valor)
        {
            while (feof(dados) == 0)
            {
                fseek(dados, t * sizeof(struct conta), SEEK_SET);
                fread(&pessoa, sizeof(struct conta), 1, dados);
                if (strcmp(pessoa.numeroC, num) == 0)
                {
                    printf("Usuario: %s\n", pessoa.nome);
                    pessoa.saldo = pessoa.saldo + valor;
                    fseek(dados, t * sizeof(struct conta), SEEK_SET);
                    fwrite(&pessoa, sizeof(struct conta), 1, dados);
                    fseek(dados, i * sizeof(struct conta), SEEK_SET);
                    fread(&pessoa, sizeof(struct conta), 1, dados);
                    pessoa.saldo = pessoa.saldo - valor;
                    fseek(dados, i * sizeof(struct conta), SEEK_SET);
                    fwrite(&pessoa, sizeof(struct conta), 1, dados);
                    printf("__________TRANSACAO CONCLUIDA!___________\n");
                    fflush(stdin);
                    getchar();
                    opcoes(dados, i);
                }
                t++;
            }
            printf("Usuario nao encontrado!, deseja procurar de novo? (S/n)\n");
            fflush(stdin);
            scanf("%c", &op);
            if (op == 'n')
                opcoes(dados, i);
            else
                transferir(dados, i);
        }
        else
        {
            printf("Voce nao tem saldo suficiente, deseja digitar outro valor? (S/n)\n");
            fflush(stdin);
            scanf("%c", &r);
            if (r == 'n')
                opcoes(dados, i);
        }
    } while (r != 'n');
}

void listadebancos(FILE *bancos)
{
    int i = 0;
    bancos = fopen("bancos.txt", "rb+");
    fseek(bancos, i * sizeof(struct banco), SEEK_SET);
    while (fread(&b, sizeof(struct banco), 1, bancos))
    {
        printf("%i - %s\n", i + 1, b.empresa);
        i++;
    }
    fclose(bancos);
}

int comp(char comp1[16], char comp2[16])
{
    int i = 0;
    while (i <= sizeof(comp1[16]))
    {
        if (comp1[i] != comp2[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}
int verificarbanco(FILE *bank, FILE *dados)
{
    int i = 0;
    while (feof(bank) == 0)
    {
        fseek(bank, i * sizeof(struct banco), SEEK_SET);
        fread(&b, sizeof(struct banco), 1, bank);
        if (strstr(pessoa.bconta, b.empresa))
        {
            return i;
        }
        i++;
    }
}