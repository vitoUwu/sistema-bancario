#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define CPF_MASK "XXX.XXX.XXX-XX"

typedef struct
{
    char nome[50];
    char cpf[11];
    int setor;
} Atendimento;

char *number_to_setor(int number)
{
    switch (number)
    {
    case 1:
        return "1 - Abertura de Conta";
    case 2:
        return "2 - Caixa";
    case 3:
        return "3 - Gerente Pessoa Física";
    case 4:
        return "4 - Gerente Pessoa Jurídica";
    default:
        return "X - Setor inválido";
    }
}

char *format_cpf(char *cpf)
{
    char *formatted_cpf = malloc(sizeof(char) * 15);
    int i = 0;
    int j = 0;
    while (CPF_MASK[i] != '\0')
    {
        if (CPF_MASK[i] == 'X')
        {
            formatted_cpf[i] = cpf[j];
            j++;
        }
        else
        {
            formatted_cpf[i] = CPF_MASK[i];
        }
        i++;
    }
    return formatted_cpf;
}

void print_atendimento(Atendimento *atendimento)
{
    printf("Nome: %s\n", atendimento->nome);
    printf("CPF: %s\n", format_cpf(atendimento->cpf));
    printf("Tipo Atendimento: %s\n", number_to_setor(atendimento->setor));
}

int main()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese");

    int atendimentos_registrados = 0;
    Atendimento *atendimentos;
    atendimentos = malloc(sizeof(Atendimento));
    int option = 0;

    do
    {
        printf("1 - Solicitar Atendimento\n");
        printf("2 - Listar Atendimentos Registrados\n");
        printf("3 - Listar Atendimento por Setor\n");
        printf("4 - Sair\n");
        printf("> ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            system("cls");
            char nome[50];
            char cpf[11];
            int setor;
            printf("Você está no menu de solicitação de atendimento\n");
            printf("Digite seu nome: ");
            fflush(stdin);
            fgets(nome, 50, stdin);
            if (nome[strlen(nome) - 1] == '\n')
            {
                nome[strlen(nome) - 1] = '\0';
            }
            printf("Digite seu CPF: ");
            fflush(stdin);
            fgets(cpf, 12, stdin);
            if (cpf[strlen(cpf) - 1] == '\n')
            {
                cpf[strlen(cpf) - 1] = '\0';
            }
            if (strlen(cpf) != 11)
            {
                printf("================================\n");
                printf("CPF inválido\n");
                printf("================================\n\n");
                break;
            }
            printf("Digite o número do setor do atendimento:\n");
            printf("1 - Abertura de Conta\n");
            printf("2 - Caixa\n");
            printf("3 - Gerente Pessoa Física\n");
            printf("4 - Gerente Pessoa Jurídica\n");
            printf("> ");
            fflush(stdin);
            scanf("%d", &setor);
            if (setor < 1 || setor > 4)
            {
                printf("================================\n");
                printf("Setor inválido\n");
                printf("================================\n\n");
                break;
            }
            strcpy(atendimentos[atendimentos_registrados].nome, nome);
            strcpy(atendimentos[atendimentos_registrados].cpf, cpf);
            atendimentos[atendimentos_registrados].setor = setor;
            atendimentos_registrados++;
            atendimentos = realloc(atendimentos, (sizeof(Atendimento) * (atendimentos_registrados + 1)));
            system("cls");
            printf("================================\n");
            printf("Seu atendimento foi registrado com sucesso!\n");
            printf("================================\n\n");
            break;
        }
        case 2:
        {
            system("cls");
            if (atendimentos_registrados == 0)
            {
                printf("================================\n");
                printf("Não há atendimentos registrados\n");
                printf("================================\n\n");
                break;
            }
            printf("===============================\n");
            for (int i = 0; i < atendimentos_registrados; i++)
            {
                print_atendimento(&atendimentos[i]);
                printf("===============================\n");
            }
            break;
        }
        case 3:
        {
            system("cls");
            printf("Digite o número do setor:\n");
            printf("1 - Abertura de Conta\n");
            printf("2 - Caixa\n");
            printf("3 - Gerente Pessoa Física\n");
            printf("4 - Gerente Pessoa Jurídica\n");
            printf("> ");
            int setor;
            scanf("%d", &setor);
            fflush(stdin);
            system("cls");
            if (setor < 1 || setor > 4)
            {
                printf("================================\n");
                printf("Setor inválido\n");
                printf("================================\n\n");
                break;
            }
            if (atendimentos_registrados == 0)
            {
                printf("================================\n");
                printf("Não há atendimentos registrados\n");
                printf("================================\n\n");
                break;
            }
            int atendimentos_encontrados = 0;
            printf("===============================\n");
            for (int i = 0; i < atendimentos_registrados; i++)
            {
                if (atendimentos[i].setor == setor)
                {
                    atendimentos_encontrados++;
                    print_atendimento(&atendimentos[i]);
                    printf("===============================\n");
                }
            }
            if (atendimentos_encontrados == 0)
            {
                printf("Não há atendimentos registrados para este setor\n");
                printf("===============================\n\n");
            }
            break;
        }
        case 4:
            system("cls");
            printf("===============================\n");
            printf("Finalizando sistema...\n");
            printf("===============================\n\n");
            free(atendimentos);
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
    } while (option != 4);

    return 0;
}
