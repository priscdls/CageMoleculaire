#include "structure.h"

/**************************************/
/* LISTE ******************************/
/**************************************/
void LST_init(List_t* l) {
	l->elts = NULL;
	l->size = 0;
}

void LST_addAlloc(List_t* l) {
	int i;

	l->elts = realloc(l->elts, (size(l)+REALLOCSIZE)*sizeof(int));

	for (i=0; i<REALLOCSIZE; i++)
		l->elts[l->size+i] = -1;

	size(l) += REALLOCSIZE;
}

unsigned LST_nbElements(List_t* l) {
	int cpt;

	for (cpt=size(l); cpt>0 && elts(l,cpt-1) == -1; cpt--);

	return cpt;
}

unsigned LST_getIndiceFree(List_t* l) {
	int i;

	for (i=0; i<size(l); i++)
		if (elts(l,i) == -1)
			return i;

	LST_addAlloc(l);
	return i;
}

unsigned LST_getIndice(List_t* l, unsigned id) {
	int i;

	for (i=0; i<size(l) && elts(l,i) != -1; i++)
		if (elts(l,i) == id)
			return i;

	return -1;
}

unsigned LST_check(List_t* l, unsigned id) {

	if (LST_getIndice(l,id) == -1)
		return 0;
	return 1;
}

void LST_addElement(List_t* l, unsigned id) {
	
	int i;
	if (LST_getIndice(l, id) == -1) {
		i = LST_getIndiceFree(l);
		l->elts[i] = id;
	}
}

void LST_removeElement(List_t* l, unsigned id) {

	int i = LST_getIndice(l,id);

	if (i != -1) {
		while (i < size(l)-1 && elts(l,i) != -1) {
			elts(l,i) = elts(l,i+1);
			i++;
		}
		elts(l,i) = -1;
	}
}


List_t* LST_create() {

	List_t* l = malloc(sizeof(List_t));
	LST_init(l);

	return l;
}

List_t* LST_copy(List_t* l) {

	int i;
	List_t* copy = LST_create();

	size(copy) = LST_nbElements(l);
	//size(copy) = size(copy) + REALLOCSIZE - size(copy)%REALLOCSIZE;

	copy->elts = malloc(size(copy)*sizeof(int));

	for (i=0; i<size(copy); i++)
		elts(copy,i) = elts(l,i);

	return copy;
}

List_t* LST_addList(List_t* l1, List_t* l2) {

	int i;

	List_t* out = LST_copy(l1);

	for (i=0; i<size(l2) && elts(l2,i)!=-1; i++)
		LST_addElement(out, elts(l2,i));

	LST_delete(l2);
	LST_delete(l1);
	return out;
}

void LST_delete(List_t* l) {

	free(l->elts);
	free(l);
}

/******************************/

List_p* LST2_init() {
	
	List_p* list = malloc(sizeof(List_p));
	list->premier = NULL;
	
	return list;
}

// Ajout au début
void LST2_addElement(List_p* list, int depart, int arrivee) {
	
	Element* elem = malloc(sizeof(Element));
	
	elem->depart = depart;
	elem->arrivee = arrivee;
	elem->suivant = list->premier;
	
	list->premier = elem;
}

void LST2_removeFirst(List_p* list) {
	
	Element* suppr = list->premier;
	list->premier = list->premier->suivant;
	free(suppr);
}

void LST2_delete(List_p* list) {

	while (list->premier)
	{
		LST2_removeFirst(list);
	}
	free(list);
}

/******************************/

List_m* LSTm_init() {
	
	List_m* list = malloc(sizeof(List_m));
	list->premier = NULL;
	
	return list;
}

// Ajout au début
void LSTm_addElement(List_m* list, Shell_t* moc) {
	
	Elem* elem = malloc(sizeof(Elem));
	
	elem->moc = moc;
	elem->suivant = list->premier;
	
	list->premier = elem;
}

void LSTm_removeFirst(List_m* list) {
	
	Elem* suppr = list->premier;
	list->premier = list->premier->suivant;
	SHL_delete(suppr->moc);
	free(suppr);
}

void LSTm_delete(List_m* list) {

	while (list->premier)
	{
		LSTm_removeFirst(list);
	}
	free(list);
}
