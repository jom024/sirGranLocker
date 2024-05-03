#ifndef LOCKERS_H_INCLUDED
#define LOCKERS_H_INCLUDED

#define MAXLOCKERS 10
#define WEIGHTLIMIT 5

typedef struct {
    char studID[9], studName[65], course[5];
}Student;

typedef struct {
    char itemName[33];
    float weight;
}ItemDets;

typedef struct ItemNode {
    ItemDets item;
    struct ItemNode* nextItem;
} ItemNode, *ItemList;

typedef struct{
    Student owner;
    ItemList IL;
    int lockerStat;
    float totWeight; 
} Locker;

void depositItem(Locker* L, char studID[], ItemDets newItem){
    if(strcmp(L->owner.studID, studID) == 0 && L->totWeight + newItem.weight <= WEIGHTLIMIT){
        ItemList temp = (ItemList)malloc(sizeof(ItemNode));
        if(temp!=NULL){
            temp->item = newItem;
            ItemList* trav;

            for(trav = &(L->IL); *trav != NULL && (*trav)->item.weight < newItem.weight; trav = &(*trav)->nextItem);
            temp->nextItem = *trav;
            *trav = temp;
            L->totWeight += newItem.weight;
        }
    }
}

ItemList getHeavyItems(Locker* L, float limit)
{
    ItemList heavyItems = NULL, temp, *trav;

    for(trav = &(L->IL); *trav!= NULL; ){
        if((*trav)->item.weight < limit){
            trav = &(*trav)->nextItem;
        } else {
            //remove
            temp = *trav;
            *trav = temp->nextItem;
            //store
            temp->nextItem = heavyItems;
            heavyItems = temp;            
        }
    }

    return heavyItems;
}

void displayItemList(ItemList L)
{
	ItemList trav;
	float totWeight = 0;
	for(trav = L; trav != NULL; trav = trav->nextItem){
		printf("Item: %-15s | Weight: %-15.2f\n", trav->item.itemName, trav->item.weight);
        totWeight += trav->item.weight;
	}
	printf("\nTotal Weight: %.2fkg\n\n", totWeight);
}

#endif