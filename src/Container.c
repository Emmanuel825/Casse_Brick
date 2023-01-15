/*
 * Container.c
 *
 *  Created on: 24 nov. 2022
 *      Author: emmanuel
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include "Container.h"
typedef struct s_node{
	struct s_node *pPrev;
	struct s_node *pNext;
	void *pElem;
}t_node;

t_node *NodeNew(t_node *pPrev, t_node *pNext, void* pElem){
	t_node *pNewNode=(t_node*)malloc(sizeof(t_node));
	pNewNode->pPrev=pPrev;
	pNewNode->pNext=pNext;
	pNewNode->pElem=pElem;
	if(pNewNode->pPrev)pPrev->pNext=pNewNode;
	if(pNewNode->pNext)pNext->pPrev=pNewNode;
	return pNewNode;
}

t_node *NodeDel(t_node *pNode, t_ptfvV DeleteFunc){
	t_node *pNewNext=pNode->pNext;
	if(DeleteFunc)DeleteFunc(pNode->pElem);
	else free(pNode->pElem);
	if(pNode->pPrev)pNode->pPrev->pNext=pNode->pNext;
	if(pNode->pNext)pNode->pNext->pPrev=pNode->pPrev;
	free(pNode);
	pNode=NULL;
	return pNewNext;
}

/****************************Container Part**********************************/

struct s_container {
	t_node 	*pTail;
	t_node 	*pHead;
	t_ptfvV	pDeleteFunc;
	int nbElem;
};

t_container *ContainerNew(t_ptfvV pDeleteFunc){
	t_container *pContainer=(t_container*)malloc(sizeof(t_container));
	pContainer->pTail=pContainer->pHead=NULL;
	pContainer->nbElem=0;
	pContainer->pDeleteFunc=pDeleteFunc;
	return pContainer;
}

void ContainerPushfront(t_container *pContainer, void*pElem){
	if(pContainer->nbElem==0){
		assert((pContainer->pTail==NULL)&&(pContainer->pHead==NULL));
		pContainer->pTail=pContainer->pHead=NodeNew(NULL, NULL, pElem);
	}
	else{
		pContainer->pHead=NodeNew(pContainer->pHead, NULL, pElem);

	}
	pContainer->nbElem++;
	assert(pContainer->pHead->pElem==pElem);
}

void ContainerParse(t_container *pContainer, t_ptfvVV ParseFunc, void *param){
	t_node *pParse=pContainer->pTail;
	while(pParse!=NULL){
		ParseFunc(pParse->pElem, param);
		pParse=pParse->pNext;
	}
}

void ContainerDel(t_container *pContainer){
	while(pContainer->nbElem){
		pContainer->pTail=NodeDel(pContainer->pTail, pContainer->pDeleteFunc);
		pContainer->nbElem--;
	}
}



void* ContainerGetElem(t_container *pContainer){
	t_node *pNode=pContainer->pTail;
	return pNode->pElem;
}

int ContainerGetNbElem(t_container *pContainer){
	return pContainer->nbElem;
}

//Exemple Casse-Brique : container source = mobile, container destination = briques
void ContainerIntersect(t_container *pContainerSrc, t_container *pContainerDst, t_ptfiVV IntersectFunc){
	t_node *pSrc=pContainerSrc->pTail;
	t_node *pScan=pContainerDst->pTail;
	if(pSrc!=NULL){
		while (pScan!=NULL){
			int n=IntersectFunc(pSrc->pElem, pScan->pElem);
			if(n!=0){
				if(pScan->pPrev==NULL){

					assert(pScan==pContainerDst->pTail);
					pContainerDst->pTail=pContainerDst->pTail->pNext;
				}
				else if(pScan->pNext==NULL){
					assert(pScan==pContainerDst->pHead);
					pContainerDst->pHead=pContainerDst->pHead->pPrev;
				}
				pContainerDst->nbElem--;
				NodeDel(pScan, pContainerDst->pDeleteFunc);
				if(pContainerDst->nbElem==0){
					pContainerDst->pHead=pContainerDst->pTail=NULL;
				}
				pScan=NULL;
				n=0;
			}
			if(pScan!=NULL)pScan=pScan->pNext;
		}
	}
}
