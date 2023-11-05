/******************************************************************************
Aluno(a): Esdras de Sousa Nogueira
Matrícula: 222006230

Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/


// Defines e Includes necessários para o funcionamento das funções e procedimentos 
#define CONSULTAR_MINIUSINA 1
#define CONSULTAR_CONSUMIDOR 2
#define LISTAR_MINIUSINAS 3
#define LISTAR_MINIUSINAS_OCDGOCE 4 // Lista de As Miniusinas em Operação por Ordem Crescente de Capacidade de Geração de Energia
#define LISTAR_RAS_ODQMU 5          //  Listar as RAs por ordem decrescente de quantidade de miniusinas
#define LISTAR_RAS_ODQC 6           // Listar as RAs por ordem crescente de número de contratos
#define LISTAR_RAS_ODCG 7           //  Listar as RAs por ordem decrescente de capacidade de geração
#define LISTAR_RAS_ODPED 8          // Listar as RAs por ordem decrescente de percentual de energia disponível
#define SAIR 9
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

// Structs
struct regiaoadministrativa
{
    char id_ra[5];
    char nome_ra[50];
    char quantidade_miniusinas[5];
    char capacidade_total[20];
    char quantidade[20];
    char gasto[20];
    char disponivel[20];
};

struct consumidor
{
    char id_consumidor[50];
    char nome[50];
    char id_ra[5];
};

struct miniusina
{
    char cnpj_miniusina[19];
    char nome_miniusina[50];
    char capacidade_total[20];
    char id_ra[5];
    char status_usina[15];
};

struct contratos
{
    char id_contrato[5];
    char id_consumidor[50];
    char cnpj_miniusina[19];
    char data_inicio_contrato[11];
    char energia_contratada[8];
};

// Procedimento para o menu do SINGDF
void menu()
{
    

    printf("....... MENU DE OPCOES SINGDF .......\n");
    printf(" \n");
    printf(" \n");
    printf("1) CONSULTAR MINIUSINA CADASTRADA\n");
    printf("2) CONSULTAR CONSUMIDOR CADASTRADO\n");
    printf("3) LISTAR MINIUSINAS CADASTRADAS\n");
    printf("4) LISTAR MINIUSINAS EM OPERAÇÃO POR ORDEM DECRESCENTE DE CAPACIDADE DE GERAÇÃO DE ENERGIA\n");
    printf("5) LISTAR RAs POR ORDEM DECRESCENTE DE CAPACIDADE DE MINIUSINAS\n");
    printf("6) LISTAR RAs POR ORDEM CRESCENTE DE NÚMERO DE CONTRATOS\n");
    printf("7) LISTAR RAs POR ORDEM DECRESCENTE DE CAPACIDADE DE GERAÇÃO\n");
    printf("8) LISTAR RAs POR ORDEM DECRESCENTE DE CAPACIDADE DE ENERGIA DISPONÍVEL\n");
    printf("9) SAIR DO PROGRAMA \n\n");
}

bool validarCNPJ(char *cnpj) // Função para validar CNPJ
{
    // Removendo caracteres não numéricos
    char cnpjNumerico[15];
    int j = 0;
    for (int i = 0; i < strlen(cnpj); i++)
    {
        // Verificará qual a natureza do caractere
        // Número ou não número
        if (isdigit(cnpj[i]))
        {
            cnpjNumerico[j] = cnpj[i];
            j++;
        }
    }
    cnpjNumerico[j] = '\0';
    // Verificando o tamanho do CNPJ, apenas números
    // Não contando com o caractere NULL
    if (strlen(cnpjNumerico) != 14)
    {
        return false;
    }
    int digito1 = 0, digito2 = 0;
    int multiplicador1 = 5, multiplicador2 = 6;
    // Cálculo do primeiro dígito verificador
    for (int i = 0; i < 12; i++)
    {
        digito1 += (cnpjNumerico[i] - '0') * multiplicador1;
        // multiplicador1 = multiplicador1 - 1
        multiplicador1--;
        if (multiplicador1 < 2)
        {
            multiplicador1 = 9;
        }
    }
    digito1 = 11 - (digito1 % 11);
    if (digito1 >= 10)
    {
        digito1 = 0;
    }
    // Cálculo do segundo dígito verificador
    for (int i = 0; i < 13; i++)
    {
        digito2 += (cnpjNumerico[i] - '0') * multiplicador2;
        // multiplicador2 = multiplicador2 - 1
        multiplicador2--;
        if (multiplicador2 < 2)
        {
            multiplicador2 = 9;
        }
    }
    digito2 = 11 - (digito2 % 11);
    if (digito2 >= 10)
    {
        digito2 = 0;
    }
    // Verificação dos dígitos verificadores
    if ((cnpjNumerico[12] - '0') == digito1 && (cnpjNumerico[13] - '0') == digito2)
    {
        return true;
    }
    return false;
}

void limpar_buffer() //procedimento para limpar o buffer e possibilitar leitura do nome (disponibilizada pelo professor)
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void limpar_tela() // Procedimento para limpar a tela antes de voltar ao menu principal 
{
#if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void charset() // Setar o mapa de caracteres para UTF8 no Windows 
{
#if defined(_WIN32) || defined(_WIN64)
    system("chcp 65001");
#endif
}


bool verificacao_CPF(const char *cpf) // Função que verifica CPF
{
    // Remove caracteres não numéricos do CPF
    char cpfNumerico[12];
    int j = 0;
    for (int i = 0; i < strlen(cpf); i++)
    {
        if (isdigit(cpf[i]))
        {
            cpfNumerico[j++] = cpf[i];
        }
    }
    cpfNumerico[j] = '\0';

    // Verifica se o CPF possui 11 dígitos
    if (strlen(cpfNumerico) != 11)
    {
        return false;
    }

    // Verifica se todos os dígitos são iguais (caso especial)
    bool digitosIguais = true;
    for (int i = 1; i < 11; i++)
    {
        if (cpfNumerico[i] != cpfNumerico[0])
        {
            digitosIguais = false;
            break;
        }
    }
    if (digitosIguais)
    {
        return false;
    }

    // Valida o primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++)
    {
        soma += (cpfNumerico[i] - '0') * (10 - i);
    }
    int digito1 = (soma * 10) % 11;
    if (digito1 == 10)
    {
        digito1 = 0;
    }
    if (digito1 != (cpfNumerico[9] - '0'))
    {
        return false;
    }

    // Valida o segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++)
    {
        soma += (cpfNumerico[i] - '0') * (11 - i);
    }
    int digito2 = (soma * 10) % 11;
    if (digito2 == 10)
    {
        digito2 = 0;
    }
    if (digito2 != (cpfNumerico[10] - '0'))
    {
        return false;
    }

    return true;
}

void aguardarComando() // procedimento para aguardar comando do usuario (disponibilizada pelo professor)
{
    printf("Pressione ENTER para retornar ao menu...");
    getc(stdin);
}

bool verificarDocumento(char *documento_consultado) // verifica se o documento consultado foi um CPF ou CPNJ 
{
    return (verificacao_CPF(documento_consultado) || validarCNPJ(documento_consultado)); // Caso seja um CNPJ/CPF válido me retorna true, invalido retorna false 
}

void sortUsinas(struct miniusina *usina) // ordenação das miniusinas em ORDEM crescente 
{
    // ordernação em ordem crescente 
    for (int i = 0; i < 10; i++)
    {
        for (int j = i; j < 10; j++)
        {
            if (atof(usina[i].capacidade_total) > atof(usina[j].capacidade_total)) // atof = conversão de string para float
            {
                struct miniusina aux = usina[i];
                usina[i] = usina[j];
                usina[j] = aux;
            }
        }
    }
    return;
}


