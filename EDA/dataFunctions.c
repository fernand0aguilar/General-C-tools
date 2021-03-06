#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "headers.h"

TreeUF *insert_uf(TreeUF *root, TreeUF *new){
	if(root == NULL)
		return new;
	else{
		if(new -> total <= root -> total)
			root -> left = insert_uf(root -> left, new);
		else
			root -> right = insert_uf(root -> right, new);
	}
	return root;
}

TreeUF *createTreeUF(FILE *fp, TreeUF* root){
	char aux[100],resposta[3];
	char *lixo, *totalAux, *ufAux;
	int line = 1,i;
	printf("De qual estado voce quer ver o Relatorio\n");
	getchar();
	scanf("%s", resposta);
	rewind(fp);
	while(fgets(aux,100,fp)){
		ufAux = strtok(aux, ";");
		if(strcmp(resposta, ufAux) == 0){
			TreeUF *new;
			new = (TreeUF*)malloc(sizeof(TreeUF));
			new -> right = NULL;
			new -> left = NULL;
			new -> linha = line;
			for(i = 0; i < 9 ; i++)
				lixo = strtok(NULL, ";");
			totalAux = strtok(NULL, ";");
			new -> total = atoi(totalAux);
			root = insert_uf(root, new);
		}
		line++;
	}

	return root;
}

void print_ufTree(TreeUF *root, FILE *fp){
	int i;
	char aux[100];
	if(root == NULL)
		return;
	else{
		print_ufTree(root -> right,fp);
		rewind(fp);
		for(i = 1; i<=root->linha;i++)
			fgets(aux,100,fp);
		printf("%s\n", aux);
		print_ufTree(root -> left,fp);
	}
}

void free_ufTree(TreeUF **root){
	if(*root != NULL){
		free_ufTree(&((*root)->left));
		free_ufTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}


TreeMun *insert_mun(TreeMun *root, TreeMun *new){
	if(root == NULL)
		return new;
	else{
		int helper;
		helper = strcmp(new -> municipio, root -> municipio);
		if(helper <= 0)
			root -> left = insert_mun(root->left, new);
		else
			root -> right = insert_mun(root->right, new);
	}
	return root;
}

TreeCD *insert_cd(TreeCD *root, TreeCD *new){
	if(root == NULL)
		return new;
	else{
		if(new -> cd <= root -> cd)
			root -> left = insert_cd(root->left, new);
		else
			root -> right = insert_cd(root->right, new);
	}
	return root;
}


TreeTotal *insert_total(TreeTotal *root, TreeTotal *new){
	if(root == NULL)
		return new;
	else{
		if(new -> total <= root -> total)
			root -> left = insert_total(root->left, new);
		else
			root -> right = insert_total(root->right, new);
	}
	return root;
}

void createTree(char *lineContent, int line, TreeMun **rootMun, TreeCD **rootCD, TreeTotal **rootTotal){
	int column = 1;
	char *auxCharacters;
	TreeMun *newMun;
	TreeCD *newCD;
	TreeTotal *newTotal;

	auxCharacters = strtok(lineContent, ";\n");
	while(auxCharacters != NULL){
		auxCharacters = strtok(NULL, ";\n");

		if(column == 1){
			newMun = (TreeMun*)malloc(sizeof(TreeMun));
			newMun -> left = NULL;
			newMun -> right = NULL;
			newMun -> linha = line;
			strcpy(newMun -> municipio, auxCharacters);
			*rootMun = insert_mun(*rootMun, newMun);
		}
		else if(column == 2){
			newCD = (TreeCD*)malloc(sizeof(TreeCD));
			newCD ->left = NULL;
			newCD -> right = NULL;
			newCD -> linha = line;
			newCD -> cd = atoi(auxCharacters);
			*rootCD = insert_cd(*rootCD, newCD);
		}
		else if(column == 10){
			newTotal = (TreeTotal*)malloc(sizeof(TreeTotal));
			newTotal -> left = NULL;
			newTotal -> right = NULL;
			newTotal -> linha = line;
			newTotal -> total = atoi(auxCharacters);
			*rootTotal = insert_total(*rootTotal, newTotal);
		}
		column++;
	}
}

void print_TreeMun(TreeMun *root, FILE *fp){
	int i;
	char aux[100];
	if(root == NULL)
		return;
	else{
		print_TreeMun(root -> left,fp);
		rewind(fp);
		for(i=0; i<root->linha; i++)
			fgets(aux,100,fp);
		printf("%s\n", aux);
		print_TreeMun(root -> right,fp);
	}
}

void print_TreeCD(TreeCD *root, FILE *fp){
	char aux[200];
	int i;
	if(root == NULL)
		return;
	else{
		print_TreeCD(root -> left,fp);
		rewind(fp);
		for(i=0;i<root->linha;i++)
			fgets(aux,200,fp);
		printf("%s\n", aux);
		print_TreeCD(root -> right, fp);
	}
}


void print_TreeTotal(TreeTotal *root, FILE *fp){
	char aux[200];
	int i;
	if(root == NULL)
		return;
	else{

		print_TreeTotal(root -> left, fp);
		rewind(fp);
		for(i=0;i<root->linha;i++)
			fgets(aux,200,fp);
		printf("%s\n", aux);
		print_TreeTotal(root -> right,fp);
	}
}

void free_TreeMun(TreeMun **root){
	if(*root != NULL){
		free_TreeMun(&((*root)->left));
		free_TreeMun(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

void free_TreeCD(TreeCD **root){
	if(*root != NULL){
		free_TreeCD(&((*root)->left));
		free_TreeCD(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

void free_TreeTotal(TreeTotal **root){
	if(*root != NULL){
		free_TreeTotal(&((*root)->left));
		free_TreeTotal(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

// IMPORTAR DADOS

void import_data(FILE *fp, TreeMun **rootMun, TreeCD **rootCD, TreeTotal **rootTotal){
	int line = 1;
	char auxLine[100];
	if(fp == NULL){
		printf("Arquivo nao encontrado\n");
		exit(0);
	}
	else{
		while(fgets(auxLine, 100 , fp)){
			createTree(auxLine, line, &(*rootMun), &(*rootCD), &(*rootTotal));
			line++;
		}
	}
	rewind(fp);
}
