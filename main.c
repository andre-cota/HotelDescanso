#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const DIAS_MES[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef struct DataEntrada
{
    int diaEntr;
    int mesEntr;
    int anoEntr;
} DataEntrada;

typedef struct DataSaida
{
    int diaSaida;
    int mesSaida;
    int anoSaida;
} DataSaida;

typedef struct Cliente
{
    int cod_cliente;
    char nome_cliente[50];
    char endereco_cliente[100];
    char telefone_cliente[12];
} Cliente;

typedef struct Quartos
{
    int num_quarto;
    int hospedes;
    float valor_diaria;
    int status;
} Quartos;

/*typedef struct Estadia
{
    int cod_estadia;
    DataEntrada entrada;
    DataSaida saida;
    int diarias;
    int cod_cliente;
    int num_quarto;
}Estadia;*/

// FUNÇÕES SISTEMA
void menu_Principal();
void cadastra_Cliente();
void cadastra_Estadia();
void cadastra_Funcionario();

// FUNÇÕES DE APLICAÇÕES
int gera_Codigo(const char *file_name);
int verifica_ArquivoVazio(const char *file_name);
void strSplit(char *strTOsplit, char *strArr[], char *strSeparet, int nArr);
int calcula_Diarias(DataEntrada data_entrada, DataSaida data_saida);
int busca_CodigoCliente(char nome_cli[]);
int busca_NumeroQuarto(int hospedes);
void ler_ClientesArquivo(Cliente VetorCliente[]);
void ler_QuartosArquivo(Quartos VetorQuartos[]);
void atualiza_Quartos(Quartos VetorQuartos[]);
int fidelidade(int diarias);
void pesquisaEstadia(char nome[],Cliente VetorCliente[], DataEntrada VetorDataEntrada[], DataSaida VetorDataSaida[]);

// FUNÇÕES MANIPULAÇÃO DE DATA
int verifica_AnoBisexto(int ano_entrd);
int valida_Data(int dia, int mes, int ano);

int numeroClientes = 0;
int numeroQuartos = 0;
Cliente VetorCliente[1000];
Quartos VetorQuartos[100];

int main()
{

    menu_Principal();

    return 0;
}

// FUNÇÃO MENU PRINCIPAL
void menu_Principal()
{

    int opcao = 0;

    do
    {

        system("cls");
        printf("\n-------------------------------------------------------------------------------------------");
        printf("\n---------------------------BEM VINDO AO HOTEL DESCANSO GARANTIDO---------------------------");
        printf("\n*******************************************************************************************\n");

        printf("\n**************************************MENU PRINCIPAL***************************************\n");

        printf("\n1 - Cadastrar cliente.");
        printf("\n2 - Cadastrar funcionario.");
        printf("\n3 - Cadastrar estadia.");
        printf("\n0 - Sair");
        printf("\n\nInforme a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:
            cadastra_Cliente();
            printf("TESTES CASE1");
            break;

        case 2:
            cadastra_Funcionario();
            break;

        case 3:
            cadastra_Estadia();
            break;

        case 0:
            printf("\nSaindo");
            for (int i = 0; i < 10; i++)
            {

                printf(".");
                _sleep(500);
            }
            printf("\n");
            system("pause");
            system("cls");
            exit(0);
            break;

        default:
            printf("\nOpcao informada invalida!");
            break;
        }

    } while (opcao != 0);
    printf("Fora WHILE");
}

//--------------------------------------------------------------------------------------------------------------------
//------------------------------------BLOCO DE FUNÇÕES DE APLICAÇÕES--------------------------------------------------

// FUNÇÃO TESTE GERNÉRICA PARA GERAR CÓDIGO
int gera_Codigo(const char *file_name)
{

    int ultimo_codigo = 0, arquivo_vazio = 0;

    arquivo_vazio = verifica_ArquivoVazio(file_name);

    if (arquivo_vazio == 0)
    {

        return 1;
    }

    else
    {

        FILE *ler_arquivo = fopen(file_name, "r");

        char linha[201];
        int conta_linhas = 0;

        while (!feof(ler_arquivo))
        {
            fgets(linha, 200, ler_arquivo);
            conta_linhas++;
        }

        fclose(ler_arquivo);

        return conta_linhas;
    }
}

