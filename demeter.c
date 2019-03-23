#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "auxiliary.h"

int main() {
	system("clear"); 
	char* productFile = "food_database.csv";
	Productptr root = NULL; 
	root = loadProductData(productFile, root); 
	//printf("%d", root->NBD_Number); 

	//root = treeDelete(root, 45226701);
	//Productptr temp = treePredecessor(temp); 
	//printf("%d", temp->NBD_Number); 
	//printf("%d", temp->parent->NBD_Number); 
	//Productptr pnode = palloc(); 
	//printf("%s", root->long_name); 
	//pnode = search(root, 45200822); 
	//printf("%s", pnode->manufacturer); 
	//preOrder(root); 

	//Productptr p1 = palloc(); 
	//p1->NBD_Number = 9;
	//Productptr p2 = palloc();
	//p2->NBD_Number = 5;
	//Productptr p3 = palloc();
	//p3->NBD_Number = 10;
	//Productptr p4 = palloc();
	//p4->NBD_Number = 0;
	//Productptr p5 = palloc();
	//p5->NBD_Number = 6;
	//Productptr p6 = palloc();
	//p6->NBD_Number = 6;
	//Productptr p7 = palloc();
	//p7->NBD_Number = 11;
	//Productptr p8 = palloc();
	//p8->NBD_Number = -1;
	//Productptr p9 = palloc();
	//p9->NBD_Number = 1;
	//Productptr p10 = palloc();
	//p10->NBD_Number = 2;

	//root = treeInsert(root, p1); 
	//root = treeInsert(root, p2);
	//root = treeInsert(root, p3);
	//root = treeInsert(root, p4);
	//root = treeInsert(root, p5);
	//root = treeInsert(root, p6);
	//root = treeInsert(root, p7);
	//root = treeInsert(root, p8);
	//root = treeInsert(root, p9);
	//root = treeInsert(root, p10);

	Productptr pnode = palloc(); 

	//preOrder(root); 
	printf("%d ", root->NBD_Number); 
	root = treeDelete(root, 45226701);
	//if (root == NULL) printf("root is null"); 
	printf("%d", root->NBD_Number); 
	//preOrder(root); 
	return 0; 
}