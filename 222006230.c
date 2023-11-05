/******************************************************************************
Aluno(a): Esdras de Sousa Nogueira
Matrícula: 222006230

Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/

// Incluindo as bibliotecas
#include <stdio.h>
#include "222006230.h"
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

// funções e procedimentos
void menu();
bool validarCNPJ(char *cnpj);
bool verificacao_CPF(const char *cpf);
bool verificarDocumento(char *documento);
void sortUsinas(struct miniusina *usina);
void Consultar_miniusina();
void Consultar_consumidor();
void Listar_miniusinas();
void Listar_miniusinas_OCDGOCE();
void Listar_ras_ODQMU();
void Listar_ras_ODQC();
void Listar_ras_ODCG();
void Listar_ras_ODPED();

int main()
{
    charset();
    setlocale(LC_CTYPE, ".utf8");
    limpar_tela();

    int escolha_opcao;

    // Impressão do Menu e leitura de escolha do usuario
    do
    {
        menu();

        while (scanf("%d", &escolha_opcao) != 1)
        { // loop para verificar se não foi digitado um caracter invalido, se for valido continua para o loop seguinte
            // Limpa o buffer de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            printf("Comando inválido! Digite novamente:\n");
        }

        // condicional que irá executar o comando do usuario
        switch (escolha_opcao)
        {
        case CONSULTAR_MINIUSINA:
            Consultar_miniusina();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case CONSULTAR_CONSUMIDOR:
            Consultar_consumidor();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case LISTAR_MINIUSINAS:
            Listar_miniusinas();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case LISTAR_MINIUSINAS_OCDGOCE:
            Listar_miniusinas_OCDGOCE();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case LISTAR_RAS_ODQMU:
            Listar_ras_ODQMU();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case LISTAR_RAS_ODQC:
            Listar_ras_ODQC();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case LISTAR_RAS_ODCG:
            Listar_ras_ODCG();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case LISTAR_RAS_ODPED:
            Listar_ras_ODPED();
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        case SAIR:
            printf("Programa Encerrado...\n");
            break;
        default:
            printf("Opção inválida!\n");
            limpar_buffer();
            aguardarComando();
            limpar_tela();
            break;
        }
    } while (escolha_opcao != SAIR);
}

void Consultar_miniusina()
{
    // Declaração de variáveis
    FILE *arquivo_Miniusina;
    struct miniusina usina_cadastrada;
    int consulta_valida = 0;
    char cnpj_usina[19];
    char linha[256];

    // Printa o comando e lê o comando do usuário
    limpar_tela();
    printf("Digite o CNPJ da miniusina a ser consultada: \n");
    limpar_buffer();
    scanf("%s", cnpj_usina);

    limpar_buffer();
    limpar_tela();

    // Valida o CNPJ digitado pelo usuário
    if (!validarCNPJ(cnpj_usina))
    {
        printf("CNPJ inválido!\n");
        return;
    }

    arquivo_Miniusina = fopen("miniusinas.csv", "r"); // Abertura do arquivo csv

    if (arquivo_Miniusina == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        // Lê uma linha do arquivo e armazena em "linha"
        while (fgets(linha, sizeof(linha), arquivo_Miniusina))
        {
            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;]",
                   usina_cadastrada.cnpj_miniusina,
                   usina_cadastrada.nome_miniusina,
                   usina_cadastrada.capacidade_total,
                   usina_cadastrada.id_ra,
                   usina_cadastrada.status_usina);

            if (strcmp(cnpj_usina, usina_cadastrada.cnpj_miniusina) == 0)
            {
                consulta_valida = 1; // Define a variável "consulta_valida" como 1 para indicar que a consulta é válida
                break;               // Interrompe o loop
            }
        }

        // Se a consulta é válida, imprime os dados da miniusina consultada
        if (consulta_valida == 1)
        {
            // Consulta do nome da Região Administrativa (RA) correspondente ao ID da miniusina
            char nome_ra[100] = ""; // Inicializa a string vazia `nome_ra` com tamanho 100 caracteres
            FILE *arquivo_ra = fopen("ra.csv", "r");
            if (arquivo_ra != NULL)
            {
                char ra_linha[100];
                fscanf(arquivo_ra, "%[^\n]\n", ra_linha);

                while (!feof(arquivo_ra))
                {
                    char ra_id[10], ra_nome[100];
                    fscanf(arquivo_ra, "%[^;];%[^\n]\n", ra_id, ra_nome);

                    if (strcmp(usina_cadastrada.id_ra, ra_id) == 0) // Compara se o `id_ra` da variável `usina_cadastrada` é igual a `ra_id` lido do arquivo
                    {
                        strcpy(nome_ra, ra_nome); // Copia o conteúdo de `ra_nome` para a variável `nome_ra`
                        break;
                    }
                }

                fclose(arquivo_ra);
            }

            printf("Minisusina Consultada: \n");
            printf("\n");

            printf("CNPJ: %s\n", usina_cadastrada.cnpj_miniusina);
            printf("Nome: %s\n", usina_cadastrada.nome_miniusina);
            printf("Capacidade total: %s\n", usina_cadastrada.capacidade_total);
            printf("RA: %s - %s\n", usina_cadastrada.id_ra, nome_ra);
            printf("Status da usina: %s\n", usina_cadastrada.status_usina);
            printf("\n");

            // Consulta dos contratos vinculados à miniusina consultada
            FILE *arq_contratos;
            struct contratos contratos_cadastrados;
            int contratos_encontrados = 0;

            arq_contratos = fopen("contratos.csv", "r");

            if (arq_contratos == NULL)
            {
                printf("Erro ao abrir o arquivo de contratos\n");
            }
            else
            {
                // Impressão dos contratos
                printf("Contratos vinculados:\n");
                printf("\n");

                while (fgets(linha, sizeof(linha), arq_contratos))
                {
                    sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^\n]",
                           contratos_cadastrados.id_contrato,
                           contratos_cadastrados.id_consumidor,
                           contratos_cadastrados.cnpj_miniusina,
                           contratos_cadastrados.data_inicio_contrato,
                           contratos_cadastrados.energia_contratada);

                    if (strcmp(cnpj_usina, contratos_cadastrados.cnpj_miniusina) == 0)
                    {
                        printf("ID do Contrato: %s\n", contratos_cadastrados.id_contrato);
                        printf("ID do Consumidor: %s\n", contratos_cadastrados.id_consumidor);
                        printf("CNPJ: %s\n", contratos_cadastrados.cnpj_miniusina);
                        printf("Data de início do contrato: %s\n", contratos_cadastrados.data_inicio_contrato);
                        printf("Energia contratada: %s\n", contratos_cadastrados.energia_contratada);
                        printf("\n");

                        contratos_encontrados++;
                    }
                }

                if (contratos_encontrados == 0)
                {
                    printf("Nenhum contrato encontrado para essa miniusina\n");
                    printf("\n");
                }

                fclose(arq_contratos); // Fecha o arquivo contratos
            }
        }
        else
        {
            printf("Essa miniusina não está cadastrada em nosso sistema\n");
            // Espera comando do usuário para retornar ao menu
        }

        fclose(arquivo_Miniusina); // Fecha o arquivo de miniusinas
    }
}

void Consultar_consumidor()
{
    // declaração de variaveis
    FILE *arquivo_consumidor;
    struct consumidor consumidor_cadastrado;
    int consulta_valida = 0;
    char documento_consultado[20];
    char linha[256];

    // leitura do usuario
    limpar_tela();
    printf("Digite o CPF ou CNPJ a ser consultado: ");
    limpar_buffer();
    scanf("%s", documento_consultado);

    limpar_buffer();
    limpar_tela();

    // verifica qual foi o documento digitado pelo usuario
    if (!verificarDocumento(documento_consultado))
    {
        printf("CNPJ ou CPF inválido!\n");
        return;
    }

    arquivo_consumidor = fopen("consumidores.csv", "r");

    if (arquivo_consumidor == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    else
    {
        // Lê uma linha do arquivo e armazena em "linha"
        while (fgets(linha, sizeof(linha), arquivo_consumidor))
        {
            sscanf(linha, "%[^;];%[^;];%[^\n]",
                   consumidor_cadastrado.id_consumidor,
                   consumidor_cadastrado.nome,
                   consumidor_cadastrado.id_ra);
            // A string de formato "%[^;];%[^;];%[^;];%[^;];%[^;]" indica que os campos são separados por ponto e vírgula

            if (strcmp(documento_consultado, consumidor_cadastrado.id_consumidor) == 0)
            {
                consulta_valida = 1;
                break;
            }
        }

        if (consulta_valida == 1)
        {
            // Consulta do nome e ID da Região Administrativa (RA) correspondente ao ID
            char nome_ra[100] = ""; // Inicializa a string vazia `nome_ra` com tamanho 100 caracteres
            char id_ra[10] = "";    // Inicializa a string vazia `id_ra` com tamanho 10 caracteres
            FILE *arquivo_ra = fopen("ra.csv", "r");
            if (arquivo_ra != NULL)
            {
                char ra_linha[100];
                fscanf(arquivo_ra, "%[^\n]\n", ra_linha);

                while (!feof(arquivo_ra))
                {
                    char ra_id[10], ra_nome[100];
                    fscanf(arquivo_ra, "%[^;];%[^\n]\n", ra_id, ra_nome);

                    if (strcmp(consumidor_cadastrado.id_ra, ra_id) == 0) // Verifica se o id_ra lido é igual ao id_ra do consumidor consultado
                    {
                        // Copia o nome_ra e id_ra para as variáveis nome_ra e id_ra
                        strcpy(nome_ra, ra_nome);
                        strcpy(id_ra, ra_id);
                        break;
                    }
                }

                fclose(arquivo_ra);
            }

            printf("Consumidor Consultado:\n\n");
            printf("CPF/CNPJ: %s\n", consumidor_cadastrado.id_consumidor);
            printf("Nome: %s\n", consumidor_cadastrado.nome);
            printf("RA: %s - %s\n", id_ra, nome_ra);
            printf("\n");

            // Consulta dos contratos vinculados ao consumidor consultado

            FILE *arq_contratos;
            struct contratos contratos_cadastrados;
            int contratos_encontrados = 0;

            arq_contratos = fopen("contratos.csv", "r");

            if (arq_contratos == NULL)
            {
                printf("Erro ao abrir o arquivo de contratos\n");
                fclose(arquivo_consumidor);
                return;
            }

            printf("Contratos vinculados:\n\n");

            while (fgets(linha, sizeof(linha), arq_contratos))
            {
                sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^\n]",
                       contratos_cadastrados.id_contrato,
                       contratos_cadastrados.id_consumidor,
                       contratos_cadastrados.cnpj_miniusina,
                       contratos_cadastrados.data_inicio_contrato,
                       contratos_cadastrados.energia_contratada);

                if (strcmp(documento_consultado, contratos_cadastrados.id_consumidor) == 0)
                {
                    printf("ID do Contrato: %s\n", contratos_cadastrados.id_contrato);
                    printf("CNPJ da Miniusina: %s\n", contratos_cadastrados.cnpj_miniusina);
                    printf("Data de início do contrato: %s\n", contratos_cadastrados.data_inicio_contrato);
                    printf("Energia contratada: %s\n", contratos_cadastrados.energia_contratada);
                    printf("\n");

                    contratos_encontrados++;
                }
            }

            if (contratos_encontrados == 0)
            {
                printf("Nenhum contrato encontrado para esse consumidor\n");
                printf("\n");
            }

            fclose(arq_contratos);
        }
        else
        {
            printf("Esse consumidor não está cadastrado em nosso sistema\n");
        }

        fclose(arquivo_consumidor);
    }
}

void Listar_miniusinas()
{
    // Limpar a tela após a escolha do item
    limpar_tela();

    printf("Miniusinas Cadastradas: \n");
    printf("\n");

    // Declaração de variáveis
    FILE *arquivo_miniusinas;
    struct miniusina listagem_miniusina;

    arquivo_miniusinas = fopen("miniusinas.csv", "r"); // abrindo o arquivo

    if (arquivo_miniusinas != NULL)
    {
        char primeiralinha[100];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeiralinha);

        // Carregar as informações das RAs do arquivo "ra.csv"
        struct regiaoadministrativa ra_decrescente[33];
        FILE *arquivo_ra = fopen("ra.csv", "r");
        if (arquivo_ra != NULL)
        {
            char ra_linha[100];
            fscanf(arquivo_ra, "%[^\n]\n", ra_linha);

            int i = 0;
            while (!feof(arquivo_ra) && i < 33)
            {
                fscanf(arquivo_ra, "%[^;];%[^\n]\n",
                       ra_decrescente[i].id_ra,
                       ra_decrescente[i].nome_ra);

                i++;
            }

            fclose(arquivo_ra);
        }
        else
        {
            printf("O arquivo de RAs nao existe\n");
            printf("\n");

            return;
        }

        while (!feof(arquivo_miniusinas)) // verifica se ainda não chegou ao final do arquivo
        {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                   listagem_miniusina.cnpj_miniusina,
                   listagem_miniusina.nome_miniusina,
                   listagem_miniusina.capacidade_total,
                   listagem_miniusina.id_ra,
                   listagem_miniusina.status_usina);

            // Encontrar o nome da RA correspondente ao ID
            char nome_ra[100] = ""; // Inicializa a string vazia `nome_ra` com tamanho 100 caracteres
            for (int i = 0; i < 33; i++)
            {
                if (strcmp(listagem_miniusina.id_ra, ra_decrescente[i].id_ra) == 0)
                {
                    strcpy(nome_ra, ra_decrescente[i].nome_ra);
                    break;
                }
            }

            printf("CNPJ: %s\n", listagem_miniusina.cnpj_miniusina);
            printf("NOME: %s\n", listagem_miniusina.nome_miniusina);
            printf("CAPACIDADE: %s\n", listagem_miniusina.capacidade_total);
            printf("RA: %s - %s\n", listagem_miniusina.id_ra, nome_ra);
            printf("STATUS: %s\n", listagem_miniusina.status_usina);
            printf("\n");
        }
    }
    else
    {
        printf("O arquivo de miniusinas nao existe\n");
        printf("\n");
    }

    fclose(arquivo_miniusinas);
}

void Listar_miniusinas_OCDGOCE()
{
    // Limpar a tela após a escolha do item
    limpar_tela();

    // Declaração de variaveis
    FILE *arquivo_miniusinas;
    FILE *arquivo_ras;
    struct miniusina mu_decrescente[11];
    struct regiaoadministrativa ras[33];

    arquivo_miniusinas = fopen("miniusinas.csv", "r");
    arquivo_ras = fopen("ra.csv", "r");

    if (arquivo_miniusinas != NULL && arquivo_ras != NULL)
    {
        char primeira_linha_usinas[100];
        char primeira_linha_ras[100];

        // Ignorar a primeira linha dos arquivos CSV
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha_usinas);
        fscanf(arquivo_ras, "%[^\n]\n", primeira_linha_ras);

        int i = 0;
        while (!feof(arquivo_miniusinas) && i < 11)
        {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                   mu_decrescente[i].cnpj_miniusina,
                   mu_decrescente[i].nome_miniusina,
                   mu_decrescente[i].capacidade_total,
                   mu_decrescente[i].id_ra,
                   mu_decrescente[i].status_usina);
            i++;
        }

        int j = 0;
        while (!feof(arquivo_ras) && j < 33)
        {
            fscanf(arquivo_ras, "%[^;];%[^\n]\n",
                   ras[j].id_ra,
                   ras[j].nome_ra);
            j++;
        }

        fclose(arquivo_miniusinas);
        fclose(arquivo_ras);

        sortUsinas(mu_decrescente); // Ordenar as miniusinas

        printf("Miniusinas em operação por ordem decrescente de capacidade de geração de energia: \n\n");

        for (int k = i - 1; k >= 0; k--)
        {
            for (int l = 0; l < j; l++)
            {
                if (strcmp(mu_decrescente[k].id_ra, ras[l].id_ra) == 0)
                {
                    printf("CNPJ: %s\n", mu_decrescente[k].cnpj_miniusina);
                    printf("NOME: %s\n", mu_decrescente[k].nome_miniusina);
                    printf("CAPACIDADE: %s\n", mu_decrescente[k].capacidade_total);
                    printf("ID: %s - %s\n", mu_decrescente[k].id_ra, ras[l].nome_ra);
                    printf("\n");
                    break;
                }
            }
        }
    }
}

void Listar_ras_ODQMU()

{
    // Limpar a tela após a escolha do item
    limpar_tela();

    FILE *arquivo_ras;
    struct regiaoadministrativa ra_decrescente[33];

    arquivo_ras = fopen("ra.csv", "r");

    if (arquivo_ras != NULL)
    {
        // Lê a primeira linha do arquivo e armazena em primeiralinha
        char primeiralinha[100];
        fscanf(arquivo_ras, "%[^\n]\n", primeiralinha);

        // Loop para ler as linhas restantes do arquivo até o final
        int i = 0;
        while (!feof(arquivo_ras))
        {
            fscanf(arquivo_ras, "%[^;];%[^\n]\n", // Lê os campos separados por ponto e vírgula e armazena nos membros da struct ra_decrescente
                   ra_decrescente[i].id_ra,
                   ra_decrescente[i].nome_ra);
            strcpy(ra_decrescente[i].quantidade_miniusinas, "0"); // Define a quantidade de miniusinas como "0" para cada RA lida

            i++; // Incrementa o índice i para ler a próxima linha do arquivo
        }
    }

    FILE *arquivo_miniusinas;
    struct miniusina mu_decrescente[10];

    arquivo_miniusinas = fopen("miniusinas.csv", "r");

    if (arquivo_miniusinas != NULL)
    {
        char primeiralinha[100];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeiralinha);
        int i = 0;
        while (!feof(arquivo_miniusinas))
        {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                   mu_decrescente[i].cnpj_miniusina,
                   mu_decrescente[i].nome_miniusina,
                   mu_decrescente[i].capacidade_total,
                   mu_decrescente[i].id_ra,
                   mu_decrescente[i].status_usina);

            for (int j = 0; j < 33; j++) // Loop para percorrer cada RA
            {                            // Verifica se o ID_RA da miniusina corresponde ao ID_RA da RA
                if (strcmp(mu_decrescente[i].id_ra, ra_decrescente[j].id_ra) == 0)
                {
                    int quantidade = atoi(ra_decrescente[j].quantidade_miniusinas);
                    quantidade++;
                    sprintf(ra_decrescente[j].quantidade_miniusinas, "%d", quantidade);
                    break;
                }
            }
            i++;
        }
    }
    // Ordenação das RAs por quantidade de miniusinas em ordem decrescente
    for (int i = 0; i < 32; i++)
    {
        for (int j = i + 1; j < 33; j++)
        {
            // quantidade_i e quantidade_j são obtidos convertendo as quantidades de miniusinas para inteiros usando atoi.
            int quantidade_i = atoi(ra_decrescente[i].quantidade_miniusinas);
            int quantidade_j = atoi(ra_decrescente[j].quantidade_miniusinas);

            // Compara as quantidades de miniusinas entre duas RAs
            if (quantidade_i < quantidade_j)
            {
                // Realiza a troca das posições das RAs na estrutura ra_decrescente
                struct regiaoadministrativa temp = ra_decrescente[i];
                ra_decrescente[i] = ra_decrescente[j];
                ra_decrescente[j] = temp;
            }
        }
    }

    printf("RAs por ordem decrescente de quantidade de miniusinas:\n\n");
    for (int i = 0; i < 33; i++)
    {
        printf("%d. ID: %s - %s - %s miniusinas\n", i + 1, ra_decrescente[i].id_ra, ra_decrescente[i].nome_ra, ra_decrescente[i].quantidade_miniusinas);
        printf("\n");
    }

    fclose(arquivo_ras);
    fclose(arquivo_miniusinas);
}

void Listar_ras_ODQC()
{
    // Listar as RAs por ordem crescente de número de contratos

    limpar_tela();

    printf("RAs por ordem crescente de número de contratos\n");
    printf("\n");

    FILE *arquivo_ras, *arquivo_contratos, *arquivo_miniusinas;
    struct miniusina miniusinas[11];
    struct regiaoadministrativa ras[33];
    struct contratos contracts[8];
    char linha[256];

    arquivo_ras = fopen("ra.csv", "r");

    if (arquivo_ras != NULL)
    {
        char primeiralinha[100];
        fscanf(arquivo_ras, "%[^\n]\n", primeiralinha);
        int i = 0;
        while (!feof(arquivo_ras))
        {
            fscanf(arquivo_ras, "%[^;];%[^\n]\n",
                   ras[i].id_ra,
                   ras[i].nome_ra);
            strcpy(ras[i].capacidade_total, "0");

            i++;
        }
        fclose(arquivo_ras);
    }

    arquivo_contratos = fopen("contratos.csv", "r");

    if (arquivo_contratos == NULL)
    {
        printf("Erro ao abrir o arquivo de contratos\n");
    }
    else
    {
        int i = 0;

        while (fgets(linha, sizeof(linha), arquivo_contratos))
        {
            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^\n]",
                   contracts[i].id_contrato,
                   contracts[i].id_consumidor,
                   contracts[i].cnpj_miniusina,
                   contracts[i].data_inicio_contrato,
                   contracts[i].energia_contratada);

            i++;
        }

        fclose(arquivo_contratos);

        arquivo_miniusinas = fopen("miniusinas.csv", "r");

        if (arquivo_miniusinas != NULL)
        {
            char primeiralinha[100];
            fscanf(arquivo_miniusinas, "%[^\n]\n", primeiralinha);

            int i = 0;
            while (!feof(arquivo_miniusinas))
            {
                fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                       miniusinas[i].cnpj_miniusina,
                       miniusinas[i].nome_miniusina,
                       miniusinas[i].capacidade_total,
                       miniusinas[i].id_ra,
                       miniusinas[i].status_usina);

                i++;
            }
            fclose(arquivo_miniusinas);
        }

        struct regiaoadministrativa rasOrdenadas[33];
        for (int i = 0; i < 33; i++)
        {
            rasOrdenadas[i] = ras[i];
        }

        int contagemContratos[33];
        for (int i = 0; i < 33; i++)
        {
            contagemContratos[i] = 0;
        }

        for (int i = 0; i < 33; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                if (strcmp(ras[i].id_ra, miniusinas[j].id_ra) == 0)
                {
                    for (int k = 0; k < 8; k++)
                    {
                        if (strcmp(miniusinas[j].cnpj_miniusina, contracts[k].cnpj_miniusina) == 0)
                        {
                            contagemContratos[i]++;
                        }
                    }
                }
            }
        }

        // Ordenação em ordem crescente
        for (int i = 0; i < 32; i++)
        {
            for (int j = i + 1; j < 33; j++)
            {
                if (contagemContratos[i] > contagemContratos[j])
                {
                    struct regiaoadministrativa aux = rasOrdenadas[i];
                    rasOrdenadas[i] = rasOrdenadas[j];
                    rasOrdenadas[j] = aux;
                    int aux2 = contagemContratos[i];
                    contagemContratos[i] = contagemContratos[j];
                    contagemContratos[j] = aux2;
                }
            }
        }

        // Imprimir resultados
        for (int i = 0; i < 33; i++)
        {
            printf("%d. RA: %s - %s - Contratos: %d\n", i + 1, rasOrdenadas[i].id_ra, rasOrdenadas[i].nome_ra, contagemContratos[i]);
            printf("\n");
        }
    }
}

void Listar_ras_ODCG()
{
    limpar_tela();

    // declaração de variaveis
    FILE *arquivo_ras;
    struct regiaoadministrativa ra_decrescente[33];

    arquivo_ras = fopen("ra.csv", "r");

    if (arquivo_ras != NULL)
    {
        char primeiralinha[100];
        fscanf(arquivo_ras, "%[^\n]\n", primeiralinha);

        int i = 0;
        while (!feof(arquivo_ras))
        {
            fscanf(arquivo_ras, "%[^;];%[^\n]\n",
                   ra_decrescente[i].id_ra,
                   ra_decrescente[i].nome_ra);
            strcpy(ra_decrescente[i].capacidade_total, "0");

            i++;
        }
    }

    FILE *arquivo_miniusinas;
    struct miniusina mu_decrescente[10];

    arquivo_miniusinas = fopen("miniusinas.csv", "r");

    if (arquivo_miniusinas != NULL)
    {
        char primeiralinha[100];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeiralinha);
        int i = 0;
        while (!feof(arquivo_miniusinas))
        {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                   mu_decrescente[i].cnpj_miniusina,
                   mu_decrescente[i].nome_miniusina,
                   mu_decrescente[i].capacidade_total,
                   mu_decrescente[i].id_ra,
                   mu_decrescente[i].status_usina);

            for (int j = 0; j < 33; j++)
            {
                if (strcmp(mu_decrescente[i].id_ra, ra_decrescente[j].id_ra) == 0)
                {
                    float capacidade = atof(ra_decrescente[j].capacidade_total);
                    capacidade += atof(mu_decrescente[i].capacidade_total);
                    sprintf(ra_decrescente[j].capacidade_total, "%.2f", capacidade);
                    break;
                }
            }
            i++;
        }
    }

    // Ordenação das RAs por capacidade de geração em ordem decrescente
    for (int i = 0; i < 33 - 1; i++)
    {
        for (int j = i + 1; j < 33; j++)
        {
            float capacidade_i = atof(ra_decrescente[i].capacidade_total);
            float capacidade_j = atof(ra_decrescente[j].capacidade_total);

            if (capacidade_i < capacidade_j)
            {
                struct regiaoadministrativa temp = ra_decrescente[i];
                ra_decrescente[i] = ra_decrescente[j];
                ra_decrescente[j] = temp;
            }
        }
    }

    printf("RAs por ordem decrescente de capacidade de geração:\n\n");
    for (int i = 0; i < 33; i++)
    {
        printf("%d. RA: %s - %s - Capacidade: %.2f kWh\n", i + 1, ra_decrescente[i].id_ra, ra_decrescente[i].nome_ra, atof(ra_decrescente[i].capacidade_total));
        printf("\n");
    }

    fclose(arquivo_ras);
    fclose(arquivo_miniusinas);
}

void Listar_ras_ODPED()
{
    limpar_tela();

    FILE *arquivo_ra;
    struct regiaoadministrativa ra_cadastradas[34];
    arquivo_ra = fopen("ra.csv", "r");
    if (arquivo_ra == NULL)
    {
        printf("Arquivo de ra nao encontrado\n");
        printf("\n");
        return;
    }

    char primeiralinha[1000];
    fscanf(arquivo_ra, "%[^\n]\n", primeiralinha);
    int i = 0;
    while (!feof(arquivo_ra))
    {
        fscanf(arquivo_ra, "%[^;];%[^\n]\n",
               ra_cadastradas[i].id_ra,
               ra_cadastradas[i].nome_ra);
        strcpy(ra_cadastradas[i].quantidade, "0");
        strcpy(ra_cadastradas[i].gasto, "0");
        strcpy(ra_cadastradas[i].disponivel, "0");
        i++;
    }
    fclose(arquivo_ra);

    FILE *arquivo_miniusina;
    struct miniusina miniusinas_cadastradas[11];
    arquivo_miniusina = fopen("miniusinas.csv", "r");
    if (arquivo_miniusina == NULL)
    {
        printf("Arquivo de miniusinas nao encontrado\n");
        printf("\n");
        return;
    }

    char primeiralinha2[100];
    fscanf(arquivo_miniusina, "%[^\n]\n", primeiralinha2);
    int k = 0;
    while (!feof(arquivo_miniusina))
    {
        fscanf(arquivo_miniusina, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
               miniusinas_cadastradas[k].cnpj_miniusina,
               miniusinas_cadastradas[k].nome_miniusina,
               miniusinas_cadastradas[k].capacidade_total,
               miniusinas_cadastradas[k].id_ra,
               miniusinas_cadastradas[k].status_usina);

        for (int i = 0; i < 33; i++) // Atualização das quantidades de energia nas regiões administrativas correspondentes
        {
            if (strcmp(ra_cadastradas[i].id_ra, miniusinas_cadastradas[k].id_ra) == 0)
            {
                int contador = atoi(ra_cadastradas[i].quantidade);
                contador += atoi(miniusinas_cadastradas[k].capacidade_total);
                sprintf(ra_cadastradas[i].quantidade, "%d", contador);
            }
        }
        k++;
    }
    fclose(arquivo_miniusina);

    FILE *arquivo_contratos;
    struct contratos contratos_cadastrados[8];
    arquivo_contratos = fopen("contratos.csv", "r");
    if (arquivo_contratos == NULL)
    {
        printf("Arquivo de contratos nao encontrado\n");
        printf("\n");
        return;
    }

    char primeiralinha3[1000];
    fscanf(arquivo_contratos, "%[^\n]\n", primeiralinha3);
    int j = 0;
    while (!feof(arquivo_contratos))
    {
        fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
               contratos_cadastrados[j].id_contrato,
               contratos_cadastrados[j].id_consumidor,
               contratos_cadastrados[j].cnpj_miniusina,
               contratos_cadastrados[j].data_inicio_contrato,
               contratos_cadastrados[j].energia_contratada);

        for (int i = 0; i < 33; i++) // Atualização dos gastos de energia nas regiões administrativas correspondentes
        {
            for (int k = 0; k < 11; k++)
            {
                if (strcmp(ra_cadastradas[i].id_ra, miniusinas_cadastradas[k].id_ra) == 0)
                {
                    if (strcmp(miniusinas_cadastradas[k].cnpj_miniusina, contratos_cadastrados[j].cnpj_miniusina) == 0)
                    {
                        int gasto = atoi(ra_cadastradas[i].gasto);
                        gasto += atoi(contratos_cadastrados[j].energia_contratada);
                        sprintf(ra_cadastradas[i].gasto, "%d", gasto);
                    }
                }
            }
        }
        j++;
    }
    fclose(arquivo_contratos);

    // Cálculo do percentual de energia disponível para cada região administrativa
    for (int i = 0; i < 33; i++)
    {
        if (!strcmp(ra_cadastradas[i].quantidade, "0"))
        {
            continue;
        }
        float porcentagem = atoi(ra_cadastradas[i].gasto);
        porcentagem = (porcentagem * 100.0) / atoi(ra_cadastradas[i].quantidade);
        sprintf(ra_cadastradas[i].disponivel, "%.2f", 100 - porcentagem);
    }

    // Ordenação das regiões administrativas com base no percentual de energia disponível
    for (int i = 0; i < 32; i++)
    {
        for (int j = i + 1; j < 33; j++)
        {
            if (!strcmp(ra_cadastradas[j].quantidade, "0"))
            {
                continue;
            }
            float comparar1 = atof(ra_cadastradas[i].disponivel);
            float comparar2 = atof(ra_cadastradas[j].disponivel);
            if (comparar1 < comparar2)
            {
                struct regiaoadministrativa auxiliar = ra_cadastradas[i];
                ra_cadastradas[i] = ra_cadastradas[j];
                ra_cadastradas[j] = auxiliar;
            }
        }
    }
    //Impressão dos percentuais
    printf("RAs por ordem decrescente de percentual de energia disponível: \n\n");
    
    for (int i = 0; i < 33; i++)
    {
        printf("%d. RA: %s - %s\n", i + 1, ra_cadastradas[i].id_ra, ra_cadastradas[i].nome_ra);
        printf("Percentual de energia disponivel: %s %%\n", ra_cadastradas[i].disponivel);
        printf("\n");
    }
}
