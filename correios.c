#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Entrega { 
    char id[10], origem[50], destino[50];
    float tempoEstimado;
};

struct Relatorio { 
    char idFuncionario[10], idVeiculo[10], idCliente[10];
    float tempoTotal;
};

struct Funcionario { 
    char id[10], nome[50];
};

struct Veiculo { 
    char id[10];
    int tipo, status;
    float capacidade;
};

struct Cliente { 
    char id[10], nome[50];
    int servico;
};

struct Endereco {
    char estado[20], cidade[50], bairro[50], rua[50];
    int numero;
};

int limpaBuffer() {
    int c;
    int contei = 0;
    while ((c = getchar()) != '\n' && c != EOF) contei++;
    return contei;
}

// FUNÇÕES DE BUSCA
int BuscaID(char IdPesquisado[], char arquivoTipo[]){
    FILE *arquivo = fopen(arquivoTipo, "r");
    if(arquivo == NULL){
        return 0;
    }

    struct Relatorio relatorio;
    struct Entrega entrega;
    struct Funcionario funcionario;
    struct Veiculo veiculo;
    struct Cliente cliente;
    struct Endereco endereco;
    char linha[100];

    while(fgets(linha, sizeof(linha), arquivo)){
        if(strcmp(arquivoTipo, "Entregas.txt") == 0){
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%f", entrega.id, entrega.origem, entrega.destino, &entrega.tempoEstimado);
            if(strcmp(entrega.id, IdPesquisado) == 0){
                fclose(arquivo);
                return 1;
            }
        }else if(strcmp(arquivoTipo, "Funcionarios.txt") == 0){
            sscanf(linha, "%[^|]|%[^\n]", funcionario.id, funcionario.nome);
            if(strcmp(funcionario.id, IdPesquisado) == 0){
                fclose(arquivo);
                return 1;
            }
        }else if(strcmp(arquivoTipo, "Veiculos.txt") == 0){
            sscanf(linha, "%[^|]|%d|%f|%d", veiculo.id, &veiculo.tipo, &veiculo.capacidade, &veiculo.status);
            if(strcmp(veiculo.id, IdPesquisado) == 0){
                fclose(arquivo);
                return 1;
            }
        }else if(strcmp(arquivoTipo, "Clientes.txt") == 0){
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d",
                cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, &endereco.numero, &cliente.servico);
            if(strcmp(cliente.id, IdPesquisado) == 0){
                fclose(arquivo);
                return 1;
            }
        }else if(strcmp(arquivoTipo, "Relatorio.txt") == 0){
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f",
                entrega.id, relatorio.idFuncionario, relatorio.idVeiculo, relatorio.idCliente, entrega.origem, entrega.destino, &relatorio.tempoTotal);
    
            if(strcmp(entrega.id, IdPesquisado) == 0){
                fclose(arquivo);
                return 1;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

int TotalCadastros(char tipo[]){
    FILE *arquivo = fopen(tipo, "r");
    if(arquivo == NULL){
        return 0;
    }

    int total = 0;
    char linha[100];

    while(fgets(linha, sizeof(linha), arquivo)){
        total++;
    }
    fclose(arquivo);
    return total;
}

int DisponibilidadeVeiculo(char ID[]){
    FILE *arquivo = fopen("Veiculos.txt", "r");
    if(arquivo == NULL){
        printf("\nNenhum veiculo cadastrado\n");
        return 1;
    }

    struct Veiculo veiculo;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%d|%f|%d", veiculo.id, &veiculo.tipo, &veiculo.capacidade, &veiculo.status);

        if(strcmp(veiculo.id, ID) == 0){
            fclose(arquivo);
            return veiculo.status;
        }
    }
    return 1;
}

void VisualizarIDs(char arquivoTipo[]){
    FILE *arquivo = fopen(arquivoTipo, "r");
    if(arquivo == NULL){
        return;
    }
    
    struct Entrega entrega;
    struct Relatorio relatorio;
    struct Funcionario funcionario;
    struct Veiculo veiculo;
    struct Cliente cliente;
    struct Endereco endereco;

    printf("\nIDs existentes: [ ");

    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        if(strcmp(arquivoTipo, "Entregas.txt") == 0){
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%f", entrega.id, entrega.origem, entrega.destino, &entrega.tempoEstimado);
            printf("%s ", entrega.id);

        }else if(strcmp(arquivoTipo, "Funcionarios.txt") == 0){
            sscanf(linha, "%[^|]|%[^\n]", funcionario.id, funcionario.nome);
            printf("%s ", funcionario.id);
            
        }else if(strcmp(arquivoTipo, "Veiculos.txt") == 0){
            sscanf(linha, "%[^|]|%d|%f|%d", veiculo.id, &veiculo.tipo, &veiculo.capacidade, &veiculo.status);
            printf("%s ", veiculo.id);
            
        }else if(strcmp(arquivoTipo, "Clientes.txt") == 0){
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d",
                cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, &endereco.numero, &cliente.servico);
            printf("%s ", cliente.id);
        }else if(strcmp(arquivoTipo, "Relatorio.txt") == 0){
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f",
                entrega.id, relatorio.idFuncionario, relatorio.idVeiculo, relatorio.idCliente, entrega.origem, entrega.destino, &relatorio.tempoTotal);
            printf("%s ", entrega.id);
        }
    }

    printf("]\n");
    fclose(arquivo);
    return;
}