// FUNÇÃO PARA SABER SE O ARQUIVO TXT ESTÁ VAZIO VERIFICANDO ATRAVÉS DO TAMANHO DO ARQUIVO
int verifica_ArquivoVazio(const char *file_name)
{
    int tamanho = 0;

    FILE *ler_arquivo = fopen(file_name, "a+");

    if (ler_arquivo == NULL)
    {

        printf("Erro na abertura do arquivo");
        system("pause");
    }

    else
    {

        fseek(ler_arquivo, 0, SEEK_END);
        tamanho = ftell(ler_arquivo);
        fclose(ler_arquivo);
        return tamanho;
    }
}

//FUNÇÃO PARA FAZER A SEPARAÇÃO DE UMA STRING EM VÁRIAS OUTRAS ATRAVÉS DE UM DELIMITADOR
void strSplit(char *strTOsplit, char *strArr[], char *strSeparet, int nArr)
{
    int i = 0;
    char *pch;

    pch = strtok(strTOsplit, strSeparet);
    for (i = 0; i < nArr; i++)
    {
        strArr[i] = pch;
        pch = strtok(NULL, strSeparet);
    }
}

void ler_ClientesArquivo(Cliente VetorCliente[])
{
    printf("\nENTROU NA FUNCAO");
    FILE *arquivo;
    printf("\nAntes de abrir o arquivo");
    arquivo = fopen("CADASTRO_CLIENTES.txt", "r");
    printf("\nAbriu arquivo");
    char linha[100];
    char *result;
    char *informacoes_linha[4];
    int i = 0;

    while (!feof(arquivo)) // Enquando não chegar no fim do arquivo..
    {
        printf("\nDENTRO DO WHILE %d", i);
        result = *fgets(linha, 100, arquivo);
        if (result == "")
        {
            printf("\n\nLINHA VAZIA");
        }                                           //Leitura de uma linha do arquivo...
        strSplit(linha, informacoes_linha, ";", 4); //Separa os campos e os armazena no vetor de 4 posições chamado informacoes_linha
        //Cada posição do vetor VetorEmpregados guarda não so uma mas quatro informações.
        VetorCliente[i].cod_cliente = atoi(informacoes_linha[0]);
        strcpy(VetorCliente[i].nome_cliente, informacoes_linha[1]);
        printf("\nnome_cliente %s", VetorCliente[i].nome_cliente);
        strcpy(VetorCliente[i].endereco_cliente, informacoes_linha[2]);
        printf("\nendereco_cliente %s", VetorCliente[i].endereco_cliente);
        strcpy(VetorCliente[i].telefone_cliente, informacoes_linha[3]);
        printf("\ntelefone_cliente %s", VetorCliente[i].telefone_cliente);
        i++;
    }

    printf("\nSAIOU DO WHILE");
    numeroClientes = i;
    printf("\n NumeroClientes = %d", numeroClientes);
}

void ler_QuartosArquivo(Quartos VetorQuartos[])
{

    FILE *arquivo;
    arquivo = fopen("CADASTRO_QUARTOS.txt", "r");
    char linha[100];
    char *result;
    char *informacoes_linha[4];
    int i = 0;
    while (!feof(arquivo)) // Enquando não chegar no fim do arquivo..
    {
        result = *fgets(linha, 100, arquivo);       //Leitura de uma linha do arquivo...
        strSplit(linha, informacoes_linha, ";", 4); //Separa os campos e os armazena no vetor de 3 posições chamado informacoes_linha
        //Cada posição do vetor VetorEmpregados guarda não so uma mas tres informações.
        VetorQuartos[i].num_quarto = atoi(informacoes_linha[0]);
        VetorQuartos[i].hospedes = atoi(informacoes_linha[1]);
        VetorQuartos[i].valor_diaria = atof(informacoes_linha[2]);
        VetorQuartos[i].status = atoi(informacoes_linha[3]);
        i++;
    }
    numeroQuartos = i;
}

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------BLOCO DE FUNÇÕES DE MANIPULAÇÃO DE DATAS--------------------------------------------

// FUNÇÃO PARA VERIFICAR SE O ANO QUE FOI PASSADO E BISEXTO
int verifica_AnoBisexto(int ano)
{

    if ((ano % 400 == 0) || ((ano % 4 == 0) && (ano % 100 != 0)))
    {

        return 1;
    }

    else
    {

        return 0;
    }
}

