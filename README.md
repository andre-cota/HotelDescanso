# HotelDescanso

## Trata-se de um software desenvolvido para as disciplinas
- Algoritimo e Estrutura de dados I 
- Fundamentos de Engenharia de Software

Curso: Engenharia de Software

Codigo foi criado na IDE VSCode. Para rodar o software basta executar o arquivo main.exe (apenas em windows).

## As funcionalidades do software são:

* Cadastro de clientes
* Cadastro de funcionario
* Cadastro de estadia
* Pesquisa de cliente
* Pesquisa de funcionario 

## Software foi feito de maneira modular separado por funções especificas contendo....

### 5 funções principais:

* void menu_Principal();
* void cadastra_Cliente();
* void cadastra_Estadia();
* void cadastra_Funcionario();
* void baixa_Estadia();

### 11 funcões de calculos, verificações e abertura de arquivos:

* int gera_Codigo(const char *file_name);
* int verifica_ArquivoVazio(const char *file_name);
* void strSplit(char *strTOsplit, char *strArr[], char *strSeparet, int nArr);
* int calcula_Diarias(DataEntrada data_entrada, DataSaida data_saida);
* int busca_CodigoCliente(char nome_cli[]);
* int busca_NumeroQuarto(int hospedes);
* void ler_ClientesArquivo(Cliente VetorCliente[]);
* void ler_FuncionarioArquivo(Funcionario VetorFuncionarios[]);
* void ler_QuartosArquivo(Quartos VetorQuartos[]);
* void atualiza_Quartos(Quartos VetorQuartos[]);
* int fidelidade(int diarias);

### 3 Funções de manipulação de dados:

* int verifica_AnoBisexto(int ano_entrd);
* int valida_Data(int dia, int mes, int ano);
* void pesquisaEstadia(char nome[],Cliente VetorCliente[], DataEntrada VetorDataEntrada[], DataSaida VetorDataSaida[]);