// FUNÇÕES DAS ENTREGAS
void CadastrarEntrega(){
    struct Entrega novaEntrega;

    printf("ID da entrega: ");
    scanf("%9s", novaEntrega.id);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado.\n");
        return;
    }

    if(BuscaID(novaEntrega.id, "Relatorio.txt") || BuscaID(novaEntrega.id, "Entregas.txt")){
        printf("\nEsse ID ja existe\n");
        return;
    }

    printf("Origem da entrega: ");
    scanf(" %49[^\n]", novaEntrega.origem);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    printf("Destino da entrega: ");
    scanf(" %49[^\n]", novaEntrega.destino);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    printf("Tempo estimado (em horas) da entrega: ");
    while (scanf("%f", &novaEntrega.tempoEstimado) != 1){
        printf("\nEntrada invalida. Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    
    FILE *arquivo = fopen("Entregas.txt", "a");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo\n");
        return;
    }

    fprintf(arquivo, "%s|%s|%s|%.1f\n", novaEntrega.id, novaEntrega.origem, novaEntrega.destino, novaEntrega.tempoEstimado);
    fclose(arquivo);

    printf("\nEntrega cadastrada!\n");
}

void VisualizarEntrega(char IdPesquisado[]){
    FILE *arquivo = fopen("Entregas.txt", "r");
    if(arquivo == NULL){
        printf("\nNenhuma entrega para visualizar\n");
        return;
    }

    struct Entrega entrega;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%f", entrega.id, entrega.origem, entrega.destino, &entrega.tempoEstimado);

        if(strcmp(entrega.id, IdPesquisado) == 0){
            printf("\nEntrega encontrada:\nID: %s\nOrigem: %s\nDestino: %s\nTempo estimado: %.1f\n",
                entrega.id, entrega.origem, entrega.destino, entrega.tempoEstimado);
            fclose(arquivo);
            return;
        }
    }
    printf("\nEntrega nao encontrada\n");
    fclose(arquivo);
}

void EditarEntrega(char ID[], int escolha){
    FILE *arquivo = fopen("Entregas.txt", "r");
    if(arquivo == NULL){
        printf("\nSem entregas para editar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Entrega entrega;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%f", entrega.id, entrega.origem, entrega.destino, &entrega.tempoEstimado);
        
        if(strcmp(entrega.id, ID) == 0){
            if(escolha == 1){
                printf("Nova origem: ");
                scanf(" %49[^\n]", entrega.origem);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    return;
                }
            }else if(escolha == 2){
                printf("Novo destino: ");
                scanf(" %49[^\n]", entrega.destino);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    return;
                }
            }else if(escolha == 3){
                printf("Novo tempo estimado: ");
                while (scanf(" %f", &entrega.tempoEstimado) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
            }
        }

        fprintf(temp, "%s|%s|%s|%.1f\n", entrega.id, entrega.origem, entrega.destino, entrega.tempoEstimado);
    }
    fclose(arquivo);
    fclose(temp);
    remove("Entregas.txt");
    rename("temp.txt", "Entregas.txt");
    printf("\nEntrega editada!\n");
}

void DeletarEntrega(char IDs[][10], int n){
    FILE *arquivo = fopen("Entregas.txt", "r");
    if(arquivo == NULL){
        printf("\nSem entregas para deletar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Entrega entrega;
    char linha[100];
    int deletados = 0;
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%f", entrega.id, entrega.origem, entrega.destino, &entrega.tempoEstimado);

        int deletar = 0;
        for(int i = 0; i < n; i++){
            if(strcmp(entrega.id, IDs[i]) == 0){
                deletar = 1;
                deletados++;
                break;
            }
        }

        if(!deletar){
            fprintf(temp, "%s|%s|%s|%.1f\n", entrega.id, entrega.origem, entrega.destino, entrega.tempoEstimado);
        }
    }
    fclose(arquivo);
    fclose(temp);
    remove("Entregas.txt");
    rename("temp.txt", "Entregas.txt");

    printf("\n%d entrega(s) deletada(s)!\n", deletados);
}

void RealizarEntrega(char idEntrega[]){
    FILE *arquivo = fopen("Entregas.txt", "r");
    if(arquivo == NULL){
        printf("\nSem entrega para concluir\n");
        return;
    }
    FILE *arquivoDadosRelatorio = fopen("Relatorio.txt", "a");
    if(arquivoDadosRelatorio == NULL){
        printf("Erro ao abrir o arquivo\n");
        fclose(arquivo);
        return;
    }
    
    struct Relatorio relatorio;
    
    VisualizarIDs("Funcionarios.txt");

    printf("Digite o ID do funcionario: ");
    scanf("%9s", relatorio.idFuncionario);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    if(BuscaID(relatorio.idFuncionario, "Funcionarios.txt") != 1){
        printf("\nFuncionario nao cadastrado\n");
        fclose(arquivo);
        fclose(arquivoDadosRelatorio);
        return;
    }
    
    VisualizarIDs("Veiculos.txt");

    printf("Digite o ID do veiculo: ");
    scanf("%9s", relatorio.idVeiculo);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    if(BuscaID(relatorio.idVeiculo, "Veiculos.txt") != 1){
        printf("\nVeiculo nao cadastrado\n");
        fclose(arquivo);
        fclose(arquivoDadosRelatorio);
        return;
    }else if(DisponibilidadeVeiculo(relatorio.idVeiculo) == 1){
        printf("\nVeiculo ocupado\n");
        fclose(arquivo);
        fclose(arquivoDadosRelatorio);
        return;
    }
    
    VisualizarIDs("Clientes.txt");

    printf("Digite o ID do cliente: ");
    scanf("%9s", relatorio.idCliente);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    if(BuscaID(relatorio.idCliente, "Clientes.txt") != 1){
        printf("\nCliente nao cadastrado\n");
        fclose(arquivo);
        fclose(arquivoDadosRelatorio);
        return;
    }

    printf("Digite o tempo total da entrega: ");
    while (scanf("%f", &relatorio.tempoTotal) != 1){
        printf("\nEntrada invalida. Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    struct Entrega entrega;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%f", entrega.id, entrega.origem, entrega.destino, &entrega.tempoEstimado);

        if(strcmp(entrega.id, idEntrega) == 0){
            fprintf(arquivoDadosRelatorio, "%s|%s|%s|%s|%s|%s|%.1f\n",
                entrega.id, relatorio.idFuncionario, relatorio.idVeiculo, relatorio.idCliente, entrega.origem, entrega.destino, relatorio.tempoTotal);
            
            fclose(arquivo);
            fclose(arquivoDadosRelatorio);
            printf("Relatorio atualizado!\n");
            char idTemp[1][10];
            strcpy(idTemp[0], entrega.id);
            DeletarEntrega(idTemp, 1);
            return;
        }
    }
    printf("\nEntrega nao encontrada\n");
    fclose(arquivo);
    fclose(arquivoDadosRelatorio);
}

void VisualizarRelatorio(char ID[]){
    FILE *arquivo = fopen("Relatorio.txt", "r");
    if(arquivo == NULL){
        printf("\nSem relatorio para visualizar\n");
    }

    struct Entrega entrega;
    struct Relatorio relatorio;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f",
            entrega.id, relatorio.idFuncionario, relatorio.idVeiculo, relatorio.idCliente, entrega.origem, entrega.destino, &relatorio.tempoTotal);

        if(strcmp(entrega.id, ID) == 0){
            printf("\nRelatorio encontrado:\nID da entrega: %s\nID do funcionario: %s\nID do veiculo: %s\n"
                "ID do cliente: %s\nOrigem e destino: %s, %s\nTempo total de entrega: %.1f\n\n",
                entrega.id, relatorio.idFuncionario, relatorio.idVeiculo, 
                relatorio.idCliente, entrega.origem, entrega.destino, relatorio.tempoTotal);
            fclose(arquivo);
            return;
        }
    }
    printf("\nRelatorio nao encontrado\n");
    fclose(arquivo);
}

