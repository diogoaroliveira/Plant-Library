/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	int i;
	planta *p;

	if(strlen(nome_cientifico)>MAX_NAME || strlen(ID)>10) return NULL;
	
	p = (planta*) calloc(1, sizeof(planta));
	if (p==NULL) return NULL;

	strcpy(p->ID, ID);
	strcpy(p->nome_cientifico, nome_cientifico);
	p->n_alcunhas=n_alcunhas;
	p->n_sementes=n_sementes;
	
	if(n_alcunhas==0) return p;

	p->alcunhas = (char**) calloc(n_alcunhas, sizeof(char*));
	for(i=0; i<n_alcunhas; i++)
	{
		p->alcunhas[i] = (char*) malloc(strlen(alcunhas[i])+1);
		strcpy(p->alcunhas[i], alcunhas[i]);
	}

	return p;	
}

colecao *colecao_nova(const char *tipo_ordem)
{
	colecao *c;
	c = (colecao*) calloc(1, sizeof(colecao));

	if (c==NULL) return NULL;
	if (strcmp(tipo_ordem, "nome")!=0 && strcmp(tipo_ordem, "ID")!=0) return NULL;

	strcpy(c->tipo_ordem, tipo_ordem);

	return c;	
}

int planta_insere(colecao *c, planta *p)
{
	planta *plant;
	int i, j;
	
	if(c==NULL) return -1;
	if(p==NULL) return -1;

	for(i=0; i<c->tamanho; i++)
	{
		plant = c->plantas[i];
		if(strcmp(plant->ID, p->ID)==0)
		{
			plant->n_sementes += p->n_sementes;
			
			if(plant->n_alcunhas == p->n_alcunhas)	return 1;

			for(j=0; j<plant->n_alcunhas; j++)
			{
				free(plant->alcunhas[j]);				
			}

			plant->n_alcunhas = p->n_alcunhas;
			plant->alcunhas = (char**)realloc(plant->alcunhas, plant->n_alcunhas*sizeof(char*));

			for(j=0; j<plant->n_alcunhas; j++)
			{
				plant->alcunhas[j] = (char*) malloc(strlen(p->alcunhas[j])+1);
				strcpy(plant->alcunhas[j], p->alcunhas[j]);			
			}
			return 1;		
		}
	}

	c->tamanho++;
	c->plantas = (planta**) realloc(c->plantas, c->tamanho*sizeof(planta*));

	c->plantas[c->tamanho-1]=p;
	
	if(strcmp(c->tipo_ordem, "nome"))
	{
		for (i = 1; i < c->tamanho; i++)
		{
			plant = c->plantas[i];
			for (j = i; j > 0 && strcmp(plant->nome_cientifico, c->plantas[j-1]->nome_cientifico) > 0; j--)
			{
				c->plantas[j] = c->plantas[j-1];
			}
			c->plantas[j] = plant;
		}
		return 0;
	}

	if(strcmp(c->tipo_ordem, "id"))
	{
		for (i = 1; i < c->tamanho; i++)
		{
			plant = c->plantas[i];
			for (j = i; j > 0 && strcmp(plant->ID, c->plantas[j-1]->ID) > 0; j--)
			{
				c->plantas[j] = c->plantas[j-1];
			}
			c->plantas[j] = plant;
		}
		return 0;
	}

	return -1;	
}

int colecao_tamanho(colecao *c)
{
	if(c==NULL) return-1;
	return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	return NULL;
}

planta *planta_remove(colecao *c, const char *nomep)
{	
	planta *p;
	int i, j;

	if(c==NULL || strlen(nomep)>MAX_NAME) return NULL;

	for(i=0; i<c->tamanho; i++)
	{
		if(strcmp(nomep, c->plantas[i]->nome_cientifico)==0)
		{
			p=c->plantas[i];
			for(j=i+1; j<c->tamanho; j++)
			{
				c->plantas[j-1]=c->plantas[j];
			}
			free(c->plantas[c->tamanho-1]);
			c->tamanho--;
			// c->plantas = (planta**) realloc(c->plantas, c->tamanho*sizeof(planta*));
			
			return p;
		}
	}
	
	return NULL;
}

int planta_apaga(planta *p)
{
	return -1;
}

int colecao_apaga(colecao *c)
{
	return -1;
}

int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	return NULL;
}

int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	return -1;
}
