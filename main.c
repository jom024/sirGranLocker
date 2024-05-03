#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lockers.h"

int main(){
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
	displayItemList(myLocker.IL);

	heavyItems = getHeavyItems(&myLocker, 1.00);
	displayItemList(myLocker.IL);
	displayItemList(heavyItems);
	
    return 0;
}