// FUNÇÕES FUNCIONÁRIOS
void CadastrarFuncionario(){
    struct Funcionario funcionario;

    printf("ID do funcionario: ");
    scanf("%9s", funcionario.id);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    if(BuscaID(funcionario.id, "Funcionarios.txt") != 0){
        printf("\nEsse ID ja existe\n");
        return;
    }

    printf("Nome completo do funcionario: ");
    scanf(" %49[^\n]", funcionario.nome);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }
    
    FILE *arquivo = fopen("Funcionarios.txt", "a");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo\n");
        return;
    }

    fprintf(arquivo, "%s|%s\n", funcionario.id, funcionario.nome);
    fclose(arquivo);

    printf("\nFuncionario cadastrado!\n");
}

void VisualizarFuncionario(char IdPesquisado[]){
    FILE *arquivo = fopen("Funcionarios.txt", "r");
    if(arquivo == NULL){
        printf("\nNenhum funcionario para visualizar\n");
        return;
    }

    struct Funcionario funcionario;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^\n]", funcionario.id, funcionario.nome);

        if(strcmp(funcionario.id, IdPesquisado) == 0){
            printf("\nFuncionario encontrado:\nID: %s\nNome: %s\n",
                funcionario.id, funcionario.nome);
            fclose(arquivo);
            return;
        }
    }
    printf("\nFuncionario nao encontrado\n");
    fclose(arquivo);
}

void EditarFuncionario(char ID[]){
    FILE *arquivo = fopen("Funcionarios.txt", "r");
    if(arquivo == NULL){
        printf("\nSem funcionarios para editar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Funcionario funcionario;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^\n]", funcionario.id, funcionario.nome);
        
        if(strcmp(funcionario.id, ID) == 0){
            printf("Nome completo atualizado: ");
            scanf(" %49[^\n]", funcionario.nome);
            if (limpaBuffer()) {
                printf("\nEntrada invalida. Processo cancelado\n");
                return;
            }
        }

        fprintf(temp, "%s|%s\n", funcionario.id, funcionario.nome);
    }
    fclose(arquivo);
    fclose(temp);
    remove("Funcionarios.txt");
    rename("temp.txt", "Funcionarios.txt");
    printf("\nFuncionario editado!\n");
}

void DeletarFuncionario(char ID[][10], int n){
    FILE *arquivo = fopen("Funcionarios.txt", "r");
    if(arquivo == NULL){
        printf("\nSem funcionarios para deletar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Funcionario funcionario;
    char linha[100];
    int deletados = 0;
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^\n]", funcionario.id, funcionario.nome);
        
        int deletar = 0;
        for(int i = 0; i < n; i++){
            if(strcmp(funcionario.id, ID[i]) == 0){
                deletar = 1;
                deletados++;
            }
        }

        if(!deletar){
            fprintf(temp, "%s|%s\n", funcionario.id, funcionario.nome);
        }
    }
    fclose(arquivo);
    fclose(temp);
    remove("Funcionarios.txt");
    rename("temp.txt", "Funcionarios.txt");
    printf("\n%d funcionario(s) deletado(s)!\n", deletados);
}

// FUNÇÕES VEÍCULOS
const char* TipoVeiculo(int tipo){
    switch (tipo){
        case 1: return "bicicleta";
        case 2: return "motocicleta";
        case 3: return "triciclo eletrico";
        case 4: return "van";
        case 5: return "caminhao VUC";
        case 6: return "caminhao toco";
        case 7: return "caminhao truck";
        case 8: return "carreta";
        default: return "ERRO";
    }
}