// FUNÇÃO PARA FAZER VALIDAÇÃO DAS DATAS INFORMADAS
int valida_Data(int dia, int mes, int ano)
{

    int bisexto = 0, dias_mes = 0;

    bisexto = verifica_AnoBisexto(ano);
    dias_mes = DIAS_MES[mes - 1];

    if (bisexto == 1)
    {

        if (mes == 2 && (dia > 0 && dia <= 29))
        {

            return 1;
        }

        else if ((dia <= dias_mes) && (mes > 2 && mes < 13 || mes == 1))
        {

            return 1;
        }

        else
        {

            return 0;
        }
    }

    else if (bisexto == 0)
    {

        if ((dia <= dias_mes) && (mes > 0 && mes < 13))
        {

            return 1;
        }

        else
        {

            return 0;
        }
    }

    else
    {

        return 0;
    }
}

int calcula_Diarias(DataEntrada data_entrada, DataSaida data_saida)
{

    int dif_mes = 0, dif_ano = 0, qtd_diarias = 0, eBisexto = 0;

    DataEntrada data_entradaAux;
    DataSaida data_saidaAux;
    int diarias_entradaAux = 0, diarias_SaidaAux = 0;

    dif_mes = data_saida.mesSaida - data_entrada.mesEntr;
    dif_ano = data_saida.anoSaida - data_entrada.anoEntr;

    if (dif_ano == 0)
    {

        eBisexto = verifica_AnoBisexto(data_saida.anoSaida);

        if (eBisexto == 0)
        {

            if (dif_mes == 0)
            {
                qtd_diarias = data_saida.diaSaida - data_entrada.diaEntr;
                return qtd_diarias;
            }

            else if (dif_mes == 1)
            {
                qtd_diarias = (DIAS_MES[data_entrada.mesEntr - 1] - data_entrada.diaEntr) + data_saida.diaSaida;
                return qtd_diarias;
            }

            else
            {

                for (int i = data_entrada.mesEntr; i <= data_saida.mesSaida; i++)
                {

                    if (i == data_entrada.mesEntr)
                    {

                        qtd_diarias += DIAS_MES[data_entrada.mesEntr - 1] - data_entrada.diaEntr;
                    }

                    else if (i == data_saida.mesSaida)
                    {

                        qtd_diarias += data_saida.diaSaida;
                    }

                    else
                    {
                        qtd_diarias += DIAS_MES[i - 1];
                    }
                }

                return qtd_diarias;
            }
        }

        else
        {

            if (dif_mes == 0)
            {

                if (data_saida.mesSaida == 2 && data_saida.diaSaida == 29)
                {

                    qtd_diarias = 29 - data_entrada.diaEntr;
                    return qtd_diarias;
                }

                else
                {

                    qtd_diarias = data_saida.diaSaida - data_entrada.diaEntr;
                    return qtd_diarias;
                }
            }

            else if (dif_mes == 1)
            {

                if (data_saida.mesSaida == 2 || data_entrada.mesEntr == 2)
                {

                    qtd_diarias = ((DIAS_MES[data_entrada.mesEntr - 1] - data_entrada.diaEntr) + data_saida.diaSaida) + 1;
                    return qtd_diarias;
                }

                else
                {

                    qtd_diarias = (DIAS_MES[data_entrada.mesEntr - 1] - data_entrada.diaEntr) + data_saida.diaSaida;
                    return qtd_diarias;
                }
            }

            else
            {

                if (data_entrada.mesEntr > 2)
                {

                    for (int i = data_entrada.mesEntr; i <= data_saida.mesSaida; i++)
                    {

                        if (i == data_entrada.mesEntr)
                        {

                            qtd_diarias += DIAS_MES[data_entrada.mesEntr - 1] - data_entrada.diaEntr;
                        }

                        else if (i == data_saida.mesSaida)
                        {

                            qtd_diarias += data_saida.diaSaida;
                        }

                        else
                        {

                            qtd_diarias += DIAS_MES[i - 1];
                        }
                    }

                    return qtd_diarias;
                }

                else
                {

                    for (int i = data_entrada.mesEntr; i <= data_saida.mesSaida; i++)
                    {

                        if (i == data_entrada.mesEntr)
                        {

                            if (data_entrada.mesEntr == 2)
                            {

                                qtd_diarias += 29 - data_entrada.diaEntr;
                            }

                            else
                            {

                                qtd_diarias += DIAS_MES[data_entrada.mesEntr - 1] - data_entrada.diaEntr;
                            }
                        }

                        else if (i == data_saida.mesSaida)
                        {

                            qtd_diarias += data_saida.diaSaida;
                        }

                        else
                        {

                            if (i == 2)
                            {

                                qtd_diarias += 29;
                            }

                            else
                            {

                                qtd_diarias += DIAS_MES[i - 1];
                            }
                        }
                    }

                    return qtd_diarias;
                }
            }
        }
    }

    if (dif_ano == 1)
    {
        data_entradaAux.diaEntr = 1;
        data_entradaAux.mesEntr = 1;
        data_entradaAux.anoEntr = data_saida.anoSaida;

        data_saidaAux.diaSaida = 31;
        data_saidaAux.mesSaida = 12;
        data_saidaAux.anoSaida = data_entrada.anoEntr;

        diarias_entradaAux = calcula_Diarias(data_entrada, data_saidaAux);
        diarias_SaidaAux = calcula_Diarias(data_entradaAux, data_saida);

        qtd_diarias = diarias_entradaAux + diarias_SaidaAux + 1;

        return qtd_diarias;
    }

    else
    {

        data_entradaAux.diaEntr = 1;
        data_entradaAux.mesEntr = 1;
        data_entradaAux.anoEntr = data_saida.anoSaida;

        data_saidaAux.diaSaida = 31;
        data_saidaAux.mesSaida = 12;
        data_saidaAux.anoSaida = data_entrada.anoEntr;

        for (int i = data_entrada.anoEntr; i <= data_saida.anoSaida; i++)
        {

            if (i == data_entrada.anoEntr)
            {

                diarias_entradaAux += calcula_Diarias(data_entrada, data_saidaAux);
            }

            else if (i == data_saida.anoSaida)
            {

                diarias_entradaAux += calcula_Diarias(data_entradaAux, data_saida);
            }

            else
            {

                eBisexto = verifica_AnoBisexto(i);

                if (eBisexto == 1)
                {

                    diarias_entradaAux += 366;
                }

                else
                {

                    diarias_entradaAux += 365;
                }
            }
        }

        return (diarias_entradaAux + 1);
    }
}

