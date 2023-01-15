/*
 * Container.h
 *
 *  Created on: 24 nov. 2022
 *      Author: emmanuel
 */


typedef void*(*t_ptfvV)(void*);
typedef void*(*t_ptfvVV)(void*, void*);
typedef int(*t_ptfiVV)(void*, void*);


typedef struct s_container t_container;

t_container *ContainerNew(t_ptfvV pDeleteFunc);
void ContainerPushfront(t_container *pContainer, void*pElem);
void ContainerParse(t_container *pContainer, t_ptfvVV ParseFunc, void *param);
void ContainerDel(t_container *pContainer);
void* ContainerGetElem(t_container *pContainer);
int ContainerGetNbElem(t_container *pContainer);
void ContainerIntersect(t_container *pContainerSrc, t_container *pContainerDst, t_ptfiVV IntersectFunc);
