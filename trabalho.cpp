#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct document
{
    int id;
    char conselho[100];
    int ano;
    int numero;
    char tipo[100];
    int vigencia;
    char texto[100];
} t_document;

void getInterface(int codInterface)
{
    /*
    códigos das interfaces
    0 - mostra a interface "Cadastro de Documentos"
    1 - mostra a interface "Documento(s) Cadastrado(s)"
    2 - mostra a interface "Buscar Documento Especifico"
    3 - mostra a interface "Buscar Tipo Especifico"
    5 - mostra a interface "Bem vindo ao Sistema de Controle de DOCS da UFU"
    6 - mostra a interface "Buscar Documento para Revogar"
    */
    if(codInterface==0)
    {
        printf("-----------------------------------------------------\n");
        printf("|             Cadastro de Documento                 |\n");
        printf("-----------------------------------------------------");
    }

    if(codInterface==1)
    {
        printf("-----------------------------------------------------\n");
        printf("|            Documento(s) Cadastrado(s)             |\n");
        printf("-----------------------------------------------------\n");
    }

    if(codInterface==2)
    {
        printf("-----------------------------------------------------\n");
        printf("|            Buscar Documento Especifico            |\n");
        printf("-----------------------------------------------------\n");
    }

    if(codInterface==3)
    {
        printf("-----------------------------------------------------\n");
        printf("|            Buscar Tipo Especifico                 |\n");
        printf("-----------------------------------------------------\n");
    }

    if(codInterface==4)
    {
        printf("-----------------------------------------------------\n");
        printf("|            Resultado(s) encontrado(s)             |\n");
        printf("-----------------------------------------------------\n");
    }

    if(codInterface==5)
    {
        printf("-----------------------------------------------------\n");
        printf("|  Bem vindo ao Sistema de Controle de DOCS da UFU  |\n");
        printf("-----------------------------------------------------\n");
        printf("| 1 - Cadastrar Documento                           |\n");
        printf("| 2 - Mostrar Todos                                 |\n");
        printf("| 3 - Buscar Documento Especifico                   |\n");
        printf("| 4 - Buscar Tipo Especifico                        |\n");
        printf("| 6 - Revogar Documento                             |\n");
        printf("| 9 - Sair                                          |\n");
        printf("-----------------------------------------------------\n");
    }

    if(codInterface==6)
    {
        printf("-----------------------------------------------------\n");
        printf("|          Buscar Documento para Revogar            |\n");
        printf("-----------------------------------------------------\n");
    }
}

void revoga_document(document doc)
{
    system("cls");
    // solicita a tela "Buscar Documento para Revogar" para a função getInterface
    getInterface(6);

    FILE *document_file = fopen("document.bin", "r+b");
    FILE *document_aux = fopen("document_aux.bin", "a+b");
    if(document_file == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)");
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");
        fseek(stdin, 0, SEEK_END);
        return;
    }

    int found_document = 0;
    char tipoDoc[100];
    int idDoc;

    // Coleta os dados a serem buscados
    setbuf(stdin, NULL);
    printf("Digite o tipo do documento: ");
    printf("ATA | PORTARIA | RESOLUCAO\n");
    scanf("%[^\n]s", tipoDoc);
    setbuf(stdin, NULL);
    printf("Digite o ID do documento: ");
    scanf("%d", &idDoc);

    int flag = 0;

    while(fread(&doc, sizeof(document), 1, document_file))
    {

        if(idDoc==doc.id && (strcmp(doc.tipo,tipoDoc)==0))
        {
            doc.vigencia = 2;
            flag = 1;
        }

        doc.id;
        doc.ano;
        doc.numero;
        doc.tipo;
        doc.conselho;
        doc.vigencia;
        doc.texto;


        fseek(stdin, 0, SEEK_END);
        fwrite(&doc, sizeof(doc), 1, document_aux);
    }

    fclose(document_file);
    fclose(document_aux);

    remove("document.bin");
    rename("document_aux.bin","document.bin");

    if (flag == 1) printf("\ndocumento  revogado com sucesso!\n");
    else printf("\ndocumento nao encontrado!\n");
    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");
}

void register_document()
{
    FILE *document_file = fopen("document.bin", "a+b");


    if(document_file == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)!\n");
        exit(1);
    }
    system("cls");
    // solicita a tela "Cadastro de Documentos" para a função getInterface
    getInterface(0);

    int cont_bytes = 0;


    fseek(document_file, 0, SEEK_END);

    cont_bytes = ftell(document_file);

    t_document document;

    if(cont_bytes == 0)
    {

        document.id = 1;
    }
    else
    {
        t_document last_document;


        fseek(document_file, cont_bytes - sizeof(t_document), SEEK_SET);


        fread(&last_document, sizeof(t_document), 1, document_file);


        document.id = last_document.id + 1;
    }

    setbuf(stdin, NULL);

    printf("\nDigite o nome do conselho: ");
    scanf("%[^\n]s", document.conselho);
    setbuf(stdin, NULL);
    printf("\nDigite o tipo do documento: ");
    scanf("%[^\n]s", document.tipo);
    setbuf(stdin, NULL);
    printf("\nDigite o texto do documento: ");
    scanf("%[^\n]s", document.texto);
    setbuf(stdin, NULL);
    printf("\nDigite o ano do documento: ");
    scanf("%d", &document.ano);
    setbuf(stdin, NULL);
    printf("\nDigite o numero do documento: ");
    scanf("%d", &document.numero);
    setbuf(stdin, NULL);
    printf("\nDigite a vigencia do documento(1 - vigente; 2 - invalido): ");
    scanf("%d", &document.vigencia);



    fseek(stdin, 0, SEEK_END);


    fseek(document_file, 0, SEEK_END);

    fwrite(&document, sizeof(t_document), 1, document_file);


    fclose(document_file);

    printf("\ndocument \"%s\" cadastrado com sucesso!\n", document.tipo);
    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");


    fseek(stdin, 0, SEEK_END);
    system("cls");
}