//----------------------------------------------------------------------------------------------------------------
//-------------------------------------BLOCO DE FUNCIONALIDADES DO SISTEMA----------------------------------------

// FUNÇÃO DE CADASTRO DE CLIENTES
void cadastra_Cliente()
{

    int cod_cliente = 0;
    char nome_cliente[50], endereco_cliente[100], telefone_cliente[12], novo_cadastro;

    FILE *escreve_arquivo;
    escreve_arquivo = fopen("CADASTRO_CLIENTES.txt", "a+");

    cod_cliente = gera_Codigo("CADASTRO_CLIENTES.txt");

    fprintf(escreve_arquivo, "%d;", cod_cliente);
    printf("\nInforme o nome do cliente: ");
    setbuf(stdin, NULL);
    gets(nome_cliente);
    fputs(nome_cliente, escreve_arquivo);
    fputc(';', escreve_arquivo);
    printf("Informe o endereco do cliente: ");
    setbuf(stdin, NULL);
    gets(endereco_cliente);
    fputs(endereco_cliente, escreve_arquivo);
    fputc(';', escreve_arquivo);
    printf("Informe o telefone do cliente: ");
    setbuf(stdin, NULL);
    gets(telefone_cliente);
    fputs(telefone_cliente, escreve_arquivo);
    fputc('\n', escreve_arquivo);

    printf("\nESCREVEU NO ARQUIVO 621");
    fclose(escreve_arquivo);
    printf("\nFECHOU ARQUIVO");
    ler_ClientesArquivo(VetorCliente);
    printf("\nTerminou funcao LER_CLIENTES");
}

