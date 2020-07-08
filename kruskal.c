#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define NIL -1


struct edge
{
	int u;
	int v;
	int weight;
	struct edge *link;
}*pointer;
void makeTree(struct edge tree[]);
void push(int i, int j, int wt);
struct edge *pop();

int n; //to store the number of nodes in the graph

void makeTree(struct edge tree[]) //makes tree for the minimul spanning tree
{
	struct edge *temp;
	int v1, v2, root_v1, root_v2;
	int parent[MAX];
	int i, count = 0;

	for (i = 0; i < n; i++)
		parent[i] = NIL;


	while (count < n - 1) //for minimum edges
	{
		temp = pop();
		v1 = temp->u;
		v2 = temp->v;

		while (v1 != NIL)
		{
			root_v1 = v1;
			v1 = parent[v1];
		}
		while (v2 != NIL)
		{
			root_v2 = v2;
			v2 = parent[v2];
		}

		if (root_v1 != root_v2) { //add to the tree if the weight is min
			count++;
			tree[count].u = temp->u;
			tree[count].v = temp->v;
			tree[count].weight = temp->weight;
			parent[root_v2] = root_v1;
		}
	}

	if (count < n - 1)
	{
		printf("\nGraph is not connected, no spanning tree possible\n");
		exit(1);
	}

}

void push(int a, int b, int wt) //push to make the queue with the least weight coming first
{
	struct edge *temp, *q;

	temp = (struct edge *)malloc(sizeof(struct edge));
	temp->u = a;
	temp->v = b;
	temp->weight = wt;

	if (pointer == NULL || temp->weight < pointer->weight)
	{
		temp->link = pointer;
		pointer = temp;
	}
	else
	{
		q = pointer;
		while (q->link != NULL && q->link->weight <= temp->weight)
			q = q->link;
		temp->link = q->link;
		q->link = temp;
		if (q->link == NULL)
			temp->link = NULL;
	}
}

struct edge *pop() //pop from the queue to make a tree
{
	struct edge *temp;
	temp = pointer;
	pointer = pointer->link;
	return temp;
}

int main(void)
{
	int x;
	FILE *fpin;
	FILE *fpout;

	int i;
	int origin, destin, weight;
	struct edge tree[MAX];
	int total = 0;

	fpin = fopen("c:\\kruskalAlgorithm\\in_1.txt", "r"); //directed file


	if (fpin == NULL) {
		printf("file does not exist\n");
		return 0;
	}

	fscanf_s(fpin, "%d %d", &n, &x); //get number of nodes and edges 

	for (int i = 0; i < x; i++) {
		fscanf_s(fpin, "%d %d %d", &origin, &destin, &weight);

		if (origin >= n || destin >= n || origin < 0 || destin < 0)
		{
			printf("\nInvalid edge!\n");
			return 0;
		}
		else {
			push(origin, destin, weight);
		}
	}

	makeTree(tree); //makes a tree using kruskal algorithm 

	fpout = fopen("c:\\kruskalAlgorithm\\out.txt", "w"); 
	for (int i = 1; i < n; i++)
		fprintf(fpout, "%d %d\n", tree[i].u, tree[i].v);
	fclose(fpin);
	fclose(fpout);

	return 0;
}