void list_document()
{
    FILE *document_file = fopen("document.bin", "rb");

    if(document_file == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)");
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
        return;
    }

    int found_document = 0;
    t_document document;
    system("cls");

    // solicita a tela "Documento(s) Cadastrado(s) para a função getInterface
    getInterface(1);

    while(1)
    {
        size_t result = fread(&document, sizeof(t_document), 1, document_file);

        if(result == 0)
            break;

        found_document = 1;

        printf("\nID do documento: %d\n", document.id);
        printf("Ano do documento: %d\n", document.ano);
        printf("Numero do documento: %d\n", document.numero);
        printf("Tipo do documento: %s\n", document.tipo);
        printf("Conselho responsavel pela emissao documento: %s\n", document.conselho);
        printf("Vigencia do documento(1 - vigente; 2 - invalido): %d\n", document.vigencia);
        printf("Texto do documento: %s\n", document.texto);
        printf("-----------------------------------------------------\n");

    }

    if(found_document == 0)
        printf("\nNenhum document cadastrado.\n");

    fclose(document_file);

    //printf("\nPressione <Enter> para continuar...\n");
    //scanf("%*c");
    system("pause");
    system("cls");


    fseek(stdin, 0, SEEK_END);
}

void fetch_document(document doc)
{
    // buscar documento específico

    // Mostra a interface
    system("cls");
    // solicita a tela "Buscar Documento Especifico" para a função getInterface
    getInterface(2);

    FILE *document_file = fopen("document.bin", "rb");
    if(document_file == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)");
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");
        fseek(stdin, 0, SEEK_END);
        return;
    }
    char tipoDoc[100];
    int idDoc;

    // Coleta os dados a serem buscados
    setbuf(stdin, NULL);
    printf("Digite o tipo do documento: ");
    printf("ATA | PORTARIA | RESOLUCAO\n");
    scanf("%[^\n]s", tipoDoc);
    setbuf(stdin, NULL);
    printf("Digite o ID do documento: ");
    scanf("%d", &idDoc);

    system("cls");

    // solicita a tela "Resuntado(s) encontrado(s) para a função getInterface
    getInterface(4);

    // Busca os dados no arquivo
    while(fread(&doc, sizeof(document), 1, document_file))
    {
        if(idDoc==doc.id && (strcmp(doc.tipo,tipoDoc)==0))
        {
            printf("Id: %d\n", doc.id);
            printf("Ano: %d\n", doc.ano);
            printf("Numero: %d\n", doc.numero);
            printf("Tipo: %s\n", doc.tipo);
            printf("Conselho: %s\n", doc.conselho);
            printf("Vigencia: %d\n", doc.vigencia);
            printf("Texto: %s\n", doc.texto);
            printf("-----------------------------------------------------\n");
        }
    }
    fclose(document_file);
    system("pause");
    system("cls");
}

void fetch_type(document doc)
{
    // buscar tipos de documentos

    // Mostra a interface
    system("cls");

    // solicita a tela "Buscar Tipo Especifico" para a função getInterface
    getInterface(3);

    FILE *document_file = fopen("document.bin", "rb");
    if(document_file == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)");
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");
        fseek(stdin, 0, SEEK_END);
        return;
    }
    char tipoDoc[100];

    // Coleta os dados a serem buscados
    setbuf(stdin, NULL);
    printf("Digite o tipo do documento: ");
    printf("ATA | PORTARIA | RESOLUCAO\n");
    scanf("%[^\n]s", tipoDoc);

    system("cls");

    // solicita a tela "Resuntado(s) encontrado(s) para a função getInterface
    getInterface(4);

    // Busca os dados no arquivo
    while(fread(&doc, sizeof(document), 1, document_file))
    {
        if(strcmp(doc.tipo,tipoDoc)==0)
        {
            printf("Id: %d\n", doc.id);
            printf("Ano: %d\n", doc.ano);
            printf("Numero: %d\n", doc.numero);
            printf("Tipo: %s\n", doc.tipo);
            printf("Conselho: %s\n", doc.conselho);
            printf("Vigencia: %d\n", doc.vigencia);
            printf("Texto: %s\n", doc.texto);
            printf("-----------------------------------------------------\n");
        }
    }
    fclose(document_file);
    system("pause");
    system("cls");
}

void menu()
{
    document doc;
    int opcao;
    struct document P[30];
    int indiceCadastro = 0;
    while(1)
    {
        system("cls");
        getInterface(5);
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1) register_document();
        if(opcao == 2) list_document();
        if(opcao == 3) fetch_document(doc);
        if(opcao == 4) fetch_type(doc);
        if(opcao == 6) revoga_document(doc);
        if(opcao == 9) return;
    }
}

int main()
{
    menu();
}

/*
    Funções do trabalho:
    ok Cadastra Ata/Resolução/Portaria
    - Alterar Ata/Resolução/Portaria
    ok Buscar Todos
    ok Buscar Tipo Específico
    ok Buscar Documento Específico
    ok Revogar
    - Cadastrar Conselho
    - Revogar Conselho
*/