// FUNÇÃO PARA CADASTRAR ESTADIA DE UM CLIENTE
void cadastra_Estadia()
{
    DataSaida saida;
    DataEntrada entrada;
    int cod_estadia = 0, diarias = 0, valida_data = 0, hospedes = 0;
    int codigo_cliente = 0, numero_quarto = 0;
    char nome_cliente[50];

    FILE *escrever_arquivo;
    escrever_arquivo = fopen("CADASTRO_ESTADIA.txt", "a+");

    cod_estadia = gera_Codigo("CADASTRO_ESTADIA.txt");

    printf("\nInforme o nome do cliente: ");
    setbuf(stdin, NULL);
    gets(nome_cliente);

    codigo_cliente = busca_CodigoCliente(nome_cliente);

    printf("\nInforme a quantidade de hospedes (1 a 5): ");
    scanf("%d", &hospedes);

    numero_quarto = busca_NumeroQuarto(hospedes);

    printf("\nInforme a data de entrada: ");
    printf("\nDia entrada (DD): ");
    scanf("%d", &entrada.diaEntr);
    printf("Mes entrada (MM): ");
    scanf("%d", &entrada.mesEntr);
    printf("Ano entrada (AAAA): ");
    scanf("%d", &entrada.anoEntr);

    valida_data = valida_Data(entrada.diaEntr, entrada.mesEntr, entrada.anoEntr);

    if (valida_data == 0)
    {
        printf("\nData Informada e invalida!\n");
        system("pause");
        menu_Principal();
    }

    printf("\nInforme a data de saida: ");
    printf("\nDia saida (DD): ");
    scanf("%d", &saida.diaSaida);
    printf("Mes saida (MM): ");
    scanf("%d", &saida.mesSaida);
    printf("Ano saida (AAAA): ");
    scanf("%d", &saida.anoSaida);

    valida_data = valida_Data(saida.diaSaida, saida.mesSaida, saida.anoSaida);

    if (valida_data == 0)
    {
        printf("\nData Informada e invalida!\n");
        system("pause");
        menu_Principal();
    }

    diarias = calcula_Diarias(entrada, saida);

    fprintf(escrever_arquivo, "%d;%d/%d/%d;%d/%d/%d;%d;%d;%d\n", cod_estadia, entrada.diaEntr, entrada.mesEntr, entrada.anoEntr, saida.diaSaida, saida.mesSaida, saida.anoSaida, diarias, codigo_cliente, numero_quarto);

    fclose(escrever_arquivo);
}

int busca_CodigoCliente(char nome_cli[])
{

    char nome_buscado[50], nome_aux[50];
    int cod_procurado = 0;
    ler_ClientesArquivo(VetorCliente);

    strcpy(nome_buscado, nome_cli);
    strupr(nome_buscado);

    for (int i = 0; i <= numeroClientes; i++)
    {

        strcpy(nome_aux, VetorCliente[i].nome_cliente);
        strupr(nome_aux);

        if (strcmp(nome_aux, nome_buscado) == 0)
        {

            cod_procurado = VetorCliente[i].cod_cliente;
        }
    }

    if (cod_procurado != 0)
    {

        return cod_procurado;
    }

    else
    {

        printf("\nCliente nao esta cadastrado.");
        system("pause");
        return -1;
    }
}

int busca_NumeroQuarto(int hospedes)
{

    int quartoBuscado = 0;
    ler_QuartosArquivo(VetorQuartos);

    for (int i = 0; i <= numeroQuartos; i++)
    {

        if (hospedes == VetorQuartos[i].hospedes && VetorQuartos[i].status != 1)
        {

            quartoBuscado = VetorQuartos[i].num_quarto;
        }
    }

    if (quartoBuscado != 0)
    {

        for (int i = 0; i <= numeroQuartos; i++)
        {

            if (quartoBuscado == VetorQuartos[i].num_quarto)
            {

                VetorQuartos[i].status == 1;
            }
        }

        atualiza_Quartos(VetorQuartos);
        return quartoBuscado;
    }

    else
    {

        printf("\nTodos quartos para esta quantidade de hospedes estao ocupados.");
        return -1;
    }
}