void CadastrarVeiculo(){
    struct Veiculo veiculo;

    printf("ID do veiculo: ");
    scanf("%9s", veiculo.id);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    if(BuscaID(veiculo.id, "Veiculos.txt") != 0){
        printf("\nEsse ID ja existe\n");
        return;
    }

    printf("\n[1: bicicleta (10kg - 25kg)]\
        \n[2: motocicleta (20kg - 50kg)]\
        \n[3: triciclo eletrico (50kg - 150kg)]\
        \n[4: van (800kg - 1500kg)]\
        \n[5: caminhao VUC (1500kg - 3000kg)]\
        \n[6: caminhao toco (3000kg - 6000kg)]\
        \n[7: caminhao truck (6000kg - 14000kg)]\
        \n[8: carreta (14000kg - 30000kg)]\
        \nTipo do veiculo: ");
    while (scanf("%d", &veiculo.tipo) != 1){
        printf("\nEntrada invalida. Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    switch (veiculo.tipo){
        case 1: case 2: case 3: case 4:
        case 5: case 6: case 7: case 8: break;
        default: printf("\nTipo invalido\n");
            return;
    }

    int capacidadeMinima[8] = {10, 20, 50, 800, 1500, 3000, 6000, 14000};
    int capacidadeMaxima[8] = {25, 50, 150, 1500, 3000, 6000, 14000, 30000};

    for(int i = 0; i < 8; i++){
        if(veiculo.tipo == i + 1){
            printf("\n[%dkg - %dkg]\nDigite a capacidade: ", capacidadeMinima[i], capacidadeMaxima[i]);
            while (scanf("%f", &veiculo.capacidade) != 1){
                printf("\nEntrada invalida. Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            if(veiculo.capacidade > capacidadeMaxima[i] || veiculo.capacidade < capacidadeMinima[i]){
                printf("\nCapacidade invalida\n");
                return;
            }
        }
    }
    
    printf("\n[0: livre]\n[1: ocupado]\nStatus do veiculo: ");
    while (scanf("%d", &veiculo.status) != 1){
        printf("\nEntrada invalida. Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    if(veiculo.status != 0 && veiculo.status != 1){
        printf("\nStatus invalido\n");
        return;
    }
    
    FILE *arquivo = fopen("Veiculos.txt", "a");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo\n");
        return;
    }

    fprintf(arquivo, "%s|%d|%.2f|%d\n", veiculo.id, veiculo.tipo, veiculo.capacidade, veiculo.status);
    fclose(arquivo);

    printf("Veiculo cadastrado!\n");
}

void VisualizarVeiculo(char IdPesquisado[]){
    FILE *arquivo = fopen("Veiculos.txt", "r");
    if(arquivo == NULL){
        printf("\nNenhum veiculo para visualizar\n");
        return;
    }

    struct Veiculo veiculo;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%d|%f|%d", veiculo.id, &veiculo.tipo, &veiculo.capacidade, &veiculo.status);

        if(strcmp(veiculo.id, IdPesquisado) == 0){
            printf("\nVeiculo encontrado:\nID: %s\nTipo: %s\nCapacidade: %.2fkg\nStatus: %s\n",
                veiculo.id, TipoVeiculo(veiculo.tipo), veiculo.capacidade, veiculo.status ? "ocupado" : "livre");
            fclose(arquivo);
            return;
        }
    }
    printf("\nFuncionario nao encontrado\n");
    fclose(arquivo);
}

void EditarVeiculo(char ID[], int escolha){
    FILE *arquivo = fopen("Veiculos.txt", "r");
    if(arquivo == NULL){
        printf("\nNenhum veiculo para editar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("Erro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Veiculo veiculo;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%d|%f|%d", veiculo.id, &veiculo.tipo, &veiculo.capacidade, &veiculo.status);
        
        if(strcmp(veiculo.id, ID) == 0){
            if(escolha == 1){ // EDITAR TIPO DO VEICULO
                printf("\n[1: bicicleta (10kg - 25kg)]\
                    \n[2: motocicleta (20kg - 50kg)]\
                    \n[3: triciclo eletrico (50kg - 150kg)]\
                    \n[4: van (800kg - 1500kg)]\
                    \n[5: caminhao VUC (1500kg - 3000kg)]\
                    \n[6: caminhao toco (3000kg - 6000kg)]\
                    \n[7: caminhao truck (6000kg - 14000kg)]\
                    \n[8: carreta (14000kg - 30000kg)]\
                    \nTipo do veiculo atualizado: ");
                while (scanf("%d", &veiculo.tipo) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
            }

            if(escolha == 1 || escolha == 2){ // EDITAR CAPACIDADE DO VEICULO
                switch (veiculo.tipo){
                    case 1: case 2: case 3: case 4:
                    case 5: case 6: case 7: case 8: break;
                    default: printf("\nTipo invalido\n");
                        return;
                }
            
                int capacidadeMinima[8] = {10, 20, 50, 800, 1500, 3000, 6000, 14000};
                int capacidadeMaxima[8] = {25, 50, 150, 1500, 3000, 6000, 14000, 30000};
            
                for(int i = 0; i < 8; i++){
                    if(veiculo.tipo == i + 1){
                        printf("\n[%dkg - %dkg]\nDigite a capacidade atualizada: ", capacidadeMinima[i], capacidadeMaxima[i]);
                        while (scanf("%f", &veiculo.capacidade) != 1){
                            printf("\nEntrada invalida. Digite um numero: ");
                            while (getchar() != '\n');
                        }
                        while (getchar() != '\n');

                        if(veiculo.capacidade > capacidadeMaxima[i] || veiculo.capacidade < capacidadeMinima[i]){
                            printf("\nCapacidade invalida\n");
                            fclose(arquivo);
                            fclose(temp);
                            remove("temp.txt");
                            return;
                        }
                    }
                }
            }else if(escolha == 3){
                printf("\n[0: livre]\n[1: ocupado]\nStatus do veiculo atualizado: ");
                while (scanf("%d", &veiculo.status) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
                if(veiculo.status != 0 && veiculo.status != 1){
                    printf("\nStatus invalido\n");
                    fclose(arquivo);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
            }
        }

        fprintf(temp, "%s|%d|%.2f|%d\n", veiculo.id, veiculo.tipo, veiculo.capacidade, veiculo.status);
    }
    fclose(arquivo);
    fclose(temp);
    remove("Veiculos.txt");
    rename("temp.txt", "Veiculos.txt");
    printf("\nVeiculo editado!\n");
}

void DeletarVeiculo(char ID[][10], int n){
    FILE *arquivo = fopen("Veiculos.txt", "r");
    if(arquivo == NULL){
        printf("\nSem veiculo para deletar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Veiculo veiculo;
    char linha[100];
    int deletados = 0;
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%d|%f|%d", veiculo.id, &veiculo.tipo, &veiculo.capacidade, &veiculo.status);
        
        int deletar = 0;
        for(int i = 0; i < n; i++){
            if(strcmp(veiculo.id, ID[i]) == 0){
                deletar = 1;
                deletados++;
            }
        }

        if(!deletar){
            fprintf(temp, "%s|%d|%.2f|%d\n", veiculo.id, veiculo.tipo, veiculo.capacidade, veiculo.status);
        }
    }
    fclose(arquivo);
    fclose(temp);
    remove("Veiculos.txt");
    rename("temp.txt", "Veiculos.txt");
    printf("\n%d veiculo(s) deletado(s)!\n", deletados);
}

// FUNÇÕES CLIENTES
void CadastrarCliente(){
    struct Cliente cliente;
    struct Endereco endereco;

    printf("ID do cliente: ");
    scanf("%9s", cliente.id);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    if(BuscaID(cliente.id, "Clientes.txt") != 0){
        printf("\nEsse ID ja existe\n");
        return;
    }

    printf("Nome completo do cliente: ");
    scanf(" %49[^\n]", cliente.nome);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }
    
    printf("\nEndereco:\nEstado: ");
    scanf(" %19[^\n]", endereco.estado);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    printf("Cidade: ");
    scanf(" %49[^\n]", endereco.cidade);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    printf("Bairro: ");
    scanf(" %49[^\n]", endereco.bairro);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }
    printf("Rua/Avenida: ");
    scanf(" %49[^\n]", endereco.rua);
    if (limpaBuffer()) {
        printf("\nEntrada invalida. Processo cancelado\n");
        return;
    }

    printf("Numero: ");
    while (scanf("%d", &endereco.numero) != 1){
        printf("\nEntrada invalida. Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    
    printf("\n[1: economico]\n[2: padrao]\n[3: premium]\nTipo de servico: ");
    while (scanf("%d", &cliente.servico) != 1){
        printf("\nEntrada invalida. Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    switch (cliente.servico){
        case 1: case 2: case 3: break;
        default: printf("\nServico invalido\n");
            return;
    }
    
    FILE *arquivo = fopen("Clientes.txt", "a");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo\n");
        return;
    }

    fprintf(arquivo, "%s|%s|%s|%s|%s|%s|%d|%d\n",
        cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, endereco.numero, cliente.servico);
    fclose(arquivo);

    printf("\nCliente cadastrado!\n");
}

void VisualzarCliente(char IdPesquisado[]){
    FILE *arquivo = fopen("Clientes.txt", "r");
    if(arquivo == NULL){
        printf("\nNenhum cliente para visualizar\n");
        return;
    }

    struct Endereco endereco;
    struct Cliente cliente;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d",
            cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, &endereco.numero, &cliente.servico);

        if(strcmp(cliente.id, IdPesquisado) == 0){
            printf("\nCliente encontrado:\
                \nID: %s\nNome: %s\
                \nEndereco: %s - %s, bairro %s, %s .%d\
                \nTipo de servico: ",
                cliente.id, cliente.nome, endereco.cidade, endereco.estado, endereco.bairro, endereco.rua, endereco.numero);
            switch (cliente.servico){
                case 1: printf("economico\n");
                    break;
                case 2: printf("padrao\n");
                    break;
                case 3: printf("premium\n");
                    break;
                default: printf("ERRO\n");
                    break;
            }
            fclose(arquivo);
            return;
        }
    }
    printf("\nCliente nao encontrado\n");
    fclose(arquivo);
}

void EditarCliente(char ID[], int escolha){
    FILE *arquivo = fopen("Clientes.txt", "r");
    if(arquivo == NULL){
        printf("\nSem cliente para editar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Endereco endereco;
    struct Cliente cliente;
    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d",
            cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, &endereco.numero, &cliente.servico);
        
        if(strcmp(cliente.id, ID) == 0){
            switch (escolha){
                case 1: printf("Nome completo do cliente: ");
                    scanf(" %49[^\n]", cliente.nome);
                    if (limpaBuffer()) {
                        printf("\nEntrada invalida. Processo cancelado\n");
                        return;
                    }
                    break;

                case 2: printf("\nEndereco:\nEstado: ");
                    scanf(" %19[^\n]", endereco.estado);
                    if (limpaBuffer()) {
                        printf("\nEntrada invalida. Processo cancelado\n");
                        return;
                    }

                    printf("Cidade: ");
                    scanf(" %49[^\n]", endereco.cidade);
                    if (limpaBuffer()) {
                        printf("\nEntrada invalida. Processo cancelado\n");
                        return;
                    }

                    printf("Bairro: ");
                    scanf(" %49[^\n]", endereco.bairro);
                    if (limpaBuffer()) {
                        printf("\nEntrada invalida. Processo cancelado\n");
                        return;
                    }

                    printf("Rua/Avenida: ");
                    scanf(" %49[^\n]", endereco.rua);
                    if (limpaBuffer()) {
                        printf("\nEntrada invalida. Processo cancelado\n");
                        return;
                    }

                    printf("Numero: ");
                    while (scanf("%d", &endereco.numero) != 1){
                        printf("\nEntrada invalida. Digite um numero: ");
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');
                    break;

                case 3: printf("\n[1: economico]\n[2: padrao]\n[3: premium]\nTipo de servico: ");
                    while (scanf("%d", &cliente.servico) != 1){
                        printf("\nEntrada invalida. Digite um numero: ");
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');

                    switch (cliente.servico){
                        case 1: case 2: case 3: break;
                        default: printf("\nServico invalido\n");
                            fclose(arquivo);
                            fclose(temp);
                            remove("temp.txt");
                            return;
                    }
            }
        }

        fprintf(temp, "%s|%s|%s|%s|%s|%s|%d|%d\n",
            cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, endereco.numero, cliente.servico);
    }
    fclose(arquivo);
    fclose(temp);
    remove("Clientes.txt");
    rename("temp.txt", "Clientes.txt");
    printf("\nCliente editado!\n");
}

void DeletarCliente(char ID[][10], int n){
    FILE *arquivo = fopen("Clientes.txt", "r");
    if(arquivo == NULL){
        printf("\nSem cliente para deletar\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario\n");
        fclose(arquivo);
        return;
    }

    struct Endereco endereco;
    struct Cliente cliente;
    char linha[100];
    int deletados = 0;
    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d",
            cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, &endereco.numero, &cliente.servico);
        
        int deletar = 0;
        for(int i = 0; i < n; i++){
            if(strcmp(cliente.id, ID[i]) == 0){
                deletar = 1;
                deletados++;
            }
        }

        if(!deletar){
            fprintf(temp, "%s|%s|%s|%s|%s|%s|%d|%d\n",
                cliente.id, cliente.nome, endereco.estado, endereco.cidade, endereco.bairro, endereco.rua, endereco.numero, cliente.servico);
        }
    }
    fclose(arquivo);
    fclose(temp);
    remove("Clientes.txt");
    rename("temp.txt", "Clientes.txt");
    printf("\n%d cliente(s) deletado(s)!\n", deletados);
}

int main(){
    int escolhaTipo;

    while(escolhaTipo != 6){
        printf("\n1: manipular entregas\
            \n2: manipular funcionarios\
            \n3: manipular veiculos\
            \n4: manipular clientes\
            \n5: visualizar relatorio\
            \n6: sair\
            \n\nO que deseja fazer: ");
        while (scanf("%d", &escolhaTipo) != 1){
            printf("\nEntrada invalida. Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        int escolhaManipulacao = 0;
        while (escolhaTipo == 1 && escolhaManipulacao != 6){
            printf("\n1: cadastrar entrega\
                \n2: visualizar entrega\
                \n3: editar entrega\
                \n4: deletar entrega\
                \n5: concluir entrega\
                \n6: voltar\
                \n\nO que deseja fazer: ");
            while (scanf("%d", &escolhaManipulacao) != 1){
                printf("\nEntrada invalida. Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            if(escolhaManipulacao == 1)
                CadastrarEntrega();
            else if(escolhaManipulacao == 2){
                char idVisualizar[10];
                if(TotalCadastros("Entregas.txt") == 0){
                    printf("\nNenhuma entrega encontrada\n");
                    continue;
                }
                VisualizarIDs("Entregas.txt");
                printf("\nID da entrega que deseja visualizar: ");
                scanf("%9s", idVisualizar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
                VisualizarEntrega(idVisualizar);
            }
            else if(escolhaManipulacao == 3){
                char idEditar[10];
                if(TotalCadastros("Entregas.txt") == 0){
                    printf("\nNenhuma entrega encontrada\n");
                    continue;
                }
                VisualizarIDs("Entregas.txt");
                printf("\nID da entrega que deseja editar: ");
                scanf("%9s", idEditar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
            
                if(BuscaID(idEditar, "Relatorio.txt") == 1){
                    printf("\nEntrega ja realizada\n");
                    continue;
                }

                if(BuscaID(idEditar, "Entregas.txt") != 1){
                    printf("\nEntrega nao encontrada\n");
                    continue;
                }

                VisualizarEntrega(idEditar);

                int escolha;
                printf("\n1: origem\
                    \n2: destino\
                    \n3: tempo estimado\
                    \n0: cancelar\
                    \n\nDado que deseja editar: ");
                while (scanf("%d", &escolha) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
            
                EditarEntrega(idEditar, escolha);
            }
            else if(escolhaManipulacao == 4){
                int n, total = TotalCadastros("Entregas.txt");
                if(TotalCadastros("Entregas.txt") == 0){
                    printf("\nNenhuma entrega encontrada\n");
                    continue;
                }

                printf("\nTotal de entregas: %d", total);
                VisualizarIDs("Entregas.txt");
                printf("\nNumero de entregas que deseja deletar: ");
                while (scanf("%d", &n) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                if(total == n){
                    FILE *arq = fopen("Entregas.txt", "w");
                    if(arq == NULL){
                        printf("Erro ao abrir o arquivo\n");
                    }
                    fclose(arq);
                    printf("Entrega(s) deletada(s)!\n");
                    continue;
                }else if(total < n){
                    printf("Erro: o numero excede o total de entregas\n");
                    continue;
                }

                if(n == 0){
                    printf("\nNenhuma entrega deletada\n");
                    continue;
                }
            
                char (*IDs)[10] = malloc(n * sizeof(char[10]));
                if(IDs == NULL){
                    printf("Erro ao alocar memoria\n");
                    continue;
                }
                printf("Digite o(s) ID(s): ");
                for(int i = 0; i < n; i++){
                    scanf("%9s", IDs[i]);
                    while (getchar() != '\n');
                }
                DeletarEntrega(IDs, n);
                free(IDs);
            }
            else if(escolhaManipulacao == 5){
                char id[10];
                if(TotalCadastros("Entregas.txt") == 0){
                    printf("\nNenhuma entrega encontrada\n");
                    continue;
                }
                VisualizarIDs("Entregas.txt");
                printf("Digite o ID da entrega: ");
                scanf("%9s", id);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
                if(BuscaID(id, "Entregas.txt") != 1){
                    printf("Entrega nao encontrada\n");
                    continue;
                }
                RealizarEntrega(id);
            }
            else if(escolhaManipulacao != 6)
                printf("Escolha invalida.\n");
        }

        while (escolhaTipo == 2 && escolhaManipulacao != 5){
            printf("\n1: cadastrar funcionario\
                \n2: visualizar funcionario\
                \n3: editar funcionario\
                \n4: deletar funcionario\
                \n5: voltar\
                \n\nO que deseja fazer: ");
            while (scanf("%d", &escolhaManipulacao) != 1){
                printf("\nEntrada invalida. Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            if(escolhaManipulacao == 1){
                CadastrarFuncionario();
            }else if(escolhaManipulacao == 2){
                char idVisualizar[10];
                if(TotalCadastros("Funcionarios.txt") == 0){
                    printf("\nNenhum funcionario encontrado\n");
                    continue;
                }
                VisualizarIDs("Funcionarios.txt");
                printf("\nID do funcionario que deseja visualizar: ");
                scanf("%9s", idVisualizar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
                VisualizarFuncionario(idVisualizar);
            }else if(escolhaManipulacao == 3){
                char idEditar[10];
                if(TotalCadastros("Funcionarios.txt") == 0){
                    printf("\nNenhum funcionario encontrado\n");
                    continue;
                }
                VisualizarIDs("Funcionarios.txt");
                printf("\nID do funcionario que deseja editar: ");
                scanf("%9s", idEditar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
            
                if(BuscaID(idEditar, "Funcionarios.txt") != 1){
                    printf("Funcionario nao encontrado\n");
                    continue;
                }

                EditarFuncionario(idEditar);
            }else if(escolhaManipulacao == 4){
                int n, total = TotalCadastros("Funcionarios.txt");
                if(TotalCadastros("Funcionarios.txt") == 0){
                    printf("\nNenhum funcionario encontrado\n");
                    continue;
                }

                printf("\nTotal de funcionarios: %d\n", total);
                VisualizarIDs("Funcionarios.txt");
                printf("Numero de funcionarios que deseja deletar: ");
                while (scanf("%d", &n) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                if(total == n){
                    FILE *arq = fopen("Funcionarios.txt", "w");
                    if(arq == NULL){
                        printf("Erro ao abrir o arquivo\n");
                    }
                    fclose(arq);
                    printf("Funcionario(s) deletado(s)!\n");
                    continue;
                }else if(total < n){
                    printf("Erro: o numero excede o total de funcionarios\n");
                    continue;
                }
                
                if(n == 0){
                    printf("\nNenhum funcionario deletado\n");
                    continue;
                }
            
                char (*IDs)[10] = malloc(n * sizeof(char[10]));
                if(IDs == NULL){
                    printf("\nErro ao alocar memoria\n");
                    continue;
                }
                printf("Digite o(s) ID(s): ");
                for(int i = 0; i < n; i++){
                    scanf("%9s", IDs[i]);
                    while (getchar() != '\n');
                }
                DeletarFuncionario(IDs, n);
                free(IDs);
            }else if(escolhaManipulacao != 5){
                printf("Escolha invalida\n");
            }
        }
        
        while (escolhaTipo == 3 && escolhaManipulacao != 5){
            printf("\n1: cadastrar veiculo\
                \n2: visualizar veiculo\
                \n3: editar veiculo\
                \n4: deletar veiculo\
                \n5: voltar\
                \n\nO que deseja fazer: ");
            while (scanf("%d", &escolhaManipulacao) != 1){
                printf("\nEntrada invalida. Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            if(escolhaManipulacao == 1){
                CadastrarVeiculo();
            }else if(escolhaManipulacao == 2){
                char idVisualizar[10];
                if(TotalCadastros("Veiculos.txt") == 0){
                    printf("\nNenhum veiculo encontrado\n");
                    continue;
                }
                VisualizarIDs("Veiculos.txt");
                printf("\nID do veiculo que deseja visualizar: ");
                scanf("%9s", idVisualizar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
                VisualizarVeiculo(idVisualizar);
            }else if(escolhaManipulacao == 3){
                char idEditar[10];
                if(TotalCadastros("Veiculos.txt") == 0){
                    printf("\nNenhum veiculo encontrado\n");
                    continue;
                }
                VisualizarIDs("Veiculos.txt");
                printf("\nID do veiculo que deseja editar: ");
                scanf("%9s", idEditar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
            
                if(BuscaID(idEditar, "Veiculos.txt") != 1){
                    printf("\nVeiculo nao encontrada\n");
                    continue;
                }

                VisualizarVeiculo(idEditar);

                int escolha;
                printf("\n1: tipo\
                    \n2: capacidade\
                    \n3: status\
                    \n0: cancelar\
                    \n\nDado que deseja editar: ");
                while (scanf("%d", &escolha) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
            
                EditarVeiculo(idEditar, escolha);
            }else if(escolhaManipulacao == 4){
                int n, total = TotalCadastros("Veiculos.txt");
                if(TotalCadastros("Veiculos.txt") == 0){
                    printf("\nNenhum veiculo encontrado\n");
                    continue;
                }

                printf("\nTotal de veiculos: %d\n", total);
                VisualizarIDs("Veiculos.txt");
                printf("Numero de veiculos que deseja deletar: ");
                while (scanf("%d", &n) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                if(total == n){
                    FILE *arq = fopen("Veiculos.txt", "w");
                    if(arq == NULL){
                        printf("Erro ao abrir o arquivo\n");
                    }
                    fclose(arq);
                    printf("Veiculo(s) deletado(s)!\n");
                    continue;
                }else if(total < n){
                    printf("Erro: o numero excede o total de veiculos\n");
                    continue;
                }
                
                if(n == 0){
                    printf("\nNenhum veiculo deletado\n");
                    continue;
                }
            
                char (*IDs)[10] = malloc(n * sizeof(char[10]));
                if(IDs == NULL){
                    printf("Erro ao alocar memoria\n");
                    continue;
                }
                printf("Digite o(s) ID(s): ");
                for(int i = 0; i < n; i++){
                    scanf("%9s", IDs[i]);
                    while (getchar() != '\n');
                }
                DeletarVeiculo(IDs, n);
                free(IDs);
            }else if(escolhaManipulacao != 5){
                printf("Escolha invalida\n");
            }
        }
        
        while (escolhaTipo == 4 && escolhaManipulacao != 5){
            printf("\n1: cadastrar cliente\
                \n2: visualizar cliente\
                \n3: editar cliente\
                \n4: deletar cliente\
                \n5: voltar\
                \n\nO que deseja fazer: ");
            while (scanf("%d", &escolhaManipulacao) != 1){
                printf("\nEntrada invalida. Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            if(escolhaManipulacao == 1){
                CadastrarCliente();
            }else if(escolhaManipulacao == 2){
                char idVisualizar[10];
                if(TotalCadastros("Clientes.txt") == 0){
                    printf("\nNenhum cliente encontrado\n");
                    continue;
                }
                VisualizarIDs("Clientes.txt");
                printf("\nID do cliente que deseja visualizar: ");
                scanf("%9s", idVisualizar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
                VisualzarCliente(idVisualizar);
            }else if(escolhaManipulacao == 3){
                char idEditar[10];
                if(TotalCadastros("Clientes.txt") == 0){
                    printf("\nNenhum cliente encontrado\n");
                    continue;
                }
                VisualizarIDs("Clientes.txt");
                printf("\nID do cliente que deseja editar: ");
                scanf("%9s", idEditar);
                if (limpaBuffer()) {
                    printf("\nEntrada invalida. Processo cancelado\n");
                    continue;
                }
            
                if(BuscaID(idEditar, "Clientes.txt") != 1){
                    printf("\nCliente nao encontrado\n");
                    continue;
                }

                VisualzarCliente(idEditar);

                int escolha;
                printf("\n1: nome\
                    \n2: endereco\
                    \n3: servico\
                    \n0: cancelar\
                    \n\nDado que deseja editar: ");
                while (scanf("%d", &escolha) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
            
                EditarCliente(idEditar, escolha);
            }else if(escolhaManipulacao == 4){
                int n, total = TotalCadastros("Clientes.txt");
                if(TotalCadastros("Clientes.txt") == 0){
                    printf("\nNenhum cliente encontrado\n");
                    continue;
                }

                printf("\nTotal de clientes: %d\n", total);
                VisualizarIDs("Clientes.txt");
                printf("Numero de clientes que deseja deletar: ");
                while (scanf("%d", &n) != 1){
                    printf("\nEntrada invalida. Digite um numero: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                if(total == n){
                    FILE *arq = fopen("Clientes.txt", "w");
                    if(arq == NULL){
                        printf("Erro ao abrir o arquivo\n");
                    }
                    fclose(arq);
                    printf("Cliente(s) deletado(s)!\n");
                    continue;
                }else if(total < n){
                    printf("Erro: o numero excede o total de clientes\n");
                    continue;
                }
                
                if(n == 0){
                    printf("\nNenhum cliente deletado\n");
                    continue;
                }
            
                char (*IDs)[10] = malloc(n * sizeof(char[10]));
                if(IDs == NULL){
                    printf("Erro ao alocar memoria\n");
                    continue;
                }
                printf("Digite o(s) ID(s): ");
                for(int i = 0; i < n; i++){
                    scanf("%9s", IDs[i]);
                    while (getchar() != '\n');
                }
                DeletarCliente(IDs, n);
                free(IDs);
            }else if(escolhaManipulacao != 5){
                printf("Escolha invalida\n");
            }
        }
        if(escolhaTipo == 5){
            char idVisualizar[10];
            if(TotalCadastros("Relatorio.txt") == 0){
                printf("\nNenhum relatorio encontrado\n");
                continue;
            }
            VisualizarIDs("Relatorio.txt");
            printf("\nID da entrega concluida: ");
            scanf("%9s", idVisualizar);
            if (limpaBuffer()) {
                printf("\nEntrada invalida. Processo cancelado\n");
                continue;
            }
            VisualizarRelatorio(idVisualizar);
        }
    }
    return 0;
}