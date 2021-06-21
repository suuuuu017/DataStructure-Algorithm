#include "ex1.h"
#include <iostream>

int dot(list_t v1, list_t v2){
	// TODO: implement dot function
    int product = 0;
	while(!list_isEmpty(v1) && !list_isEmpty(v2)){
        product = product + list_first(v1) * list_first(v2);
        v1 = list_rest(v1);
        v2 = list_rest(v2);
	}
	return product;
}

list_t filter_odd(list_t list){
	// TODO: implement filter_odd function
	list_t oddList = list_make();
	list_t returnList = list_make();
    while(!list_isEmpty(list)){
        int cand = list_first(list);
        if(((cand % 2) == 1)){
            oddList = list_make(cand, oddList);
        }
        list = list_rest(list);
    }
    while(!list_isEmpty(oddList)){
        returnList = list_make(list_first(oddList), returnList);
        oddList = list_rest(oddList);
    }
    return returnList;
}

list_t filter(list_t list, bool (*fn)(int)){
	// TODO: implement filter function
	list_t filtered = list_make();
    list_t returnList = list_make();
    while(!list_isEmpty(list)){
        int cand = list_first(list);
        if(fn(cand)){
            filtered = list_make(cand, filtered);
        }
        list = list_rest(list);
    }
    while(!list_isEmpty(filtered)){
        returnList = list_make(list_first(filtered), returnList);
        filtered = list_rest(filtered);
    }
    return returnList;
}