void cadastra_Funcionario()
{
    printf("ENTROU EM CADASTRA FUNCIONARIO");
    _sleep(500);

    int cod_func = 0;
    char nome_func[50], telefone_func[12], cargo_func[15], novo_cadastro, salario_func[200];

    FILE *escreve_arquivo;
    escreve_arquivo = fopen("CADASTRO_FUNC.txt", "a+");

    // cod_func = gera_CodigoCliente();
    cod_func = gera_Codigo("CADASTRO_FUNC.txt");

    fprintf(escreve_arquivo, "%d;", cod_func);
    printf("\nInforme o nome do funcionario: ");
    setbuf(stdin, NULL);
    gets(nome_func);
    fputs(nome_func, escreve_arquivo);
    fputc(';', escreve_arquivo);
    printf("Informe o cargo do funcionario: ");
    setbuf(stdin, NULL);
    gets(cargo_func);
    fputs(cargo_func, escreve_arquivo);
    fputc(';', escreve_arquivo);
    printf("Informe o salario do funcionario: ");
    setbuf(stdin, NULL);
    gets(salario_func);
    fputs(salario_func, escreve_arquivo);
    fputc(';', escreve_arquivo);
    printf("Informe o telefone do funcionario: ");
    setbuf(stdin, NULL);
    gets(telefone_func);
    fputs(telefone_func, escreve_arquivo);
    fputc('\n', escreve_arquivo);

    fclose(escreve_arquivo);
}

//Essa funçao deve ser chamada para cada estadia que o cliente solicitar
//Estadia é uma struct. Dentro dessa struct deve haver a quantidade de diarias do cliente. O parametro dessa funçao recebe a quantidade de diárias
//contidas na struct estadia (dependendo de quantas estadias o cliente solicitou e fará o calculo de pontos de fidelidade para cada estadia.
int fidelidade(int diarias)
{
    int pontos_fid, i;

    for (i = 0; i < diarias; i++)
    {
        pontos_fid = pontos_fid + 10;
    }
    
    return pontos_fid;
}

void atualiza_Quartos(Quartos VetorQuartos[])
{

    int cod_cliente = 0;
    char nome_cliente[50], endereco_cliente[100], telefone_cliente[12], novo_cadastro;

    FILE *escreve_arquivo;
    escreve_arquivo = fopen("CADASTRO_QUARTOS.txt", "w");

    for (int i = 0; i < numeroQuartos; i++)
    {

        fprintf(escreve_arquivo, "%d;%d;%f;%d\n", VetorQuartos[i].num_quarto, VetorQuartos[i].hospedes, VetorQuartos[i].valor_diaria, VetorQuartos[i].status);

        /*fputs(VetorQuartos[i].num_quarto,escreve_arquivo);
        fputc(';', escreve_arquivo);
        fputs(VetorQuartos[i].hospedes,escreve_arquivo);
        fputc(';', escreve_arquivo);
        fputs(VetorQuartos[i].valor_diaria,escreve_arquivo);
        fputc(';', escreve_arquivo);
        fputs(VetorQuartos[i].status,escreve_arquivo);
        fputc('\n', escreve_arquivo);*/
    }

    fclose(escreve_arquivo);
}

void pesquisaEstadia(char nome[],Cliente VetorCliente[], DataEntrada VetorDataEntrada[], DataSaida VetorDataSaida[])
    {
		int i;
        for (i = 0; i < numeroClientes; i++)
        {
            if(nome == hospedes[i].nome))
            {
                printf(" %s : %d : %.2f \n", Cliente[i].cod_cliente, Cliente[i]nome_cliente,Cliente[i].telefone_cliente, DataEntrada[i].diaEntr, DataEntrada[i].mesEntr, DataEntrada[i].anoEntr, DataSaida[i].diaSaida, DataSaida[i].MesSaida, DataSaida[i].AnoSaida);
            }
        }
    }



//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------FUNÇÕES DESCARTADAS OU EM TESTE---------------------------------------------------

// FUNÇÃO PARA GERAR CÓDIGO DE CLIENTE PARA CADASTRO

/*int gera_CodigoCliente()
{

    int ultimo_codigo = 0, arquivo_vazio = 0;

    arquivo_vazio = verifica_ArquivoVazio("CADASTRO_CLIENTES.txt");

    if (arquivo_vazio == 0)
    {

        return 1;
    }

    else
    {

        FILE *ler_arquivo = fopen("CADASTRO_CLIENTES.txt", "r");

        char linha[201];
        int conta_linhas = 0;

        while (!feof(ler_arquivo))
        {

            fgets(linha, 200, ler_arquivo);
            conta_linhas++;
        }

        fclose(ler_arquivo);

        return conta_linhas;
    }
} */