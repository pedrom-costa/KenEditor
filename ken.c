#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINHAS 100

enum{
        CMD_INVALIDO = 0,
        CMD_ADD, // 1
        CMD_DEL, // 2
        CMD_LIST, // 3
        CMD_SAVE, // 4
        CMD_EXIT, // 5
    };

void limpador_string(char *str);
int get_command();

int main(int argc, char *agrv[]){

    if(argc != 2){
        printf("Uso correto: %s <nome_do_arquivo>\n", agrv[0]);
        return 1;
    }

    int NUM_LINHAS = 00;
    char LINHA_TEMPORARIA[256];
    char *EDITOR[MAX_LINHAS];
    FILE *ARQUIVO;
    
    ARQUIVO = fopen(agrv[1], "r");

    if(ARQUIVO == NULL){
        printf("Arquivo %s não encontrado. Criando arquivo...\n", agrv[1]);
    
    } else {
        printf("Carregando '%s'...\n", agrv[1]);
    while(fgets(LINHA_TEMPORARIA, sizeof(LINHA_TEMPORARIA), ARQUIVO) != NULL && NUM_LINHAS < MAX_LINHAS){

        limpador_string(LINHA_TEMPORARIA);

        EDITOR[NUM_LINHAS] = malloc(strlen(LINHA_TEMPORARIA) + 1);
        if(EDITOR[NUM_LINHAS] == NULL){
            perror("Falha ao alocar memória");
            return 1;

        }
        strcpy(EDITOR[NUM_LINHAS], LINHA_TEMPORARIA);

        NUM_LINHAS ++;

    }
    fclose(ARQUIVO);
    printf("%d linhas carregadas.\n", NUM_LINHAS);

    }

    while(1){

    int command = get_command();
        if(command == CMD_ADD){
            if(NUM_LINHAS < MAX_LINHAS){
                printf("Digite o que você deseja salvar no arquivo\n");
                printf("> ");

                fgets(LINHA_TEMPORARIA, sizeof(LINHA_TEMPORARIA), stdin);
                limpador_string(LINHA_TEMPORARIA);
                // "+ 1" devido ao /n;
                EDITOR[NUM_LINHAS] = malloc(strlen(LINHA_TEMPORARIA) + 1);

                if(EDITOR[NUM_LINHAS] == NULL){
                    perror("Erro de alocação de memória.\n");
                    return 1;
                } else {

                strcpy(EDITOR[NUM_LINHAS], LINHA_TEMPORARIA);
                NUM_LINHAS++;
                printf("SUCCESSO!");
                }
            }


        } else if(command == CMD_DEL){
                if(NUM_LINHAS == 0){
                    printf("O arquivo já está vazio.\n");
                } else {
                    char buffer_para_numero[100]; 
                    int numero_linha_usuario = -1;

                    printf("Digite o número da linha a ser apagada (1 a %d): ", NUM_LINHAS);

                    if (fgets(buffer_para_numero, sizeof(buffer_para_numero), stdin) != NULL) {
                        // Tenta extrair o número da string lida
                        if (sscanf(buffer_para_numero, "%d", &numero_linha_usuario) != 1) {
                        numero_linha_usuario = -1; // Falha na conversão, marca como erro
            }
        }   

        if (numero_linha_usuario == -1) {
            printf("Entrada inválida. Por favor, digite um número.\n");
        } else {

            // Converte a entrada do usuário para o índice real do array
            int indice_real = numero_linha_usuario - 1;

                if(indice_real >= 0 && indice_real < NUM_LINHAS){
                    printf("REMOVENDO LINHA %d: %s", numero_linha_usuario, EDITOR[indice_real]);
                    free(EDITOR[indice_real]);
                    for(int i = indice_real; i < NUM_LINHAS - 1; i++){
                        EDITOR[i] = EDITOR[i + 1];
                    }
                    NUM_LINHAS --;
                    printf("SUCCESO!");
                    
                } else {
                    printf("ERRO! LINHA %d INEXISTENTE.\n", numero_linha_usuario);
                }
            
                }
            }
            } else if(command == CMD_LIST){
                if(NUM_LINHAS == 0){
                    printf("O arquivo está vazio.\n");
                } else {

                    for(int i = 0; i < NUM_LINHAS; i++){
                        printf("%d - %s", i + 1, EDITOR[i]);
                    }

                }



        } else if(command == CMD_SAVE){
            ARQUIVO = fopen(agrv[1], "w");
            if(ARQUIVO != NULL){
                for (int i = 0; i < NUM_LINHAS - 1; i++){
                    fprintf(ARQUIVO, "%s", EDITOR[i]);
                }
                fclose(ARQUIVO);
                printf("ARQUIVO SALVO COM SUCESSO!\n");
            } else {
                printf("ERRO! Não foi possível salvar o arquivo.\n");
            }
            
        
        
        }else if(command == CMD_EXIT){
            printf("Saindo... Até logo.\n");
            break;
        } else {

            printf("Comando inválido.\n");

        }

    }
}
    





void limpador_string(char *str){
    if (str == NULL) return;

    size_t posicao_newline = strspn(str, "\n");
    if(str[posicao_newline] == '\n'){
        str[posicao_newline] = '\0';
    }
}

int get_command(){
    char buffer_entrada[256];
    char comando[100];

    printf("\n------- EDITOR KEN -------\n");
    printf("Comandos: add, del, list, save, exit\n");
    printf("> ");

    if(fgets(buffer_entrada, sizeof(buffer_entrada), stdin) == NULL){
        return CMD_EXIT;
    }

    if(sscanf(buffer_entrada,"%99s", comando) == 1){
        // Compara o input e o comando "esperado", se for igual (0), parte pro próximo passo;
        if(strcmp(comando, "add") == 0){
            return CMD_ADD;
        } else if(strcmp(comando, "del") == 0){
            return CMD_DEL;
        } else if(strcmp(comando, "list") == 0){
            return CMD_LIST; 
        } else if(strcmp(comando, "save") == 0){
            return CMD_SAVE;
        } else if(strcmp(comando, "exit") == 0){
            return CMD_EXIT;
        }
    }

    return CMD_INVALIDO;

}   