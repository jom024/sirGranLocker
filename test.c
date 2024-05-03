#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLOCKERS 10
#define WEIGHTLIMIT 5

typedef struct{
	char studID[9];		
	char studName[65];  
	char course[5];		
}Student;

typedef struct{
	char itemName[33];	 
	float weight;	
}ItemDets;

typedef struct ItemNode{
	ItemDets item;
	struct ItemNode* nextItem;
}ItemNode, *ItemList;

typedef struct{
	Student owner;
	ItemList IL;
	int lockerStat; 
	float totWeight;
}Locker;

void depositItem(Locker* L, char studID[], ItemDets newItem) {
    if(strcmp(L->owner.studID, studID) == 0 && (L->totWeight + newItem.weight) <= WEIGHTLIMIT){
        ItemList temp = malloc(sizeof(ItemNode));
        if(temp != NULL) {
            temp->item = newItem;
            ItemList *trav;
            // trav = &(L->IL);
            // while(*trav != NULL && (*trav)->item.weight < newItem.weight){
            //     trav = &(*trav)->nextItem;
            // }
            for(trav = &(L->IL); *trav != NULL && (*trav)->item.weight < newItem.weight; trav = &(*trav)->nextItem){}
            temp->nextItem = *trav;
            *trav = temp;
            L->totWeight += newItem.weight;
        }
    }
}


ItemList getHeavyItems(Locker* L, float limit) {
    ItemList curr = L->IL;
    ItemList prev = NULL;
    ItemList heavyList = NULL;

    if(curr->item.weight > limit && prev == NULL) {
        heavyList = L->IL;
        L->IL = prev;
        return heavyList;
    }
    while(curr->item.weight < limit) {
        prev = curr;
        curr = curr->nextItem;
    }
    prev->nextItem = NULL;
    heavyList = curr;
    
    return heavyList;
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

int main(void)
{
	ItemDets item1 = {"Prog 1 Book", 0.35};
	ItemDets item2 = {"Shoes", 0.87};
	ItemDets item3 = {"Laptop", 2.35};
	ItemDets item4 = {"Keyboard", 1.17};
	
	Locker myLocker = {{"14101941", "Cris Militante", "BSCS"}, NULL, 1, 0};
	ItemList heavyItems;
	
	depositItem(&myLocker, "14101941", item4);
	depositItem(&myLocker, "14101941", item2);
	depositItem(&myLocker, "14101941", item3);
	depositItem(&myLocker, "14101941", item1);
    printf("ORIGINAL LIST\n\n");
	displayItemList(myLocker.IL);

	heavyItems = getHeavyItems(&myLocker, 1.00);
    printf("UNHEAVY LIST\n\n");
	displayItemList(myLocker.IL);
    printf("HEAVY LIST\n\n");
	displayItemList(heavyItems);
    
	return 0;
}